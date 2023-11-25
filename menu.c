#include "menu.h"
#include "menuAdmin.h"
#include "menuSecretaria.h"
#include "menuLaboratorio.h"
#include "home.h"
#include "pacientes.h"
#include "usuario.h"
#include "gotoxy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------//
//MENU PRINCIPAL//
//-----------------------------//
void menuPrincipal()
{
    nodoPac * arbolPacientes;
    arbolPacientes = inicArbolPacientes();
    arbolPacientes = inicioDeSistema();
    empleados_laboratorio usuario;


    int option = 1;
    do
    {   printf("/////////////////////////////////////////////\n");
        printf("//          BIENVENIDOS A APPLab           //\n");
        printf("//    Laboratorio de Analisis Clinicos     //\n");
        printf("/////////////////////////////////////////////\n");
        printf("\n");
        printf("1. Inicio de sesion\n");
        printf("0. Salir del programa\n");
        printf("\n");
        fflush(stdin);
        if(scanf("%i",&option) != 1){
            option = 80;
        }
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            usuario = iniciarSesion();
            system("cls");
            if(usuario.alta != -1)
            {
                if(strcmpi(usuario.perfil, "administrador") == 0)
                {
                    printf("---------------------------------------------\n");
                    printf("!Hola, admin %s!\n", usuario.apellidoYnombre);
                    printf("---------------------------------------------\n");
                    arbolPacientes = menuAdmin(usuario, arbolPacientes);
                    system("cls");
                }
                if(strcmpi(usuario.perfil, "laboratorio") == 0)
                {
                    printf("---------------------------------------------\n");
                    printf("!Hola, %s! \n", usuario.apellidoYnombre);
                    printf("---------------------------------------------\n");
                    arbolPacientes = menuLaboratorio(usuario, arbolPacientes);
                    system("cls");
                }
                if(strcmpi(usuario.perfil, "administrativo") == 0)
                {
                    printf("---------------------------------------------\n");
                    printf("!Hola, %s! \n", usuario.apellidoYnombre);
                    printf("---------------------------------------------\n");
                    arbolPacientes = menuSecretaria(usuario, arbolPacientes);
                    system("cls");
                }
            }
            system("pause");
            system("cls");
            break;

        case 0:
            printf("!Gracias por su visita! \n");
            system("pause");
            system("cls");
            break;

        default:
            printf("La opcion que ha seleccionado no es valida. \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option != 0);
    cierreDeSistema(arbolPacientes);
}
