
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "pid.h"

/** @addtogroup APP
  * @{
  */

/** @defgroup CAR CAR
  * @brief CAR Application
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

typedef struct
{
    u16     diameter_mm;                /*!< The diamete of wheel, unit: mm */
    s16     pulse;                      /*!< The pulse of wheel */
    f32     rotationSpeed_rps;          /*!< The rotation speed of wheel, unit: revolutions per second */
} WHEEL_TypeDef;


typedef struct
{
    WHEEL_TypeDef   leftWheel;
    WHEEL_TypeDef   rightWheel;
    PID_Typedef     velocityPID;
    void            (*pControl)();
} CAR_TypeDef;

/* Private define ------------------------------------------------------------*/

/**
 * @brief How often is the task called.
 * @note  unit: ms
 */
#define     PERIODOFTASK        5U

/**
 * @brief The encoder counts corresponding to one cricle of the wheel.
 */
#define     CNTOFONECIRCLE      1560U

/**
 * @brief The factor that converts the pulse into rotational speed.
 * @details                 pulse        pulse       pulse * 1000      
 *          rotate speed = ------- = ------------ = -------------- = pulse * 0.1282051282 (rps)
 *                          Z * T     1560 * 5ms      1560 * 5s
 *          Z = 1560 means the wheel turns in one turn, and the encoder outputs how many pulses.
 */
#define     PULSE2ROTATESPEED   0.1282F

#define     PID_SAMPLETIME_T    PERIODOFTASK
#define     PID_VELOCITY_Kp     1.0F
#define     PID_VELOCITY_Ti     0.0F
#define     PID_VELOCITY_Td     0.0F

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CAR_TypeDef     IAMSTRAIGHT;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



static void calculate_speed()
{
    BSP_Get_Encoder_Count_PerUnitTime(&IAMSTRAIGHT.leftWheel.pulse, &IAMSTRAIGHT.rightWheel.pulse);
    IAMSTRAIGHT.leftWheel.rotationSpeed_rps  = (f32)(IAMSTRAIGHT.leftWheel.pulse * PULSE2ROTATESPEED);
    IAMSTRAIGHT.rightWheel.rotationSpeed_rps = (f32)(IAMSTRAIGHT.rightWheel.pulse * PULSE2ROTATESPEED);
}

void control(s16 *l_curPulse, s16 *r_curPulse)
{
    calculate_speed();
    *l_curPulse = IAMSTRAIGHT.leftWheel.pulse;
    *r_curPulse = IAMSTRAIGHT.rightWheel.pulse;
    // PID_Output(0, IAMSTRAIGHT.leftWheel.pulse);
    // PID_Output(0, IAMSTRAIGHT.rightWheel.pulse);
    // BSP_SetMotorPWMPulse(l_pulse, r_pulse);
}
/* Exported functions --------------------------------------------------------*/
void car_Init()
{
    IAMSTRAIGHT.leftWheel.diameter_mm  = 800;
    IAMSTRAIGHT.rightWheel.diameter_mm = 800;
    IAMSTRAIGHT.pControl = control;
    IAMSTRAIGHT.velocityPID.T  = PID_SAMPLETIME_T;
    IAMSTRAIGHT.velocityPID.Kp = PID_VELOCITY_Kp;
    IAMSTRAIGHT.velocityPID.Ti = PID_VELOCITY_Ti;
    IAMSTRAIGHT.velocityPID.Td = PID_VELOCITY_Td;
}
/**
  * @}
  */

/**
  * @}
  */
