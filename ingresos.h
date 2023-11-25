#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED
#include <time.h>

#define NROINGRESO 0
//-----------------------------//
//ESTRUCTURAS INGRESOS//
//-----------------------------//

typedef struct
{
    int nroDeIngreso;
    char fechaIngreso[20];
    char fechaRetiro[20];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
} ingreso;

typedef struct nodoIngreso
{
    ingreso ingreso;
    struct nodoIngreso * anterior;
    struct nodoIngreso * siguiente;
    struct nodoPxi * practicas;
} nodoIngreso;

//-----------------------------//
//FUNCIONES BASICAS//
//-----------------------------//
/*1*/nodoIngreso * inicListaIngresos();
/*2*/int CantidadIngresosXdni (nodoIngreso *listaIngreso);
/*3*/ingreso cargarIngreso(nodoIngreso *listaIngreso,int dni);
/*4*/void mostrarIngreso(ingreso i);
/*5*/nodoIngreso * crearNodoIngreso(ingreso in);
/*6*/nodoIngreso * agregarNodoPpioIngreso(nodoIngreso * listaIngreso, nodoIngreso * nuevoIngreso);
/*7*/nodoIngreso *BuscarIngreso (nodoIngreso *listaIngreso, int idIngreso);
/*8*/nodoIngreso *altaIngreso(nodoIngreso * listaIngreso, int dni);
/*9*/nodoIngreso * bajaIngreso(nodoIngreso * listaIngreso);
/*10*/nodoIngreso *modificacionIngreso (nodoIngreso *listaIngreso);
/*11*/void listadoIngresosAlta(nodoIngreso * listaIngreso);
/*12*/void listadoIngresosBaja(nodoIngreso * listaIngreso);
/*13*/void listadoIngresos(nodoIngreso * listaIngreso);
/*14*/int estaEnRango (char fechaStr[],char rangoInicioStr[],char rangoFinStr[]);
/*15*/int compararFechas(struct tm fecha1, struct tm fecha2);
/*16*/void listadoIngresosRangoFechas (nodoIngreso *listaIngreso);



#endif // INGRESOS_H_INCLUDED

