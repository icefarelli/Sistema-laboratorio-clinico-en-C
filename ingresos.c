#include "ingresos.h"
#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//-----------------------------//
//INGRESOS//
//-----------------------------//
//-----------------------------//
//FUNCIONES BASICAS//
//-----------------------------//
//1. INICIAR LISTA


nodoIngreso * inicListaIngresos()
{
    return NULL;
}
//2. CARGAR INGRESO

int CantidadIngresosXdni (nodoIngreso *listaIngreso)
{
    nodoIngreso *seg=listaIngreso;
    int i = 1;
    while(seg!=NULL)
    {
        i++;
        seg=seg->siguiente;
    }
    return i;
}

ingreso cargarIngreso(nodoIngreso *listaIngreso,int dni)
{
    ingreso in;
    int flag=0;
    char valid_matricula[50];

    in.nroDeIngreso = CantidadIngresosXdni(listaIngreso);

    while(flag==0){
        printf("\nIngrese fecha de Ingreso (DD-MM-AAAA): ");  //validar fechas
        fflush(stdin);
        gets(in.fechaIngreso);
        if(esFechaValida(in.fechaIngreso)==0){
            printf("Formato de fecha incorrecto: \n");
        }else{
            flag=1;
        }
    }
    strcpy(in.fechaRetiro,"");
    in.dniPaciente = dni;

   do{
    printf("\nIngrese la matricula de profesional: ");
    fflush(stdin);
    gets(valid_matricula);
    in.matriculaProfesional=validar_matrricula(valid_matricula);
        if(validar_matrricula(valid_matricula)==0){
            printf("Matricula no valida. Ingresar solo caracteres numericos enteros.\n\n");
        }
    }while(validar_matrricula(valid_matricula)==0);

    in.eliminado = 0;

    return in;
}
//3. MOSTRAR INGRESO
void mostrarIngreso(ingreso i)
{
    printf("\nDNI: %i\n", i.dniPaciente);
    printf("Fecha de ingreso: %s\n", i.fechaIngreso);
    printf("Fecha de retiro: %s\n", i.fechaRetiro);
    printf("Matricula Profesional: %i\n", i.matriculaProfesional);
    printf("Id Ingreso: %i\n\n", i.nroDeIngreso);
    printf("----------------------------------------------\n");
}
//4. CREAR NODO INGRESO
nodoIngreso * crearNodoIngreso(ingreso in)
{
    nodoIngreso * nuevoIngreso = (nodoIngreso*) malloc(sizeof(nodoIngreso));
    nuevoIngreso->ingreso = in;
    nuevoIngreso->practicas = NULL;
    nuevoIngreso->anterior = NULL;
    nuevoIngreso->siguiente = NULL;
    return nuevoIngreso;
}
//5. AGREGAR NODO Ppio
nodoIngreso * agregarNodoPpioIngreso(nodoIngreso * listaIngreso, nodoIngreso * nuevoIngreso)
{
    if(listaIngreso!= NULL)
    {
        nodoIngreso * seg = listaIngreso;
        seg->anterior = nuevoIngreso;
        nuevoIngreso->siguiente=seg;
        listaIngreso = nuevoIngreso;
    }
    else
    {
        listaIngreso = nuevoIngreso;
    }
    return listaIngreso;
}
//-----------------------------//
//FUNCIONES ARCHIVO//
//-----------------------------//

//-----------------------------//
//ABML//
//-----------------------------//
//1. ALTA INGRESOS

nodoIngreso *altaIngreso(nodoIngreso * listaIngreso, int dni)
{
    ingreso in=cargarIngreso(listaIngreso,dni);

    nodoIngreso *aux=crearNodoIngreso(in);

    listaIngreso=agregarNodoPpioIngreso(listaIngreso,aux);

    return listaIngreso;
}

//2. BAJA INGRESOS
nodoIngreso * bajaIngreso(nodoIngreso * listaIngreso)
{
    int id;
    int flag=0;
    nodoIngreso *aux;

    while(flag==0)
    {
        printf("Que ingreso quiere dar de baja? \n");
        listadoIngresosAlta(listaIngreso);
        scanf("%i",&id);

        aux=BuscarIngreso(listaIngreso,id);

        if(aux==NULL)
        {
            printf("El ingreso no se encontro \n");
        }
        else
        {
            flag=1;
        }
    }
    if(aux->practicas==NULL){

        aux->ingreso.eliminado=1;
         printf("Dado de baja con exito. \n");

    } else{
    printf("El ingreso tiene practicas cargadas. No se puede dar de baja.\n");
    }

    return listaIngreso;
}

//3. MODIFICACION INGRESOS
nodoIngreso *modificacionIngreso (nodoIngreso *listaIngreso){
int id,op;
int flag=0;
ingreso in;
nodoIngreso *aux;

    while(flag==0)
    {
        printf("Que ingreso desea modificar? elegir el numero de ID. \n");
        listadoIngresos(listaIngreso);
        scanf("%i",&id);

        aux=BuscarIngreso(listaIngreso,id);

        if(aux==NULL)
        {
            printf("El ingreso no se encontro \n");
        }
        else
        {
            flag=1;
        }
    }

printf("Seleccione el campo que desea modificar. \n");
printf("1. Fecha de Ingreso (DD-MM-AAAA)\n");
printf("2. Fecha de retiro (DD-MM-AAAA)\n");
printf("3. Matricula Profesional:\n");

if(aux->ingreso.eliminado==1){
    printf("4. Dar de alta este ingreso:\n");
}
printf("0. Cancelar:\n");
scanf("%i",&op);
flag=0;
switch(op){
case 1:

    while(flag==0){
    printf("\nIngrese la nueva fecha de ingreso (DD-MM-AAAA): ");  //validar fechas
    fflush(stdin);
    gets(in.fechaIngreso);
    if(esFechaValida(in.fechaIngreso)==0){
        printf("Formato de fecha incorrecto: \n");
    }else{
    flag=1;
    }
    }

    strcpy(aux->ingreso.fechaIngreso,in.fechaIngreso);
    printf("Modificacion exitosa");

    break;
case 2:
    while(flag==0){
    printf("Ingrese la nueva fecha de retiro: (DD-MM-AAAA) ");
    fflush(stdin);
    gets(in.fechaRetiro);
    if(esFechaValida(in.fechaIngreso)==0){
        printf("Formato de fecha incorrecto: \n");
    }else{
    flag=1;
    }
    }
    strcpy(aux->ingreso.fechaRetiro,in.fechaRetiro);
    printf("Modificacion exitosa");
    break;
case 3:
    printf("Ingrese la nueva matricula: ");
    scanf("%i",&in.matriculaProfesional);

    aux->ingreso.matriculaProfesional=in.matriculaProfesional;
    printf("Modificacion exitosa");
    break;
 case 4:
    aux->ingreso.eliminado=0;
    printf("Dado de alta correctamente\n");
    break;
case 0:
    break;

default:
        printf("La opcion que ha seleccionado no es válida. Para modificar algun otro campo que no este en la lista debe pedir permiso al admin. \n");
        system("pause");
        system("cls");
        break;

}

return listaIngreso;
}




//4. LISTADO INGRESOS
//a. LISTADO ALTA
void listadoIngresosAlta(nodoIngreso * listaIngreso)
{
    if(listaIngreso == NULL)
    {
        printf("No hay ingresos\n");
    }
    else
    {
        nodoIngreso * seg = listaIngreso;
        while(seg != NULL)
        {
            if(seg->ingreso.eliminado != 1)
            {
                mostrarIngreso(seg->ingreso);
            }
        seg = seg->siguiente;
        }
    }
}
//b. LISTADO BAJA
void listadoIngresosBaja(nodoIngreso * listaIngreso)
{
    if(listaIngreso == NULL)
    {
        printf("No hay ingresos dados de baja\n");
    }
    else
    {
        nodoIngreso * seg = listaIngreso;
        while(seg != NULL)
        {
            if(seg->ingreso.eliminado == 1)
            {
                mostrarIngreso(seg->ingreso);
            }
         seg = seg->siguiente;
        }
    }
}
//.c LISTADO INGRESOS
void listadoIngresos(nodoIngreso * listaIngreso)
{
    if(listaIngreso == NULL)
    {
        printf("No hay ingresos\n");
    }
    else
    {
        nodoIngreso * seg = listaIngreso;
        while(seg != NULL)
        {
            printf("\nDNI: %i\n", seg->ingreso.dniPaciente);
            printf("Fecha de ingreso: %s\n", seg->ingreso.fechaIngreso);
            printf("Fecha de retiro: %s\n", seg->ingreso.fechaRetiro);
            printf("Matricula Profesional: %i\n", seg->ingreso.matriculaProfesional);
            printf("Id ingreso: %i\n", seg->ingreso.nroDeIngreso);
            if(seg->ingreso.eliminado==1){
                printf("BAJA\n\n");
            } else {
            printf("ACTIVO\n\n");
            }
            printf("----------------------------------------------\n");
            seg = seg->siguiente;
        }

    }
}

//d. LISTADO DE INGRESOS POR FECHA DESDE - HASTA
void listadoIngresosRangoFechas (nodoIngreso *listaIngreso){

char fechaDesde[20];
char fechaHasta[20];

nodoIngreso *seg=listaIngreso;

printf("\nIngrese fecha desde (DD-MM-AAAA): ");
fflush(stdin);
gets(fechaDesde);

printf("\nIngrese fecha hasta (DD-MM-AAAA): ");
fflush(stdin);
gets(fechaHasta);

while(seg!=NULL){
if (estaEnRango(seg->ingreso.fechaIngreso, fechaDesde, fechaHasta)==1) {
        mostrarIngreso(seg->ingreso);
    }
    seg=seg->siguiente;
}

}



// BUSCAR INGRESOS POR ID INGRESO
nodoIngreso *BuscarIngreso (nodoIngreso *listaIngreso, int idIngreso)
{
    nodoIngreso *seg=listaIngreso;
    while(seg!=NULL && seg->ingreso.nroDeIngreso!=idIngreso)
    {
            seg=seg->siguiente;
    }
    return seg;
}


int compararFechas(struct tm fecha1, struct tm fecha2) {
    if (fecha1.tm_mday < fecha2.tm_mday) {
        return -1; // fecha1 es anterior a fecha2
    } else if (fecha1.tm_mday > fecha2.tm_mday) {
        return 1; // fecha1 es posterior a fecha2
    } else {
        if (fecha1.tm_mon < fecha2.tm_mon) {
            return -1; // mismo año, pero fecha1 es anterior a fecha2
        } else if (fecha1.tm_mon > fecha2.tm_mon) {
            return 1; // mismo año, pero fecha1 es posterior a fecha2
        } else {
            if (fecha1.tm_year < fecha2.tm_year) {
                return -1; // misma año y mes, pero fecha1 es anterior a fecha2
            } else if (fecha1.tm_year > fecha2.tm_year) {
                return 1; // misma año y mes, pero fecha1 es posterior a fecha2
            } else {
                return 0; // las fechas son iguales
            }
        }
    }
}

int estaEnRango (char fechaStr[],char rangoInicioStr[],char rangoFinStr[]) {
    struct tm fecha, rangoInicio, rangoFin;

   if (sscanf(fechaStr, "%d-%d-%d", &fecha.tm_year, &fecha.tm_mon, &fecha.tm_mday) != 3 ||
        sscanf(rangoInicioStr, "%d-%d-%d", &rangoInicio.tm_year, &rangoInicio.tm_mon, &rangoInicio.tm_mday) != 3 ||
        sscanf(rangoFinStr, "%d-%d-%d", &rangoFin.tm_year, &rangoFin.tm_mon, &rangoFin.tm_mday) != 3) {
        fprintf(stderr, "Error al convertir las fechas.\n");
        return -1; // Error en la conversión
    }

    // Ajustar los valores de los años y meses, ya que struct tm usa años desde 1900 y meses de 0 a 11
    fecha.tm_year -= 1900;
    rangoInicio.tm_year -= 1900;
    rangoFin.tm_year -= 1900;
    fecha.tm_mon -= 1;
    rangoInicio.tm_mon -= 1;
    rangoFin.tm_mon -= 1;


    if (compararFechas(fecha, rangoInicio) >= 0 && compararFechas(fecha, rangoFin) <= 0) {
        return 1; // La fecha está dentro del rango
    } else {
        return 0; // La fecha está fuera del rango
    }
}
