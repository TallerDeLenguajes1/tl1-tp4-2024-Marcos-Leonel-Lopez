#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Tarea
{
    int tareaID;
    char *descripcion;
    int duracion;
} typedef Tarea;

struct Nodo
{
    Tarea tarea;
    Nodo *siguiente;
};
typedef struct Nodo* HeadLista;

bool esListaVacia(HeadLista Lista);
HeadLista ListaVacia();
HeadLista agregarTareas(HeadLista Lista, int *id);
HeadLista insertar(HeadLista tareas, Tarea nuevaTarea);
void mostrarLista(HeadLista Lista);
void liberarMemoria(HeadLista *Lista);


int main()
{

    int id = 1000, numTareas = 2;
    HeadLista tareasPendientes = ListaVacia();
    HeadLista tareasRealizadas = ListaVacia();
    for (int i = 0; i < numTareas; i++)
    {
        tareasPendientes = agregarTareas(tareasPendientes, &id);
    }
    mostrarLista(tareasPendientes);
    mostrarLista(tareasPendientes);
    mostrarLista(tareasPendientes);

    liberarMemoria(&tareasPendientes);
    liberarMemoria(&tareasRealizadas);

    mostrarLista(tareasPendientes);

    return 0;
}

bool esListaVacia(HeadLista Lista)
{
    return (Lista == NULL);
}

HeadLista ListaVacia()
{
    return NULL;
}

HeadLista agregarTareas(HeadLista Lista, int *id)
{
    Tarea nuevaTarea;
    char buff[250];
    int long_char;
    nuevaTarea.tareaID = *id;
    (*id)++;
    printf("\nId: %d", nuevaTarea.tareaID);
    printf("\nDescripcion: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = '\0'; // Eliminar el salto de línea final
    long_char = strlen(buff) + 1;
    nuevaTarea.descripcion = (char *)malloc(sizeof(char) * long_char);
    strcpy(nuevaTarea.descripcion, buff);
    printf("Duracion : ");
    scanf("%d", &nuevaTarea.duracion);
    printf("\n ");
    getchar(); // Consumir el carácter de nueva línea
    return insertar(Lista, nuevaTarea);
}

HeadLista insertar(HeadLista tareas, Tarea nuevaTarea)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->tarea = nuevaTarea;
    nuevoNodo->siguiente = tareas;
    return nuevoNodo;
}

void mostrarLista(HeadLista Lista)
{
    printf("----------------\n");
    printf("Lista de tareas:\n");
    if (!esListaVacia(Lista))
    {
        while (!esListaVacia(Lista))
        {
            printf("ID: %d\n", Lista->tarea.tareaID);
            printf("Descripcion: %s\n", Lista->tarea.descripcion);
            printf("Duracion: %d\n\n", Lista->tarea.duracion);
            Lista = Lista->siguiente;
        }
    }
    else
    {
        printf("Lista Vacia\n");
    }
}

void liberarMemoria(HeadLista *Lista)
{
    struct Nodo *actual = *Lista;
    struct Nodo *temp;

    while (actual != NULL)
    {
        temp = actual;
        actual = actual->siguiente;
        free(temp->tarea.descripcion); // Liberar la memoria asignada a la descripción de la tarea
        free(temp);                    // Liberar la memoria asignada al nodo
    }

    *Lista = NULL;
}