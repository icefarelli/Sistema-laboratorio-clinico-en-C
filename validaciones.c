#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
//-----------------------------//
//FUNCIONES VALIDACIONES//
//-----------------------------//
//1. VALIDAR STRING CHAR
int validarStringNombre(char nombre[])
{
    for(int i=0; i<strlen(nombre); i++)
    {
        if(!isalpha(nombre[i]) && !isspace(nombre[i]))
        {
            return 0;
        }
    }
    return 1;
}
//2. VALIDAR STRING NUM
int validarStringNum(char nombre[])
{
    for(int i=0; i<strlen(nombre); i++)
    {
        if(!isdigit(nombre[i]))
        {
            return 0;
        }
    }
    return 1;
}
//3. VALIDAR LENGHT DE UNA PALABRA
int validarLenght(char prototipo[], int minChar)
{
    if(strlen(prototipo)<minChar)
    {
        return 0;
    }
    return 1;
}
//4. VALIDAR LENGHT DE LA CONTRASENIA
int validarLenghtContrasenia(char contrasenia[])
{
    if(strlen(contrasenia)<5)
    {
        return 0;
    }
    return 1;
}
//5. VALIDAR CONTRASENIA
int validarContrasenia(char contrasenia[], char contrasenia1[])
{
    if(strcmp(contrasenia, contrasenia1)==0)
    {
        return 1;
    }
    return 0;
}
//6. VALIDAR DIA FECHA
int validarDiaFecha(int dia)
{
    if(dia<1 || dia>31)
    {
        return 0;
    }
    return 1;
}
//7. VALIDAR MES FECHA
int validarMesFecha(int mes)
{
    if(mes<1 || mes>12)
    {
        return 0;
    }
    return 1;
}
//8. VALIDAR DNI
int validarDNI(char dniString[20])
{

    if(!validarStringNum(dniString))
    {
        return 0;
    }

    if (strlen(dniString) > 8)
    {
        return 0;
    }
    if(strlen(dniString)<6)
    {
        return 0;
    }
    return 1;
}
//9.CONVERTIR CHAR A INT
int convertirCharAInt(char string[20]){
return atoi(string);
}
//10.CONVERTIR INT A CHAR
void convertirIntAChar(char string[20], int dni){
itoa(dni,string,10);
}
//11. OTRO TIPO DE VALIDACION DE DNI
int validar_DNI(char numero_str[])
{
    // Verificamos que todos los digitos sean numeros entre 0 y 9
    int i;
    for (i = 0; i < strlen(numero_str); i++)
    {
        if (!isdigit(numero_str[i]))
        {
            return 0;
        }
    }
    // Verificamos que la cantidad de digitos no sea mayor a 8
    if (strlen(numero_str) > 8)
    {
        return 0;
    }

    // Convertimos el string a integer nuevamente
    int numero_validado = atoi(numero_str);


    return numero_validado;
}
//12.VALIDACION NOMBRE Y APELLIDO
int validar_NyA(char NyA[])
{
    int rta = 0;
    for (int i = 0; i < strlen(NyA); i++)
    {
        if (!isalpha(NyA[i]) && NyA[i]!=' ')
        {
            rta = -1;
        }
    }
    if (strlen(NyA) > 40)
    {
        rta = -1;
    }
    return rta;
}
//13. VAIDAR EDAD
int validar_Edad(char numero_str[])
{
    // Verificamos que todos los digitos sean numeros entre 0 y 9
    int i;
    for (i = 0; i < strlen(numero_str); i++)
    {
        if (!isdigit(numero_str[i]))
        {
            return 0;
        }
    }

    // Convertimos el string a integer nuevamente
    int numero_validado = atoi(numero_str);

    if(numero_validado>120)
    {
        return 0;
    }

    return numero_validado;
}
//14. VALIDAR DIRECCION
int validar_direccion(char direccion[])
{
    int rta = 0;
    for (int i = 0; i < strlen(direccion); i++)
    {
        if (!isalnum(direccion[i]) && direccion[i]!=' ')
        {
            rta = -1;
        }
    }
    if (strlen(direccion) > 30)
    {
        rta = -1;
    }
    return rta;
}
//15. VALIDAR TELEFONO
int validar_telefono(char tel[])
{
    int rta = 0;
    // Verificamos que todos los digitos sean numeros entre 0 y 9
    int i;
    for (i = 0; i < strlen(tel); i++)
    {
        if (!isdigit(tel[i]))
        {
            rta = -1;
        }
    }
    // Verificamos que la cantidad de digitos no sea mayor a 15
    if (strlen(tel) > 15)
    {
        rta =-1;
    }

    return rta;
}

//16.VALIDAR USERNAME
int validarUsername(char nombre[])
{
    for(int i=0; i<strlen(nombre); i++)
    {
        if(!islower(nombre[i]) && !isspace(nombre[i]))
        {
            return 0;
        }
    }
    return 1;
}

//17.VALIDAR AÑO DE FECHA
int validarAnioFecha(int anio)
{
    if(anio<1970 || anio>2023){
        return 0;
    } else {
        return 1;
    }
}

//18.VALIDAR FECHA
int validar_fecha(char fecha[])
{
    //pido mil millones de disculpas

    char dia[3];
    dia[0] = fecha[0];
    dia[1] = fecha[1];
    dia[2] = '\0';

    if(validarDiaFecha(atoi(dia)) == 1){
        return 1;
    }

    char mes[3];
    mes[0] = fecha[3];
    mes[1] = fecha[4];
    mes[2] = '\0';

    if(validarMesFecha(atoi(mes)) == 1){
        return 1;
    }

    char anio[5];
    anio[0] = fecha[6];
    anio[1] = fecha[7];
    anio[2] = fecha[8];
    anio[3] = fecha[9];
    anio[4] = '\0';

    if(validarAnioFecha(atoi(anio)) == 1){
        return 1;
    }

    return 0;
}

int esFechaValida (char fechaStr[]) {
    struct tm fecha;

   if (sscanf(fechaStr, "%d-%d-%d", &fecha.tm_mday, &fecha.tm_mon, &fecha.tm_year) == 3){
        if((fecha.tm_mday>=01 && fecha.tm_mday<=31) && (fecha.tm_mon>=01 && fecha.tm_mon<=12) && (fecha.tm_year>1990 && fecha.tm_year<2030))
            {
        return 1;
   }
}
return 0;
}


int validar_matrricula(char numero_str[])
{
    // Verificamos que todos los digitos sean numeros entre 0 y 9
    int i;
    for (i = 0; i < strlen(numero_str); i++)
    {
        if (!isdigit(numero_str[i]))
        {
            return 0;
        }
    }

    // Convertimos el string a integer nuevamente
    int numero_validado = atoi(numero_str);


    return numero_validado;
}
