#include "usuario.h"
#include "menuAdmin.h"
#include "home.h"
#include "ingresos.h"
#include "practicas.h"
#include "practicasXingreso.h"
//1. MENU PRINCIPAL ADMIN
nodoPac * menuAdmin(empleados_laboratorio admin, nodoPac * arbolPacientes)
{
    empleados_laboratorio *ptr_admin = &admin;
    empleados_laboratorio aux;
    int option = 1;
    int eleccion;
    char dniChar[20];
    do
    {
        printf("--------------\n");
        printf("|----MENU----|\n");
        printf("--------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Registrar un empleado\n");
        printf("2. Configuracion\n");
        printf("3. Mi perfil\n");
        printf("0. Salir de mi sesion\n");
        printf("--------------------------\n");
        fflush(stdin);

        if(scanf("%i",&option) != 1){
            option = 80;
        }

        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            adMenuRegistro();
            system("pause");
            system("cls");
            break;

        case 2:
            arbolPacientes = adMenuConfiguracion(arbolPacientes, admin);
            system("pause");
            system("cls");
            break;


        case 3:
            printf("------------\n");
            printf("Mi perfil:  \n");
            printf("------------\n");
            printf("\n");
            mostrarEmpleado(*ptr_admin);
            printf("Tipo de usuario: %s\n", ptr_admin->perfil);
            printf("\n");
            printf("1. Modificar mi perfil\n");
            printf("0. Volver\n");
            scanf("%i",&eleccion);
            fflush(stdin);
            if(eleccion == 1)
            {
                //esta función originalmente trabajaba únicamente a base de
                //copias, pero parchee las funciones para que haya de intermediario un
                //puntero que se encargue de mostrar la información

                //esto es para que no se buguee mostrando información desactualizada al
                //entrar de vuelta luego de una modificación
                convertirIntAChar(dniChar, ptr_admin->dni);
                aux = modificarUsuario(dniChar, *ptr_admin);
                ptr_admin = &aux;
            }
            system("pause");
            system("cls");
            break;

        case 0:
            system("cls");
            break;

        default:
            printf("Opcion no valida \n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option != 0);
    return arbolPacientes;
}
//2. MENU REGISTRO ADMIN
void adMenuRegistro()
{
    int opcion = -1;
    char perfil[20];
    while(opcion!=1 && opcion !=2 && opcion!=3 && opcion!=0)
    {
        printf("Seleccione el perfil del usuario: \n");
        printf("------------------------------------\n");
        printf("1. Personal Administrativo \n2. Personal de Laboratorio\n3. Administrador de sistema\n0. Volver atras\n");
        printf("------------------------------------\n");
        scanf("%i",&opcion);
        fflush(stdin);
        system("cls");
        switch(opcion)
        {
        case 0:
            system("cls");
            break;
        case 1:
            strcpy(perfil,"administrativo");
            system("cls");
            registrarUsuario(perfil);
            break;
        case 2:
            strcpy(perfil,"laboratorio");
            system("cls");
            registrarUsuario(perfil);
            break;
        case 3:
            strcpy(perfil,"administrador");
            system("cls");
            registrarUsuario(perfil);
            break;
        default:
            printf("Opcion incorrecta \n");
            system("cls");
            break;
        }
    }

}
//3. MENU CONFIGURACION ADMIN
nodoPac * adMenuConfiguracion(nodoPac * arbolPacientes, empleados_laboratorio admin)
{
    int option;
    do
    {
        printf("----------------------------\n");
        printf("|----MENU CONFIGURACION----|\n");
        printf("----------------------------\n");
        printf("\n");
        printf("---------------------------\n");
        printf("1. Pacientes\n");
        printf("2. Laboratorio\n");
        printf("3. Secretaria\n");
        printf("0. Volver \n");
        printf("---------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            arbolPacientes = adMenuPacientes(arbolPacientes);
            system("pause");
            system("cls");
            break;

        case 2:
            arbolPacientes = adMenuLaboratorio(admin, arbolPacientes);
            system("pause");
            system("cls");
            break;

        case 3:
            arbolPacientes = adMenuSecretaria(arbolPacientes, admin);
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
//4. MENU PACIENTES ADMIN
nodoPac * adMenuPacientes(nodoPac * arbolPacientes)
{
    int option;
    do
    {
        printf("-----------------------------------------\n");
        printf("|----MENU CONFIGURACION -> PACIENTES----|\n");
        printf("-----------------------------------------\n");
        printf("\n");
        printf("---------------------------\n");
        printf("1. Pacientes\n");
        printf("2. Ingresos del paciente\n");
        printf("3. Practicas del paciente\n");
        printf("0. Volver\n");
        printf("--------------------------\n");
            fflush(stdin);
        if(scanf("%i",&option) != 1){
            option = 8;
        }
        system("cls");
        switch(option)
        {
        case 1:
            arbolPacientes = adMenuPacientesPacientes(arbolPacientes);
            system("pause");
            system("cls");
            break;

        case 2:
            arbolPacientes = adMenuPacientesIngresos(arbolPacientes);
            system("pause");
            system("cls");
            break;

        case 3:
            arbolPacientes = adMenuPacientesPracticas(arbolPacientes);
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
//5. MENU PACIENTES ADMIN - PACIENTE
nodoPac * adMenuPacientesPacientes(nodoPac * arbolPacientes)
{
    pacientes paciente;
    nodoPac* pacienteEncontrado;
    int option;
    char valid_dni[10];
    int dni;
    do
    {
        printf("-----------------------------------------\n");
        printf("|------MENU PACIENTES -> PACIENTES------|\n");
        printf("-----------------------------------------\n");
        printf("\n");
        printf("---------------------------\n");
        printf("1. Dar de alta a un paciente\n");
        printf("2. Dar de baja a un paciente\n");
        printf("3. Modificar un paciente\n");
        printf("4. Listado de pacientes por dni\n");
        printf("5. Listado de pacientes por nombre\n");
        printf("6. Ver inforacion de paciente\n");
        printf("0. Volver \n");
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
            do{
                printf("Ingrese el dni del paciente que desea eliminar: \n");
                fflush(stdin);
                gets(valid_dni);
                dni=validar_DNI(valid_dni);
                if(validar_DNI(valid_dni)==0){
                    printf("DNI no valido. Ingresar hasta 8 caracteres numericos enteros.\n");
                    system("pause");
                    system("cls");
                }
                }while(validar_DNI(valid_dni)==0);

            arbolPacientes = bajaPacientes(arbolPacientes, dni);
            printf("Paciente %s de Baja \n", paciente.NyA);
            system("pause");
            system("cls");
            break;

        case 3:
            do{
                printf("Ingrese el dni del paciente que desea modificar: \n");
                fflush(stdin);
                gets(valid_dni);
                dni=validar_DNI(valid_dni);
                if(validar_DNI(valid_dni)==0){
                    printf("DNI no valido. Ingresar hasta 8 caracteres numericos enteros.\n");
                    system("pause");
                    system("cls");
                }
                }while(validar_DNI(valid_dni)==0);

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
            printf("Error...\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(option!=0);
    return arbolPacientes;
}
//6. MENU PACIENTES ADMIN - INGRESO
nodoPac * adMenuPacientesIngresos(nodoPac * arbolPacientes)
{
    int option;
    int dni;
    nodoPac * pacienteBuscado;
    do
    {
        printf("-----------------------------------------\n");
        printf("|------MENU PACIENTES -> INGRESOS ------|\n");
        printf("-----------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Dar de alta un ingreso\n");
        printf("2. Dar de baja un ingreso\n");
        printf("3. Modificar un ingreso\n");
        printf("4. Listado de Ingresos alta de un paciente\n");
        printf("5. Listado de Ingresos baja de un paciente\n");
        printf("6. Listado de Ingresos de un paciente\n");
        printf("7. Listado de Ingresos por fecha\n");
        printf("0. Volver \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            printf("Ingrese el dni del paciente: \n");
            scanf("%i",&dni);
            pacienteBuscado = buscarPacXdni(arbolPacientes, dni);
            if(pacienteBuscado!=NULL)
            {
                pacienteBuscado->ingresos = altaIngreso(pacienteBuscado->ingresos, dni);
            }
            else
            {
                printf("Paciente no encontrado \n");
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
                printf("Paciente no encontrado \n");
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
                printf("Paciente no encontrado \n");
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
                printf("Paciente no encontrado \n");
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
                listadoIngresosBaja(pacienteBuscado->ingresos);
            }
            else
            {
                printf("Paciente no encontrado \n");
            }
            system("pause");
            system("cls");
            break;
        case 6:
            printf("Ingrese el dni del paciente buscado: \n");
            scanf("%i",&dni);
            fflush(stdin);
            pacienteBuscado = buscarPacXdni(arbolPacientes,dni);
            if(pacienteBuscado!=NULL)
            {
                listadoIngresos(pacienteBuscado->ingresos);
            }
            else
            {
                printf("Paciente no encontrado \n");
            }
            system("pause");
            system("cls");
            break;

        case 7:
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
                printf("Paciente no encontrado \n");
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
//7. MENU PACIENTES ADMIN - PRACTICAS
nodoPac * adMenuPacientesPracticas(nodoPac * arbolPacientes)
{
    int option;
    int dni;
    nodoPac * pacienteBuscado;
    nodoIngreso * ingresoBuscado;
    int id;
    do
    {
        printf("------------------------------------------\n");
        printf("|------MENU PACIENTES -> PRACTICAS ------|\n");
        printf("------------------------------------------\n");
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
//8. MENU LABORATORIO ADMIN
nodoPac * adMenuLaboratorio(empleados_laboratorio admin, nodoPac * arbolPacientes)
{
    int option;
    do
    {
        printf("--------------------------------------------\n");
        printf("|----MENU CONFIGURACION -> LABORATORIO ----|\n");
        printf("--------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Personal \n");
        printf("2. Practicas\n");
        printf("0. Volver \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            adMenuLaboratorioPersonal(admin);
            system("pause");
            system("cls");
            break;

        case 2:
            arbolPacientes = adMenuLaboratorioPracticas(arbolPacientes);
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
//9. MENU LABORATORIO ADMIN - PERSONAL
void adMenuLaboratorioPersonal(empleados_laboratorio admin)
{
    int option;
    char dni[20];
    empleados_laboratorio empleado;
    char perfil[20];
    strcpy(perfil,"laboratorio");
    do
    {
        printf("-------------------------------------------\n");
        printf("|------MENU LABORATORIO -> PERSONAL ------|\n");
        printf("-------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Dar de alta a Personal de Laboratorio\n");
        printf("2. Dar de baja a Personal de Laboratorio\n");
        printf("3. Modificar un Personal de Laboratorio\n");
        printf("4. Listado de a Personal de Laboratorio Alta\n");
        printf("5. Listado de a Personal de Laboratorio Baja\n");
        printf("6. Listado de a Personal de Laboratorio\n");
        printf("0. Volver \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");
        switch(option)
        {
        case 1:
            printf("Ingrese el dni del personal: \n");
            fflush(stdin);
            gets(dni);
            empleado = buscarEmpleadoEnArchivo(dni);
            if(empleado.alta!=-1)
            {
                empleado = altaLogica(empleado);
            }
            else
            {
                printf("No se ha encontrado a el empleado \n");
            }
            system("pause");
            system("cls");
            break;

        case 2:
            printf("Ingrese el dni del personal: \n");
            fflush(stdin);
            gets(dni);
            empleado = buscarEmpleadoEnArchivo(dni);
            if(empleado.alta!=-1)
            {
                empleado = bajaLogica(empleado);
            }
            else
            {
                printf("No se ha encontrado a el empleado \n");
            }
            system("pause");
            system("cls");
            break;

        case 3:
            printf("Ingrese el dni del personal de laboratorio \n");
            fflush(stdin);
            gets(dni);
            empleado = buscarEmpleadoEnArchivo(dni);
            if(empleado.alta != -1)
            {
                convertirIntAChar(dni, empleado.dni);
                modificarUsuario(dni, admin);
            }
            else
            {
                printf("No se ha encontrado el usuario\n");
            }
            system("pause");
            system("cls");
            break;

        case 4:
            listadoEmpleadosAlta(admin,perfil);
            system("pause");
            system("cls");
            break;

        case 5:
            adMostrarListadoEmpleadosBaja(perfil);
            system("pause");
            system("cls");
            break;

        case 6:
            adMostrarListadoEmpleadosTodos(perfil);
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
}
//10. MENU LABORATORIO ADMIN- ANALISIS
nodoPac * adMenuLaboratorioPracticas(nodoPac * arbolPacientes)
{
    int option;
    practicas practica;
    do
    {
        printf("---------------------------------------------\n");
        printf("|------MENU LABORATORIO -> PRACTICAS -------|\n");
        printf("---------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Dar de alta una practica\n");
        printf("2. Dar de baja una practica\n");
        printf("3. Modificar una practica\n");
        printf("4. Listado de practicas\n");
        printf("5. Listado de practicas segun busqueda\n");
        printf("0. Volver \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");

        switch(option)
        {
        case 1:
            altaPractica();
            system("pause");
            system("cls");
            break;

        case 2:
            bajaPractica(arbolPacientes);
            system("pause");
            system("cls");
            break;

        case 3:
            mostrarPracticasOrdenadas();
            practica  = PedirPractica();
            if(practica.nroPractica != -1)
            {
                modificacionPracticas(practica.nroPractica);
            }
            system("pause");
            system("cls");
            break;

        case 4:
            mostrarArchivoPracticas("ArchivoPracticas.bin");
            system("pause");
            system("cls");
            break;

        case 5:
            mostrarParcialPractica();
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
//11. MENU SECRETARIA ADMIN
nodoPac * adMenuSecretaria(nodoPac * arbolPacientes, empleados_laboratorio admin)
{
    int option;
    char dni[20];
    char perfil[20];
    strcpy(perfil,"administrativo");
    empleados_laboratorio empleado;
    do
    {
        printf("-----------------------------------------------\n");
        printf("|----MENU CONFIGURACION -> ADMINISTRACION ----|\n");
        printf("-----------------------------------------------\n");
        printf("\n");
        printf("--------------------------\n");
        printf("1. Dar de alta a Personal Administrativo\n");
        printf("2. Dar de baja a Personal Administrativo\n");
        printf("3. Modificar Personal Administrativo\n");
        printf("4. Listado del Personal Administrativo de Alta\n");
        printf("5. Listado del Personal Administrativo de Baja\n");
        printf("6. Listado del Personal Administrativo (Todos)\n");
        printf("0. Volver \n");
        printf("--------------------------\n");
        scanf("%i",&option);
        fflush(stdin);
        system("cls");

        switch(option)
        {
        case 1:
            printf("Ingrese el dni del personal: \n");
            fflush(stdin);
            gets(dni);
            empleado = buscarEmpleadoEnArchivo(dni);
            if(empleado.alta!=-1)
            {
                empleado = altaLogica(empleado);
            }
            else
            {
                printf("No se ha encontrado a el empleado \n");
            }
            system("pause");
            system("cls");
            break;

        case 2:
            printf("Ingrese el dni del personal: \n");
            fflush(stdin);
            gets(dni);
            empleado = buscarEmpleadoEnArchivo(dni);
            if(empleado.alta!=-1)
            {
                empleado = bajaLogica(empleado);
            }
            else
            {
                printf("No se ha encontrado a el empleado \n");
            }
            system("pause");
            system("cls");
            break;

        case 3:
            convertirIntAChar(dni, empleado.dni);
            modificarUsuario(dni, admin);
            system("pause");
            system("cls");
            break;

        case 4:
            listadoEmpleadosAlta(admin, perfil);
            system("pause");
            system("cls");
            break;

        case 5:
            adMostrarListadoEmpleadosBaja(perfil);
            system("pause");
            system("cls");
            break;

        case 6:
            adMostrarListadoEmpleadosTodos(perfil);
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
