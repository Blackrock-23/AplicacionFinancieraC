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

    // Llamar a la funcion para generar reportes
    generar_reportes();

    // Preguntar al usuario si desea borrar las compras
    do
    {
        printf("Desea borrar todas las compras registradas? (s/n): ");
        gets(entrada);

        // Validamos que solo se ingrese un caracter y sea 's' o 'n'
        if (strlen(entrada) == 1)
        {
            opcion = entrada[0];
            if (opcion == 's' || opcion == 'S' || opcion == 'n' || opcion == 'N')
                break;
        }
        printf("Opcion invalida. Ingrese solo 's' o 'n'.\n");

    } while (1);
    system("cls");

    // Borramos el archivo si el usuario lo confirma
    if (opcion == 's' || opcion == 'S')
    {
        system("cls");
        FILE *archivo = fopen(ARCHIVO, "w");
        if (archivo != NULL)
        {
            fclose(archivo);
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
