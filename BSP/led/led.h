#ifndef __LED_H__
#define __LED_H__

typedef enum
{
    /* ADD LED BEGIN 1 */
    LED0 = 0,

    /* ADD LED END 1 */

    LED_TOTAL,   // Do not move to bottom

    /* ADD LED BEGIN 2 */
    LED_BLUE = LED0

    /* ADD LED END 2 */
}Led_TypeDef;
#define LEDn                LED_TOTAL

#define LED0_PIN            GPIO_PIN_4
#define LED0_GPIO_Port      GPIOA
#define LED0_WORK_STATE     GPIO_PIN_SET    /* LED ON when set pin */

void BSP_LED_ON(Led_TypeDef led_index);
void BSP_LED_OFF(Led_TypeDef led_index);
void BSP_LED_Toggle(Led_TypeDef Led);

#endif /* __LED_H__ */
