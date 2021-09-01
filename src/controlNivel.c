#include "controlNivel.h"

#define UMBRAL_ALERTA 75 //Umbral para generar una alerta en porcentaje del tacho que esta lleno
#define UMBRAL_ALARMA 35 //Umbral para generar una alarma

bool* led_ok_dir;
bool* led_alerta_dir;
bool* led_alarma_dir;
uint8_t* nivel_alerta_dir;
uint8_t* nivel_alarma_dir;
uint8_t ultima_medida;

void controlNivelInit(bool* led_ok, bool* led_alerta, bool* led_alarma, uint8_t* nivel_alerta, uint8_t* nivel_alarma)
{
    led_ok_dir = led_ok;
    led_alerta_dir = led_alerta;
    led_alarma_dir = led_alarma;
    *led_ok_dir = true;
    *led_alerta_dir = false;
    *led_alarma_dir = false;
    nivel_alerta_dir = nivel_alerta;
    nivel_alarma_dir = nivel_alarma;
}

void actualizarControlNivel(uint8_t nivel_medido)
{
    ultima_medida = nivel_medido;
    if (nivel_medido > *nivel_alerta_dir) {
        *led_ok_dir = true;
        *led_alarma_dir = false;
        *led_alerta_dir = false;
    }
    if (*led_ok_dir & (nivel_medido < *nivel_alerta_dir)) {
        *led_ok_dir = false;
        *led_alerta_dir = true;
    }
    if (nivel_medido < *nivel_alarma_dir) {
        *led_alerta_dir = false;
        *led_alarma_dir = true;
    }
}

void actualizarlNiveles(uint8_t alerta_new, uint8_t alarma_new)
{
    *nivel_alerta_dir = alerta_new;
    *nivel_alarma_dir = alarma_new;
    actualizarControlNivel(ultima_medida);
}