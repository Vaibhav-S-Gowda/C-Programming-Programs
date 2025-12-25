#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define PI 3.141592

int main()
{
    // Circle calculations in C

    double radius = 0.0;
    double area = 0.0;
    double surfaceArea = 0.0;
    double volume = 0.0;
    
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);

    area = PI * pow(radius,2); // Area = πr²
    surfaceArea = 4 * PI * pow(radius,2); // Surface Area = 4πr²
    volume = (4.0/3.0) * PI * pow(radius,3); // Volume = (4/3)πr³

    printf("Area of the circle: %.2lf\n", area);
    printf("Surface Area of the sphere: %.2lf\n", surfaceArea);
    printf("Volume of the sphere: %.2lf\n", volume);
    return 0;
}