#ifndef _CONTROL_NIVEL_H_
#define _CONTROL_NIVEL_H_

#include "stdbool.h"
#include "stdint.h"

void controlNivelInit(bool* led_ok, bool* led_alerta, bool* led_alarma, uint8_t* nivel_alerta, uint8_t* nivel_alarma);
void actualizarControlNivel(uint8_t nivel_medido);
void actualizarlNiveles(uint8_t alerta_new, uint8_t alarma_new);

#endif