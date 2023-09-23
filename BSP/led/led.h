/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H__
#define __LED_H__

/* Includes ------------------------------------------------------------------*/

/** @addtogroup BSP
  * @{
  */

/** @addtogroup LED
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/** @defgroup LED_Exported_Types LED Exported Types
  * @{
  */
/**
 * @brief LED Types Definition
 * @note  The enumeration value of @LED_TOTAL should be calculated automatically. \n
 *        So do not change its position
 */
typedef enum
{
    /* ADD LED BEGIN 1 */
    LED0 = 0,                   /*!< index of LED0 */

    /* ADD LED END 1 */
    LED_TOTAL,                  /*!< total number of LEDs */
    /* ADD LED BEGIN 2 */
    LED_BLUE = LED0             /*!< map LED0 to its color*/

    /* ADD LED END 2 */
}Led_TypeDef;
/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup LED_Exported_Types LED Exported Types
  * @{
  */
#define LEDn                LED_TOTAL   /*!< the total number of LED */
/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup LED_Exported_Functions LED Exported Functions
  * @{
  */
void BSP_LED_ON(Led_TypeDef led_index);
void BSP_LED_OFF(Led_TypeDef led_index);
void BSP_LED_Toggle(Led_TypeDef Led);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* __LED_H__ */
