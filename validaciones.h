#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-----------------------------//
//FUNCIONES VALIDACIONES//
//-----------------------------//
//1. VALIDAR STRING CHAR
//2. VALIDAR STRING NUM
//3. VALIDAR LENGHT DE UNA PALABRA
//4. VALIDAR LENGHT DE LA CONTRASENIA
//5. VALIDAR CONTRASENIA
//6. VALIDAR DIA FECHA
//7. VALIDAR MES FECHA
//8. VALIDAR DNI
//9.CONVERTIR CHAR A INT
//10.CONVERTIR INT A CHAR
//11. OTRO TIPO DE VALIDACION DE DNI
//12.VALIDACION NOMBRE Y APELLIDO
//13. VAIDAR EDAD
//14. VALIDAR DIRECCION
//15. VALIDAR TELEFONO
//16.VALIDAR USERNAME
/*1*/int validarStringNombre(char nombre[]);
/*2*/int validarStringNum(char nombre[]);
/*3*/int validarLenght(char prototipo[], int minChar);
/*4*/int validarLenghtContrasenia(char contrasenia[]);
/*5*/int validarContrasenia(char contrasenia[], char contrasenia1[]);
/*6*/int validarDiaFecha(int dia);
/*7*/int validarMesFecha(int mes);
/*8*/int validarDNI(char dniString[20]);
/*9*/int convertirCharAInt(char string[20]);
/*10*/void convertirIntAChar(char string[20], int dni);
/*11*/int validar_DNI(char numero_str[]);
/*12*/int validar_NyA(char NyA[]);
/*13*/int validar_Edad(char numero_str[]);
/*14*/int validar_direccion(char direccion[]);
/*15*/int validar_telefono(char tel[]);
/*16*/int validarUsername(char nombre[]);
/*17*/int validarAnioFecha(int anio);
/*18*/int validar_fecha(char fecha[]);
int esFechaValida (char fechaStr[]);
int validar_matrricula(char numero_str[]);
#endif // ORDENES_H_INCLUDED
