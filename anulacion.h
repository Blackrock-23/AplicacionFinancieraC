#ifndef ANULACION_H
#define ANULACION_H

// Prototipo de la función para anular una compra
int anular_compra();
int ingresarReferencia(char *referencia);
int ingresarUltimosPan(char *ultimopan);
int ingresarCVV(char *cvv);
int buscarYAnularCompra(const char *referencia, const char *ultimopan, const char *cvv);

#endif
