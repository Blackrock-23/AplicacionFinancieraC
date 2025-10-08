#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "compra.h"

void ingreso_dato(compra *com)
{
    printf("--- Nueva compra ---");
    printf("\nIngrese el monto de la compra en dolares (00.00): ");
    scanf("%lf", &com->monto_compra);
    getchar();

    printf("Ingrese el PAN: ");
    gets(com->pan);

    printf("Ingrese el CVV: ");
    scanf("%d", &com->cvv);
    getchar();

    printf("Ingrese la fecha de expiracion (MM/AA): ");
    gets(com->fecha_Expiracion);

    while (!validar_fecha_expiracion(com->fecha_Expiracion)) {
    printf("Vuelva a ingresar una fecha valida (MM/AA): ");
    gets(com->fecha_Expiracion);
}

}

void imprimir(const compra *com)
{
    printf("--- Datos de la compra ---");
    printf("\nMonto: %.2f\n", com->monto_compra);
    printf("Referencia: %d\n", com->referencia);
    printf("PAN: %s\n", com->pan);
    printf("CVV: %d\n", com->cvv);
    printf("Fecha de expiracion: %s\n", com->fecha_Expiracion);
}

void almacenamiento_archivo(compra *compras, int cantidad)
{
    FILE *archivo = fopen("compras.txt", "a");
    if (!archivo)
    {
        printf("Error al abrir el archivo");
        return;
    }

    for (int i = 0; i < cantidad; i++)
    {
        fprintf(archivo, "Numero de Referencia: %i\n\n", compras[i].referencia);
        fprintf(archivo, "Monto: %.2f\n", compras[i].monto_compra);
        fprintf(archivo, "PAN: %s\n", compras[i].pan);
        fprintf(archivo, "CVV: %d\n", compras[i].cvv);
        fprintf(archivo, "Fecha: %s\n\n", compras[i].fecha_Expiracion);
        
    }

    fclose(archivo);
    printf("Compras guardadas en 'compras.txt'");
}

void registrar_compras()
{
    FILE *archivo = fopen(ARCHIVO, "a+");
    if (!archivo)
    {
        printf("Error al abrir archivo");
        return;
    }


    int cantidad = 0;
    compra temp;
    while (fscanf(archivo, "Referencia: %d\nMonto: %lf\nPAN: %[^\n]\nCVV: %d\nFecha: %[^\n]\n\n",
                  &temp.referencia, &temp.monto_compra, temp.pan, &temp.cvv, temp.fecha_Expiracion) == 5)
    {
        cantidad++;
    }

    if (cantidad >= MAX_COMPRAS)
    {
        printf(" Ya existen 20 compras registradas. No se pueden agregar más.\n");
        fclose(archivo);
        return;
    }

    compra *compras = malloc(sizeof(compra));
    if (!compras)
    {
        printf("Error al asignar memoria");
        fclose(archivo);
        return;
    }

    int agregar = 1;
    while (agregar && cantidad < MAX_COMPRAS)
    {
        compras[0].referencia = cantidad + 1; 
        ingreso_dato(&compras[0]);

        fprintf(archivo, "Referencia: %d\nMonto: %.2f\nPAN: %s\nCVV: %d\nFecha: %s\n\n",
                compras[0].referencia, compras[0].monto_compra,
                compras[0].pan, compras[0].cvv, compras[0].fecha_Expiracion);

        cantidad++;
        printf("Compra guardada (%d/20)\n", cantidad);
        imprimir(compras);

        if (cantidad < MAX_COMPRAS)
        {
            printf("Desea registrar otra compra (1=Si, 0=No): ");
            scanf("%d", &agregar);
            getchar();
        }
        else
        {
            printf("Se alcanzó el límite de 20 compras.\n");
        }
    }

    free(compras);
    fclose(archivo);
}
int validar_fecha_expiracion(const char *fecha) {
    int mes, anio;
    time_t t = time(NULL);
    struct tm *fecha_actual = localtime(&t);

    int mes_actual = fecha_actual->tm_mon + 1;  
    int anio_actual = (fecha_actual->tm_year + 1900) % 100; 


    if (sscanf(fecha, "%2d/%2d", &mes, &anio) != 2) {
        printf("Formato de fecha invalido. Use MM/AA.\n");
        return 0;
    }

    if (mes < 1 || mes > 12) {
        printf("Mes invalido.\n");
        return 0;
    }

    if (anio < anio_actual || (anio == anio_actual && mes < mes_actual)) {
        printf("La tarjeta está vencida (%02d/%02d).\n", mes, anio);
        return 0;
    }

    return 1; 
}

