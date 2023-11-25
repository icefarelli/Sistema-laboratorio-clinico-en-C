#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pacientes.h"
#include "ingresos.h"
#include "validaciones.h"
#include "practicasXingreso.h"
#include "home.h"
#include <string.h>

//-----------------------------//
//FUNCIONES PACIENTES//
//-----------------------------//


// Alta_de_paciente: debe verificarse que el mismo no exista antes del alta
// Modificacion_de_paciente
// Baja_de_paciente: debe verificarse que no tenga ingresos asociados
// Listado general de pacientes ordenado por apellido y nombre.
// Consulta de 1 paciente en particular, filtrado por dni.
// Listado de ingresos por paciente (sin detalle de prácticas).
// Consulta de 1 ingreso en particular, filtrado por nro o fecha de ingreso, con detalle de prácticas y resultados obtenidos.


//-----------------------------//
//FUNCIONES PACIENTES//
//-----------------------------//

nodoPac *inicArbolPacientes()
{
    return NULL;
}

//--------------------------------------------------------------------------------------//
//Cargo los datos de un paciente nuevo y retorno una variable con los datos cargados (LLEVA TODAS LAS VALIDACIONES)
//--------------------------------------------------------------------------------------//
pacientes cargaPacientesPorTeclado()
{
    pacientes pac;

    char e1;
    char verif_dni[15];
    char verif_edad[15];
    do
    {

        printf("---------------CARGA DE PACIENTE---------------\n");

        printf("Ingrese DNI: ");
        fflush(stdin);
        gets(verif_dni);

        while(validar_DNI(verif_dni)==0)
        {
            printf("DNI no valido. Ingresar hasta 8 caracteres numericos enteros.\n");
            printf("Ingrese DNI: ");
            fflush(stdin);
            gets(verif_dni);
        }
        pac.DNI = atoi(verif_dni);


        printf("Ingresar apellido y nombre: ");
        fflush(stdin);
        gets(pac.NyA);

        while (validar_NyA(pac.NyA)==-1)
        {
            printf("Datos no valido. Ingresar hasta 40 caracteres alfabeticos.\n");
            printf("Ingresar apellido y nombre: ");
            fflush(stdin);
            gets(pac.NyA);
        }

        printf("Ingrese edad: ");
        gets(verif_edad);
        while(validar_Edad(verif_edad)==0)
        {
            printf("Edad no valida. Ingresar numero entero menor a 120.\n");
            printf("Ingrese edad: ");
            fflush(stdin);
            gets(verif_edad);
        }
        pac.edad = atoi(verif_edad);


        printf("Ingrese direccion: ");
        fflush(stdin);
        gets(pac.direccion);

        while (validar_direccion(pac.direccion)==-1)
        {
            printf("Direccion no valido. Ingresar hasta 30 caracteres alfanumericos.\n");
            printf("Ingrese direccion: ");
            fflush(stdin);
            gets(pac.direccion);
        }

        printf("Ingrese telefono: ");
        fflush(stdin);
        gets(pac.tel);

        while (validar_telefono(pac.tel)==-1)
        {
            printf("Telefono no valido. Ingresar hasta 15 caracteres numericos enteros.\n");
            printf("Ingrese telefono: ");
            fflush(stdin);
            gets(pac.tel);
        }

        pac.elim=0;


        printf("\nVerifique el DNI ingresado, este no podra modificarse posteriormente\n");
        printf("DNI ingresado: %i\n", pac.DNI);
        do
        {
            printf("Es correcto? (s/n): ");
            fflush(stdin);
            scanf("%c",&e1);
        }
        while(e1 !='s' && e1 != 'n');

    }
    while(e1!='s');
    return pac;
}


//------------------------------------//
//Crear nodo en arbol pacientes
//------------------------------------//
nodoPac* crearNodoArbolPac (pacientes datoNuevo)
{
    nodoPac* aux = (nodoPac*)malloc(sizeof(nodoPac));

    aux->pac=datoNuevo;
    aux->derecha=NULL;
    aux->izquierda=NULL;
    aux->ingresos=NULL;
    return aux;
}


///-----------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------//
//Funciones para insertar un nuevo paciente en el arbol paciente BALANCEADO
//-------------------------------------------------------------------------//

// Función para obtener la altura de un nodo
int altura(nodoPac *nodo)
{
    if (nodo == NULL)
        return 0;
    return 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
}

// Función para obtener el máximo de dos números
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Función para realizar una rotación simple a la derecha
nodoPac* rotacionDerecha(nodoPac *y)
{
    nodoPac *x = y->izquierda;
    nodoPac *T2 = x->derecha;

    // Realizar rotación
    x->derecha = y;
    y->izquierda = T2;

    return x;
}

// Función para realizar una rotación simple a la izquierda
nodoPac* rotacionIzquierda(nodoPac *x)
{
    nodoPac *y = x->derecha;
    nodoPac *T2 = y->izquierda;

    // Realizar rotación
    y->izquierda = x;
    x->derecha = T2;

    return y;
}

// Función para obtener el factor de equilibrio de un nodo
int factorEquilibrio(nodoPac *nodo)
{
    if (nodo == NULL)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// Función para actualizar la altura de un nodo
nodoPac* actualizarAltura(nodoPac *nodo)
{
    int alturaIzq = altura(nodo->izquierda);
    int alturaDer = altura(nodo->derecha);

    nodo->altura = max(alturaIzq, alturaDer) + 1;

    return nodo;
}

nodoPac* insertarPacienteEnArbolAVL (nodoPac* arbol, nodoPac* nodoNuevo)
{
// Paso 1: Realizar la inserción en un árbol de búsqueda binaria
    if (arbol == NULL)
    {
        arbol = nodoNuevo;
    }
    else
    {
        if(nodoNuevo->pac.DNI > arbol->pac.DNI)
        {
            arbol->derecha = insertarPacienteEnArbolAVL(arbol->derecha, nodoNuevo);
        }
        else
        {
            arbol->izquierda = insertarPacienteEnArbolAVL(arbol->izquierda, nodoNuevo);
        }
    }

// Paso 2: Actualizar la altura de este nodo
    arbol = actualizarAltura(arbol);

// Paso 3: Obtener el factor de equilibrio de este nodo
    int equilibrio = factorEquilibrio(arbol);

// Paso 4: Realizar rotaciones según el factor de equilibrio
    if (equilibrio > 1)
    {
        if (nodoNuevo->pac.DNI < arbol->izquierda->pac.DNI)
        {
            // Caso: Rotación simple a la derecha
            return rotacionDerecha(arbol);
        }
        else
        {
            // Caso: Rotación doble a la izquierda (izquierda-derecha)
            arbol->izquierda = rotacionIzquierda(arbol->izquierda);
            return rotacionDerecha(arbol);
        }
    }

    if (equilibrio < -1)
    {
        if (nodoNuevo->pac.DNI > arbol->derecha->pac.DNI)
        {
            // Caso: Rotación simple a la izquierda
            return rotacionIzquierda(arbol);
        }
        else
        {
            // Caso: Rotación doble a la derecha (derecha-izquierda)
            arbol->derecha = rotacionDerecha(arbol->derecha);
            return rotacionIzquierda(arbol);
        }
    }



    return arbol;
}


//--------------------------------------------------------------------------------------//
//Inserta los datos cargados en la funcion anterior (YA VERIFICADOS) al arbol y lo retorna.
//--------------------------------------------------------------------------------------//
nodoPac* altaPacientes(nodoPac* arbolPacientes, pacientes pac)
{

    nodoPac* nodoAinsertar = crearNodoArbolPac(pac);
    arbolPacientes = insertarPacienteEnArbolAVL(arbolPacientes, nodoAinsertar);

    return arbolPacientes;
}

//--------------------------------------------------------------------------------------//
//Pasar arbol a archivo
//--------------------------------------------------------------------------------------//

void escribirPacienteEnArchivo(FILE* archivo, pacientes pac)
{
    fwrite(&pac, sizeof(pacientes), 1, archivo);
}


void escribirArbolEnArchivo(nodoPac* arbolPaciente, FILE* archivo)
{
    if (arbolPaciente != NULL)
    {
        // Recorre en orden: izquierda, raíz, derecha
        escribirArbolEnArchivo(arbolPaciente->izquierda, archivo);
        escribirPacienteEnArchivo(archivo, arbolPaciente->pac);
        escribirArbolEnArchivo(arbolPaciente->derecha, archivo);
    }
}

// Función principal para escribir el árbol en el archivo
void escribirArbolEnArchivoPrincipal(nodoPac* arbolPaciente)
{
    FILE* archivo = fopen("ArchivoPacientes.bin", "wb");
    if (archivo != NULL)
    {
        escribirArbolEnArchivo(arbolPaciente, archivo);
    }
    fclose(archivo);
}

//----------------------------------------------//
//Funciones de muestra de arbol
//----------------------------------------------//
void mostrarNodoPac (nodoPac *nodo)
{
    printf("------------------------- \n");
    printf(" Apellido y Nombre: %s \n",nodo->pac.NyA);
    printf(" DNI: %i \n",nodo->pac.DNI);
    printf(" Edad: %i \n",nodo->pac.edad );
    printf(" Direccion: %s \n",nodo->pac.direccion);
    printf(" Telefono: %s \n",nodo->pac.tel);
    printf("------------------------- \n");
}

void preorderPac(nodoPac* arbol)
{
    if (arbol!=NULL)
    {
        if(arbol->pac.elim!=1)          ///CONDICION SI ESTA ACTIVO O NO EL PACIENTE PARA LUEGO MOSTRAR
        {
            mostrarNodoPac(arbol);
        }
        preorderPac(arbol->izquierda);
        preorderPac(arbol->derecha);
    }
}

void inorderPac(nodoPac* arbol)
{
    if (arbol!=NULL)
    {
        inorderPac(arbol->izquierda);

        if(arbol->pac.elim!=1)          ///CONDICION SI ESTA ACTIVO O NO EL PACIENTE PARA LUEGO MOSTRAR
        {
            mostrarNodoPac(arbol);
        }
        inorderPac(arbol->derecha);
    }
}

void posorderPac(nodoPac* arbol)
{
    if (arbol!=NULL)
    {
        posorderPac(arbol->izquierda);
        posorderPac(arbol->derecha);
        if(arbol->pac.elim!=1)          ///CONDICION SI ESTA ACTIVO O NO EL PACIENTE PARA LUEGO MOSTRAR
        {
            mostrarNodoPac(arbol);
        }
    }
}

//---------------------------------------------------------------------------------------------------//
// Pasa los pacientes del archivo al arbol por Nombre. Sirve para listar los pacientes por apellido.
//---------------------------------------------------------------------------------------------------//
nodoPac *pasarArchivoArbolPorNombre()
{

    FILE *archivoP=fopen("ArchivoPacientes.bin","rb");
    pacientes pac;
    nodoPac* aux;
    nodoPac *arbol = NULL;

    if (archivoP!=NULL)
    {
        while(!feof(archivoP))
        {
            fread(&pac,sizeof(pacientes),1,archivoP);
            if (!feof(archivoP))
            {
                aux = crearNodoArbolPac(pac);
                arbol=insertarPacienteEnArbolPorNombre(arbol,aux);
            }
        }
        fclose(archivoP);
    }
    return arbol;
}


//-------------------------------------------------------------------------//
//Inserto un nuevo paciente en el arbol paciente por nombre SIN BALANCEAR
//-------------------------------------------------------------------------//

nodoPac* insertarPacienteEnArbolPorNombre(nodoPac* arbol, nodoPac* nodoNuevo)
{
    if (arbol == NULL)
    {
        arbol = nodoNuevo;
    }
    else
    {
        if(strcmpi(nodoNuevo->pac.NyA,arbol->pac.NyA)>0)
        {
            arbol->derecha = insertarPacienteEnArbolPorNombre(arbol->derecha, nodoNuevo);
        }
        else
        {
            arbol->izquierda = insertarPacienteEnArbolPorNombre(arbol->izquierda, nodoNuevo);
        }
    }
    return arbol;
}

void autoGuardadoPacientes (nodoPac* arbolPacientes){
    FILE* archivoPacientes = fopen("ArchivoPacientes.bin","wb");
    pasarArbolAArchivos(arbolPacientes, archivoPacientes);
    fclose(archivoPacientes);
}



void pasarArbolAArchivos(nodoPac* arbolPacientes, FILE* archivoPacientes)
{

    if (arbolPacientes != NULL)
    {
        pasarArbolAArchivos(arbolPacientes->izquierda,archivoPacientes);

        fwrite(&(arbolPacientes->pac),sizeof(pacientes),1,archivoPacientes);

        pasarArbolAArchivos(arbolPacientes->derecha, archivoPacientes);
    }
}



void mostrarPacientesPorNombre(nodoPac* arbolDNI){
autoGuardadoPacientes(arbolDNI);
nodoPac* arbolPorNombre = NULL;
arbolPorNombre = pasarArchivoArbolPorNombre();

inorderPac(arbolPorNombre);

liberarArbolPacientes(arbolPorNombre);
}

//---------------------------------------------------------------------------------------------------//
// Busca un paciente por DNI y retorna un puntero a él.
// Se pide al usuario el DNI a buscar en el main() y se ingresa por parámetro a esta funcion.
//---------------------------------------------------------------------------------------------------//
nodoPac* buscarPacXdni(nodoPac* arbol, int dni)
{
    nodoPac* rta = NULL;
    if(arbol != NULL)
    {
        if(dni==arbol->pac.DNI)
        {
            rta = arbol;
        }
        else
        {
            if(dni<arbol->pac.DNI)
            {
                rta = buscarPacXdni(arbol->izquierda, dni);
            }
            else
            {
                rta = buscarPacXdni(arbol->derecha, dni);
            }
        }
    }
    return rta;

}

nodoPac* buscarPacXnombre(nodoPac* arbol, char nombre[])
{
    nodoPac* rta = NULL;
    if(arbol != NULL)
    {
        if(strcmpi(nombre,arbol->pac.NyA))
        {
            rta = arbol;
        }
        else
        {
            if(strcmpi(nombre,arbol->pac.NyA)!=0)
            {
                rta = buscarPacXnombre(arbol->izquierda, nombre);
                rta = buscarPacXnombre(arbol->derecha, nombre);
            }
        }
    }
    return rta;
}

//---------------------------------------------------------------------------------------------------//
// Pasa los pacientes del archivo al arbol. Se debe llamar al inicio del programa.
//---------------------------------------------------------------------------------------------------//
nodoPac *pasarArchivoArbol()
{

    FILE *archivoP=fopen("ArchivoPacientes.bin","rb");
    pacientes pac;
    nodoPac* aux;
    nodoPac *arbol = NULL;

    if (archivoP!=NULL)
    {
        while(!feof(archivoP))
        {
            fread(&pac,sizeof(pacientes),1,archivoP);
            if (!feof(archivoP))
            {
                aux = crearNodoArbolPac(pac);
                arbol=insertarPacienteEnArbolAVL(arbol,aux);
            }
        }
        fclose(archivoP);
    }
    return arbol;
}



//---------------------------------------------------------------------------------------------------//
// Modifica algun campo del paciente.
// Se pide al usuario el DNI a buscar en el main() y se ingresa por parámetro a esta funcion.
//---------------------------------------------------------------------------------------------------//
nodoPac* modificacionPacientes(nodoPac* arbolPacientes, int dni)
{
    int opcion;
    char verif_edad[15];
    // Buscamos el paciente con el DNI especificado
    nodoPac *pacienteEncontrado = buscarPacXdni(arbolPacientes, dni);

    // Si el paciente se encontró, mostramos sus datos
    if (pacienteEncontrado != NULL){
        do{
            printf("\n------DATOS DEL PACIENTE A MODIFICAR-----\n");
            printf("DNI: %i\n", pacienteEncontrado->pac.DNI);
            printf("Apellido y nombre: %s\n", pacienteEncontrado->pac.NyA);
            printf("Edad: %i\n", pacienteEncontrado->pac.edad);
            printf("Direccion: %s\n", pacienteEncontrado->pac.direccion);
            printf("Telefono: %s\n", pacienteEncontrado->pac.tel);

            // Solicitamos al usuario que ingrese qué quiere modificar
            printf("\n¿Que desea modificar?\n");
//        printf("1. DNI\n");                     /// EL DNI lo tendria que poder modificar? o carga un nuevo paciente y luego lo borra el admin?
            printf("1. Apellido y nombre\n");
            printf("2. Edad\n");
            printf("3. Direccion\n");
            printf("4. Telefono\n");
            if(pacienteEncontrado->pac.elim==1){
                printf("5. Dar de alta nuevamente\n");
            }
            printf("0. Cancelar\n");
            scanf("%i", &opcion);

            // Modificamos la variable seleccionada
            switch (opcion)
            {
//        case 1:
//            printf("Ingrese el nuevo DNI: ");
//            scanf("%i", &pacienteEncontrado->pac.DNI);
//            break;
            case 1:
                printf("Ingrese el nuevo apellido y nombre: ");
                fflush(stdin);
                gets(pacienteEncontrado->pac.NyA);

                while (validar_NyA(pacienteEncontrado->pac.NyA)==-1)
                {
                    printf("Datos no validos. Ingresar hasta 40 caracteres alfabeticos.\n");
                    printf("Ingresar apellido y nombre: ");
                    fflush(stdin);
                    gets(pacienteEncontrado->pac.NyA);
                }
                break;
            case 2:
                printf("Ingrese la nueva edad: ");
                fflush(stdin);
                gets(verif_edad);

                while(validar_Edad(verif_edad)==0)
                {
                    printf("Edad no valida. Ingresar numero entero menor a 120.\n");
                    printf("Ingrese edad: ");
                    fflush(stdin);
                    gets(verif_edad);
                }
                pacienteEncontrado->pac.edad = atoi(verif_edad);

                break;
            case 3:
                printf("Ingrese la nueva dirección: ");
                fflush(stdin);
                gets(pacienteEncontrado->pac.direccion);

                while (validar_direccion(pacienteEncontrado->pac.direccion)==-1)
                {
                    printf("Direccion no valido. Ingresar hasta 30 caracteres alfanumericos.\n");
                    printf("Ingrese direccion: ");
                    fflush(stdin);
                    gets(pacienteEncontrado->pac.direccion);
                }

                break;
            case 4:
                printf("Ingrese el nuevo teléfono: ");
                fflush(stdin);
                gets(pacienteEncontrado->pac.tel);

                while (validar_telefono(pacienteEncontrado->pac.tel)==-1)
                {
                    printf("Telefono no valido. Ingresar hasta 15 caracteres numericos enteros.\n");
                    printf("Ingrese telefono: ");
                    fflush(stdin);
                    gets(pacienteEncontrado->pac.tel);
                }
                break;
            case 5:
                pacienteEncontrado->pac.elim=0;
                printf("Paciente reactivado correctamente.\n");
                system("pause");
                break;
            case 0:
                break;
            default:
                printf("Opción no válida. Ingrese un valor nuevamente: \n");
                break;
            }
            system("cls");
        }while(opcion>5);
        }

    printf("\nPaciente no encontrado\n");

    return arbolPacientes;
}

//-----------------------------------------------------------------------//
// Función para eliminar un nodo con el DNI dado en un árbol
//-----------------------------------------------------------------------//
nodoPac* eliminarPaciente(nodoPac* arbolPacientes, int dni)
{
    if (arbolPacientes == NULL)
    {
        return arbolPacientes;
    }

    // Buscar el nodo a eliminar
    if (dni < arbolPacientes->pac.DNI)
    {
        arbolPacientes->izquierda = eliminarPaciente(arbolPacientes->izquierda, dni);
    }
    else if (dni > arbolPacientes->pac.DNI)
    {
        arbolPacientes->derecha = eliminarPaciente(arbolPacientes->derecha, dni);
    }
    else
    {
        // Nodo encontrado, manejar casos para eliminar el nodo
        if (arbolPacientes->izquierda == NULL)
        {
            // Caso 1: Sin hijo izquierdo o sin hijos
            nodoPac* temp = arbolPacientes->derecha;
            free(arbolPacientes);
            return temp;
        }
        else if (arbolPacientes->derecha == NULL)
        {
            // Caso 2: Sin hijo derecho
            nodoPac* temp = arbolPacientes->izquierda;
            free(arbolPacientes);
            return temp;
        }

        // Caso 3: Nodo con dos hijos
        // Encontrar el sucesor in-order (mínimo en el subárbol derecho)
        nodoPac* temp = encontrarMinimo(arbolPacientes->derecha);

        // Copiar el contenido del sucesor a este nodo
        arbolPacientes->pac.DNI = temp->pac.DNI;

        // Eliminar el sucesor
        arbolPacientes->derecha = eliminarPaciente(arbolPacientes->derecha, temp->pac.DNI);
    }

    return arbolPacientes;
}

nodoPac* encontrarMinimo(nodoPac* nodo)
{
    while (nodo->izquierda != NULL)
    {
        nodo = nodo->izquierda;
    }
    return nodo;
}

nodoPac* encontrarMaximo(nodoPac* nodo)
{
    while (nodo->derecha != NULL)
    {
        nodo = nodo->derecha;
    }
    return nodo;
}

//---------------------------------------------------------------------------------------------------//
// Da de baja pacientes o elimina segun corresponda.
// Se pide al usuario el DNI a buscar en el main() y se ingresa por parámetro a esta funcion.
//---------------------------------------------------------------------------------------------------//
nodoPac* bajaPacientes(nodoPac *arbolPacientes, int dni)
{

    nodoPac *pacienteEncontrado = buscarPacXdni(arbolPacientes, dni);       /// Buscamos el paciente con el DNI especificado

    if (pacienteEncontrado==NULL)                                           /// Verifico si el DNI se encontró o no. En caso afirmativo,
    {

        printf("El DNI ingresado no esta registrado como paciente.\n");
    }
    else if(pacienteEncontrado->ingresos!=NULL)                             /// Verifico si tiene ingresos cargados.
    {
        pacienteEncontrado->pac.elim=1;                             /// Caso afirmativo, pongo en 1 el campo elim
        printf("El paciente fue dado de baja correctamente.\n");
    }
    else
    {
        arbolPacientes = eliminarPaciente(arbolPacientes, dni);     /// Caso negativo, elimino el nodo.
    }

    return arbolPacientes;                                                  /// Retorno arbolPacientes con dato modificado o nodo eliminado.
}

//-----------------------------------------------------------------------//
// Función para mostrar el archivo de pacientes.
//-----------------------------------------------------------------------//
void mostrarArchivoPacientes()
{

    FILE *archivo = fopen("ArchivoPacientes.bin","rb");
    pacientes pac;
    if(archivo!=NULL)
    {
        while(fread(&pac,sizeof(pacientes), 1, archivo))
        {
            printf("------------------------- \n");
            printf(" Apellido y nombre: %s \n",pac.NyA);
            printf(" DNI: %i \n",pac.DNI);
            printf(" Edad: %i \n",pac.edad );
            printf(" Direccion: %s \n",pac.direccion);
            printf(" Telefono: %s \n",pac.tel);
            printf("------------------------- \n");
        }
    }
}


//-----------------------------------------------------------------------//
// Función para liberar arbol al cerrar el programa
//-----------------------------------------------------------------------//
void liberarArbolPacientes (nodoPac* arbolPacientes)
{

    if (arbolPacientes != NULL)
    {

        liberarArbolPacientes(arbolPacientes->izquierda);
        liberarArbolPacientes(arbolPacientes->derecha);

        free(arbolPacientes);
    }
}

///LA AGREGO ACA PORQUE NECESITO PASARLE EL ARBOL POR PARAMETRO PARA RECORRER TODO EL SISTEMA.
//------------------------------------------------------------------------------------------------------//
// Baja_de_practica: solo si no fue incluida en ningún ingreso
//------------------------------------------------------------------------------------------------------//

// Esta funcion recorre todo el sistema buscando el idPractica, si lo encuentra, retorna 0. Si no, retorna -1.

//int busquedaPracticasEnSistema(nodoPac* arbolPacientes, int idPractica)
//{
//    int rta = -1;
//    if (arbolPacientes != NULL)
//    {
//        busquedaPracticasEnSistema(arbolPacientes->izquierda, idPractica);
//
//        while((arbolPacientes->ingresos != NULL) && (rta == -1))
//        {
//            while((arbolPacientes->ingresos->practicas != NULL) && (rta == -1))
//            {
//                if(arbolPacientes->ingresos->practicas->pxi.NroDePractica!=idPractica)
//                {
//                    arbolPacientes->ingresos->practicas = arbolPacientes->ingresos->practicas->siguiente;
//                }
//                else
//                {
//                    rta=0;
//                }
//            }
//            arbolPacientes->ingresos = arbolPacientes->ingresos->siguiente;
//        }
//
//        busquedaPracticasEnSistema(arbolPacientes->derecha, idPractica);
//    }
//    return rta;
//}


int busquedaPracticasEnSistema(nodoPac* arbolPacientes, int idPractica)
{
    int rta = -1;
    if (arbolPacientes != NULL)
    {
        // Buscar en el subárbol izquierdo
        rta = busquedaPracticasEnSistema(arbolPacientes->izquierda, idPractica);

        // Buscar en la lista de ingresos del paciente actual
        if (rta == -1)
        {
            nodoIngreso* ingresoActual = arbolPacientes->ingresos;
            while (ingresoActual != NULL && rta == -1)
            {
                nodoPxi* practicaActual = ingresoActual->practicas;
                while (practicaActual != NULL && rta == -1)
                {
                    if (practicaActual->pxi.NroDePractica == idPractica)
                    {
                        rta = 0;  // Encontrado
                    }
                    practicaActual = practicaActual->siguiente;
                }
                ingresoActual = ingresoActual->siguiente;
            }
        }

        // Buscar en el subárbol derecho si no se encontró en el izquierdo o en el actual
        if (rta == -1)
        {
            rta = busquedaPracticasEnSistema(arbolPacientes->derecha, idPractica);
        }
    }
    return rta;
}



// Esta funcion usa la de arriba, si no se uso la practica, se cambia el campo "elim" a 1 dentro del archivo. Si fue usada,
// Imprime un msj que esta en uso y finaliza.

void bajaPractica(nodoPac* arbolPacientes)
{
    practicas aux;
    practicas p = PedirPractica();

    int practicaUsada = busquedaPracticasEnSistema(arbolPacientes, p.nroPractica);     ///retorna -1 si no la encuentra o 0 si la encuentra.
    FILE* archivoPractica = fopen("ArchivoPracticas.bin", "r+b");
    if(archivoPractica!=NULL)
    {
        if(practicaUsada != 0)
        {
            do
            {
                fread(&aux, sizeof(practicas),1,archivoPractica);
            }
            while(aux.nroPractica != p.nroPractica);

            fseek(archivoPractica,-sizeof(practicas), SEEK_CUR);

            strcpy(aux.nombrePractica,p.nombrePractica);
            aux.nroPractica = p.nroPractica;
            aux.elim = 1;

            fwrite(&aux, sizeof(practicas),1,archivoPractica);
            printf("Practica dada de baja exitosamente\n");

        }
        else
        {
            printf ("La practica no puede darse de baja porque fue usada.\n");
        }
    fclose(archivoPractica);
    }
}

