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
f32 IPID_Output(f32 target, f32 actual, PID_Typedef *pid)
{
    s16 err = target - actual;
    f32 f32output = 0.0F;

#if DEBUG_PID == 1
    (*pid).POut = (*pid).Kp * (f32)err * (1 + (*pid).T / (*pid).Ti + (*pid).Td / (*pid).T);
    (*pid).IOut = (*pid).Kp * (f32)(*pid).errPrev * (1 + 2 * (*pid).Td / (*pid).T);
    (*pid).DOut = (*pid).Kp * (*pid).Td * (f32)(*pid).errPPrev / (*pid).T;
#else
    (*pid).POut = (*pid).Kp * (f32)err;
    (*pid).IOut = (*pid).Ki * (f32)(*pid).errPrev;
    (*pid).DOut = (*pid).Kd * (f32)(*pid).errPPrev;
#endif

    /* save error */
    (*pid).errPPrev = (*pid).errPrev;
    (*pid).errPrev = err;

    /* output_now = output_prev + Δuk */
    f32output = pid->f32Output + ((*pid).POut - (*pid).IOut + (*pid).DOut);

    /* check the max/min value */
    if (f32output > pid->f32OutputMax)
    {
        pid->f32Output = pid->f32OutputMax;
    }
    else if (f32output < -pid->f32OutputMax)
    {
        pid->f32Output = -pid->f32OutputMax;
    }
    else
    {
        /* f32output in range: [-Max, Max] */
        pid->f32Output = (s16)f32output;
    }

    return pid->f32Output;
}

/**
 * @brief   Positional PID
 * @details The PID output is: \f$ u(k) = (K_p \cdot e_k) + (K_i \cdot \sum_{j=0}^{k}e_j) + [K_d \cdot (e_k - e_{k-1})] \f$
 * @param   target 
 * @param   actual 
 */
f32 PPID_Output(f32 target, f32 actual, PID_Typedef *pid)
{
    f32 err = target - actual;
    f32 f32output = 0.0F;

    (*pid).errSum += err;

    (*pid).POut = (*pid).Kp * (f32)err;
#if DEBUG_PID == 1
    (*pid).IOut = (*pid).Kp * (*pid).T * (f32)(*pid).errSum / (*pid).Ti;
    (*pid).DOut = (*pid).Kp * (*pid).Td * (f32)(err - (*pid).errPrev) / (*pid).T;
#else
    (*pid).IOut = (*pid).Ki * (f32)(*pid).errSum;
    (*pid).DOut = (*pid).Kd * (f32)(err - (*pid).errPrev);
#endif

    /* integral separation */
    if (((pid->errSum > -pid->f32IntegralSepThreshold)
        && (pid->errSum < 0.0F))
    || ((pid->errSum < pid->f32IntegralSepThreshold)
        && (pid->errSum > 0.0F)))
    {
        pid->IOut = 0;
    }
    else
    {
        /* keep pid->IOut */
    }

    pid->errPrev = err;
    f32output = pid->POut + pid->IOut + pid->DOut;
    
    /* check the max/min value */
    if (f32output > pid->f32OutputMax)
    {
        pid->f32Output = pid->f32OutputMax;
    }
    else if (f32output < -pid->f32OutputMax)
    {
        pid->f32Output = -pid->f32OutputMax;
    }
    else
    {
        /* f32output in range: [-Max, Max] */
        pid->f32Output = (s16)f32output;
    }

    return pid->f32Output;
}
/**
  * @}
  */

/**
  * @}
  */