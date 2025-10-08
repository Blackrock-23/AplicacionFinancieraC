#ifndef COMPRA_H
#define COMPRA_H

typedef struct {
    double monto_compra;
    char pan[32];
    int cvv;
    char fecha_Expiracion[6];
    int referencia;
} compra;

#define MAX_COMPRAS 20
#define ARCHIVO "compras.txt"

void ingreso_dato(compra *com);
void imprimir(const compra *com);
void almacenamiento_archivo(compra *compras, int cantidad);
void registrar_compras();
int validar_fecha_expiracion(const char *fecha);

#endif
