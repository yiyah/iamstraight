/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PID_H
#define __PID_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct
{
    u8  T;                   /* sample time, unit: ms */
    f32 Kp;
    f32 Ti;
    f32 Td;

    /* for release use */
    f32 Ki;
    f32 kd;
} PID_Typedef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

s16 IPID_Output(s16 target, s16 actual, PID_Typedef pid);
s16 PPID_Output(s16 target, s16 actual, PID_Typedef pid);

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#endif
