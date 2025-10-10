#include <stdio.h>
#include <stdlib.h>
#include "compra.h"
#include "anulacion.h"
#include "reeimpresion.h"
#include "reportes.h"
#include "cierre.h"

int main(){

    int opcion;
    do {
        printf("--- BIENVENIDO A LA APLICACION FINANCIERA ---\n");
        printf("---------------------------------------------\n");
        printf("               1. COMPRA\n");
        printf("               2. ANULACION\n");
        printf("               3. REEIMPRESION\n");
        printf("               4. REPORTES\n");
        printf("               5. CIERRE\n");
        printf("               6. SALIR\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        system("cls");
        getchar(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                registrar_compras();
                break;
            case 2:
                {
                    int referencia;
                    char ultimopan[5];
                    char cvv[5];

                    printf("Ingrese la referencia de la compra a anular: ");
                    scanf("%d", &referencia);
                    getchar(); // Limpiar el buffer

                    printf("Ingrese los ultimos 4 digitos del PAN: ");
                    gets(ultimopan);

                    printf("Ingrese el CVV: ");
                    gets(cvv);

                    anular_compra(referencia, ultimopan, cvv);
                }
                break;
            case 3:
                reeimprimir_compras();
                break;
            case 4:
                generar_reportes();
                break;
            case 5:
                realizar_cierre();
                break;
            case 6:
                printf("Saliendo de la aplicacion...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
    return 0;
}