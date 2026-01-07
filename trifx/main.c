#include <stdio.h>
#include <math.h>
#define SIN0 0.0002908882046

// trifx 指 triangular function
// tri 取自 triangular
// fx 在数学里指 function

int main() {
    //初始化 initialization
    double COS0 = sqrt(1 - SIN0 * SIN0);
    double TAN0 = SIN0 / COS0;
    double DEG0 = 1.0 / 60.0;
    printf("Minute = 1\n");
    printf("Degree(1') = %.6f\n", DEG0);
    printf("Sine(1') = %.4f\n", SIN0);
    printf("Cosine(1') = %.4f\n", COS0);
    printf("Tangent(1') = %.4f\n", TAN0);
    double sine = SIN0;
    double cosine = COS0;
    double tangent;
    double degree;

    //角度的倍数 multiple of the angle
    int n=2;
    do {
        //计算 calculate
        sine = SIN0 * cosine + COS0 * sine;
        cosine = sqrt(1 - sine * sine);
        tangent = sine / cosine;
        degree = n / 60.0;
        printf("Minute = %d\n", n);
        printf("Degree(%d') = %.4f\n", n, degree);
        printf("Sine(%d') = %.4f\n", n, sine);
        printf("Cosine(%d') = %.4f\n", n, cosine);
        printf("Tangent(%d') = %.4f\n", n, tangent);
        printf("---------------\n");
        printf("\n");
        n++;
    } while (n <= 5400);

    return 0;
}