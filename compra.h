#ifndef COMPRA_H
#define COMPRA_H

// Struct para almacenar los datos de la compra
typedef struct
{
    double monto_compra;
    char pan[32];
    char cvv[5];
    char fecha_Expiracion[6];
    int referencia;
    char franquicia[20];
    char estado[10];
} compra;

// definiciones
#define MAX_COMPRAS 20
#define ARCHIVO "compras.bin"

// Prototipos de funciones
void ingreso_dato(compra *com);
void imprimir(const compra compras[], int cantidad);
void almacenamiento_archivo(compra *compras, int cantidad);
void registrar_compras();
int validar_fecha_expiracion(const char *fecha);
int validar_tarjeta(const char *pan);
int validar_cvv(const char *cvv);
void hallarfranquicia(const char *pan, char *franquicia);
void estadoTransaccion(compra *com);
int pan_unido( char *pan);
int es_numero(const char *cadena);
int validar_monto( char *monto_str);
void pan_oculto(const char *pan, char *resultado);

#endif
