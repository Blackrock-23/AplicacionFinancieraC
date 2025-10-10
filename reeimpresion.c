#include "anulacion.h"
#include "reeimpresion.h"
#include "compra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int reeimprimir_compras() {

    FILE *archivo = fopen(ARCHIVO, "rt");
    if (!archivo) {
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
                  compras[cantidad].estado) == 7) {
        cantidad++;
        if (cantidad >= MAX_COMPRAS)
            break;
    }
    fclose(archivo);
    if (cantidad == 0) {
        printf("No hay compras registradas.\n");
        return 0;
    }
    printf("Listado de Compras:\n");
    for (int i = cantidad -1; i >=0; i--) {
        printf("Referencia: %d\n", compras[i].referencia);
        printf("Monto: %.2lf\n", compras[i].monto_compra);
        printf("PAN: %s\n", compras[i].pan);
        printf("Franquicia: %s\n", compras[i].franquicia);
        printf("CVV: %s\n", compras[i].cvv);
        printf("Fecha de Vencimiento: %s\n", compras[i].fecha_Expiracion);
        printf("Estado: %s\n", compras[i].estado);
        printf("-------------------------\n");
    }
    return 1; 
}