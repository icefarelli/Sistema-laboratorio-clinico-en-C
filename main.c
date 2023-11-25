#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "usuario.h"


int main()
{

//CREACION ADMIN
/*
empleados_laboratorio admin;
char dni[20];
printf("Ingrese su dni \n");
fflush(stdin);
gets(dni);
admin = buscarEmpleadoEnArchivo(dni);
if(admin.alta == -1){

    admin = cargaEmpleado("administrador", dni);
    altaEmpleado(admin);
    printf("Admin registrado exitosamente \n");
}else{
printf("Usuario registrado \n");
}
*/

    menuPrincipal();
    return 0;
}
