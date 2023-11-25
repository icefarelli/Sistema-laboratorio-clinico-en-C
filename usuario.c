#include "usuario.h"
#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------//
//FUNCIONES USUARIO//
//-----------------------------//0.


//1.BUSQUEDA EMPLEADO X DNI
empleados_laboratorio buscarEmpleadoEnArchivo(char dni[20])
{
    empleados_laboratorio e;
    empleados_laboratorio empleado;
    empleado.alta = -1;
    FILE * buffer = fopen("empleados_laboratorio.dat", "rb");
    int dniConvertido = convertirCharAInt(dni);
    if(buffer)
    {
        while(fread(&e,sizeof(empleados_laboratorio),1,buffer))
        {
            if(e.dni == dniConvertido)
            {
                return e;
            }
        }
        fclose(buffer);
    }
    return empleado;
}
//2.ALTA EMPLEADO
void altaEmpleado(empleados_laboratorio empleado)
{
    FILE * buffer = fopen("empleados_laboratorio.dat", "ab");
    if(buffer)
    {
        fwrite(&empleado,sizeof(empleados_laboratorio),1, buffer);
        fclose(buffer);
    }
}

//3. BAJA EMPLEADO
empleados_laboratorio bajaLogica(empleados_laboratorio empleado)
{
    char dni[20];
    convertirIntAChar(dni,empleado.dni);
    empleado = buscarEmpleadoEnArchivo(dni);
    if(empleado.alta == 1)
    {
        printf("Dando de baja.....\n");
        empleado.alta = 0;
        printf("Operacion exitosa. \n");
    }
    else
    {
        printf("El usuario ya esta dado de baja.....\n");
    }
    return empleado;
}
//3. BAJA EMPLEADO  - ALTA EMPLEADO
empleados_laboratorio bajaAltaLogica(empleados_laboratorio empleado)
{
    char dni[20];
    convertirIntAChar(dni,empleado.dni);
    empleado = buscarEmpleadoEnArchivo(dni);
    if(empleado.alta != -1)
    {
        if(empleado.alta == 1)
        {
            printf("Dando de baja.....\n");
            empleado.alta = 0;
        }
        if(empleado.alta == 0)
        {
            printf("Dando de alta.....\n");
            empleado.alta = 1;
        }
    }
    return empleado;
}

//4. MOSTRAR EMPLEADO
void mostrarEmpleado(empleados_laboratorio empleado)
{
    printf("Nombre de usuario: %s\n",empleado.usuario);
    printf("Apellido y nombre: %s\n",empleado.apellidoYnombre);
    printf("Dni: %i\n",empleado.dni);
}

//5. LISTADO EMPLEADOS
void listadoEmpleadosAlta(empleados_laboratorio empleado, char perfil[20]) //SE LE PASA YA QUE SI ES ADMIN SE MUESTRA MAS INFORMACION
{
    empleados_laboratorio e;
    FILE * buffer = fopen("empleados_laboratorio.dat", "rb");
    if(buffer)
    {
        while(fread(&e,sizeof(empleados_laboratorio),1,buffer))
        {
            if(e.alta == 1 && strcmp(e.perfil,perfil)==0)
            {

                printf("------------------------------------------------------\n");
                mostrarEmpleado(e);
                if(strcmpi(empleado.perfil, "administrador") == 0)
                {
                    printf("Tipo: %s\n",e.perfil);
                }
                printf("------------------------------------------------------\n");
            printf("\n");
            }
        }
        fclose(buffer);
    }
}

//6. LISTADO EMPLEADOS BAJA
void adMostrarListadoEmpleadosBaja(char perfil[20])
{
    empleados_laboratorio e;
    e.alta = -1;
    FILE * buffer = fopen("empleados_laboratorio.dat", "rb");
    if(buffer)
    {
        while(fread(&e,sizeof(empleados_laboratorio),1,buffer))
        {
            if(e.alta == 0 && strcmp(e.perfil,perfil)==0)
            {
                printf("------------------------------------------------------\n");
                mostrarEmpleado(e);
                printf("------------------------------------------------------\n");
                printf("\n");
            }
        }
        fclose(buffer);
    }
}
//7. LISTADO EMPLEADOS TODOS
void adMostrarListadoEmpleadosTodos(char perfil[20])
{
    empleados_laboratorio e;
    e.alta = -1;
    FILE * buffer = fopen("empleados_laboratorio.dat", "rb");
    if(buffer)
    {
        while(fread(&e,sizeof(empleados_laboratorio),1,buffer))
        {
            if(e.alta == 1 && strcmp(e.perfil,perfil)==0)
            {
                printf("\n");
                printf("------------------------------------------------------\n");
                mostrarEmpleado(e);
                printf("Tipo: %s\n",e.perfil);
                if(e.alta == 1)
                {
                    printf("ACTIVO\n");
                }
                if(e.alta == 0)
                {
                    printf("ELIMINADO\n");
                }
                printf("------------------------------------------------------\n");

            }

        }
        fclose(buffer);
    }
}
//8. CONTAR CANTIDAD USUARIOS
int contarCantidadUsuarios()
{
    FILE* buffer = fopen("empleados_laboratorio.dat", "rb");
    int i = 1;
    if(buffer)
    {
        fseek(buffer, 0, SEEK_END);
        i = (int) ftell(buffer) / sizeof(empleados_laboratorio);
        fclose(buffer);
    }
    return i;
}
//9. PEDIR CONTRASENIA
void pedirContrasenia(char contrasenia[20])
{
    char ch;
    int i = 0;

    while (1)
    {
        ch = getch();
        if (ch == '\r') // Si se presiona el enter
            break;

        if(ch == '\b')   //Si se presiona el retroceso
        {
            if(i<=0)
                continue;
            putch('\b');
            putch(' ');
            putch('\b');
            contrasenia[i] = '\0';
            i--;
            continue;
        }

        printf("*");
        contrasenia[i] = ch;
        i++;
    }

    contrasenia[i] = '\0';
    printf("\n");
}
//10. CARGAR CONTRASENIA
empleados_laboratorio cargarContraseniaRegistro(empleados_laboratorio empleado)
{
    char contrasenia[20];
    char confirmacion[20];
    printf("Ingrese su nueva contrasenia:  \n");
    pedirContrasenia(contrasenia);
    while(!validarLenghtContrasenia(contrasenia))
    {
        printf("La contrasenia es muy corta \n");
        printf("Ingrese su nueva contrasenia:  \n");
        pedirContrasenia(contrasenia);
    }
    printf("Vuelva a ingresar su contrasenia \n");
    pedirContrasenia(confirmacion);
    while(!validarContrasenia(contrasenia, confirmacion))
    {
        printf("Las contrasenias no coinciden\n");
        pedirContrasenia(contrasenia);
        while(!validarLenghtContrasenia(contrasenia))
        {
            printf("La contrasenia es muy corta \n");
            printf("Ingrese su nueva contrasenia:  \n");
            pedirContrasenia(contrasenia);
        }
        printf("Vuelva a ingresar su contrasenia \n");
        pedirContrasenia(confirmacion);
    }
    strcpy(empleado.password, contrasenia);
    return empleado;
}
//11. BUSCA AL USUARIO PARA INICIAR SESION
empleados_laboratorio buscarEmpleadoLogin(int dni, char contrasenia[30])
{
    empleados_laboratorio e;
    empleados_laboratorio empleado;
    empleado.alta = -1;
    FILE * buffer = fopen("empleados_laboratorio.dat", "rb");
    if(buffer)
    {
        while(fread(&e,sizeof(empleados_laboratorio),1,buffer))
        {
            if(e.dni == dni && strcmp(e.password, contrasenia)==0)
            {
                return e;
            }
        }
        fclose(buffer);
    }
    return empleado;
}
//12.CARGAR EMPLEADO
empleados_laboratorio cargaEmpleado(char perfil[20], char dni[20])
{
    empleados_laboratorio usuario;
    empleados_laboratorio nombreUsuario;
    strcpy(usuario.perfil, perfil);
    usuario.alta = 1;

    while(!validarDNI(dni))
    {
        printf("Error. Formato invalido\n");
        printf("Ingrese nuevamente su DNI: \n");
        fflush(stdin);
        gets(dni);
    }
    usuario.dni = convertirCharAInt(dni);

    printf("Username: \n");
    fflush(stdin);
    gets(usuario.usuario);
    nombreUsuario = buscarEmpleadoEnArchivoUsername(usuario.usuario);
    while(nombreUsuario.alta != -1)
    {
        printf("Lo sentimos, ese nombre de usuario ya ha sido registrado \n");
        printf("Username: \n");
        fflush(stdin);
        gets(usuario.usuario);
        nombreUsuario = buscarEmpleadoEnArchivoUsername(usuario.usuario);
    }
    while(!validarUsername(usuario.usuario))
    {
        printf("Error. Username invalido. Solo Minusculas y sin espacios\n");
        printf("Username: \n");
        fflush(stdin);
        gets(usuario.usuario);

    }
    while(!validarLenght(usuario.usuario, 5))
    {
        printf("Error. Username muy corto. \n");
        fflush(stdin);
        printf("Username: \n");
        gets(usuario.usuario);
    }

    printf("Apellido y nombre: \n");
    fflush(stdin);
    gets(usuario.apellidoYnombre);
    while(!validarStringNombre(usuario.apellidoYnombre))
    {
        printf("Error. Nombre Invalido. \n");
        printf("Apellido y nombre: \n");
        fflush(stdin);
        gets(usuario.apellidoYnombre);
    }
    while(!validarLenght(usuario.apellidoYnombre, 5))
    {
        printf("Error. Nombre muy corto. \n");
        fflush(stdin);
        printf("Apellido y Nombre: \n");
        gets(usuario.apellidoYnombre);
    }



    usuario = cargarContraseniaRegistro(usuario);
    return usuario;
}
//13.BUSQUEDA EMPLEADO X USERNAME
empleados_laboratorio buscarEmpleadoEnArchivoUsername(char username[20])
{
    empleados_laboratorio e;
    empleados_laboratorio empleado;
    empleado.alta = -1;
    FILE * buffer = fopen("empleados_laboratorio.dat", "rb");
    if(buffer)
    {
        while(fread(&e,sizeof(empleados_laboratorio),1,buffer))
        {
            if(strcmp(e.usuario, username)==0)
            {
                return e;
            }
        }
        fclose(buffer);
    }
    return empleado;
}
//14. MODIFICAR USUARIO
empleados_laboratorio modificarUsuario(char dniChar[20], empleados_laboratorio esAdmin)
{
    int eleccion;
    empleados_laboratorio aux;
    int flag=0;
    int dni = convertirCharAInt(dniChar);
    FILE * buffer;
    buffer = fopen("empleados_laboratorio.dat", "r+b" );
    if(buffer)
    {
        while (flag==0 && (fread(&aux, sizeof(empleados_laboratorio),1, buffer)) > 0)
        {
            if(aux.dni ==  dni)
            {
                flag=1;
            }
        }
        if(flag == 1)
        {
            mostrarEmpleado(aux);

            printf("Que quiere modificar?\n");
            printf("1. Dni \n");
            printf("2. Apellido y nombre \n");
            printf("3. Username \n");
            printf("4. Password \n");
            if(strcmpi(esAdmin.perfil,"administrador")==0)
            {
                printf("5. Perfil \n");
            }
            if(scanf("%d",&eleccion) != 1){
            eleccion = 8;
            }
            if(eleccion==1)
            {
                printf("Ingrese el nuevo dni: \n");
                fflush(stdin);
                gets(dniChar);
                while(!validarDNI(dniChar))
                {
                    printf("Error. Formato invalido\n");
                    printf("Ingrese nuevamente su DNI: \n");
                    fflush(stdin);
                    gets(dniChar);
                }
                aux.dni = convertirCharAInt(dniChar);
            }
            else if(eleccion==2)
            {
                printf("Ingrese el nuevo Apellido y nombre: \n");
                fflush(stdin);
                gets(aux.apellidoYnombre);
                while(!validarStringNombre(aux.apellidoYnombre))
                {
                    printf("Error. Nombre Invalido. \n");
                    printf("Apellido y nombre: \n");
                    fflush(stdin);
                    gets(aux.apellidoYnombre);
                }
            }
            else if (eleccion==3)
            {
                printf("Ingrese el nuevo Username: \n");
                fflush(stdin);
                gets(aux.usuario);
                while(!validarStringNombre(aux.usuario))
                {
                    printf("Error. Username invalido. \n");
                    printf("Username: \n");
                    fflush(stdin);
                    gets(aux.usuario);
                }
                while(!validarLenght(aux.usuario, 5))
                {
                    printf("Error. Username muy corto. \n");
                    fflush(stdin);
                    printf("Username: \n");
                    gets(aux.usuario);
                }
            }
            else if (eleccion==4)
            {
                aux = cargarContraseniaRegistro(aux);
            }
            else if (eleccion==5)
            {
                if(strcmp(esAdmin.perfil,"administrador")==0)
                {
                    do{
                    printf("Ingrese el nuevo perfil del usuario: \n");
                    printf("1. Administrador \n");
                    printf("2. Personal Administrativo \n");
                    printf("3. Personal de Laboratorio \n");
                    printf("0. Volver atras \n");
                    fflush(stdin);
                    if(scanf("%i",&eleccion)!=1){
                            eleccion=98;
                    }
                    fflush(stdin);

                    switch(eleccion)
                    {
                    case 1:
                        strcpy(aux.perfil,"administrador");
                        printf("El usuario ahora tiene perfil de administrador \n");
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        strcpy(aux.perfil,"administrativo");
                        printf("El usuario ahora tiene perfil de administrativo \n");
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        strcpy(aux.perfil,"laboratorio");
                        printf("El usuario ahora tiene perfil de personal de laboratorio \n");
                        system("pause");
                        system("cls");
                        break;
                    case 0:
                        system("pause");
                        system("cls");
                        break;
                    default:
                        printf("Opcion incorrecta \n");

                        system("cls");
                        break;
                    }
                    }while (eleccion != 1 && eleccion != 2 && eleccion != 3 && eleccion != 0);
                }
                else
                {
                    printf("Usted no tiene permiso para modificar el perfil \n");
                }
            }
            else
            {
                printf("la opcion es incorrecta \n");
            }

            fseek(buffer,sizeof(empleados_laboratorio)*(-1), SEEK_CUR);
            fwrite(&aux,sizeof(empleados_laboratorio),1, buffer);
            fclose(buffer);
        }
        if(flag == 0)
        {
            printf("Usuario no encontrado \n");
        }
    }

    return aux;
}
//15. DAR DE ALTA UN USUARIO QUE ESTABA DADO DE BAJA
empleados_laboratorio altaLogica(empleados_laboratorio empleado)
{
    char dni[20];
    convertirIntAChar(dni,empleado.dni);
    empleado = buscarEmpleadoEnArchivo(dni);
    if(empleado.alta == 0)
    {
        printf("Dando de alta.....\n");
        empleado.alta = 0;
        printf("Operacion exitosa. \n");
    }
    else
    {
        printf("El usuario ya esta dado de alta....\n");
    }
    return empleado;
}
