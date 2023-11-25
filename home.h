#ifndef HOME_H_INCLUDED
#define HOME_H_INCLUDED
#include "menu.h"
#include "home.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicas.h"
#include "practicasXingreso.h"
#include "usuario.h"
#include "validaciones.h"

//-----------------------------//
//FUNCIONES HOME//
//-----------------------------//
//1. INICIO DE SESION
//2. REGISTRO DE USUARIO
//3. PACIENTES AL ARBOL DE LISTAS
//4. ARBOL DE PACIENTES A ARCHIVO
//5. LIBERADO DEL ARBOL DE PACIENTES


/*1*/empleados_laboratorio iniciarSesion();
/*2*/void registrarUsuario(char perfil[20]);
/*3*/nodoPac *inicioDeSistema();
/*4*/void pasarInfoAArchivos(nodoPac* arbolPaciente, FILE* archivoPacientes, FILE* archivoIngreso, FILE* archivoPxI);
/*5*/void cierreDeSistema(nodoPac* arbolPacientes);































#endif // HOME_H_INCLUDED
