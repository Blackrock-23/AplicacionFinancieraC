#include "anulacion.h"
#include "reeimpresion.h"
#include "compra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int reeimprimir_compras()
{

    FILE *archivo = fopen(ARCHIVO, "rt");
    if (!archivo)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }
    compra compras[MAX_COMPRAS];

    int cantidad = 0;
    while (fscanf(archivo,
                  "Referencia: %d\nMonto: %lf\nPAN: %31[^\n]\nFranquicia: %19[^\n]\nCVV: %4[^\n]\nFecha de Vencimiento: %5[^\n]\nEstado: %9[^\n]\n\n",
                  &compras[cantidad].referencia,
                  &compras[cantidad].monto_compra,
                  compras[cantidad].pan,
                  compras[cantidad].franquicia,
                  compras[cantidad].cvv,
                  compras[cantidad].fecha_Expiracion,
                  compras[cantidad].estado) == 7)
    {
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
    printf("Listado de Compras:\n");

    // Encabezado alineado
    printf("===============================================================================================\n");
    printf("%-5s %-13s %-15s %-18s %-6s %-8s %-8s\n",
           "Ref", "Monto", "Franquicia", "PAN", "CVV", "Fecha", "Estado");
    printf("===============================================================================================\n");

    // Filas de datos
    for (int i = cantidad - 1; i >= 0; i--)
    {
        printf("%-5d %-13.2lf %-15s %-18s %-6s %-8s %-8s\n",
               compras[i].referencia,
               compras[i].monto_compra,
               compras[i].franquicia,
               compras[i].pan,
               compras[i].cvv,
               compras[i].fecha_Expiracion,
               compras[i].estado);
    }
    printf("===============================================================================================\n");

    return 1;
}