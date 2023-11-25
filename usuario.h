#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED


//-----------------------------//
//ESTRUCTURAS USUARIO//
//-----------------------------//
typedef struct
{
    int dni;
    char apellidoYnombre[40];
    char usuario[20];
    char password[20];
    char perfil[20];
    int alta;
} empleados_laboratorio;

/** OBSERVACIONES **/
/**
1. CAMPO ALTA -> ALTA: 1, BAJA: 0, `NO EXISTENTE: -1
-> EN LA BUSQUEDA DE EMPLEADO POR DNI, SE RETORNA AL EMPLEADO. SI NO FUE ENCONTRADO EL CAMPO ALTA ESTARA EN -1
-> EN LA BUSQUEDA DEL LOGIN PASA LO MISMO.
2.LA FUNCION LISTADO EMPLEADOS ALTA SE UTILIZA TANTO PARA ADMIN, COMO PARA SECRETARIA
POR LO TANTO SE PASA AL USUARIO COMO PARAMETRO PARA MOSTRAR ACORDE AL TIPO

**/


//-----------------------------//
//FUNCIONES USUARIO//
//-----------------------------//

//1.BUSQUEDA EMPLEADO X DNI
//2.ALTA EMPLEADO
//3. BAJA EMPLEADO  - ALTA EMPLEADO
//4. MOSTRAR EMPLEADO
//5. LISTADO EMPLEADOS ALTA
//6. LISTADO EMPLEADOS BAJA
//7. LISTADO EMPLEADOS TODOS
//8. CONTAR CANTIDAD USUARIOS
//9. PEDIR CONTRASENIA
//10. CARGAR CONTRASENIA
//11. BUSCA AL USUARIO PARA INICIAR SESION
//12.CARGAR EMPLEADO
//13.BUSQUEDA EMPLEADO X USERNAME
//14. MODIFICAR USUARIO
//15. DAR DE ALTA UN USUARIO QUE ESTABA DADO DE BAJA

/*1*/empleados_laboratorio buscarEmpleadoEnArchivo(char dni[20]);
/*2*/void altaEmpleado(empleados_laboratorio empleado);
/*3*/empleados_laboratorio bajaLogica(empleados_laboratorio empleado);
/*4*/void mostrarEmpleado(empleados_laboratorio empleado);
/*5*/void listadoEmpleadosAlta(empleados_laboratorio empleado, char perfil[20]); //SE LE PASA YA QUE SI ES ADMIN SE MUESTRA MAS INFORMACION
/*6*/void adMostrarListadoEmpleadosBaja(char perfil[20]);
/*7*/void adMostrarListadoEmpleadosTodos(char perfil[20]);
/*8*/int contarCantidadUsuarios();
/*9*/void pedirContrasenia(char contrasenia[20]);
/*10*/empleados_laboratorio cargarContraseniaRegistro(empleados_laboratorio usuario);
/*11*/empleados_laboratorio buscarEmpleadoLogin(int dni, char contrasenia[30]);
/*12*/empleados_laboratorio cargaEmpleado(char perfil[20], char dni[20]);
/*13*/empleados_laboratorio buscarEmpleadoEnArchivoUsername(char username[20]);
/*14*/empleados_laboratorio modificarUsuario(char dniChar[20], empleados_laboratorio esAdmin);
/*15*/empleados_laboratorio altaLogica(empleados_laboratorio empleado);

#endif // USUARIO_H_INCLUDED
