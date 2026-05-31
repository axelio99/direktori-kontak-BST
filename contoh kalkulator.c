#include <stdio.h>

int main() {
    float angka1, angka2, hasil;
    char operator;

    printf("=== KALKULATOR SEDERHANA ===\n");

    printf("Masukkan angka pertama : ");
    scanf("%f", &angka1);

    printf("Masukkan operator (+, -, *, /) : ");
    scanf(" %c", &operator);

    printf("Masukkan angka kedua : ");
    scanf("%f", &angka2);

    switch(operator) {
        case '+':
            hasil = angka1 + angka2;
            printf("Hasil = %.2f\n", hasil);
            break;

        case '-':
            hasil = angka1 - angka2;
            printf("Hasil = %.2f\n", hasil);
            break;

        case '*':
            hasil = angka1 * angka2;
            printf("Hasil = %.2f\n", hasil);
            break;

        case '/':
            if(angka2 != 0) {
                hasil = angka1 / angka2;
                printf("Hasil = %.2f\n", hasil);
            } else {
                printf("Error! Pembagian dengan nol tidak diperbolehkan.\n");
            }
            break;

        default:
            printf("Operator tidak valid!\n");
    }

    return 0;
}