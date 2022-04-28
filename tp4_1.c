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

void cargarTareas(tarea **tareasPendientes, int cantidadTareas);
void ordenarTareas(tarea **tareasPendientes, tarea **tareasRealizadas, int cantidadTareas);
void mostrarTareas(tarea **tareasPendientes, tarea **tareasRealizadas, int cantidadTareas);
void escribirTareas(tarea *listaDeTareas);

int main(){
    srand(time(NULL));
    int cantidadTareas;
    tarea **tareasPendientes, **tareasRealizadas;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d",&cantidadTareas);
    tareasPendientes=(tarea **)malloc(cantidadTareas*sizeof(tarea *));
    tareasRealizadas=(tarea **)malloc(cantidadTareas*sizeof(tarea *));

    cargarTareas(tareasPendientes, cantidadTareas);
    ordenarTareas(tareasPendientes, tareasRealizadas, cantidadTareas);
    mostrarTareas(tareasPendientes, tareasRealizadas, cantidadTareas);

    fflush(stdin);
    getchar();
    return 0;
}

void cargarTareas(tarea **tareasPendientes, int cantidadTareas){
    char *buff;
    buff=(char*)malloc(50*sizeof(char));

    for (int i = 0; i < cantidadTareas; i++)
    {
        (*(tareasPendientes+i))=(tarea *)malloc(sizeof(tarea));
        fflush(stdin);
        printf("Ingrese una breve descripcion de la tarea %d: ",i+1);
        gets(buff);
        (*(tareasPendientes+i))->tareaID=i+1;
        (*(tareasPendientes+i))->descripcion=(char *)malloc((strlen(buff)+1)*sizeof(char));
        strcpy((*(tareasPendientes+i))->descripcion,buff);
        (*(tareasPendientes+i))->duracion=rand()%90+10;
    }
    free(buff);
}

void ordenarTareas(tarea **tareasPendientes, tarea **tareasRealizadas, int cantidadTareas){
    int completada=0;
    printf("\n------------LISTA DE TAREAS CARGADAS------------\n");
    for (int i = 0; i < cantidadTareas; i++)
    {
        printf("Tarea numero %d:\n",(*(tareasPendientes+i))->tareaID);
        printf("%s\n",(*(tareasPendientes+i))->descripcion);
        printf("¿Ya esta completada? [0]: No [1]: Si\n");
        scanf("%d",&completada);
        if (completada==1)
        {
            (*(tareasRealizadas+i))=(tarea *)malloc(sizeof(tarea));
            (*(tareasRealizadas+i))->descripcion=(char *)malloc((strlen((*(tareasPendientes+i))->descripcion)+1)*sizeof(char));
            strcpy((*(tareasRealizadas+i))->descripcion,(*(tareasPendientes+i))->descripcion);
            (*(tareasRealizadas+i))->duracion=(*(tareasPendientes+i))->duracion;
            (*(tareasRealizadas+i))->tareaID=(*(tareasPendientes+i))->tareaID;
            (*(tareasPendientes+i))=NULL;
        }else{
            (*(tareasRealizadas+i))=NULL;
        }
    }    
}

void mostrarTareas(tarea **tareasPendientes, tarea** tareasRealizadas, int cantidadTareas){
    printf("\n------------LISTA DE TAREAS PENDIENTES------------\n");
    for (int i = 0; i < cantidadTareas; i++)
    {
        escribirTareas(*(tareasPendientes+i));
    }

    printf("\n------------LISTA DE TAREAS REALIZADAS------------\n");
    for (int i = 0; i < cantidadTareas; i++)
    {
        escribirTareas(*(tareasRealizadas+i));
    }
}

void escribirTareas(tarea *listaDeTareas){
    if (listaDeTareas!=NULL)
    {
        printf("Tarea numero %d\n",listaDeTareas->tareaID);
        printf("Descripcion: %s\n",listaDeTareas->descripcion);
        printf("Duracion estimada: %d horas\n",listaDeTareas->duracion);
    }
}

