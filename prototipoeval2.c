#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Publicacion { // estructura de las publicaciones
    int id;
    char *usuario;
    char *titulo;
    char **imagenes;
    int num_imagenes;
    int likes;
    int comentarios;
    int compartido;
    struct Publicacion *siguiente;
} Publicacion;

typedef struct ListaPublicaciones { // estructura de listas de publicaciones
    Publicacion *cabeza;
} ListaPublicaciones;


ListaPublicaciones *crearLista() {                                                       // se crea la lista de publicaciones
    ListaPublicaciones *lista = (ListaPublicaciones *)malloc(sizeof(ListaPublicaciones));//y se reserva memoria para estas mismas
    lista->cabeza = NULL;
    return lista;
}

// para crear una nueva publi
Publicacion *crearPublicacion(int id, const char *usuario, const char *titulo, char **imagenes, int num_imagenes, int likes, int comentarios, int compartido) {
    Publicacion *pub = (Publicacion *)malloc(sizeof(Publicacion));
    pub->id = id;
    pub->usuario = strdup(usuario);
    pub->titulo = strdup(titulo);
    pub->imagenes = NULL;
    pub->num_imagenes = 0;
    if (imagenes && num_imagenes > 0) {
        pub->imagenes = (char **)malloc(num_imagenes * sizeof(char *));
        pub->num_imagenes = num_imagenes;
        for (int i = 0; i < num_imagenes; i++) {
            pub->imagenes[i] = strdup(imagenes[i]);
        }
    }
    pub->likes = likes;
    pub->comentarios = comentarios;
    pub->compartido = compartido;
    pub->siguiente = NULL;
    return pub;
}

// funcion para liberar memoria de una publicacion
void liberarPublicacion(Publicacion *pub) {
    free(pub->usuario);
    free(pub->titulo);
    if (pub->imagenes) {
        for (int i = 0; i < pub->num_imagenes; i++) {
            free(pub->imagenes[i]);
        }
        free(pub->imagenes);
    }
    free(pub);
}

//  funcion para liberar memoria de la lista de publis (en caso de que se saltara una publicacion con la funcion naterior)
void liberarLista(ListaPublicaciones *lista) {
    Publicacion *actual = lista->cabeza;
    while (actual != NULL) {
        Publicacion *siguiente = actual->siguiente;
        liberarPublicacion(actual);
        actual = siguiente;
    }
    free(lista);
}

// funcion para colocar una publicacion primero
void insertarCabeza(ListaPublicaciones *lista, Publicacion *pub) {
    pub->siguiente = lista->cabeza;
    lista->cabeza = pub;
}

// funcion para colocar una publicacion ultima
void insertarCola(ListaPublicaciones *lista, Publicacion *pub) {
    if (lista->cabeza == NULL) {
        lista->cabeza = pub;
        return;
    }
    Publicacion *actual = lista->cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    actual->siguiente = pub;
}

// funcion para insertar una publicacion por la id
void insertarOrdenado(ListaPublicaciones *lista, Publicacion *pub) {
    if (lista->cabeza == NULL || pub->id < lista->cabeza->id) {
        pub->siguiente = lista->cabeza;
        lista->cabeza = pub;
        return;
    }
    Publicacion *actual = lista->cabeza;
    while (actual->siguiente != NULL && actual->siguiente->id < pub->id) {
        actual = actual->siguiente;
    }
    pub->siguiente = actual->siguiente;
    actual->siguiente = pub;
}

// funcion para borrar la primera publi
Publicacion *borrarCabeza(ListaPublicaciones *lista) {
    if (lista->cabeza == NULL) {
        return NULL;
    }
    Publicacion *temp = lista->cabeza;
    lista->cabeza = lista->cabeza->siguiente;
    return temp;
}

// funcion para borrar la ultima publi
Publicacion *borrarCola(ListaPublicaciones *lista) {
    if (lista->cabeza == NULL) {
        return NULL;
    }
    if (lista->cabeza->siguiente == NULL) {
        Publicacion *temp = lista->cabeza;
        lista->cabeza = NULL;
        return temp;
    }
    Publicacion *actual = lista->cabeza;
    while (actual->siguiente->siguiente != NULL) {
        actual = actual->siguiente;
    }
    Publicacion *temp = actual->siguiente;
    actual->siguiente = NULL;
    return temp;
}

// funcion para borrar una publi por la id
Publicacion *borrarPorId(ListaPublicaciones *lista, int id) {
    if (lista->cabeza == NULL) {
        return NULL;
    }
    if (lista->cabeza->id == id) {
        return borrarCabeza(lista);
    }
    Publicacion *actual = lista->cabeza;
    while (actual->siguiente != NULL && actual->siguiente->id != id) {
        actual = actual->siguiente;
    }
    if (actual->siguiente != NULL) {
        Publicacion *temp = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        return temp;
    }
    return NULL;
}

// funcion para mostrar por terminal los daros
void mostrarPublicaciones(ListaPublicaciones *lista) {
    Publicacion *actual = lista->cabeza;
    while (actual != NULL) {
        printf("ID: %d, Usuario: %s, Titulo: %s, Likes: %d, Comentarios: %d, Compartido: %d\n",
               actual->id, actual->usuario, actual->titulo, actual->likes, actual->comentarios, actual->compartido);
        printf("  Imagenes: [");
        for (int i = 0; i < actual->num_imagenes; i++) {
            printf("%s%s", actual->imagenes[i], (i < actual->num_imagenes - 1) ? ", " : "");
        }
        printf("]\n");
        actual = actual->siguiente;
    }
}

// funcion para comparar dos publicaciones por los likes (para ordenar)
int compararPorLikes(const void *a, const void *b) {
    const Publicacion *pa = *(const Publicacion **)a;
    const Publicacion *pb = *(const Publicacion **)b;
    return pb->likes - pa->likes;
}

// funcion para comparar dos publicaciones por los comentarios (para ordenar)
int compararPorComentarios(const void *a, const void *b) {
    const Publicacion *pa = *(const Publicacion **)a;
    const Publicacion *pb = *(const Publicacion **)b;
    return pb->comentarios - pa->comentarios;
}

// funcion para comparar dos publicaciones por los compartidos (para ordenar)
int compararPorCompartido(const void *a, const void *b) {
    const Publicacion *pa = *(const Publicacion **)a;
    const Publicacion *pb = *(const Publicacion **)b;
    return pb->compartido - pa->compartido;
}

// funcion para ordenar la lista de publicaciones usando un comparador
void ordenarLista(ListaPublicaciones *lista, int (*comparar)(const void *, const void *)) {
    if (lista->cabeza == NULL || lista->cabeza->siguiente == NULL) {
        return;
    }

    // se cuenta el numero de publicaciones
    int count = 0;
    Publicacion *actual = lista->cabeza;
    while (actual != NULL) {
        count++;
        actual = actual->siguiente;
    }

    // se crea un array para almacenar los punteros de las publicaciones
    Publicacion **arr = (Publicacion **)malloc(count * sizeof(Publicacion *));
    actual = lista->cabeza;
    for (int i = 0; i < count; i++) {
        arr[i] = actual;
        actual = actual->siguiente;
    }

    // se ordena el array usando la función qsort
    qsort(arr, count, sizeof(Publicacion *), comparar); //en este caso el qsort le damos el parametro para ordenar por el arrat, luego los n elementos del array,
                                                        // se especifica el tamano de la publicacion y luego se compara (compara likes,megusta,compartidos)

    // se rescontruye la lista enlazada con el orden del array
    lista->cabeza = arr[0];
    for (int i = 0; i < count - 1; i++) {
        arr[i]->siguiente = arr[i + 1];
    }
    arr[count - 1]->siguiente = NULL;

    free(arr);
}

// funcion para cargar las publicaciones desde el archivo status_ini_social.txt
void cargarDesdeArchivo(ListaPublicaciones *lista, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    // en esta parte del codigo se podria agilizar la toma del caracteres, pero por facilidad lo dejamos con valores fijos

    char linea[512]; // pusimos como limite la lectura de 10 lineas 
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = 0; // sacamos el salto de linea 

        int id, likes, comentarios, compartido;
        char usuario[64], titulo[256], imagenes_str[256], reacciones_str[32];

        if (sscanf(linea, "%d; %[^;]; %[^;]; %[^;]; %[^;];", &id, usuario, titulo, imagenes_str, reacciones_str) == 5) {
            char *start_img = strchr(imagenes_str, '['); 
            char *end_img = strchr(imagenes_str, ']');
            char *imagenes[10];
            int num_imagenes = 0;
            if (start_img != NULL && end_img != NULL && start_img < end_img) {
                char *token = strtok(start_img + 1, ","); // el strtok es colocarle un token o una marca a un caracter para diferenciarlo en este caso es "," 
                while (token != NULL && num_imagenes < 10) {
                    char *corte = token;
                    while (*corte == ' ') corte++;
                    char *fin = corte + strlen(corte) - 1;
                    while (fin > corte && *fin == ' ') fin--;
                    *(fin + 1) = '\0';
                    imagenes[num_imagenes++] = corte;
                    token = strtok(NULL, ",");
                }
            }

            char *start_reac = strchr(reacciones_str, '[');
            char *end_reac = strchr(reacciones_str, ']');
            if (start_reac != NULL && end_reac != NULL && start_reac < end_reac) {
                if (sscanf(start_reac + 1, "%d, %d, %d", &likes, &comentarios, &compartido) == 3) {
                    char *imagenes_duplicadas[10];
                    int num_imagenes_duplicadas = 0;
                    for (int i = 0; i < num_imagenes; i++) {
                        imagenes_duplicadas[num_imagenes_duplicadas++] = strdup(imagenes[i]);
                    }
                    Publicacion *nueva_publicacion = crearPublicacion(id, usuario, titulo, imagenes_duplicadas, num_imagenes_duplicadas, likes, comentarios, compartido);
                    insertarCola(lista, nueva_publicacion);
                    for (int i = 0; i < num_imagenes_duplicadas; i++) {
                        free(imagenes_duplicadas[i]);
                    }
                }
            }
        }
    }
    fclose(archivo);
}

int main() {
    ListaPublicaciones *red_social = crearLista();

    cargarDesdeArchivo(red_social, "status_ini_social_net.txt");

    printf("--- Contenido inicial ---\n");
    mostrarPublicaciones(red_social);

    // Ejemplo de modificaciones
    Publicacion *nueva_pub_inicio = crearPublicacion(111, "Nuevo Usuario", "#Publicacion inicial", NULL, 0, 0, 69, 7);
    insertarCabeza(red_social, nueva_pub_inicio);

    Publicacion *nueva_pub_orden = crearPublicacion(500, "Usuario Medio", "#Publicacion intermedia", NULL, 0, 45, 7, 7);
    insertarOrdenado(red_social, nueva_pub_orden);

    Publicacion *nueva_pub_cola = crearPublicacion(1000, "Otro Usuario", "#Publicacion final", NULL, 0, 20, 12, 5);
    insertarCola(red_social, nueva_pub_cola);


    printf("\n--- Despues de insertar ---\n");
    mostrarPublicaciones(red_social);

    Publicacion *borrado_cabeza = borrarCabeza(red_social);
    liberarPublicacion(borrado_cabeza);

    Publicacion *borrado_cola = borrarCola(red_social);
    liberarPublicacion(borrado_cola);

    Publicacion *borrado_id = borrarPorId(red_social, 3121134);
    liberarPublicacion(borrado_id);

    printf("\n--- Despues de borrar ---\n");
    printf("\nSe borro al primer usuario, al ultimo y uno por ID\n");
    mostrarPublicaciones(red_social);

    printf("\n--- Ordenado por Likes ---\n");
    ordenarLista(red_social, compararPorLikes);
    mostrarPublicaciones(red_social);

    printf("\n--- Ordenado por Comentarios ---\n");
    ordenarLista(red_social, compararPorComentarios);
    mostrarPublicaciones(red_social);

    printf("\n--- Ordenado por Compartido ---\n");
    ordenarLista(red_social, compararPorCompartido);
    mostrarPublicaciones(red_social);

    liberarLista(red_social);

    return 0;
}