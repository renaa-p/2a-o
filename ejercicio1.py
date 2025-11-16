#renato ortiz
#vamos a definir factoriales y sus coeficientes
def factorial(n):
    resu = 1
    for x in range(1, n + 1):
        resu *= x
    return resu

def coeficiente(n, k):
    if k > n:
        return "k no puede ser mayor que n"
    num = factorial(n)
    denom = factorial(k) * factorial(n - k)
    return num / denom

if __name__ == "__main__":
    n = int(input("Ingrese el valor de n: "))
    k = int(input("Ingrese el valor de k: "))
    v_final = coeficiente(n, k)
    print(f"El coeficiente factorial de (n k) es de: {v_final}")
