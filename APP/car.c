
/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "set_params.h"
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
    u16             diameter_mm;                /*!< The diamete of wheel, unit: mm */
    s16             pulse;                      /*!< The pulse of wheel */
    f32             rotationSpeed_rps;          /*!< The rotation speed of wheel, unit: revolutions per second */
    PID_Typedef     velocityPID;
} WHEEL_TypeDef;

typedef struct
{
    WHEEL_TypeDef   leftWheel;
    WHEEL_TypeDef   rightWheel;
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
#define     PID_VELOCITY_Ti     100000.0F
#define     PID_VELOCITY_Td     0.0F

#define     PID_OUTPUT_MAX      7200U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

CAR_TypeDef     IAMSTRAIGHT;
extern s16 s16l_target, s16r_target;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void calculate_speed()
{
    // BSP_Get_Encoder_Count_PerUnitTime(&IAMSTRAIGHT.leftWheel.pulse, &IAMSTRAIGHT.rightWheel.pulse);
    IAMSTRAIGHT.leftWheel.rotationSpeed_rps  = (f32)(IAMSTRAIGHT.leftWheel.pulse * PULSE2ROTATESPEED);
    IAMSTRAIGHT.rightWheel.rotationSpeed_rps = (f32)(IAMSTRAIGHT.rightWheel.pulse * PULSE2ROTATESPEED);
}

/**
 * @brief 
 * target(5ms): max:48 -- 7200pwm
 *          5 -- 1000pwm
 *          1 -- 200pwm
 * @param l_targetPulse 
 * @param r_targetPulse 
 * @param l_curPulse 
 * @param r_curPulse 
 * @param l_output 
 * @param r_output 
 */
void control(const s16 l_targetPulse, const s16 r_targetPulse,
             const s16 l_curPulse, const s16 r_curPulse,
             s16 *l_output, s16 *r_output)
{
    IAMSTRAIGHT.leftWheel.pulse  = l_curPulse;
    IAMSTRAIGHT.rightWheel.pulse = r_curPulse;
    // calculate_speed();

    *l_output = PPID_Output(l_targetPulse, IAMSTRAIGHT.leftWheel.pulse, &IAMSTRAIGHT.leftWheel.velocityPID);
    *r_output = PPID_Output(r_targetPulse, IAMSTRAIGHT.rightWheel.pulse, &IAMSTRAIGHT.rightWheel.velocityPID);
}

void vSetParams(u8 cmd, f32 val)
{
    switch (cmd)
    {
    case 'p':
    case 'P':
        IAMSTRAIGHT.leftWheel.velocityPID.Kp = val;
        IAMSTRAIGHT.rightWheel.velocityPID.Kp = val;
        break;
    case 'i':
    case 'I':
        IAMSTRAIGHT.leftWheel.velocityPID.Ti = val;
        IAMSTRAIGHT.rightWheel.velocityPID.Ti = val;
        break;
    case 'd':
    case 'D':
        IAMSTRAIGHT.leftWheel.velocityPID.Td = val;
        IAMSTRAIGHT.rightWheel.velocityPID.Td = val; 
        break;
    case 'l':
    case 'L':
        s16l_target = (s16)val;
        break;
    case 'r':
    case 'R':
        s16r_target = (s16)val; 
        break;
    default:
        break;
    }
}

/* Exported functions --------------------------------------------------------*/

void car_Init()
{
    IAMSTRAIGHT.leftWheel.diameter_mm  = 800;
    IAMSTRAIGHT.rightWheel.diameter_mm = 800;
    // IAMSTRAIGHT.pControl = control;
    IAMSTRAIGHT.leftWheel.velocityPID.T  = PID_SAMPLETIME_T;
    IAMSTRAIGHT.leftWheel.velocityPID.Kp = PID_VELOCITY_Kp;
    IAMSTRAIGHT.leftWheel.velocityPID.Ti = PID_VELOCITY_Ti;
    IAMSTRAIGHT.leftWheel.velocityPID.Td = PID_VELOCITY_Td;
    IAMSTRAIGHT.leftWheel.velocityPID.u16OutputMax = PID_OUTPUT_MAX;

    IAMSTRAIGHT.rightWheel.velocityPID.T  = PID_SAMPLETIME_T;
    IAMSTRAIGHT.rightWheel.velocityPID.Kp = PID_VELOCITY_Kp;
    IAMSTRAIGHT.rightWheel.velocityPID.Ti = PID_VELOCITY_Ti;
    IAMSTRAIGHT.rightWheel.velocityPID.Td = PID_VELOCITY_Td;
    IAMSTRAIGHT.rightWheel.velocityPID.u16OutputMax = PID_OUTPUT_MAX;

    PARAMS_vRegisterCallBackFunc(vSetParams);
}

void car_app(const u8 *pdata, u8 len)
{
    PARAMS_vSetParams(pdata, len);
}

/**
  * @}
  */

/**
  * @}
  */
