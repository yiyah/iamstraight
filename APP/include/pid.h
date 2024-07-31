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
    u8  T;                  /* sample time, unit: ms */
    f32 Kp;                 /* Need to initialize */
    f32 Ti;                 /* Need to initialize */
    f32 Td;                 /* Need to initialize */
    f32 POut;
    f32 IOut;
    f32 DOut;
#else /* DEBUG_PID == 1 */
    /* for release use */
    f32 Ki;                 /* Need to initialize */
    f32 kd;                 /* Need to initialize */
#endif /* DEBUG_PID == 1 */
    s16 errPrev;            /* for IPID, PPID */
    s16 errPPrev;           /* for IPID */
    s16 errSum;             /* for PPID */
    s16 s16Output;          /* for IPID, PPID */
    u16 u16OutputMax;       /* for IPID, PPID. Need to initialize */
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
