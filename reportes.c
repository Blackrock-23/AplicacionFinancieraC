#include "anulacion.h"
#include "compra.h"
#include "reportes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Función para generar reportes
int generar_reportes()
{
    FILE *archivo = fopen(ARCHIVO, "r");
    if (!archivo)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    compra compras[MAX_COMPRAS];

    // Sumatoria de compras y conteo
    int cantidad = 0;
    int anuladas = 0;
    int activas = 0;
    double total_monto = 0.0;

    // leer todas las compras del archivo
    while (fread(&compras[cantidad], sizeof(compra), 1, archivo) == 1)
    {
        

        if (strcmp(compras[cantidad].estado, "Anulada") == 0)
        {
            anuladas++;
        }
        else if (strcmp(compras[cantidad].estado, "Activa") == 0)
        {
            // Solo sumar las compras activas
            total_monto += compras[cantidad].monto_compra;
            activas++;
        }

        cantidad++;
        if (cantidad >= MAX_COMPRAS)
            break;
    }
    fclose(archivo);
    if (cantidad == 0)
    {
        printf("No hay compras registradas.\n");
        return 0;
    }

    // Mostrar el reporte
    printf("----- Reporte de Compras -----\n");
    printf("Total de compras registradas: %d\n", cantidad);
    printf("Total de compras activas: %d\n", activas);
    printf("Total de compras anuladas: %d\n", anuladas);
    printf("Monto total de todas las compras: %.2lf\n", total_monto);
    printf("------------------------------\n");
    return 1;
}