#include "anulacion.h"
#include "compra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Función para anular una compra
int anular_compra()
{
    char referencia[5];
    char ultimopan[5];
    char cvv[5];

    do
    {
        printf("Ingrese la referencia de la compra a anular: ");
        gets(referencia);

        if (strlen(referencia) == 0)
            printf(" La referencia no puede estar vacia.\n");

    } while (strlen(referencia) == 0);

    do
    {
        printf("Ingrese los ultimos 4 digitos del PAN: ");
        gets(ultimopan);

        if (strlen(ultimopan) == 0)
            printf(" Los ultimos 4 digitos no pueden estar vacios.\n");

    } while (strlen(ultimopan) == 0);

    do
    {
        printf("Ingrese el CVV: ");
        gets(cvv);

        if (strlen(cvv) == 0)
            printf("  El CVV no puede estar vacio.\n");

    } while (strlen(cvv) == 0);

    // Abrir el archivo para lectura
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    compra compras[MAX_COMPRAS];
    int cantidad = 0;

    // leer todas las compras del archivo
    while (fread(&compras[cantidad], sizeof(compra), 1, archivo) == 1)
    {
        cantidad++;
        if (cantidad >= MAX_COMPRAS)
            break;
    }

    fclose(archivo);

    // Buscar la compra por referencia y verificar ultimos 4 dígitos del PAN y CVV
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
                printf("PAN o CVV incorrectos.\n");
                return 0;
            }
        }
    }

    if (!encontrada)
    {
        printf("Compra con referencia %s no encontrada.\n", referencia);
        return 0;
    }

    // Reescribir el archivo con las compras actualizadas
    archivo = fopen("compras.bin", "wb"); // "wb" sobrescribe el archivo
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
    system("cls");

    printf("Compra anulada correctamente.\n");
    return 1;
}
