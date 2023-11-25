#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuSecretaria.h"
#include "pacientes.h"
#include "usuario.h"
#include "practicas.h"
#include "practicasXingreso.h"
#include "validaciones.h"


//-----------------------------//
//FUNCIONES MENU SECRETARIA//
//-----------------------------//
//1.MENU SECRETARIA
nodoPac * menuSecretaria(empleados_laboratorio usuario, nodoPac * arbolPacientes)
{
    empleados_laboratorio *ptr_usuario = &usuario;
    empleados_laboratorio aux;

    int option;
    char dniChar[20];
    int eleccion;
    do
    {
        printf("-------------\n");
        printf("|----MENU----|\n");
        printf("-------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Pacientes \n");
        printf("2. Laboratorio \n");
        printf("3. Mi perfil \n");
        printf("0. Salir de mi sesion\n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            arbolPacientes = menuSecretariaPacientes(arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 2:
            menuSecretariaLaboratorio(usuario);
            system("pause");
            system("cls");
            break;
        case 3:
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
            fflush(stdin);

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
            printf("Opcion Incorrecta \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
    return arbolPacientes;
}

//2.MENU SECRETARIA - PACIENTES
nodoPac * menuSecretariaPacientes(nodoPac * arbolPacientes)
{
    int option;
    do
    {
        printf("---------------------------------------------\n");
        printf("|----MENU -> PACIENTES -> OPCIONES ----------|\n");
        printf("---------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Pacientes \n");
        printf("2. Ingresos \n");
        printf("3. Practicas \n");
        printf("0. Volver al menu anterior \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            arbolPacientes = menuSecretariaPacientesOp(arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 2:
            arbolPacientes = menuSecretariaIngresosOp(arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 3:
            arbolPacientes = menuSecretariaPracticasOp(arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            printf("Opcion Incorrecta \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
    return arbolPacientes;
}
//3.MENU SECRETARIA - PACIENTES - OPCIONES PACIENTES
nodoPac * menuSecretariaPacientesOp(nodoPac * arbolPacientes)
{
    int option;
    int eleccion;
    int dni;
    char valid_dni[10];
    pacientes paciente;
    nodoPac * pacienteNuevo;
    nodoPac * pacienteEncontrado;

    do
    {
        printf("---------------------------------------------\n");
        printf("|----MENU -> PACIENTES ----------------------|\n");
        printf("---------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Cargar Paciente \n");
        printf("2. Dar de baja un paciente \n");
        printf("3. Modificar paciente \n");
        printf("4. Listado de pacientes por DNI\n");
        printf("5. Listado de pacientes por nombre\n");
        printf("6. Ver informacion de paciente\n");
        printf("0. Volver al menu anterior \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            paciente = cargaPacientesPorTeclado();
            pacienteEncontrado = buscarPacXdni(arbolPacientes, paciente.DNI);
            if(pacienteEncontrado==NULL){
            arbolPacientes = altaPacientes(arbolPacientes, paciente);
            printf("1. Cargar un ingreso para el paciente \n");
            printf("0. Volver\n");
            scanf("%i",&eleccion);
            system("cls");
            if(eleccion != 0)
            {
                if(eleccion == 1)
                {
                    pacienteNuevo = buscarPacXdni(arbolPacientes, paciente.DNI);
                    pacienteNuevo->ingresos = altaIngreso(pacienteNuevo->ingresos, paciente.DNI);
                    printf("El ingreso ha sido cargado con exito \n");
                    printf("1. Cargar una practica para el paciente\n");
                    printf("0. Volver\n");
                    scanf("%i",&eleccion);
                    fflush(stdin);
                    if(eleccion != 0)
                    {
                        if(eleccion == 1)
                        {
                            pacienteNuevo->ingresos->practicas = altaPxI(pacienteNuevo->ingresos->practicas, pacienteNuevo->ingresos->ingreso.nroDeIngreso);
                            printf("La practica ha sido cargada con exito\n");
                        }
                        else
                        {
                            printf("Error \n");
                        }
                    }
                    else
                    {
                        printf("Error\n");
                    }
                }
            }
            system("pause");
            system("cls");
            }else{
                printf("Paciente ya cargado\n");
                if(pacienteEncontrado->pac.elim==0){
                    printf("Sus datos son:\n");
                    mostrarNodoPac(buscarPacXdni(arbolPacientes, paciente.DNI));
                }else{
                    printf("El paciente existe en la base de datos pero esta dado de baja. Dar de alta desde la opcion 3\n");
                }
                system("pause");
                system("cls");
            }
            break;
        case 2:
            printf("Ingrese el dni del usuario que desea dar de baja: \n");
            scanf("%i",&dni);
            fflush(stdin);
            arbolPacientes = bajaPacientes(arbolPacientes, dni);
            system("pause");
            system("cls");
            break;
        case 3:
            printf("Ingrese el dni del usuario que desea modificar: \n");
            scanf("%i",&dni);
            fflush(stdin);
            arbolPacientes = modificacionPacientes(arbolPacientes, dni);
            system("pause");
            system("cls");
            break;
        case 4:
            inorderPac(arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 5:
            mostrarPacientesPorNombre(arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 6:
            do{
                printf("Ingrese el dni del paciente buscado: \n");
                fflush(stdin);
                gets(valid_dni);
                dni=validar_DNI(valid_dni);
                if(validar_DNI(valid_dni)==0){
                    printf("DNI no valido. Ingresar hasta 8 caracteres numericos enteros.\n");
                    system("pause");
                    system("cls");
                }
                }while(validar_DNI(valid_dni)==0);

            pacienteEncontrado = buscarPacXdni(arbolPacientes,dni);
            if(pacienteEncontrado!=NULL){
            mostrarNodoPac(pacienteEncontrado);
            }else{
                printf("Paciente no encontrado\n");
            }
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            printf("Opcion Incorrecta \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
    return arbolPacientes;
}
//4.MENU SECRETARIA - PACIENTES - OPCIONES INGRESOS
nodoPac * menuSecretariaIngresosOp(nodoPac * arbolPacientes)
{
    int option;
    int eleccion;
    int dni;
    nodoPac * pacienteBuscado = inicArbolPacientes();
    do
    {
        printf("---------------------------------------------\n");
        printf("|----MENU -> INGRESOS --------------------|\n");
        printf("---------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Cargar Ingreso \n");
        printf("2. Dar de baja un Ingreso \n");
        printf("3. Modificar Ingreso \n");
        printf("4. Listado de Ingresos \n");
        printf("5. Listado de Ingresos por fecha\n");
        printf("0. Volver al menu anterior \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            printf("Ingrese el dni del paciente: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                pacienteBuscado->ingresos = altaIngreso(pacienteBuscado->ingresos, dni);
                printf("1. Cargar una practica \n");
                printf("0. Volver \n");
                scanf("%i",&eleccion);
                fflush(stdin);
                if(eleccion != 0)
                {
                    if(eleccion == 1)
                    {
                        pacienteBuscado->ingresos->practicas = altaPxI(pacienteBuscado->ingresos->practicas, pacienteBuscado->ingresos->ingreso.nroDeIngreso);
                        printf("Practica cargada con exito. \n");
                    }
                    else
                    {
                        printf("Error. \n");
                    }
                }
            }
            else
            {
                printf("404. Paciente not found \n");
            }
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Ingrese el dni del paciente: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                pacienteBuscado->ingresos = bajaIngreso(pacienteBuscado->ingresos);
            }
            else
            {
                printf("404. Paciente not found \n");
            }
            system("pause");
            system("cls");
            break;
        case 3:
            printf("Ingrese el dni del paciente buscado: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes,dni);
            if(pacienteBuscado!=NULL)
            {
                pacienteBuscado->ingresos = modificacionIngreso(pacienteBuscado->ingresos);
            }
            else
            {
                printf("404. Paciente not found \n");
            }
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Ingrese el dni del paciente buscado: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes,dni);
            if(pacienteBuscado!=NULL)
            {
                listadoIngresosAlta(pacienteBuscado->ingresos);
            }
            else
            {
                printf("404. Paciente not found \n");
            }
            system("pause");
            system("cls");
            break;
        case 5:
            printf("Ingrese el dni del paciente buscado: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes,dni);
            if(pacienteBuscado!=NULL)
            {
                listadoIngresosRangoFechas(pacienteBuscado->ingresos);
            }
            else
            {
                printf("404. Paciente not found \n");
            }
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            printf("Opcion Incorrecta \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
    return arbolPacientes;
}

//5.MENU SECRETARIA - OPCIONES DE PRACTICAS
nodoPac * menuSecretariaPracticasOp(nodoPac * arbolPacientes)
{
    int option;
    int dni;
    nodoPac * pacienteBuscado;
    nodoIngreso * ingresoBuscado;
    int id;
    do
    {
        printf("---------------------------------------------\n");
        printf("|----MENU -> PRACTICAS --------------------|\n");
        printf("---------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Dar de alta una practica \n");
        printf("2. Dar de baja una practica\n");
        printf("3. Modificar una practica\n");
        printf("4. Listados de practicas de un ingreso\n");
        printf("0. Volver \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            printf("Ingrese el DNI del paciente: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                listadoIngresosAlta(pacienteBuscado->ingresos);
                printf("Ingrese el id del ingreso: \n");
                scanf("%i",&id);
                fflush(stdin);
                ingresoBuscado = BuscarIngreso(pacienteBuscado->ingresos,id);
                if(ingresoBuscado != NULL)
                {
                    ingresoBuscado->practicas = altaPxI(ingresoBuscado->practicas, ingresoBuscado->ingreso.nroDeIngreso);
                    printf("Practica cargada con exito. \n");
                }
                else
                {
                    printf("No se encontro un ingreso con ese id. \n");
                }
            }
            else
            {
                printf("No se encontro el paciente. \n");
            }
            system("pause");
            system("cls");
            break;

        case 2:
            printf("Ingrese el DNI del paciente: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                listadoIngresosAlta(pacienteBuscado->ingresos);
                printf("Ingrese el id del ingreso: \n");
                scanf("%i",&id);
                fflush(stdin);
                ingresoBuscado = BuscarIngreso(pacienteBuscado->ingresos,id);
                if(ingresoBuscado != NULL)
                {
                    ingresoBuscado->practicas = bajaPxI(ingresoBuscado->practicas, ingresoBuscado->ingreso.nroDeIngreso);
                }
                else
                {
                    printf("No se encontro un ingreso con ese id. \n");
                }
            }
            else
            {
                printf("No se encontro el paciente. \n");
            }
            system("pause");
            system("cls");
            break;

        case 3:
            printf("Ingrese el DNI del paciente: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                listadoIngresosAlta(pacienteBuscado->ingresos);
                printf("Ingrese el id del ingreso: \n");
                scanf("%i",&id);
                fflush(stdin);
                ingresoBuscado = BuscarIngreso(pacienteBuscado->ingresos,id);
                if(ingresoBuscado != NULL)
                {
                    ingresoBuscado->practicas = modificacionPxI(ingresoBuscado->practicas);
                }
                else
                {
                    printf("No se encontro un ingreso con ese id. \n");
                }
            }
            else
            {
                printf("No se encontro el paciente. \n");
            }
            system("pause");
            system("cls");
            break;

        case 4:
            printf("Ingrese el DNI del paciente: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                if(pacienteBuscado->ingresos == NULL){
                    printf("No tiene ingresos cargados\n");
                }else{
                    listadoIngresosAlta(pacienteBuscado->ingresos);
                    printf("Ingrese el id del ingreso: \n");
                    scanf("%i",&id);
                    fflush(stdin);
                    ingresoBuscado = BuscarIngreso(pacienteBuscado->ingresos,id);
                    if(ingresoBuscado != NULL)
                    {
                        mostrarListaPxI(ingresoBuscado->practicas);
                    }
                    else
                    {
                        printf("No se encontro un ingreso con ese id. \n");
                    }
                }
            }
            else
            {
                printf("No se encontro el paciente. \n");
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



//6.MENU SECRETARIA - LABORATORIO
void menuSecretariaLaboratorio(empleados_laboratorio administrativo)
{
    int option;
    char perfil[20];
    strcpy(perfil, "laboratorio");

    do
    {
        printf("---------------------------------------------\n");
        printf("|----MENU -> LABORATORIO --------------------|\n");
        printf("---------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Listado Personal de Laboratorio \n");
        printf("2. Listado Analisis Clinicos \n");
        printf("0. Volver al menu anterior \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            listadoEmpleadosAlta(administrativo, perfil);
            system("pause");
            system("cls");
            break;
        case 2:
            mostrarPracticasOrdenadas();
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            printf("Opcion Incorrecta \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
}
