#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compra.h"
#include "anulacion.h"
#include "reimpresion.h"
#include "reportes.h"
#include "cierre.h"

int main()
{

    int opcion;
    char entrada[10];
    do
    {
        printf("--- BIENVENIDO A LA APLICACION FINANCIERA ---\n");
        printf("---------------------------------------------\n");
        printf("               1. COMPRA\n");
        printf("               2. ANULACION\n");
        printf("               3. REEIMPRESION\n");
        printf("               4. REPORTES\n");
        printf("               5. CIERRE\n");
        printf("               6. SALIR\n");
        printf("Seleccione una opcion: ");
        gets(entrada);

        // Validamos que la entrada sea un solo caracter y este entre '1' y '6'
        if (strlen(entrada) == 1 && entrada[0] >= '1' && entrada[0] <= '6')
        {
            opcion = entrada[0] - '0';
        }
        else
        {
            opcion = 0;
        }

        system("cls");

        switch (opcion)
        {
        case 1:
            registrar_compras();
            break;
        case 2:
            anular_compra();
            break;
    
        case 3:
            reimprimir_compras();
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