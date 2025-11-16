#el programa inicia con (iniciarCompra.) pero me falta hacer la suma y el bucle de la lista
producto(manzanas, 600).
producto(platanos, 900).
producto(naranjas, 700).
producto(pan, 1400).
producto(leche, 1010).

calcularPrecio([], 0).

calcularPrecio([Nombre,precio], TotalFinal) :-
    producto(Nombre, Precio),
    calcularPrecio(Resto, TotalRestante).

iniciarCompra :-
    write('Escriba el nombre del producto'), nl,
    write('Escribir: fin. para terminar y sumar.'), nl,
    write("Los productos son:\n"),
    write("manzanas - 600\n"),
    write("platanos - 900\n"),
    write("naranjas - 700\n"),
    write("pan - 1400\n"),
    write("leche - 1010\n"),

    listaDeCompras([], ListaFinal),
    calcularPrecio(ListaFinal, PrecioTotal),nl,
    mostrarLista(ListaFinal),nl,
    write('Total: '), write(PrecioTotal), nl.

listaDeCompras(ListaActual, ListaActual) :-
    read(Producto),
    (Producto == fin; Producto == 'Fin'),!.

listaDeCompras(ListaActual, ListaFinal) :-
    read(Producto).

mostrarLista([]) :-
    write('Total'), nl.

mostrarLista([Nombre,precio]) :-
    producto(Nombre, Precio),
    write(Nombre), write(' - '), write(Precio), write(' '), nl.








