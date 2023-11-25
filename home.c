
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
empleados_laboratorio iniciarSesion()
{
    empleados_laboratorio usuario;
    char username[20];
    char contrasenia[20];
    printf("Ingrese su username: \n");
    fflush(stdin);
    gets(username);
    usuario = buscarEmpleadoEnArchivoUsername(username);

    if(usuario.alta == -1)
    {
        printf("No se encuentra registrado. \n");
        system("pause");
        return usuario;
    }
    printf("Ingrese su contrasenia \n");
    pedirContrasenia(contrasenia);
    usuario = buscarEmpleadoLogin(usuario.dni, contrasenia);
    if(usuario.alta == -1){
        printf("Contrasenia incorrecta \n");
        system("pause");
    }
    return usuario;
}
//2. REGISTRO DE USUARIO
void registrarUsuario(char perfil[20])
{
    empleados_laboratorio usuario;
    char dni[20];
    printf("Ingrese el DNI:  \n");
    fflush(stdin);
    gets(dni);
    usuario = buscarEmpleadoEnArchivo(dni);

    if(usuario.alta == -1)
    {
        usuario = cargaEmpleado(perfil, dni);
        altaEmpleado(usuario);
        printf("Usuario registrado exitosamente! \n");
    }
    else
    {
        printf("El usuario ya existe \n");
    }
}
//3. PACIENTES AL ARBOL DE LISTAS
nodoPac *inicioDeSistema()
{

    FILE* archivoIngreso = fopen("ArchivoIngresos.bin","rb");
    FILE* archivoPxI = fopen("ArchivoPracticasXIngreso.bin","rb");
    ingreso ing;
    pracXingreso pxi;
    nodoPac* aux;
    nodoIngreso *nodoNuevo;
    nodoIngreso* aux2;
    nodoPxi* nodoNuevo2;

    nodoPac *arbolPaciente = NULL;
    arbolPaciente = pasarArchivoArbol();

    if(archivoIngreso!=NULL && archivoPxI !=NULL)
    {
        while(fread(&ing,sizeof(ingreso), 1, archivoIngreso))
        {
            aux = buscarPacXdni(arbolPaciente,ing.dniPaciente);
            nodoNuevo = crearNodoIngreso(ing);
            aux->ingresos = agregarNodoPpioIngreso(aux->ingresos, nodoNuevo);

            rewind(archivoPxI);
            while(fread(&pxi,sizeof(pracXingreso), 1, archivoPxI))
            {
                if(pxi.NroDeIngreso == aux->ingresos->ingreso.nroDeIngreso)
                {
                    aux2 = BuscarIngreso(aux->ingresos, ing.nroDeIngreso);
                    nodoNuevo2 = crearNodoPxI(pxi);
                    aux2->practicas = agregarAlPrincipioPxI(aux2->practicas, nodoNuevo2);
                }
            }
        }
    }


    return arbolPaciente;
}

//4. ARBOL DE PACIENTES A ARCHIVO
void cierreDeSistema(nodoPac* arbolPacientes)
{

    FILE* archivoIngreso = fopen("ArchivoIngresos.bin","wb");
    FILE* archivoPxI = fopen("ArchivoPracticasXIngreso.bin","wb");
    FILE* archivoPacientes = fopen("ArchivoPacientes.bin","wb");

    pasarInfoAArchivos(arbolPacientes, archivoPacientes, archivoIngreso, archivoPxI);


    fclose(archivoPacientes);
    fclose(archivoIngreso);
    fclose(archivoPxI);


    liberarArbolPacientes(arbolPacientes);

}

//5. LIBERADO DEL ARBOL DE PACIENTES
void pasarInfoAArchivos(nodoPac* arbolPacientes, FILE* archivoPacientes, FILE* archivoIngreso, FILE* archivoPxI)
{

    if (arbolPacientes != NULL)
    {
        pasarInfoAArchivos(arbolPacientes->izquierda,archivoPacientes, archivoIngreso, archivoPxI);

        fwrite(&(arbolPacientes->pac),sizeof(pacientes),1,archivoPacientes);

        while(arbolPacientes->ingresos != NULL)
        {
            fwrite(&(arbolPacientes->ingresos->ingreso),sizeof(ingreso),1,archivoIngreso);
            while(arbolPacientes->ingresos->practicas != NULL)
            {
                fwrite(&(arbolPacientes->ingresos->practicas->pxi),sizeof(pracXingreso),1,archivoPxI);
                arbolPacientes->ingresos->practicas = arbolPacientes->ingresos->practicas->siguiente;
            }
            arbolPacientes->ingresos = arbolPacientes->ingresos->siguiente;
        }

        pasarInfoAArchivos(arbolPacientes->derecha, archivoPacientes, archivoIngreso, archivoPxI);
    }
}
