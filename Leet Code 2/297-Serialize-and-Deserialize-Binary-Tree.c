#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ═══════════════════════════════════════════════════════════════════════════
   THE ENCODING FORMAT (key to understanding every line below)

   Each node is written as:

       [optional '-'] [digits] 'L' [left subtree or 'N'] 'R' [right subtree or 'N']

   Example tree:       1
                      / \
                     2   3
                    / \
                   4   5

   Serialized string (buffer):

     Index: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
     Char:  1  L  2  L  4  L  N  R  N  R  5  L  N  R  N  R  3  L  N  R  N

   Reading rules:
     • Digits before 'L'  → node value
     • char after 'L' = 'N'  → left child is NULL  (skip 2: 'L','N')
     • char after 'L' ≠ 'N'  → left child exists   (step 1 past 'L', recurse)
     • char after 'R' = 'N'  → right child is NULL  (skip 2: 'R','N')
     • char after 'R' ≠ 'N'  → right child exists   (step 1 past 'R', recurse)
═══════════════════════════════════════════════════════════════════════════ */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* ── helpers ────────────────────────────────────────────────────────────── */

static struct TreeNode* newNode(int v) {
    struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    n->val = v; n->left = n->right = NULL;
    return n;
}

/* Prints the buffer up to 'size' chars with a visible cursor at 'cur'.    */
static void printBuf(const char* buf, int size, int cur, const char* label) {
    printf("  %-30s  buf[0..%d] = \"", label, size - 1);
    for (int i = 0; i < size; i++) {
        if (buf[i] == '\0') printf("\\0");
        else                printf("%c", buf[i]);
    }
    printf("\"");
    if (cur >= 0) printf("  <── cursor=%d ('%c')", cur, buf[cur] ? buf[cur] : '0');
    printf("\n");
}

/* ═══════════════════════════════════════════════════════════════════════════
   encode()  –  recursive preorder writer
   ─────────────────────────────────────────────────────────────────────────
   Parameters:
     root   current node being encoded
     in     pointer-to-pointer so we can return the same buffer address
     size   pointer to running byte count; (*in)[*size-1] = last written byte

   STEP-BY-STEP for a node with val=2, left=4, right=5:
     1. val negative?  → prepend '-', flip sign.
     2. Digit loop (power = 1000 → 100 → 10 → 1):
           only emit a digit when root->val/power ≠ 0  → skips leading zeros.
           digit char = (root->val / power) % 10 + '0'
     3. Write sentinel 'L' (marks end of value / start of left branch).
     4. Left child exists?  recurse.  Else write 'N'.
     5. Write sentinel 'R' (marks end of left branch / start of right branch).
     6. Right child exists?  recurse.  Else write 'N'.
═══════════════════════════════════════════════════════════════════════════ */

char* encode(struct TreeNode* root, char** in, int* size) {

    printf("\n  ┌─ encode(val=%d)  size_before=%d\n", root->val, *size);

    /* ── STEP 1: handle negative ─────────────────────────────────────── */
    if (root->val < 0) {
        *size += 1;
        (*in)[*size - 1] = '-';
        root->val *= -1;               /* TRACE: flip so digit loop works  */
        printBuf(*in, *size, *size-1, "wrote '-'");
    }

    /* ── STEP 2: write digits, skip leading zeros ─────────────────────
       power starts at 1000 → handles values 0-9999.
       Condition: root->val / power  gives the digit at that place value.
       If zero AND we haven't started writing yet, skip (leading zero).    */
    int power = 1000;
    while (power) {
        if (root->val / power) {           /* non-zero digit at this place */
            *size += 1;
            (*in)[*size - 1] = (char)((root->val / power) % 10 + '0');
            char label[64];
            sprintf(label, "wrote digit '%c' (power=%d)",
                    (*in)[*size-1], power);
            printBuf(*in, *size, *size-1, label);
        }
        power /= 10;
    }
    /* ⚠ BUG NOTE: val==0 emits NO digits (0/1000=0, 0/100=0, 0/10=0, 0/1=0).
       decode() would then see 'L' immediately and loop 0 times → val stays 0
       by coincidence.  Works for val=0 only because the loop body never runs
       and root->val was already initialised to 0 in decode(). */

    /* ── STEP 3: write 'L' sentinel ──────────────────────────────────── */
    *size += 1;
    (*in)[*size - 1] = 'L';
    printBuf(*in, *size, *size-1, "wrote 'L' sentinel");

    /* ── STEP 4: left child ───────────────────────────────────────────── */
    if (root->left) {
        printf("  │  left child val=%d → recurse\n", root->left->val);
        *in = encode(root->left, in, size);
    } else {
        *size += 1;
        (*in)[*size - 1] = 'N';
        printBuf(*in, *size, *size-1, "left=NULL → wrote 'N'");
    }

    /* ── STEP 5: write 'R' sentinel ──────────────────────────────────── */
    *size += 1;
    (*in)[*size - 1] = 'R';
    printBuf(*in, *size, *size-1, "wrote 'R' sentinel");

    /* ── STEP 6: right child ──────────────────────────────────────────── */
    if (root->right) {
        printf("  │  right child val=%d → recurse\n", root->right->val);
        *in = encode(root->right, in, size);
    } else {
        *size += 1;
        (*in)[*size - 1] = 'N';
        printBuf(*in, *size, *size-1, "right=NULL → wrote 'N'");
    }

    printf(" encode(val=%d) done  size_after=%d\n", root->val, *size);
    return (*in);
}

/* ═══════════════════════════════════════════════════════════════════════════
   serialize()  –  entry point
   Allocates the output buffer, seeds size=0, calls encode, null-terminates.
═══════════════════════════════════════════════════════════════════════════ */

char* serialize(struct TreeNode* root) {
    printf("\n══════════════════ SERIALIZE ══════════════════\n");
    if (root == NULL) {
        printf("  root is NULL → return NULL\n");
        return NULL;
    }

    int size = 0;
    char* in = (char*)malloc(sizeof(char) * 100000);
    memset(in, 0, sizeof(char) * 100000);
    printf("  Allocated 100 000-byte buffer at %p\n", (void*)in);

    in = encode(root, &in, &size);

    size++;
    in[size - 1] = '\0';              /* null-terminate the string         */
    printf("\n  Final serialized string (%d bytes): \"%s\"\n", size, in);
    printf("══════════════════════════════════════════════\n");
    return in;
}

/* ═══════════════════════════════════════════════════════════════════════════
   decode()  –  recursive preorder reader
   ─────────────────────────────────────────────────────────────────────────
   *index always points to the FIRST character of the current token.

   STEP-BY-STEP:
     1. Check for '-'  → set sign flag, advance index.
     2. Allocate a new node (val=0, children=NULL).
     3. Accumulate digits until we hit 'L':
           val = val*10 + (data[index]-'0'),  index++
        After loop: index points AT 'L'.
     4. Apply sign if needed.
     5. Peek at data[index+1] (the char right after 'L'):
           ≠ 'N' → real left child: index++ (step past 'L'), recurse.
           = 'N' → NULL left:       index += 2 (skip 'L' and 'N').
        After either branch: index points AT 'R'.
     6. Same logic for right child using 'R' sentinel.
     7. Return the node. index now points just past this subtree's last char.
═══════════════════════════════════════════════════════════════════════════ */

struct TreeNode* decode(char* data, int* index) {

    /* ── STEP 1: sign ─────────────────────────────────────────────────── */
    char sign = 0;
    if (data[*index] == '-') {
        sign = 1;
        *index += 1;
        printf("  [decode] sign=negative  index now=%d\n", *index);
    }

    /* ── STEP 2: allocate node ────────────────────────────────────────── */
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val   = 0;
    root->left  = NULL;
    root->right = NULL;

    /* ── STEP 3: accumulate digits until 'L' ─────────────────────────── */
    printf("  [decode] parsing digits from index=%d: ", *index);
    while (data[*index] != 'L') {
        printf("'%c'", data[*index]);
        root->val = (root->val * 10) + (data[*index] - '0');
        (*index)++;
    }
    /* index now sits ON 'L' */
    printf("  → val=%d  index=%d (at 'L')\n", root->val, *index);

    /* ── STEP 4: apply sign ───────────────────────────────────────────── */
    if (sign) root->val *= -1;

    /* ── STEP 5: left child  (peek at index+1, right after 'L') ─────── */
    printf("  [decode] val=%d: data[%d+1]='%c'  ",
           root->val, *index, data[*index + 1]);
    if (data[(*index) + 1] != 'N') {
        printf("→ left child exists, recurse\n");
        (*index)++;                    /* step past 'L'; index now on left  */
        root->left = decode(data, index);
    } else {
        printf("→ left=NULL, skip 'L'+'N'\n");
        *index += 2;                   /* skip 'L' and 'N'; index now on 'R'*/
    }
    /* index now sits ON 'R' */

    /* ── STEP 6: right child (peek at index+1, right after 'R') ─────── */
    printf("  [decode] val=%d: data[%d+1]='%c'  ",
           root->val, *index, data[*index + 1]);
    if (data[(*index) + 1] != 'N') {
        printf("→ right child exists, recurse\n");
        (*index)++;                    /* step past 'R'; index now on right  */
        root->right = decode(data, index);
    } else {
        printf("→ right=NULL, skip 'R'+'N'\n");
        *index += 2;                   /* skip 'R' and 'N'                  */
    }

    printf("  [decode] returning node(val=%d)  index now=%d\n",
           root->val, *index);
    return root;
}

/* ═══════════════════════════════════════════════════════════════════════════
   deserialize()  –  entry point
═══════════════════════════════════════════════════════════════════════════ */

struct TreeNode* deserialize(char* data) {
    printf("\n══════════════════ DESERIALIZE ════════════════\n");
    if (data == NULL) {
        printf("  data is NULL → return NULL\n");
        return NULL;
    }
    printf("  Input string: \"%s\"\n\n", data);

    /* Print the indexed view so every decode() printf makes visual sense  */
    printf("  Index map:\n  ");
    for (int i = 0; data[i]; i++) printf("[%2d]", i);
    printf("\n  ");
    for (int i = 0; data[i]; i++) printf("  %c ", data[i]);
    printf("\n\n");

    int index = 0;
    struct TreeNode* root = decode(data, &index);

    printf("\n  Deserialization complete. index ended at %d.\n", index);
    printf("══════════════════════════════════════════════\n");
    return root;
}

/* ═══════════════════════════════════════════════════════════════════════════
   Utility: inorder print to verify round-trip correctness
═══════════════════════════════════════════════════════════════════════════ */
static void inorder(struct TreeNode* n, int depth) {
    if (!n) return;
    inorder(n->right, depth + 1);
    printf("%*s%d\n", depth * 4, "", n->val);
    inorder(n->left,  depth + 1);
}

/* ═══════════════════════════════════════════════════════════════════════════
   main()  –  builds the tree below, serializes, then deserializes it.

       Original tree:
                  1
                 / \
                2   3
               / \
              4   5

   Expected serialized buffer (indices):
     0:'1' 1:'L' 2:'2' 3:'L' 4:'4' 5:'L' 6:'N' 7:'R' 8:'N'
     9:'R' 10:'5' 11:'L' 12:'N' 13:'R' 14:'N' 15:'R' 16:'3'
     17:'L' 18:'N' 19:'R' 20:'N'  → "1L2L4LNRNR5LNRNR3LNRN"
═══════════════════════════════════════════════════════════════════════════ */

int main(void) {

    /* ── build the tree ─────────────────────────────────────────────── */
    struct TreeNode* n1 = newNode(1);
    struct TreeNode* n2 = newNode(2);
    struct TreeNode* n3 = newNode(3);
    struct TreeNode* n4 = newNode(4);
    struct TreeNode* n5 = newNode(5);
    n1->left  = n2;  n1->right = n3;
    n2->left  = n4;  n2->right = n5;
    /* n3, n4, n5 have no children */

    printf("Original tree (sideways, right branch on top):\n");
    inorder(n1, 0);

    /* ── serialize ───────────────────────────────────────────────────── */
    char* data = serialize(n1);

    /* ── deserialize ─────────────────────────────────────────────────── */
    struct TreeNode* restored = deserialize(data);

    printf("\nRestored tree (should match original):\n");
    inorder(restored, 0);

    /* ── quick sanity check ──────────────────────────────────────────── */
    printf("\nNode values (BFS order check):\n");
    printf("  root=%d  root->left=%d  root->right=%d\n",
           restored->val, restored->left->val, restored->right->val);
    printf("  root->left->left=%d  root->left->right=%d\n",
           restored->left->left->val, restored->left->right->val);
    printf("  root->right->left=%s  root->right->right=%s\n",
           restored->right->left  ? "EXISTS (BUG)" : "NULL(ok)",
           restored->right->right ? "EXISTS (BUG)" : "NULL(ok)");

    free(data);
    return 0;
}