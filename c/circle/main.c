#include <stdio.h>
#include <locale.h>
#define PI 3.14159

int main() {
    setlocale(LC_ALL, "Chinese");
    float radius;
    float Circumference;
    float Square;
    printf("Please enter the radius of the circle: ");
    scanf("%f", &radius);
    Circumference = 2 * PI * radius;
    Square = PI * radius * radius;
    printf("The circumference of the circle is: %.2f\n", Circumference);
    printf("The area of the circle is: %.2f\n", Square);
    return 0;
}