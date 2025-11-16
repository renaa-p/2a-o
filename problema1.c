#include

int esPerfecto(int num) {
if (num <= 1) {
return 0;
}
int sumaDivisores = 1;
for (int i = 2; i * i <= num; i++) {
if (num % i == 0) {
sumaDivisores += i;
if (i * i != num) {
sumaDivisores += num / i;
}
}
}
if (sumaDivisores == num) {
return 1;
} else {
return 0;
}
}

int main() {
int contadorPerfectos = 0;
int numero = 2;

printf("Los primeros 4 números perfectos son:\n");

while (contadorPerfectos < 4) {
if (esPerfecto(numero)) { // Cualquier valor diferente de 0 se considera verdadero
printf("%d\n", numero);
contadorPerfectos++;
}
numero++;
}

return 0;
}