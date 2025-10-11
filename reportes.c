#include "anulacion.h"
#include "compra.h"
#include "reportes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int generar_reportes(){
    FILE *archivo = fopen(ARCHIVO, "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return 0;
    }
    compra compras[MAX_COMPRAS];
    int cantidad = 0;
    int anuladas = 0;
    int activas = 0;
    double total_monto = 0.0;

    while (fscanf(archivo,
                  "Referencia: %d\nMonto: %lf\nPAN: %31[^\n]\nFranquicia: %19[^\n]\nCVV: %4[^\n]\nFecha de Vencimiento: %5[^\n]\nEstado: %9[^\n]\n\n",
                  &compras[cantidad].referencia,
                  &compras[cantidad].monto_compra,
                  compras[cantidad].pan,
                  compras[cantidad].franquicia,
                  compras[cantidad].cvv,
                  compras[cantidad].fecha_Expiracion,
                  compras[cantidad].estado) == 7) {
        total_monto += compras[cantidad].monto_compra;
        if (strcmp(compras[cantidad].estado, "Anulada") == 0) {
            anuladas++;
        } else if (strcmp(compras[cantidad].estado, "Activa") == 0) {
            activas++;
        }
        cantidad++;
        if (cantidad >= MAX_COMPRAS)
            break;
    }
    fclose(archivo);
    if (cantidad == 0) {
        printf("No hay compras registradas.\n");
        return 0;
    }
    printf("----- Reporte de Compras -----\n");
    printf("Total de compras registradas: %d\n", cantidad);
    printf("Total de compras activas: %d\n", activas);
    printf("Total de compras anuladas: %d\n", anuladas);
    printf("Monto total de todas las compras: %.2lf\n", total_monto);
    printf("------------------------------\n");
    return 1;

}