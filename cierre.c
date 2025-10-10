#include "cierre.h"
#include "compra.h"
#include "reportes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int realizar_cierre()
{
    char entrada[10];
    char opcion;

    generar_reportes();
    do
    {
        printf("Desea borrar todas las compras registradas? (s/n): ");
        scanf("%s", entrada);

        // Solo aceptamos una letra
        if (strlen(entrada) == 1)
        {
            opcion = entrada[0];
            if (opcion == 's' || opcion == 'S' || opcion == 'n' || opcion == 'N')
                break;
        }
        printf("Opcion invalida. Ingrese solo 's' o 'n'.\n");

    } while (1);
    system("cls");

    if (opcion == 's' || opcion == 'S')
    {
        system("cls");
        if (remove(ARCHIVO) == 0)
        {
            printf("Cierre realizado. Todas las compras han sido borradas.\n");
        }
        else
        {
            printf("Error al borrar el archivo de compras.\n");
            return 0;
        }
    }
    else
    {
        printf("Cierre cancelado. Las compras no han sido borradas.\n");
    }
    return 1;
}
