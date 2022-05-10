#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct tarea{
    int tareaID; //numerado ciclo iterativo
    char *descripcion;
    int duracion;//entre 10 y 100
}tarea;

typedef struct nodo{
    tarea tarea;
    struct nodo *siguiente;
}nodo;

typedef nodo *lista;

void listaVacia(lista *);
tarea cargarTarea(int);
nodo *crearNodo(int);
void insertarNodo(lista *,nodo *);
void ordenarTareas(lista *,lista *);
void mostrarListaDeTareas(lista);
void *buscarPorPalabra(lista,char*);
void *buscarPorID (lista,int);
void eliminarNodo(lista *);
void eliminarLista(lista *);

void main(){
    srand(time(NULL));
    int cantidadDeTareas,id;
    nodo *nodoAuxiliar;
    char *palabraClave, *buff=(char *)malloc(30*sizeof(char));
    lista tareasRealizadas,tareasPendientes;

    listaVacia(&tareasRealizadas);
    listaVacia(&tareasPendientes);

    puts("\nIngrese la cantidad de tareas que desea cargar: ");
    scanf("%d",&cantidadDeTareas);
    for (int i = 0; i < cantidadDeTareas; i++)
    {
        nodoAuxiliar=crearNodo(i);
        insertarNodo(&tareasPendientes,nodoAuxiliar);
    }

    printf("\nLAS TAREAS CARGADAS EN ESTE MOMENTO SON:\n");
    mostrarListaDeTareas(tareasPendientes);
    printf("PARA ORDENAR LAS TAREAS PRESIONE CUALQUIER TECLA ");
    getchar();

    ordenarTareas(&tareasPendientes,&tareasRealizadas);
    printf("\nLAS TAREAS REALIZADAS EN ESTE MOMENTO SON:\n");
    mostrarListaDeTareas(tareasRealizadas);
    printf("\nLAS TAREAS PENDIENTES EN ESTE MOMENTO SON:\n");
    mostrarListaDeTareas(tareasPendientes);

    printf("\nIngrese la ID de la tarea que quiere buscar: ");
    scanf("%d",&id);
    buscarPorID(tareasPendientes,id);
    buscarPorID(tareasRealizadas,id);

    printf("\nIngrese la palabra clave que desea buscar: ");
    fflush(stdin);
    gets(buff);
    palabraClave= (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(palabraClave,buff);
    free(buff);
    buscarPorPalabra(tareasPendientes,palabraClave);
    buscarPorPalabra(tareasRealizadas,palabraClave);

    printf("LIBERO LA MEMORIA RESERVADA.");
    eliminarLista(&tareasPendientes);
    eliminarLista(&tareasRealizadas);

    fflush(stdin);
    getchar();
}

void listaVacia(lista *nuevaLista){
    *nuevaLista=NULL;
}

tarea cargarTarea(int id){
    char *buff=malloc(100*sizeof(char));
    tarea nuevaTarea;
    printf("\nIngrese una breve descripcion de la tarea %d\n",id+1);
    fflush(stdin);
    gets(buff);
    nuevaTarea.descripcion=(char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevaTarea.descripcion,buff);
    nuevaTarea.duracion=rand()%90 + 10;
    nuevaTarea.tareaID=id+1;
    free (buff);

    return nuevaTarea;
}

nodo *crearNodo(int id){
    nodo *nuevoNodo=(nodo *)malloc(sizeof(nodo));
    nuevoNodo->tarea=cargarTarea(id);
    nuevoNodo->siguiente=NULL;
}

void insertarNodo(lista *head, nodo *nodoAInsertar){
    nodoAInsertar->siguiente=*head;
    *head=nodoAInsertar;
}

void escribirTarea(tarea tareaAEscribir){
    printf("\n----------Tarea numero %d----------\n",tareaAEscribir.tareaID);
    printf("\n-----------Descripcion-----------\n");
    puts(tareaAEscribir.descripcion);
    printf("Duracion: %d\n",tareaAEscribir.duracion);
}

void ordenarTareas(lista *tareasPendientes,lista *tareasRealizadas){
    int completada;
    lista listaAuxiliar=*tareasPendientes;
    nodo *nodoAuxiliar,*nodoAnterior=listaAuxiliar;
    printf("\n------------------TAREAS CARGADAS------------------\n");
    while (listaAuxiliar)
    {
        escribirTarea(listaAuxiliar->tarea);
        fflush(stdin);
        printf("\n¿Tarea completada? [0]: NO [1]:SI\n");
        scanf("%d",&completada);
        if (completada==1)
        {
            nodoAuxiliar=listaAuxiliar;
            if (nodoAnterior==listaAuxiliar)//es el primer elemento de la lista
            {
                (*tareasPendientes)=(*tareasPendientes)->siguiente;
                listaAuxiliar=*tareasPendientes;
            }else{
                    (*nodoAnterior).siguiente=listaAuxiliar->siguiente;
                    listaAuxiliar=listaAuxiliar->siguiente;
            }
            (*nodoAuxiliar).siguiente=*tareasRealizadas;
            *tareasRealizadas=nodoAuxiliar;
        }else{
            listaAuxiliar=listaAuxiliar->siguiente;
            nodoAnterior=*tareasPendientes;
        }
    }
}


void mostrarListaDeTareas(lista listaAMostrar){
    while (listaAMostrar)
    {
        escribirTarea(listaAMostrar->tarea);
        listaAMostrar=listaAMostrar->siguiente;
    }
}

void *buscarPorPalabra(lista lista,char* palabraClave){

    while(lista && strcmp(lista->tarea.descripcion,palabraClave)!=0)
    {
        lista=lista->siguiente;
    }
    if (lista)
    {
        puts("\n-----------Tarea Encontrada-----------\n");
        escribirTarea(lista->tarea);
    }
   
}

void *buscarPorID (lista lista, int id){
    while(lista && lista->tarea.tareaID!=id)
    {
        lista=lista->siguiente;
    }
    if (lista)
    {
        puts("\n-----------Tarea Encontrada-----------\n");
        escribirTarea(lista->tarea);
    }
}

void eliminarNodo(lista *lista){
    nodo *eliminado=*lista;
    *lista=(*lista)->siguiente;
    free(eliminado);
}

void eliminarLista(lista *listaABorrar){
    while (*listaABorrar)
    {
        eliminarNodo(listaABorrar);   
    }
}
