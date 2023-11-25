#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "practicas.h"
#include "ingresos.h"
#include "practicasXingreso.h"


//-------------------//
//FUNCIONES DE LISTAS//
//-------------------//

nodoPxi *inicListaPxI()
{

    return NULL;
}

nodoPxi *crearNodoPxI(pracXingreso datoNuevo)
{

    nodoPxi *aux=(nodoPxi*)malloc(sizeof(nodoPxi));

    aux->pxi.NroDeIngreso=datoNuevo.NroDeIngreso;
    aux->pxi.NroDePractica=datoNuevo.NroDePractica;
    strcpy(aux->pxi.Resultado,"NULL");
    aux->anterior=NULL;
    aux->siguiente=NULL;

    return aux;
}

nodoPxi *agregarAlPrincipioPxI(nodoPxi *lista, nodoPxi *NuevoNodo)
{
  NuevoNodo->siguiente=lista;
  if(lista!=NULL){
    lista->anterior=NuevoNodo;

  }

    return NuevoNodo;


}

nodoPxi *borrarNodoPxI(nodoPxi *listaP, int idPracticas)
{
    nodoPxi *aux;
    if(listaP==NULL){
        return listaP;                  //no hay nada que borrar
    }
    aux=listaP;
    if (idPracticas == aux->pxi.NroDePractica)
    {
                                        // Borrar el primer nodo
        listaP = aux->siguiente;
        if (listaP != NULL)
        {
            listaP->anterior = NULL;
        }
        free(aux);
        return listaP;
    }
                                        // Buscar el nodo a borrar
    while (aux != NULL && idPracticas != aux->pxi.NroDePractica)
    {
        aux = aux->siguiente;
    }

    if (aux == NULL)
    {
                                        // El nodo no se encontró
        return listaP;
    }

                                        // Borrar el nodo
    if (aux->anterior != NULL)
    {
        aux->anterior->siguiente = aux->siguiente;
    }
    if (aux->siguiente != NULL)
    {
        aux->siguiente->anterior = aux->anterior;
    }
    free(aux);

    return listaP;
}


void mostrarListaPxI(nodoPxi *listaP)
{
    nodoPxi *seg;
    practicas p;
    if(listaP==NULL){
        printf("No existen practicas cargadas. \n");

    } else{
    seg=listaP;
    while(seg!=NULL)
    {
        printf("-------------------------------------------------\n");
        printf("ID ingreso: %i \n",seg->pxi.NroDeIngreso);
        printf("Cod. practica: %i \n",seg->pxi.NroDePractica);
        p=validacionPractica(seg->pxi.NroDePractica);
        printf("Nombre de practica: %s \n",p.nombrePractica);
        printf("Resultado: %s \n",seg->pxi.Resultado);
        printf("-------------------------------------------------\n");
        seg=seg->siguiente;

    }
}
}
nodoPxi *BuscarPxI (nodoPxi *listaP, int idPractica)
{
        nodoPxi *seg=listaP;
        while(seg!=NULL && seg->pxi.NroDePractica!=idPractica)
        {
            seg=seg->siguiente;
        }

    return seg;
}

nodoPxi *altaPxI (nodoPxi *listaP, int ing)
{
    nodoPxi *aux,*buscado;
    pracXingreso reg;

    practicas p=PedirPractica();

    reg.NroDePractica=p.nroPractica;
    reg.NroDeIngreso=ing;
    strcpy(reg.Resultado,"0");

    buscado=BuscarPxI(listaP,reg.NroDePractica);
    if(buscado!=NULL)
    {
        printf("La practica ya fue cargada");
    }
    else
    {

        aux=crearNodoPxI(reg);

        listaP=agregarAlPrincipioPxI(listaP,aux);
    }
    return listaP;
}

nodoPxi *bajaPxI(nodoPxi *listaP, int ing)
{

    practicas p;
    int flag=0;
    nodoPxi *aux;

    while(flag==0)
    {
        printf("Que parctica desea eliminar? (Ingrese codigo de practica)\n");
        mostrarListaPxI(listaP);
        scanf("%i",&p.nroPractica);

        aux=BuscarPxI(listaP,p.nroPractica);

        if(aux==NULL)
        {
            printf("La practica no se encontró \n");
        }
        else
        {
            flag=1;
        }
    }

    if(strcmpi(aux->pxi.Resultado,"NULL")==0)     ///
    {
        listaP=borrarNodoPxI(listaP,p.nroPractica);
        printf("Practica eliminada con exito\n");
    }
    else
    {
        printf("La practica tiene resultados cargados, no se puede eliminar");
    }

    return listaP;
}

nodoPxi *modificacionPxI(nodoPxi *listaP)
{

    practicas pe,pn;
    int flag=0;
    nodoPxi *aux;

    while(flag==0)
    {
        printf("Que parctica desea modificar? (Ingrese codigo de practica)\n");
        mostrarListaPxI(listaP);
        scanf("%i",&pe.nroPractica);

        aux=BuscarPxI(listaP,pe.nroPractica);

        if(aux==NULL)
        {
            printf("La practica no se encontro \n");
        }
        else
        {
            flag=1;
        }
    }
    if(strcmpi(aux->pxi.Resultado,"NULL")==0)
    {
        pn=PedirPractica();
        aux->pxi.NroDePractica=pn.nroPractica;
         printf("Practica modificada con exito\n");
    }
    else
    {
        printf("La practica tiene resultados cargados, no se puede eliminar");
    }

    return listaP;
}

//MUESTRA TODOS LOS INGRESOS CON SUS RESPECTIVAS PRACTICAS
void mostrarIngresosAltaConPracticas(nodoIngreso * listaIngreso)
{
    if(listaIngreso == NULL)
    {
        printf("No hay ingresos\n");
    }
    else
    {
        nodoIngreso * seg = listaIngreso;
        while(seg != NULL)
        {
            if(seg->ingreso.eliminado != 1)
            {
                mostrarIngreso(seg->ingreso);
                mostrarListaPxI(seg->practicas);

            }
            seg=seg->siguiente;
        }
    }
}

nodoPxi *cargarResultadosLaboratorio(nodoPxi *listaP)
{
    int idP;
    nodoPxi *aux;
    char res[40];
    int flag = 0;

    if(listaP==NULL){
        printf("No existe practicas a cargadas");
    } else{

    mostrarListaPxI(listaP);

    while(flag==0)
    {
        printf("Ingrese el codigo de practica a la cual cargar resultados: \n");
        scanf("%i",&idP);

        aux = BuscarPxI(listaP, idP);

        if(aux == NULL)
        {
            printf("La practica no se encontro \n");
        }
        else if(strcmpi(aux->pxi.Resultado,"NULL")!=0){
            printf("La practica ya tiene resultados cargados. Contactese con el admin para modificarlo.\n");
            break;
        }else{
            flag=1;
        }
    }

    printf("Ingrese el resultado de la practica: \n");
    fflush(stdin);
    gets(res);

    strcpy(aux->pxi.Resultado, res);
    printf("Resultado cargado con exito \n");
    }
    return listaP;
}

nodoPxi *modificacionResultadosAdmin(nodoPxi *listaP){
    int idP;
    nodoPxi *aux;
    char res[40];
    int flag = 0;

    if(listaP==NULL){
        printf("No existe practicas cargadas");

    } else{
    mostrarListaPxI(listaP);
    while(flag==0)
    {
        printf("Ingrese el codigo de practica a la cual modificar resultados: \n");
        scanf("%i",&idP);

        aux = BuscarPxI(listaP, idP);

        if(aux == NULL)
        {
            printf("La practica no se encontro \n");
        }
        else
        {
            flag=1;
        }
    }
    printf("El resultado cargado anteriormente es: %s\n", aux->pxi.Resultado);
    printf("Ingrese el resultado de la practica: \n");
    fflush(stdin);
    gets(res);

    strcpy(aux->pxi.Resultado, res);
    printf("Resultado modificado con exito \n");
    }
    return listaP;

}


