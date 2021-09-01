/* _Si el nivel se encuentra por encima de la altura de alerta solo se tiene que encender el led verde.
   _Si el nivel baja de la altura de alerta y queda entre el nivel de alertay alarma se tiene que encender solo el led amarillo.
   _Si el nivel baja de la altura de alarma desde estado de alarma se tiene que encender solo el led rojo.
   _Si el nivel baja desde la altura ok por debajo de alarma se tiene que encender solo el led rojo.
   _Si el nivel pasa de estar por debajo de la altura de alarma a estar por encima de alerta solo se enciende el led verde.
   _Si el nivel pasa de estar por debajo de la altura de alarma a estar entre alarma y alerta el led queda en rojo.
   _Si el nivel pasa de estar entre los niveles de alerta y alarma a estar por encima del de alerta y led amarillo estaba encendido, 
    pasa a quedar encendido solo el verde.
   _Los niveles se tienen que poder modificar en tiempo de ejecucion.
   _El estado se tiene que actualizar automaticamente cuando se modifican los niveles.
*/

#include "controlNivel.h"
#include "stdbool.h"
#include "unity.h"

bool led_verde;
bool led_amarillo;
bool led_rojo;
uint8_t nivel_alerta;
uint8_t nivel_alarma;

void setUp(void)
{
    nivel_alerta = 75;
    nivel_alarma = 35;
    controlNivelInit(&led_verde, &led_amarillo, &led_rojo, &nivel_alerta, &nivel_alarma);
}

void tearDown(void)
{
}

/*_Si el nivel se encuentra por encima de la altura de alerta solo se tiene que encender el led verde.*/
void test_nivelEncimaAlerta(void)
{
    uint8_t nivel_medido = 80;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((led_verde & ~led_amarillo & ~led_rojo));
}

/*_Si el nivel baja de la altura de alerta y queda entre el nivel de alertay alarma se tiene que encender solo el led amarillo.*/
void test_nivelEntreAlertaAlarmaDesdeSuperior(void)
{
    uint8_t nivel_medido = 80;
    actualizarControlNivel(nivel_medido);
    nivel_medido = 60;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((~led_verde & led_amarillo & ~led_rojo));
}

/*_Si el nivel baja de la altura de alarma desde estado de alarma se tiene que encender solo el led rojo.*/
void test_nivelDebajoAlarmaDesdeAlerta(void)
{
    uint8_t nivel_medido = 60;
    actualizarControlNivel(nivel_medido);
    nivel_medido = 30;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((~led_verde & ~led_amarillo & led_rojo));
}

/*_Si el nivel baja desde la altura ok por debajo de alarma se tiene que encender solo el led rojo.*/
void test_nivelDebajoAlarmaDesdeOk(void)
{
    uint8_t nivel_medido = 30;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((~led_verde & ~led_amarillo & led_rojo));
}

/*_Si el nivel pasa de estar por debajo de la altura de alarma a estar por encima de alerta solo se enciende el led verde.*/
void test_nivelOkDesdeAlarma(void)
{
    uint8_t nivel_medido = 30;
    actualizarControlNivel(nivel_medido);
    nivel_medido = 80;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((led_verde & ~led_amarillo & ~led_rojo));
}

/*_Si el nivel pasa de estar por debajo de la altura de alarma a estar entre alarma y alerta el led queda en rojo.*/
void test_nivelEntreAlertaAlarmaDesdeAlarma(void)
{
    uint8_t nivel_medido = 30;
    actualizarControlNivel(nivel_medido);
    nivel_medido = 60;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((~led_verde & ~led_amarillo & led_rojo));
}

/*_Si el nivel pasa de estar entre los niveles de alerta y alarma a estar por encima del de alerta y led amarillo estaba encendido, 
    pasa a quedar encendido solo el verde.*/
void test_nivelOkDesdeEntreAlertaAlarma(void)
{
    uint8_t nivel_medido = 60;
    actualizarControlNivel(nivel_medido);
    nivel_medido = 80;
    actualizarControlNivel(nivel_medido);
    TEST_ASSERT_TRUE((led_verde & ~led_amarillo & ~led_rojo));
}

/*_Los niveles se tienen que poder modificar en tiempo de ejecucion.*/
void test_ActualizacionDeNiveles(void)
{
    uint8_t alerta_new = 80;
    uint8_t alarma_new = 40;
    actualizarlNiveles(alerta_new, alarma_new);
    TEST_ASSERT_TRUE((alerta_new == nivel_alerta) & (alarma_new == nivel_alarma));
}

/*_El estado se tiene que actualizar automaticamente cuando se modifican los niveles.*/
void test_ActualizacionDeNivelesYEstados(void)
{
    uint8_t alerta_new = 80;
    uint8_t alarma_new = 40;
    uint8_t nivel_medido = 75;
    bool prueba_alerta = false;
    bool prueba_alarma = false;
    actualizarlNiveles(alerta_new, alarma_new);
    actualizarControlNivel(nivel_medido);
    prueba_alerta = (~led_verde & led_amarillo & ~led_rojo);
    nivel_medido = 35;
    actualizarControlNivel(nivel_medido);
    prueba_alarma = (~led_verde & ~led_amarillo & led_rojo);
    TEST_ASSERT_TRUE(prueba_alerta & prueba_alarma);
}