#ifndef MENUSECRETARIA_H_INCLUDED
#define MENUSECRETARIA_H_INCLUDED
#include "usuario.h"
#include "pacientes.h"

//-----------------------------//
//FUNCIONES MENU SECRETARIA//
//-----------------------------//
//1.MENU SECRETARIA
//2.MENU SECRETARIA - PACIENTES
//3.MENU SECRETARIA - PACIENTES - OPCIONES PACIENTES
//4.MENU SECRETARIA - PACIENTES - OPCIONES INGRESOS
//5.MENU SECRETARIA - PACIENTES - OPCIONES DE PRACTICAS
//6.MENU SECRETARIA - LABORATORIO

/*1*/nodoPac * menuSecretaria(empleados_laboratorio usuario, nodoPac * arbolPacientes);
/*2*/nodoPac * menuSecretariaPacientes(nodoPac * arbolPacientes);
/*3*/nodoPac * menuSecretariaPacientesOp(nodoPac * arbolPacientes);
/*4*/nodoPac * menuSecretariaIngresosOp(nodoPac * arbolPacientes);
/*5*/nodoPac * menuSecretariaPracticasOp(nodoPac * arbolPacientes);
/*6*/void menuSecretariaLaboratorio(empleados_laboratorio administrativo);
#endif // MENUSECRETARIA_H_INCLUDED
