#include <stdio.h>
#include <stdlib.h>
#include "practicas.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicasXingreso.h"
#include <string.h>
#include <ctype.h>

//-----------------------------//
// FUNCIONES PRACTICAS//
//-----------------------------//

practicas validacionPractica (int NroPractica)
{

    FILE *archi=fopen("ArchivoPracticas.bin","rb");
    practicas practica;
    practicas aux;
    practica.nroPractica = -1;
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&aux,sizeof(practicas),1,archi);
            if(!feof(archi))
                if (aux.nroPractica==NroPractica)
                {
                    practica = aux;
                }
        }
    }
    fclose(archi);

    return practica;
}

int validacionNombrePractica(char nombrePractica[])
{

    int rta = -1;

    practicas p;
    FILE* archivo = fopen("ArchivoPracticas.bin","rb");
    if(archivo!= NULL)
    {
        while(fread(&p, sizeof(practicas), 1, archivo))
        {
            if(strcmpi(p.nombrePractica,nombrePractica)==0)
            {
                rta = 0;
            }
        }
    }
    return rta;
}



int validacionBajaPractica (practicas p)
{

    if(p.elim==1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


/**Listado de practicas que “comiencen con”. En este caso debe poder filtrar todas las
practicas cuyo nombre comiencen con lo seleccionado por el usuario. Ejemplo: si se
elige la combinación “he”, deberían mostrarse practicas como: “hemograma o
hepatograma” etc.**/

void convertirMayusculas(char *cadena)
{
    while (*cadena)
    {
        *cadena = toupper((unsigned char)*cadena);
        cadena++;
    }
}

void mostrarParcialPractica()
{
    char nombre[20];
    practicas reg;

    printf("Ingresar el nombre de la practica (al menos las 4 primeras letras): ");
    fflush(stdin);
    gets(nombre);
    convertirMayusculas(nombre);

    FILE *archi=fopen("ArchivoPracticas.bin","rb");


    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&reg,sizeof(practicas),1,archi);
            if(!feof(archi))
            {
                if(strncmp(nombre,reg.nombrePractica,4)==0)
                {
                    mostrarPractica(reg);
                }
            }
        }
    }
    fclose(archi);
}


practicas PedirPractica()
{

    mostrarParcialPractica();
    practicas aux;
    int codigo;
    int flag=0;

    do
    {
        printf("Ingrese el codigo de la practica: \n");
        scanf("%i",&codigo);

        aux=validacionPractica(codigo);

        if(aux.nroPractica==-1)
        {
            printf("Practica no valida\n\n");
        }
        else
        {
            flag=1;
        }
    }
    while(flag==0);

    return aux;
}

///FUNCIONES PARA VER EL ARCHIVO DE PRACTICAS//
void mostrarPractica (practicas p)
{

    printf("COD: %i  ",p.nroPractica);
    printf("%s \n",p.nombrePractica);

}

void mostrarArchivoPracticas(char nombreArchivo[])
{

    FILE *archi;
    practicas reg;

    archi=fopen(nombreArchivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&reg,sizeof(practicas),1,archi))
        {
            if(reg.elim!=1){
            mostrarPractica(reg);
            }
        }

    }
    fclose(archi);

}

//------------------------------------------------------------------------------------------------------//
// Funcion que cuenta cantidad de practicas cargadas en el archivo para determinar un secuencial en el ID
//------------------------------------------------------------------------------------------------------//

int cuentaCantidadPracticas()
{
    FILE* archivo = fopen("ArchivoPracticas.bin","rb");
    fseek(archivo,0,SEEK_END);
    int cant = ftell(archivo)/sizeof(practicas);
    return cant;
}

//------------------------------------------------------------------------------------------------------//
// Funcion que pide por pantalla el nombre de la practica, guarda hasta 30 caracteres.
// El NroPractica se carga solo y el campo eliminado se pone en 0
//------------------------------------------------------------------------------------------------------//

practicas cargarPracticaPorTeclado()
{
    practicas p;

    p.nroPractica=cuentaCantidadPracticas()+1;
    printf("\nIngrese nombre de practica nueva: ");
    fflush(stdin);
    fgets(p.nombrePractica,30,stdin);
    convertirMayusculas(p.nombrePractica);
    p.elim = 0;

    return p;

}



//------------------------------------------------------------------------------------------------------//
// Funcion que agrega una practica nueva al archivo de practicas
//------------------------------------------------------------------------------------------------------//

void altaPractica()
{

    FILE* archivoPractica = fopen("ArchivoPracticas.bin","a+b");
    if(archivoPractica!= NULL)
    {
        practicas p = cargarPracticaPorTeclado();
        fwrite(&p, sizeof(practicas), 1, archivoPractica);

        fclose(archivoPractica);
    }
}


// Modificacion_de_practica: solo su nombre

void modificacionPracticas(int idPractica)
{
    practicas p;
    char nombrePracticaNueva[30];
    FILE* archivoPractica = fopen("ArchivoPracticas.bin","r+b");

    if(archivoPractica!= NULL)
    {
        do
        {
            fread(&p, sizeof(practicas), 1, archivoPractica);
        }
        while(p.nroPractica != idPractica);

        fseek(archivoPractica,-sizeof(practicas), SEEK_CUR);
        printf("El nombre de la practica cargado en la base: %s\n", p.nombrePractica);
        printf("Ingrese nuevo nombre para la practica: ");
        fflush(stdin);
        gets(nombrePracticaNueva);
        convertirMayusculas(nombrePracticaNueva);
        strcpy(p.nombrePractica,nombrePracticaNueva);
        p.nroPractica = idPractica;
        p.elim = 0;

        fwrite(&p, sizeof(practicas),1,archivoPractica);

        fclose(archivoPractica);
    }

}



//------------------------------------------------------------------------------------------------------//
// Baja_de_practica: solo si no fue incluida en ningún ingreso
//------------------------------------------------------------------------------------------------------//
 //FUNCION DESARROLLADA EN "pacientes.c" por necesitar pasar el arbol como parametro y el tipo de dato "nodoPac" es de esa libreria.


//------------------------------------------------------------------------------------------------------//
// Funcion que muestra listado general de practicas de laboratorio ordenadas por nombre.
//------------------------------------------------------------------------------------------------------//

int compararPorNombre(const void *a, const void *b)
{
    return strcmp(((practicas *)a)->nombrePractica, ((practicas *)b)->nombrePractica);
}

void mostrarPracticasOrdenadas()
{
    FILE *archivoPractica = fopen("ArchivoPracticas.bin", "rb");
    int cantidadPracticas = cuentaCantidadPracticas();

    if (archivoPractica != NULL)
    {

        practicas *practicasArray = (practicas *)malloc(cantidadPracticas * sizeof(practicas));

        if (practicasArray != NULL)
        {
            fread(practicasArray, sizeof(practicas), cantidadPracticas, archivoPractica);
            fclose(archivoPractica);

            // Ordenar por nombre alfabéticamente
            qsort(practicasArray, cantidadPracticas, sizeof(practicas), compararPorNombre);

            // Mostrar los datos ordenados
            for (int i = 0; i < cantidadPracticas; i++)
            {
                if (practicasArray[i].elim == 0)
                {
                    printf("COD: %i  %s\n",practicasArray[i].nroPractica,practicasArray[i].nombrePractica);
                }
            }

            free(practicasArray);
        }
        else
        {
            fclose(archivoPractica);
            printf("Error: No se pudo asignar memoria para el arreglo de prácticas.\n");
        }
    }
    else
    {
        printf("Error: No se pudo abrir el archivo.\n");
    }
}
