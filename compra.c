#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "compra.h"

// Ingreso de datos de la compra
void ingreso_dato(compra *com)
{
    printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n ");
    printf("Ingrese la letra 'p' si quiere cancelar la compra\n ");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n ");
    printf("---------- Nueva compra ------------\n");

    char entrada[32];

    // monto
    do
    {
        printf("Ingrese el monto de la compra en dolares (00.00): ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            entrada[strcspn(entrada, "\n")] = '\0';
        }

        if (strcmp(entrada, "p") == 0 || strcmp(entrada, "P") == 0)
        {
            com->monto_compra = -1;
            printf("Compra cancelada.\n");
            return;
        }

        if (validar_monto(entrada))
        {
            // atof convierte una cadena en un float
            com->monto_compra = atof(entrada);
            break;
        }
        else
        {
            printf("Monto invalido.\n");
        }
    } while (1);

    // pan
    do
    {
        printf("Ingrese el PAN (Numero de tarjeta sin puntos ni letras): ");

        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            entrada[strcspn(entrada, "\n")] = '\0';
        }

        if (strcmp(entrada, "p") == 0 || strcmp(entrada, "P") == 0)
        {
            com->monto_compra = -1;
            printf("Compra cancelada.\n");
            return;
        }

        strcpy(com->pan, entrada);

    } while (!validar_tarjeta(com->pan));

    // cvv
    do
    {
        printf("Ingrese el CVV (Solo 3 o 4 digitos): ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            entrada[strcspn(entrada, "\n")] = '\0';
        }

        if (strcmp(entrada, "p") == 0 || strcmp(entrada, "P") == 0)
        {
            com->monto_compra = -1;
            printf("Compra cancelada.\n");
            return;
        }

        strcpy(com->cvv, entrada);

    } while (!validar_cvv(com->cvv));

    // fecha de expiracion
    do
    {
        printf("Ingrese la fecha de expiracion (MM/AA): ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            entrada[strcspn(entrada, "\n")] = '\0';
        }

        if (strcmp(entrada, "p") == 0 || strcmp(entrada, "P") == 0)
        {
            com->monto_compra = -1;
            printf("Compra cancelada.\n");
            return;
        }

        strcpy(com->fecha_Expiracion, entrada);

    } while (!validar_fecha_expiracion(com->fecha_Expiracion));

    // Determinar la franquicia
    hallarfranquicia(com->pan, com->franquicia);

    // Activar la compra
    estadoTransaccion(com);

    printf("Compra registrada exitosamente.\n");
}

// Activar la compra
void estadoTransaccion(compra *com)
{
    strcpy(com->estado, "Activa");
}

// Validar que el monto sea correcto (00.00)
int validar_monto(char *monto)
{
    int antes = 0, despues = 0;
    int punto_encontrado = 0;

    // Validar estructura
    for (int i = 0; monto[i] != '\0'; i++)
    {
        char c = monto[i];

        // Contar dígitos antes y después del punto decimal
        // unsigned char para evitar problemas con caracteres negativos
        if (isdigit((unsigned char)c))
        {
            if (!punto_encontrado)
                antes++;
            else
                despues++;
        }
        else if (c == '.')
        {
            if (punto_encontrado)
                return 0; // más de un punto
            punto_encontrado = 1;
        }
        else
        {
            return 0; // carácter no permitido
        }
    }

    // Si no hay punto, agregar ".00"
    if (!punto_encontrado)
    {
        strcat(monto, ".00");
        punto_encontrado = 1;
        despues = 2;
    }

    // Si tiene 1 decimal agregar un 0
    else if (despues == 1)
    {
        strcat(monto, "0");
        despues = 2;
    }

    // Validaciones finales
    if (antes == 0 || antes > 10)
        return 0;
    if (despues != 2)
        return 0;

    return 1;
}

// Hallar la franquicia de la tarjeta
void hallarfranquicia(const char *pan, char *franquicia)
{

    if (pan[0] == '4')
    {
        strcpy(franquicia, "Visa");
    }
    else if (pan[0] == '5' && (pan[1] >= '1' && pan[1] <= '5'))
    {
        strcpy(franquicia, "MasterCard");
    }
    else if ((strncmp(pan, "34", 2) == 0) || (strncmp(pan, "37", 2) == 0))
    {
        strcpy(franquicia, "American Express");
    }
    else if (strncmp(pan, "6011", 4) == 0 || strncmp(pan, "65", 2) == 0 ||
             (strncmp(pan, "644", 3) >= 0 && strncmp(pan, "649", 3) <= 0))
    {
        strcpy(franquicia, "Discover");
    }
    else if (strncmp(pan, "35", 2) == 0)
    {
        strcpy(franquicia, "JCB");
    }
    else if ((strncmp(pan, "300", 3) >= 0 && strncmp(pan, "305", 3) <= 0) ||
             (strncmp(pan, "36", 2) == 0) || (strncmp(pan, "38", 2) == 0))
    {
        strcpy(franquicia, "Diners Club");
    }
    else
    {
        strcpy(franquicia, "Desconocida");
    }
}

// validar el cvv
int validar_cvv(const char *cvv)
{
    int longitud = (int)strlen(cvv);
    if (longitud < 3 || longitud > 4)
        return 0;

    // Cada carácter debe ser un dígito
    for (int i = 0; i < longitud; i++)
    {
        if (!isdigit((unsigned char)cvv[i]))
            return 0;
    }

    return 1;
}

// validar si es numero
int es_numero(const char *cadena)
{
    int longitud = (int)strlen(cadena);
    for (int i = 0; i < longitud; i++)
    {
        if (!isdigit((unsigned char)cadena[i]))
            return 0;
    }
    return 1;
}

// imprimir los datos
void imprimir(const compra compras[], int cantidad)
{
    printf("===============================================================================================\n");
    printf("%-5s %-13s %-15s %-18s %-8s %-8s %-8s\n",
           "Ref", "Monto", "Franquicia", "PAN", "CVV", "Fecha", "Estado");
    printf("===============================================================================================\n");

    // Filas de datos
    for (int i = cantidad - 1; i >= 0; i--)
    {
        char pan_formateado[32];
        pan_oculto(compras[i].pan, pan_formateado);
        printf("%-5s %-13.2lf %-15s %-18s %-6s %-8s %-8s\n",
               compras[i].referencia,
               compras[i].monto_compra,
               compras[i].franquicia,
               pan_formateado,
               compras[i].cvv,
               compras[i].fecha_Expiracion,
               compras[i].estado);
    }
    printf("===============================================================================================\n");
}

// Registrar las compras (Es la funcion principal)
void registrar_compras()
{
    FILE *archivo = fopen(ARCHIVO, "ab+");
    if (!archivo)
    {
        printf("Error al abrir archivo");
        return;
    }

    int cantidad = 0;
    compra temp;

    // Mover el puntero al inicio para poder leer las compras existentes
    rewind(archivo);

    // Contar las compras existentes en el archivo.
    while (fread(&temp, sizeof(compra), 1, archivo) == 1)
    {
        // Cada compra leída incrementa el contador
        cantidad++;
    }

    // Verificar si se ha alcanzado el limite
    if (cantidad >= MAX_COMPRAS)
    {
        printf(" Ya existen 20 compras registradas. No se pueden agregar mas.\n");
        fclose(archivo);
        return;
    }

    // Asignar memoria para una compra temporal
    compra *compras = malloc(sizeof(compra));
    if (!compras)
    {
        printf("Error al asignar memoria");
        fclose(archivo);
        return;
    }

    int agregar = 1;
    char entrada[10];
    // Guardar nuevas compras
    while (agregar && cantidad < MAX_COMPRAS)
    {

        // Ingresar los datos de la compra
        ingreso_dato(&compras[0]);

        // validar si se cancelo o no
        if (compras[0].monto_compra == -1)
        {
            break;
        }

        // Asignar la referencia
        sprintf(compras[0].referencia, "%d", cantidad + 100);

        pan_unido(compras[0].pan);

        // Guardar la compra en el archivo
        fwrite(&compras[0], sizeof(compra), 1, archivo);

        cantidad++;
        system("cls");
        printf("Compra guardada (%d/20)\n", cantidad);

        // Mostrar los datos ingresados
        imprimir(&compras[0], 1);

        // Verificar si no se ha alcanzado el limite
        if (cantidad < MAX_COMPRAS)
        {

            do
            {
                printf("Desea registrar otra compra (1=Si, 0=No): ");
                if (fgets(entrada, sizeof(entrada), stdin) != NULL)
                {
                    entrada[strcspn(entrada, "\n")] = '\0';
                }

                if (strlen(entrada) == 1 && entrada[0] >= '0' && entrada[0] <= '1')
                {
                    agregar = entrada[0] - '0';
                }
                else
                {
                    agregar = -1;
                    printf("Entrada invalida. Por favor ingrese 1 para Si o 0 para No.\n");
                }
            } while (agregar == -1);

            system("cls");
        }
        else
        {
            printf("Se alcanzo el limite de 20 compras.\n");
        }
    }

    // Liberar memoria y cerrar el archivo
    free(compras);
    fclose(archivo);
}

// valida la fecha expiracion
int validar_fecha_expiracion(const char *fecha)
{
    int mes, anio;
    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm *fecha_actual = localtime(&t);

    int mes_actual = fecha_actual->tm_mon + 1;
    int anio_actual = (fecha_actual->tm_year + 1900) % 100;

    // Comprobar el formato MM/AA
    if (sscanf(fecha, "%2d/%2d", &mes, &anio) != 2)
    {
        printf("Formato de fecha invalido. Use MM/AA.\n");
        return 0;
    }

    // Comprobar mes
    if (mes < 1 || mes > 12)
    {
        printf("Mes invalido.\n");
        return 0;
    }

    // Comprobar si la tarjeta está vencida
    if (anio < anio_actual || (anio == anio_actual && mes < mes_actual))
    {
        printf("La tarjeta esta vencida (%02d/%02d).\n", mes, anio);
        return 0;
    }

    return 1;
}

// valida la tarjeta con el algoritmo de luhn
int validar_tarjeta(const char *pan)
{
    char cadenaDigitos[64];
    int cantidadDijitos = 0;

    // Extraer solo los dígitos del PAN
    for (int i = 0; pan[i] != '\0'; i++)
    {
        char c = pan[i];
        if (isdigit((unsigned char)c))
        {
            if (cantidadDijitos < (int)sizeof(cadenaDigitos) - 1)
                cadenaDigitos[cantidadDijitos++] = c;
            else
                return 0;
        }
        else if (c == ' ' || c == '-')
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    // Asegurar que la cadena termine con null
    cadenaDigitos[cantidadDijitos] = '\0';

    int cantidad = cantidadDijitos;

    // Validar la longitud del PAN
    if (cantidad < 13 || cantidad > 19)
        return 0;
    int sumatoria = 0;

    // Aplicar el algoritmo de Luhn
    for (int k = cantidad - 1, pos = 0; k >= 0; k--, pos++)
    {
        int valor = cadenaDigitos[k] - '0';
        if (pos % 2 == 1)
        {
            valor *= 2;
            if (valor > 9)
                valor -= 9;
        }
        sumatoria += valor;
    }

    // Validar si la suma es múltiplo de 10
    if (sumatoria % 10 == 0)
    {
        return 1;
    }
    else
        return 0;
}

// Ocultar los digitos del pan, mostrando solo los primeros 4 y los ultimos 4
void pan_oculto(const char *pan, char *resultado)
{
    int len = (int)strlen(pan);
    if (len <= 8) // mostrar todo si es muy corto
    {
        strcpy(resultado, pan);
        return;
    }

    // Copiar los primeros 4
    strncpy(resultado, pan, 4);

    // Rellenar con '*' los intermedios
    for (int i = 4; i < len - 4; i++)
        resultado[i] = '*';

    // Copiar los últimos 4
    strncpy(resultado + len - 4, pan + len - 4, 4);

    resultado[len] = '\0'; // terminar cadena
}

// Unir los digitos del pan, removiendo espacios o guiones
int pan_unido(char *pan)
{
    char cadenaDigitos[64];
    int cantidadDijitos = 0;

    for (int i = 0; pan[i] != '\0'; i++)
    {
        char c = pan[i];
        if (isdigit((unsigned char)c))
        {
            if (cantidadDijitos < (int)sizeof(cadenaDigitos) - 1)
                cadenaDigitos[cantidadDijitos++] = c;
            else
                return 0;
        }
        else if (c == ' ' || c == '-')
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    // Asegurar que la cadena termine con null
    cadenaDigitos[cantidadDijitos] = '\0';

    // Copiar de vuelta al pan original
    strcpy(pan, cadenaDigitos);
    return 1;
}
