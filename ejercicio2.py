#renato ortiz
def analizar_palabras(texto):
    
    palabras = texto.lower().split() # "limpiamos el textp"
    total_palabras = len(palabras)
    palabras_con_vocal = 0
    menos_3_letras = 0
    entre_3_y_5_letras = 0
    mas_5_letras = 0
    
    vocales = "aeiouáéíóú"
    
    for palabra in palabras:
        # verificamos si la palabra termina en una vocal
        if palabra[-1] in vocales:
            palabras_con_vocal += 1
        
        # clasificamos la longitud de la palabra
        if len(palabra) < 3:
            menos_3_letras += 1
        elif 3 <= len(palabra) <= 5:
            entre_3_y_5_letras += 1
        else:
            mas_5_letras += 1

    porcentaje_vocal = (palabras_con_vocal / total_palabras) * 100 if total_palabras > 0 else 0
    porcentaje_menos_3 = (menos_3_letras / total_palabras) * 100 if total_palabras > 0 else 0
    porcentaje_entre_3_y_5 = (entre_3_y_5_letras / total_palabras) * 100 if total_palabras > 0 else 0
    porcentaje_mas_5 = (mas_5_letras / total_palabras) * 100 if total_palabras > 0 else 0

    return (porcentaje_vocal, porcentaje_menos_3, porcentaje_entre_3_y_5, porcentaje_mas_5)


if __name__ == "__main__":
    texto_usuario = "La espera me agotó, no sé nada de vos,dejaste tanto en mí, En llamas me acosté y en un lento degradé supe que perdí"
    porcentaje_vocal, porcentaje_menos_3, porcentaje_entre_3_y_5, porcentaje_mas_5 = analizar_palabras(texto_usuario)
    
    print(f"Porcentaje de palabras que terminan con vocal: {porcentaje_vocal:}%")
    print(f"Porcentaje de palabras con menos de 3 letras: {porcentaje_menos_3:}%")
    print(f"Porcentaje de palabras con entre 3 y 5 letras: {porcentaje_entre_3_y_5:}%")
    print(f"Porcentaje de palabras con más de 5 letras: {porcentaje_mas_5:}%")
