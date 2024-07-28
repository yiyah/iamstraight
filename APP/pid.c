/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "pid.h"

/** @addtogroup APP
  * @{
  */

/** @defgroup PID PID
  * @brief PID APP driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief   Incremental PID
 * @details The PID output is: 
 *          \f[ u(k) = u(k-1) + \Delta u_k
 *                   = K_p \cdot e_k \cdot (1 + \frac{T}{T_i} + \frac{T_d}{T}) - K_p \cdot e_{k-1} \cdot (1 + \frac{2T_d}{T}) + K_p \cdot \frac{T_d}{T} \cdot e_{k-2}
 *          \f]
 * 
 * @param   target 
 * @param   actual 
 */
s16 IPID_Output(s16 target, s16 actual, PID_Typedef pid)
{
    s16 err = target - actual;
    static s16 errPrev = 0;
    static s16 errPPrev = 0;
    static s16 output = 0;

#if DEBUG_PID == 1
    pid.POut = pid.Kp * (f32)err * (1 + pid.T / pid.Ti + pid.Td / pid.T);
    pid.IOut = pid.Kp * (f32)errPrev * (1 + 2 * pid.Td / pid.T);
    pid.DOut = pid.Kp * pid.Td * (f32)errPPrev / pid.T;
#else
    pid.POut = pid.Kp * (f32)err;
    pid.IOut = pid.Ki * (f32)errPrev;
    pid.DOut = pid.Kd * (f32)errPPrev;
#endif

    /* save error */
    errPPrev = errPrev;
    errPrev = err;

    /* output_now = output_prev + Δuk */
    output = output + (s16)(pid.POut - pid.IOut + pid.DOut);
    return output;
}

/**
 * @brief   Positional PID
 * @details The PID output is: \f$ u(k) = (K_p \cdot e_k) + (K_i \cdot \sum_{j=0}^{k}e_j) + [K_d \cdot (e_k - e_{k-1})] \f$
 * @param   target 
 * @param   actual 
 */
s16 PPID_Output(s16 target, s16 actual, PID_Typedef *pid)
{
    s16 err = target - actual;
    static s16 errPrev = 0;
    static s16 errSum = 0;
    s16 output = 0;

    errSum += err;

    (*pid).POut = (*pid).Kp * (f32)err;
#if DEBUG_PID == 1
    (*pid).IOut = (*pid).Kp * (*pid).T * (f32)errSum / (*pid).Ti;
    (*pid).DOut = (*pid).Kp * (*pid).Td * (f32)(err - errPrev) / (*pid).T;
#else
    (*pid).IOut = (*pid).Ki * (f32)errSum;
    (*pid).DOut = (*pid).Kd * (f32)(err - errPrev);
#endif

    errPrev = err;
    output = (s16)((*pid).POut + (*pid).IOut + (*pid).DOut);
    return output;
}
/**
  * @}
  */

/**
  * @}
  */