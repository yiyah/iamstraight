/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PID_H
#define __PID_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#define DEBUG_PID 1

typedef struct
{
#if DEBUG_PID == 1
    /* for debug use */
    u8  T;                   /* sample time, unit: ms */
    f32 Kp;
    f32 Ti;
    f32 Td;
    f32 POut;
    f32 IOut;
    f32 DOut;
#else /* DEBUG_PID == 1 */
    /* for release use */
    f32 Ki;
    f32 kd;
#endif /* DEBUG_PID == 1 */
    s16 errPrev;            /* for IPID, PPID */
    s16 errPPrev;           /* for IPID */
    s16 errSum;             /* for PPID */
    s16 output;             /* for IPID, PPID */
} PID_Typedef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

s16 IPID_Output(s16 target, s16 actual, PID_Typedef *pid);
s16 PPID_Output(s16 target, s16 actual, PID_Typedef *pid);

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#endif
