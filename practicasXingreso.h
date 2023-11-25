#ifndef PRACTICASXINGRESO_H_INCLUDED
#define PRACTICASXINGRESO_H_INCLUDED

#include "practicas.h"
#include "ingresos.h"


//-----------------------------//
//ESTRUCTURAS PRACTICAS X INGRESO//
//-----------------------------//

typedef struct pracXingreso {
int NroDeIngreso;
int NroDePractica;
char Resultado[40];
} pracXingreso;

typedef struct nodoPxi {
pracXingreso pxi;
struct nodoPxi *anterior;
struct nodoPxi *siguiente;
} nodoPxi;

//-----------------------------//
//FUNCIONES PRACITCAS X INGRESO //
//-----------------------------//
nodoPxi *inicListaPxI();
nodoPxi *crearNodoPxI(pracXingreso datoNuevo);
nodoPxi *agregarAlPrincipioPxI(nodoPxi *lista, nodoPxi *NuevoNodo);
nodoPxi *borrarNodoPxI(nodoPxi *listaP, int idPracticas);
void mostrarListaPxI(nodoPxi *listaP);
nodoPxi *BuscarPxI (nodoPxi *listaP, int idPractica);
nodoPxi *altaPxI (nodoPxi *listaP, int ing);
nodoPxi *bajaPxI(nodoPxi *listaP, int ing);
nodoPxi *modificacionPxI(nodoPxi *listaP);
void mostrarIngresosAltaConPracticas(nodoIngreso * listaIngreso);
nodoPxi *cargarResultadosLaboratorio(nodoPxi *listaP);
nodoPxi *modificacionResultadosAdmin(nodoPxi *listaP);

#endif // PRACTICASXINGRESO_H_INCLUDED
