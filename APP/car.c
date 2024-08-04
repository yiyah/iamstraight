
/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "set_params.h"
#include "pid.h"
#include "math.h"

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
    PID_Typedef     bodyPID;
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

/**
 * @brief 速度环 PID 参数
 * 使用 临界比例法 获取的，1020是引起系统震荡的Ku, 100ms 是震荡时两个波峰间的时间间隔
 */
#define     PID_VELOCITY_Kp     612.0F      /*!< 1020 * 0.6 */
#define     PID_VELOCITY_Ti     50.0F       /*!< 100ms / 2 */
#define     PID_VELOCITY_Td     12.5F       /*!< 100ms / 8 */

#define     PID_OUTPUT_MAX      7200.0F     /*!< the motor PWM max pulse */

/**
 * @brief the threshold of integral separation
 * @details 当预期值为 0，用手转轮子，发现积分项累积的误差是 [-3, 3]，
 *          而此时编码器返回的 pulse 是 0，导致误差一直是 0。
 *          然后 积分项的误差保持非零，一直有输出，轮子就一直再转。
 *          所以引入了积分分离 下限。
 */
#define     PID_THRESH_SEP_INTEG 5.0F

/**
 * @brief 直立环 PID 参数
 */
#define     PID_BODY_Kp     0.0F
#define     PID_BODY_Ti     1000000.0F
#define     PID_BODY_Td     0.0F

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
    IAMSTRAIGHT.leftWheel.velocityPID.f32OutputMax = PID_OUTPUT_MAX;
    IAMSTRAIGHT.leftWheel.velocityPID.f32IntegralSepThreshold = PID_THRESH_SEP_INTEG;

    IAMSTRAIGHT.rightWheel.velocityPID.T  = PID_SAMPLETIME_T;
    IAMSTRAIGHT.rightWheel.velocityPID.Kp = PID_VELOCITY_Kp;
    IAMSTRAIGHT.rightWheel.velocityPID.Ti = PID_VELOCITY_Ti;
    IAMSTRAIGHT.rightWheel.velocityPID.Td = PID_VELOCITY_Td;
    IAMSTRAIGHT.rightWheel.velocityPID.f32OutputMax = PID_OUTPUT_MAX;
    IAMSTRAIGHT.rightWheel.velocityPID.f32IntegralSepThreshold = PID_THRESH_SEP_INTEG;

    IAMSTRAIGHT.bodyPID.T  = PID_SAMPLETIME_T;
    IAMSTRAIGHT.bodyPID.Kp = PID_BODY_Kp;
    IAMSTRAIGHT.bodyPID.Ti = PID_BODY_Ti;
    IAMSTRAIGHT.bodyPID.Td = PID_BODY_Td;
    IAMSTRAIGHT.bodyPID.f32OutputMax = PID_OUTPUT_MAX;
    IAMSTRAIGHT.bodyPID.f32IntegralSepThreshold = PID_THRESH_SEP_INTEG;
    PARAMS_vRegisterCallBackFunc(vSetParams);
}

void car_app(const u8 *pdata, u8 len)
{
    PARAMS_vSetParams(pdata, len);
}

f32 CAR_f32KeepStandUP(f32 f32target, f32 f32curPitch)
{
    static f32 f32res = 0.0F;
    if (fabs(f32curPitch) > 1.0F)
    {
        f32res = PPID_Output(f32target, f32curPitch, &IAMSTRAIGHT.bodyPID);
    }
    else
    {
        /* do nothing */
    }

    return f32res;
}

/**
  * @}
  */

/**
  * @}
  */
