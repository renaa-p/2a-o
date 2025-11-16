#renato ortiz
import random

def es_primo(n):
    if n <= 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

def es_narcisista(n):
    # Convertir el número a una lista de sus dígitos
    digitos = [int(d) for d in str(n)]
    potencia = len(digitos)
    # Sumar los dígitos elevados a la potencia de la cantidad de dígitos
    suma = 0
    for d in digitos:
        suma += d ** potencia
    return suma == n

if __name__=="__main__":
    primos = [n for n in range(1, 1000) if es_primo(n)]
    narcisistas = [n for n in range(1, 1000) if es_narcisista(n)]
    numeros_combinados = list(set(primos + narcisistas))
    numeros_seleccionados = random.sample(numeros_combinados, 10)

    print("Lista de 10 números aleatorios primos o narcisos menores que 1000:")
    print(numeros_seleccionados)
