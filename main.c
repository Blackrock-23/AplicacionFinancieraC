#include <stdio.h>
#include "compra.h"
#include "anulacion.h"

int main(){

    int opcion;
    do {
        printf("--- BIENVENIDO A LA APLICACION FINANCIERA ---\n");
        printf("---------------------------------------------\n");
        printf("               1. COMPRA\n");
        printf("               2. ANULACION\n");
        printf("               3. CIERRE\n");
        printf("               4. REEIMPRESION\n");
        printf("               5. REPORTES\n");
        printf("               6. SALIR\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
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
            case 4:
            case 5:
            case 6:
                printf("Saliendo de la aplicacion...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
    return 0;
}