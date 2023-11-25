#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuLaboratorio.h"
#include "usuario.h"
#include "pacientes.h"
#include "practicas.h"
#include "practicasXingreso.h"
#include "validaciones.h"

//-----------------------------//
//FUNCIONES MENU LABORATORIO//
//-----------------------------//
//1.MENU LABORATORIO
nodoPac * menuLaboratorio(empleados_laboratorio usuario, nodoPac * arbolPacientes)
{
    empleados_laboratorio *ptr_usuario = &usuario;
    empleados_laboratorio aux;

    int option;
    int dni;
    int id;
    char dniChar[20];
    int eleccion;
    nodoPac * pacienteBuscado = inicArbolPacientes();
    nodoIngreso * ingresoBuscado;
    do
    {
        system("cls");
        printf("--------------\n");
        printf("|----MENU----|\n");
        printf("--------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Cargar Resultado de Analisis Clinico\n");
        printf("2. Ver historial del paciente\n");
        printf("3. Listado de Pacientes\n");
        printf("4. Listado de Analisis clinicos\n");
        printf("5. Mi perfil\n");
        printf("0. Salir de mi sesión \n");
        printf("--------------------------\n");

        fflush(stdin);
        if(scanf("%i",&option) != 1){
            option = 8;
        }

        fflush(stdin);
        system("cls");

        switch(option)
        {
        case 1:
            printf("Ingrese el DNI del paciente: \n");
            scanf("%i",&dni);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                if(pacienteBuscado->ingresos == NULL){
                    printf("No tiene ingresos cargados\n");
                }else{
                    listadoIngresosAlta(pacienteBuscado->ingresos);
                    printf("Ingrese el id del ingreso: \n");
                    scanf("%i",&id);
                    ingresoBuscado = BuscarIngreso(pacienteBuscado->ingresos,id);
                    if(ingresoBuscado != NULL)
                    {
                        ingresoBuscado->practicas = cargarResultadosLaboratorio(ingresoBuscado->practicas);
                    }
                    else
                    {
                        printf("No se encontro un ingreso con ese id. \n");
                    }
                }
            }
            system("pause");
            system("cls");
            break;

        case 2:
            printf("Ingrese el dni del paciente: \n");
            scanf("%i",&dni);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado != NULL)
            {
                mostrarIngresosAltaConPracticas(pacienteBuscado->ingresos);
            }
            else
            {
                printf("Lo sentimos. No se encontro el paciente \n");
            }
            system("pause");
            system("cls");
            break;

        case 3:
            mostrarPacientesPorNombre(arbolPacientes);
            system("pause");
            system("cls");
            break;

        case 4:
            mostrarPracticasOrdenadas();
            system("pause");
            system("cls");
            break;

        case 5:
           printf("------------\n");
            printf("Mi perfil: \n");
            printf("------------\n");
            printf("\n");
            mostrarEmpleado(*ptr_usuario);
            printf("Tipo de usuario: %s\n", ptr_usuario->perfil);
            printf("\n");
            printf("1. Modificar mi perfil\n");
            printf("0. Volver\n");
            scanf("%i",&eleccion);

            if(eleccion == 1)
            {
                convertirIntAChar(dniChar, ptr_usuario->dni);
                aux = modificarUsuario(dniChar, *ptr_usuario);
                ptr_usuario = &aux;
            }
            system("pause");
            system("cls");
            break;

        case 0:
            system("cls");
            break;

        default:
            printf("Error...\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
    return arbolPacientes;
}
