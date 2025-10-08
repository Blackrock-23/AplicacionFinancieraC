#include "anulacion.h"
#include "compra.h"
#include <stdio.h>
#include <string.h>

int anular_compra(int referencia, const char *ultimopan, const char *cvv) {

    // Abrir el archivo para lectura (se reescribirá posteriormente con "w" después de modificar)
    FILE *archivo = fopen(ARCHIVO, "r");
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

    // Buscar la compra por referencia y verificar ultimos 4 dígitos del PAN y CVV
    int encontrada = 0;
    for (int i = 0; i < cantidad; i++) {
        if (compras[i].referencia == referencia) {
            int len_pan = (int)strlen(compras[i].pan);
            if (len_pan >= 4 && strcmp(compras[i].pan + len_pan - 4, ultimopan) == 0 && strcmp(compras[i].cvv, cvv) == 0) {
                strcpy(compras[i].estado, "Anulada");
                encontrada = 1;
                break;
            } else {
                printf("PAN o CVV incorrectos.\n");
                return 0;
            }
        }
    }

    if (!encontrada) {
        printf("Compra con referencia %d no encontrada.\n", referencia);
        return 0;
    }

    // Reescribir el archivo con las compras actualizadas
    archivo = fopen(ARCHIVO, "w");
    if (!archivo) {
        printf("Error al abrir el archivo para escritura\n");
        return 0;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "Referencia: %d\nMonto: %.2f\nPAN: %s\nFranquicia: %s\nCVV: %s\nFecha de Vencimiento: %s\nEstado: %s\n\n",
                compras[i].referencia,
                compras[i].monto_compra,
                compras[i].pan,
                compras[i].franquicia,
                compras[i].cvv,
                compras[i].fecha_Expiracion,
                compras[i].estado);
    }

    fclose(archivo);

    printf("Compra anulada correctamente.\n");
    return 1;
}

