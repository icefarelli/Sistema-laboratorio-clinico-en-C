#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "practicas.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicasXingreso.h"
#include <string.h>
#include <ctype.h>


typedef struct {
int nroPractica;
char nombrePractica[30];
int elim; // 1 si esta eliminado, 0 si no esta eliminado
}practicas;

int validacionNombrePractica(char nombrePractica[]);
practicas validacionPractica (int NroPractica);
int validacionBajaPractica (practicas p);
void mostrarParcialPractica();
practicas PedirPractica();
void mostrarPractica (practicas p);
void mostrarArchivoPracticas (char nombreArchivo[]);
void convertirMayusculas(char *cadena);
int cuentaCantidadPracticas();
practicas cargarPracticaPorTeclado();
void altaPractica();
void modificacionPracticas(int idPractica);
int compararPorNombre(const void *a, const void *b);
void mostrarPracticasOrdenadas();


#endif // PRACTICAS_H_INCLUDED
