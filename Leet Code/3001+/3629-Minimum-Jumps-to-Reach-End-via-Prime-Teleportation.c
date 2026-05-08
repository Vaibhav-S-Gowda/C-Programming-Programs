#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma GCC target("abm,bmi,bmi2,avx,avx2,tune=znver5")

__attribute__((no_sanitize("all")))
unsigned minJumps(unsigned *nums, size_t cnt) {

    static unsigned char
        tails[1000001],
        seen[100002] = {[0] = 1};

    static unsigned
        bases[1000001] = {[1] = 1},
        units[1000001],
        pending[100001],
        edges[700000],
        forward[700000],
        indices[1000001];

    size_t
        at, others, tail, next;

    if (bases[2] == 0) {

        unsigned primes[72300];
        size_t to;

        next = 0;

        at = 2;
        do {

            if ((tail = tails[at]) == 0)
                primes[(tail = ++next) - 1]
                    = bases[at] = units[at] = at;

            to = at + at;
            others = 1;

            do {
                tails[to] = others;

                if (tail == others) {
                    bases[to] = bases[at];
                    units[to] = units[at];
                    break;
                }

                bases[to] = primes[others - 1] * bases[at];
                units[to] = primes[others - 1];

            } while ((to = primes[others++] * at) < 1000001);

        } while (++at < 500001);

        do {
            if (tails[at] == 0)
                bases[at] = units[at] = at;
        } while (++at < 1000001);
    }

    --nums;

    tail = 0;

    at = cnt;
    do {

        unsigned item = bases[nums[at]];

        for (; item != 1; item /= units[item]) {

            edges[++tail] = at;
            forward[tail] = indices[units[item]];
            indices[units[item]] = tail;
        }

    } while (--at);

    memset(&seen[1], 0, cnt * sizeof(seen[0]));

    seen[pending[0] = 1] = seen[cnt + 1] = 1;

    unsigned steps = 0;

    for (at = 0, next = 1;; steps++) {

        if (seen[cnt]) {

            at = cnt;

            do {

                unsigned item = bases[nums[at]];

                for (; item != 1; item /= units[item])
                    indices[units[item]] = 0;

            } while (--at);

            return steps;
        }

        tail = next;

        do {

            if ((others = indices[nums[pending[at]]])) {

                indices[nums[pending[at]]] = 0;

                do {

                    if (seen[edges[others]] == 0)
                        seen[pending[next++] = edges[others]] = 1;

                } while ((others = forward[others]));
            }

            if (seen[pending[at] + 1] == 0)
                seen[pending[next++] = pending[at] + 1] = 1;

            if (seen[pending[at] - 1] == 0)
                seen[pending[next++] = pending[at] - 1] = 1;

        } while (++at < tail);
    }
}

int main() {

    unsigned nums[] = {2, 3, 6, 9, 18};
    size_t cnt = sizeof(nums) / sizeof(nums[0]);

    unsigned result = minJumps(nums, cnt);

    printf("Minimum jumps: %u\n", result);

    return 0;
}