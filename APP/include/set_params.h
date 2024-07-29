/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SET_PARAMS_H
#define __SET_PARAMS_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef void (*PTRFUNC)(u8 cmd, f32 value);
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void PARAMS_vRegisterCallBackFunc(PTRFUNC pf);
s32 PARAMS_vSetParams(const u8 *pdata, u8 len);

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#endif