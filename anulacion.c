#include "anulacion.h"
#include "compra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// funcion para validar la referencia
void ingresarReferencia(char *referencia)
{
    int valido;
    do
    {
        printf("Ingrese la referencia de la compra a anular: ");
        gets(referencia);

        if (strlen(referencia) == 0)
        {
            printf("La referencia no puede estar vacia.\n");
            valido = 0;
        }
        else
        {
            valido = 1;
        }
    } while (!valido);
}

// funcion para validar los ultimos 4 digitos del PAN
void ingresarUltimosPan(char *ultimopan)
{
    int valido;
    do
    {
        printf("Ingrese los ultimos 4 digitos del PAN: ");
        gets(ultimopan);

        int largo = strlen(ultimopan);
        int es_numerico = 1;

        for (int i = 0; i < largo; i++)
        {
            if (!isdigit(ultimopan[i]))
            {
                es_numerico = 0;
                break;
            }
        }

        if (largo != 4 || !es_numerico)
        {
            printf("El PAN debe tener exactamente 4 digitos numericos.\n");
            valido = 0;
        }
        else
        {
            valido = 1;
        }

    } while (!valido);
}

// funcion para validar el cvv
void ingresarCVV(char *cvv)
{
    int valido;
    do
    {
        printf("Ingrese el CVV: ");
        gets(cvv);

        int largo = strlen(cvv);
        int es_numerico = 1;

        for (int i = 0; i < largo; i++)
        {
            if (!isdigit(cvv[i]))
            {
                es_numerico = 0;
                break;
            }
        }

        if (largo != 4 || !es_numerico)
        {
            printf(" El CVV debe tener exactamente 4 digitos numericos.\n");
            valido = 0;
        }
        else
        {
            valido = 1;
        }

    } while (!valido);
}

// funcion que anula la compra
int buscarYAnularCompra(const char *referencia, const char *ultimopan, const char *cvv)
{
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    compra compras[MAX_COMPRAS];
    int cantidad = 0;

    while (fread(&compras[cantidad], sizeof(compra), 1, archivo) == 1)
    {
        cantidad++;
        if (cantidad >= MAX_COMPRAS)
            break;
    }

    fclose(archivo);

    int encontrada = 0;
    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(compras[i].referencia, referencia) == 0)
        {
            int len_pan = (int)strlen(compras[i].pan);
            if (len_pan >= 4 && strcmp(compras[i].pan + len_pan - 4, ultimopan) == 0 && strcmp(compras[i].cvv, cvv) == 0)
            {
                strcpy(compras[i].estado, "Anulada");
                encontrada = 1;
                break;
            }
            else
            {
                printf(" PAN o CVV incorrectos.\n");
                return 0;
            }
        }
    }

    if (!encontrada)
    {
        printf(" Compra con referencia %s no encontrada.\n", referencia);
        return 0;
    }

    archivo = fopen(ARCHIVO, "wb");
    if (!archivo)
    {
        printf("Error al abrir el archivo para escritura\n");
        return 0;
    }

    for (int i = 0; i < cantidad; i++)
    {
        fwrite(&compras[i], sizeof(compra), 1, archivo);
    }

    fclose(archivo);
    printf(" Compra anulada correctamente.\n");
    return 1;
}

//funcion princirpal
int anular_compra()
{
    char referencia[10];
    char ultimopan[10];
    char cvv[10];

    ingresarReferencia(referencia);
    ingresarUltimosPan(ultimopan);
    ingresarCVV(cvv);

    system("cls"); 

    return buscarYAnularCompra(referencia, ultimopan, cvv);
}
