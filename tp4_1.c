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

    ordenarTareas(&tareasPendientes,&tareasRealizadas);

    puts("\nIngrese la ID de la tarea que quiere buscar: ");
    scanf("%d",&id);
    buscarPorID(tareasPendientes,id);
    buscarPorID(tareasRealizadas,id);

    puts("\nIngrese la palabra clave que desea buscar: ");
    fflush(stdin);
    gets(buff);
    palabraClave= (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(palabraClave,buff);
    free(buff);
    buscarPorPalabra(tareasPendientes,palabraClave);
    buscarPorPalabra(tareasRealizadas,palabraClave);

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
    printf("----------Tarea numero %d----------\n",tareaAEscribir.tareaID);
    printf("-----------Descripcion-----------\n");
    puts(tareaAEscribir.descripcion);
    printf("Duracion: %d\n",tareaAEscribir.duracion);
}

void ordenarTareas(lista *tareasPendientes,lista *tareasRealizadas){
    int completada;
    lista auxiliar=*tareasPendientes;
    nodo *nodoAuxiliar;
    printf("\n------------------TAREAS CARGADAS------------------\n");
    while (auxiliar)
    {
        escribirTarea(auxiliar->tarea);
        fflush(stdin);
        printf("¿Tarea completada? [0]: NO [1]:SI\n");
        scanf("%d",&completada);
        if (completada==1)
        {
            if (auxiliar->siguiente!=NULL)//LA LISTA TIENE MAS DE UN ELEMENTO
            {
                if (auxiliar->siguiente->siguiente!=NULL)//LA LISTA TIENE DOS ELEMENTOS O MAS
                {
                    
                }
            }else{//SI LA LISTA TIENE 1 ELEMENTO
                nodoAuxiliar=auxiliar;
                *tareasPendientes=(*tareasPendientes)->siguiente;
                // insertarNodo(*tareasRealizadas,nodoAuxiliar);
                nodoAuxiliar->siguiente=*tareasRealizadas;
                *tareasRealizadas=nodoAuxiliar;
            }
            // nodoAuxiliar=auxiliar;
            // *tareasPendientes=(*tareasPendientes)->siguiente;
            // // insertarNodo(*tareasRealizadas,nodoAuxiliar);
            // nodoAuxiliar->siguiente=*tareasRealizadas;
            // *tareasRealizadas=nodoAuxiliar;
        }
        auxiliar=auxiliar->siguiente;
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
        puts("-----------Tarea Encontrada-----------");
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
        puts("-----------Tarea Encontrada-----------");
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

void ordenarTareas(lista *tareasPendientes, lista *tareasRealizadas)