#include "anulacion.h"
#include "reimpresion.h"
#include "compra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Función para reimprimir compras
int reimprimir_compras()
{
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    compra compras[MAX_COMPRAS];
    int cantidad = 0;

    // leer todas las compras del archivo
    while (fread(&compras[cantidad], sizeof(compra), 1, archivo) == 1)
    {
        cantidad++;
        if (cantidad >= MAX_COMPRAS)
            break;
    }
    fclose(archivo);

    if (cantidad == 0)
    {
        printf("---------------------------------------------\n");
        printf("       No hay compras registradas.\n");
        printf("---------------------------------------------\n");
        return 0;
    }

    int indice = cantidad - 1;
    char tecla;

    // Bucle principal para navegar entre las compras
    while (1)
    {
        system("cls");

        // Encabezado
        printf("================================ REIMPRESION ==================================================\n");
        printf("%-5s %-13s %-15s %-18s %-8s %-8s %-8s\n",
               "Ref", "Monto", "Franquicia", "PAN", "CVV", "Fecha", "Estado");
        printf("===============================================================================================\n");

        char pan_formateado[32];
        // Llamar a la funcion para ocultar el pan
        pan_oculto(compras[indice].pan, pan_formateado);

        printf("%-5s %-13.2lf %-15s %-18s %-6s %-8s %-8s\n",
               compras[indice].referencia,
               compras[indice].monto_compra,
               compras[indice].franquicia,
               pan_formateado,
               compras[indice].cvv,
               compras[indice].fecha_Expiracion,
               compras[indice].estado);
        printf("===============================================================================================\n");

        // Muestra los hints (flechas)
        mostrar_hint(indice, cantidad);

        // Pedir una tecla válida
        tecla = pedir_tecla_valida();

        // Acciones para poder moverse en orden descendente
        if (tecla == 'd' && indice > 0)
            indice--;
        else if (tecla == 'a' && indice < cantidad - 1)
            indice++;
        else if (tecla == 's')
        {
            printf("Saliendo de reimpresion...\n");
            break;
        }
        else
        {
            printf("Tecla no valida.\n");
            system("pause");
        }
    }

    return 1;
}

// Función para mostrar los hints de navegación
void mostrar_hint(int indice, int cantidad)
{
    printf("\n");
    if (indice < cantidad - 1)
        printf("<-- (a) "); 
    else
        printf("         ");
    if (indice > 0)
        printf("(d) -->   "); 
    printf("(s) Salir\n");
}

// Función para pedir una tecla válida
char pedir_tecla_valida()
{
    char entrada[10];

    // Bucle hasta que se ingrese una tecla válida
    while (1)
    {
        printf("Ingrese una tecla: ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            entrada[strcspn(entrada, "\n")] = '\0';
        }

        // Validar que solo haya un carácter
        if (entrada[1] != '\0')
        {
            printf("Solo se permite una letra.\n");
            continue;
        }

        char tecla = (char)tolower(entrada[0]);

        // Verificar si es letra
        if (!isalpha(tecla))
        {
            printf(" Debe ingresar una letra.\n");
            continue;
        }

        return tecla;
    }
}