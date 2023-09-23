/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "stm32f1xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @defgroup LED LED
  * @brief LED BSP driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup LED_Private_Constants LED Private Constants
  * @{
  */

/** @defgroup LED_Private_Constants_LED0 LED0
  * @brief Define the GPIO and work state of LED0
  * @{
  */
#define LED0_PIN            GPIO_PIN_4
#define LED0_GPIO_Port      GPIOA
#define LED0_WORK_STATE     GPIO_PIN_SET    /*!< LED ON when set pin */
/**
  * @}
  */
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup LED_Private_Variables LED Private Variables
  * @{
  */
GPIO_TypeDef* LED_PORT[LEDn] = {LED0_GPIO_Port};
const uint16_t LED_PIN[LEDn] = {LED0_PIN};

/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup LED_Exported_Functions LED Exported Functions
  * @{
  */
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
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
