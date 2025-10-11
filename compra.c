#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "compra.h"

// Ingreso de datos de la compra
void ingreso_dato(compra *com)
{
    printf("--- Nueva compra ---\n");

    char entrada[32];
    do
    {
        printf("Ingrese el monto de la compra en dolares (00.00): ");
        scanf("%s", entrada);

        //se llama a la funcion validar monto
        if (validar_monto(entrada))
        {
            com->monto_compra = atof(entrada);
            break;
        }
        else
        {
            printf("Monto invalido.\n");
        }
    } while (1);
    getchar();

    printf("Ingrese el PAN(Numero de tarjeta sin puntos ni letras): ");
    gets(com->pan);

    // Validar el PAN
    while (!validar_tarjeta(com->pan))
    {
        printf("La tarjeta no es valida, vuelve ingresar el valor: ");
        gets(com->pan);
    }

    printf("Ingrese el CVV (Solo 3 o 4 dijitos):");
    gets(com->cvv);

    // Validar el CVV
    while (!validar_cvv(com->cvv))
    {
        printf("El CVV no es valido, vuelve ingresar el valor: ");
        gets(com->cvv);
    }

    // Determinar la franquicia
    hallarfranquicia(com->pan, com->franquicia);

    printf("Ingrese la fecha de expiracion (MM/AA): ");
    gets(com->fecha_Expiracion);

    // Validar la fecha de expiracion
    while (!validar_fecha_expiracion(com->fecha_Expiracion))
    {
        printf("Vuelva a ingresar una fecha valida (MM/AA): ");
        gets(com->fecha_Expiracion);
    }

    // Activar la compra
    estadoTransaccion(com);
}

// Activar la compra
void estadoTransaccion(compra *com)
{
    strcpy(com->estado, "Activa");
}

int validar_monto(char *monto_str)
{
    int antes = 0, despues = 0;
    int punto_encontrado = 0;

    // Validar estructura
    for (int i = 0; monto_str[i] != '\0'; i++)
    {
        char c = monto_str[i];
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
        strcat(monto_str, ".00");
        punto_encontrado = 1;
        despues = 2;
    }

    // Si tiene 1 decimal → agregar un 0
    else if (despues == 1)
    {
        strcat(monto_str, "0");
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
    printf("%-5s %-13s %-15s %-18s %-6s %-8s %-8s\n",
           "Ref", "Monto", "Franquicia", "PAN", "CVV", "Fecha", "Estado");
    printf("===============================================================================================\n");

    // Filas de datos
    for (int i = cantidad - 1; i >= 0; i--)
    {
        printf("%-5d %-13.2lf %-15s %-18s %-6s %-8s %-8s\n",
               compras[i].referencia,
               compras[i].monto_compra,
               compras[i].franquicia,
               compras[i].pan,
               compras[i].cvv,
               compras[i].fecha_Expiracion,
               compras[i].estado);
    }
    printf("===============================================================================================\n");
}

// Almacenar el archivo
void almacenamiento_archivo(compra *compras, int cantidad)
{

    // Abrir el archivo
    FILE *archivo = fopen("compras.txt", "a");
    if (!archivo)
    {
        printf("Error al abrir el archivo");
        return;
    }

    // Escribir cada compra en el archivo
    for (int i = 0; i < cantidad; i++)
    {

        fprintf(archivo, "Numero de Referencia: %i\n\n", compras[i].referencia);
        fprintf(archivo, "Monto: %.2f\n", compras[i].monto_compra);
        fprintf(archivo, "PAN: %s\n", compras[i].pan);
        fprintf(archivo, "Franquicia: %s\n", compras[i].franquicia);
        fprintf(archivo, "CVV: %s\n", compras[i].cvv);
        fprintf(archivo, "Fecha de vencimiento: %s\n\n", compras[i].fecha_Expiracion);
        fprintf(archivo, "Estado: %s\n", compras[i].estado);
    }

    // Cerrar el archivo
    fclose(archivo);
    printf("Compras guardadas en 'compras.txt'");
}

// Registrar las compras (Es la funcion principal)
void registrar_compras()
{
    FILE *archivo = fopen(ARCHIVO, "a+");
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
    // El formato debe coincidir exactamente con lo que se escribe en el archivo (nota la capitalización
    // y ausencia de espacios extra antes de 'Estado').
    while (fscanf(archivo, "Referencia: %d\nMonto: %lf\nPAN: %31[^\n]\nFranquicia: %19[^\n]\nCVV: %4[^\n]\nFecha de Vencimiento: %5[^\n]\nEstado: %9[^\n]\n\n",
                  &temp.referencia, &temp.monto_compra, temp.pan, temp.franquicia, temp.cvv, temp.fecha_Expiracion, temp.estado) == 7)
    {
        // Cada compra leida incrementa el contador
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
        // Incrementar la referencia
        compras[0].referencia = cantidad + 1;

        // Ingresar los datos de la compra
        ingreso_dato(&compras[0]);

        pan_unido(compras[0].pan);

        // Guardar la compra en el archivo
        fprintf(archivo, "Referencia: %d\nMonto: %.2f\nPAN: %s\nFranquicia: %s\nCVV: %s\nFecha de Vencimiento: %s\nEstado: %s\n\n",
                compras[0].referencia, compras[0].monto_compra,
                compras[0].pan, compras[0].franquicia,
                compras[0].cvv, compras[0].fecha_Expiracion,
                compras[0].estado);

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
                scanf("%s", entrada);

                if (isdigit(entrada[0]) && entrada[1] == '\0')
                    agregar = entrada[0] - '0';
                else
                    agregar = -1;

                if (agregar != 0 && agregar != 1)
                    printf("Opcion invalida. Ingrese 1 o 0.\n");

            } while (agregar != 0 && agregar != 1);

            system("cls");
            getchar();
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

    if (sumatoria % 10 == 0)
    {
        return 1;
    }
    else
        return 0;
}

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
    cadenaDigitos[cantidadDijitos] = '\0';
    strcpy(pan, cadenaDigitos);
    return 1;
}
