#ifndef MENUADMIN_H_INCLUDED
#define MENUADMIN_H_INCLUDED
#include "usuario.h"
#include "menuAdmin.h"
#include "home.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-----------------------------//
//FUNCIONES MENU ADMIN//
//-----------------------------//
//1. MENU PRINCIPAL ADMIN
//2. MENU REGISTRO ADMIN
//3. MENU CONFIGURACION ADMIN
//4. MENU PACIENTES ADMIN
//5. MENU PACIENTES ADMIN - PACIENTE
//6. MENU PACIENTES ADMIN - INGRESO
//7. MENU PACIENTES ADMIN - PRACTICAS
//8. MENU LABORATORIO ADMIN
//9. MENU LABORATORIO ADMIN- PERSONAL
//10. MENU LABORATORIO ADMIN- ANALISIS
//11. MENU SECRETARIA ADMIN

/*1*/nodoPac * menuAdmin(empleados_laboratorio usuario, nodoPac * arbolPacientes);
/*2*/void adMenuRegistro();
/*3*/nodoPac * adMenuConfiguracion(nodoPac * arbolPacientes, empleados_laboratorio admin);
/*4*/nodoPac * adMenuPacientes(nodoPac * arbolPacientes);
/*5*/nodoPac * adMenuPacientesPacientes(nodoPac * arbolPacientes);
/*6*/nodoPac * adMenuPacientesIngresos(nodoPac * arbolPacientes);
/*7*/nodoPac * adMenuPacientesPracticas(nodoPac * arbolPacientes);
/*8*/nodoPac * adMenuLaboratorio(empleados_laboratorio admin, nodoPac * arbolPacientes);
/*9*/void adMenuLaboratorioPersonal(empleados_laboratorio admin);
/*10*/nodoPac * adMenuLaboratorioPracticas(nodoPac * arbolPacientes);
/*11*/nodoPac * adMenuSecretaria(nodoPac * arbolPacientes, empleados_laboratorio admin);


#endif // MENUADMIN_H_INCLUDED
