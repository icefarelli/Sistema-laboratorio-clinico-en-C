#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "ingresos.h"
#include <string.h>
//-----------------------------//
//ESTRUCTURAS PACIENTES//
//-----------------------------//

typedef struct pacientes{
char NyA[40];
int edad;
int DNI;
char direccion[30];
char tel[15];
int elim; // 0 significa que no esta eliminado
}pacientes;


typedef struct nodoPac{
pacientes pac;
struct nodoPac *izquierda;
struct nodoPac *derecha;
int altura;
struct nodoIngreso *ingresos;
}nodoPac;

nodoPac * inicArbolPacientes();
pacientes cargaPacientesPorTeclado();
nodoPac* altaPacientes(nodoPac* arbolPacientes, pacientes pac);
nodoPac* crearNodoArbolPac (pacientes datoNuevo);
nodoPac* insertarPacienteEnArbolPorNombre (nodoPac* arbol, nodoPac* nodoNuevo);
void preorderPac(nodoPac* arbol);
void inorderPac(nodoPac* arbol);
void posorderPac(nodoPac* arbol);
nodoPac* buscarPacXdni(nodoPac* arbol, int dni);
nodoPac *pasarArchivoArbol ();
nodoPac *pasarArchivoArbolPorNombre();
nodoPac* buscarPacXnombre(nodoPac* arbol, char nombre[]);
void mostrarNodoPac (nodoPac *nodo);
void mostrarArchivoPacientes();
void autoGuardadoPacientes (nodoPac* arbolPacientes);
void pasarArbolAArchivos(nodoPac* arbolPacientes, FILE* archivoPacientes);
void mostrarPacientesPorNombre(nodoPac* arbolDNI);
int contarDigitos(int numero);
nodoPac* modificacionPacientes(nodoPac* arbolPacientes, int dni);
nodoPac* bajaPacientes(nodoPac *arbolPacientes, int dni);
int validar_numero(char numero_str[]);
nodoPac* encontrarMinimo(nodoPac* nodo);
nodoPac* encontrarMaximo(nodoPac* nodo);
nodoPac* eliminarPaciente(nodoPac* arbolPacientes, int dni);
void liberarArbolPacientes (nodoPac* arbolPacientes);

void escribirPacienteEnArchivo(FILE* archivo, pacientes pac);
void escribirArbolEnArchivo(nodoPac* arbolPaciente, FILE* archivo);
void escribirArbolEnArchivoPrincipal(nodoPac* arbolPaciente);

int altura(nodoPac *nodo) ;
int max(int a, int b);
nodoPac* rotacionDerecha(nodoPac *y);
nodoPac* rotacionIzquierda(nodoPac *x);
int factorEquilibrio(nodoPac *nodo);
nodoPac* actualizarAltura(nodoPac *nodo);
nodoPac* insertarPacienteEnArbolAVL (nodoPac* arbol, nodoPac* nodoNuevo);

///Estas dos funciones pertenecen a "practicas" LA AGREGO ACA PORQUE NECESITO PASARLE EL ARBOL POR PARAMETRO PARA RECORRER TODO EL SISTEMA.
int busquedaPracticasEnSistema(nodoPac* arbolPacientes, int idPractica);
void bajaPractica(nodoPac* arbolPacientes);

#endif // PACIENTES_H_INCLUDED
