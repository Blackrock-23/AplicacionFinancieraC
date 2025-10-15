#include "anulacion.h"
#include "reeimpresion.h"
#include "compra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int reeimprimir_compras()
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
        char pan_formateado[32];
        pan_oculto(compras[i].pan, pan_formateado);
        printf("%-5d %-13.2lf %-15s %-18s %-6s %-8s %-8s\n",
               compras[i].referencia,
               compras[i].monto_compra,
               compras[i].franquicia,
               pan_formateado,
               compras[i].cvv,
               compras[i].fecha_Expiracion,
               compras[i].estado);
    }
    printf("===============================================================================================\n");

    return 1;
}