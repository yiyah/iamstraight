#include "led.h"
#include "stm32f1xx_hal.h"


GPIO_TypeDef* LED_PORT[LEDn] = {LED0_GPIO_Port};
const uint16_t LED_PIN[LEDn] = {LED0_PIN};

/**
 * @brief Turns selected LED on.
 * @param led_index: Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED_BLUE
 */
void BSP_LED_ON(Led_TypeDef led_index)
{
    HAL_GPIO_WritePin(LED_PORT[led_index], LED_PIN[led_index], LED0_WORK_STATE);
}

/**
 * @brief Turns selected LED off.
 * @param led_index: Specifies the Led to be set off.
 *   This parameter can be any value of @ref Led_TypeDef:
 *     @arg LED_BLUE
 */
void BSP_LED_OFF(Led_TypeDef led_index)
{
    HAL_GPIO_WritePin(LED_PORT[led_index], LED_PIN[led_index], !LED0_WORK_STATE);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg  LED_BLUE
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}
