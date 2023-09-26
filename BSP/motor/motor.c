
/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#include "tim.h"


/** @addtogroup BSP
  * @{
  */

/** @defgroup MOTOR MOTOR
  * @brief MOTOR BSP driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/** @defgroup MOTOR_Private_Types_Definitions MOTOR Private Types Definitions
  * @{
  */
typedef struct MOTOR_S {
    TIM_HandleTypeDef *htim;    /*!< Specify which htim the motor uses. */
    uint32_t Channel;           /*!< Specify which channel the motor uses.
                                     This parameter can be a value of @ref TIM_Channel*/
}MOTOR_T;
/**
  * @}
  */
/* Private define ------------------------------------------------------------*/
/** @defgroup MOTOR_Private_Constants MOTOR Private Constants
  * @{
  */
#define MOTOR_PWM_PERIOD        (7200 - 1)              /*!< need to sync with timer's period  */
#define MOTOR_PWM_PERIOD_MASK   (~MOTOR_PWM_PERIOD)     /*!< PWM mask for assert test          */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
#define IS_PWM_VALID(pwm)   ((pwm & MOTOR_PWM_PERIOD_MASK) == 0)

/* Private variables ---------------------------------------------------------*/
/** @defgroup MOTOR_Private_Variables MOTOR Private Variables
  * @{
  */
MOTOR_T l_motor = {0};
MOTOR_T r_motor = {0};
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup MOTOR_Exported_Functions MOTOR Exported Functions
  * @{
  */

/**
 * @brief starts the L&R motor PWM signal generation
 */
void initMotor()
{
    l_motor.htim = &htim1;
    l_motor.Channel = TIM_CHANNEL_4;    
    r_motor.htim = &htim1;
    r_motor.Channel = TIM_CHANNEL_1;
    HAL_TIM_PWM_Start(l_motor.htim, l_motor.Channel);
    HAL_TIM_PWM_Start(r_motor.htim, r_motor.Channel);
}

/**
 * @brief stops the L&R motor and their PWM signal generation.
 */
void stopMotor()
{
    HAL_GPIO_WritePin(MOTOR_AIN1_GPIO_Port, MOTOR_AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_AIN1_GPIO_Port, MOTOR_AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_AIN2_GPIO_Port, MOTOR_AIN2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_AIN2_GPIO_Port, MOTOR_AIN2_Pin, GPIO_PIN_RESET);

    HAL_TIM_PWM_Stop(l_motor.htim, l_motor.Channel);
    HAL_TIM_PWM_Stop(r_motor.htim, r_motor.Channel);
}

/**
 * @brief Set the PWM value of left and right motor.
 * 
 * @param l_pwm specifies the left motor PWM value.
 *   @arg [0, @ref MOTOR_PWM_PERIOD]
 * @param r_pwm specifies the right motor PWM value.
 *   @arg [0, @ref MOTOR_PWM_PERIOD]
 */
void setMotorPWM(int l_pwm, int r_pwm)
{
    assert_param(IS_PWM_VALID(l_pwm));
    assert_param(IS_PWM_VALID(r_pwm));

    /* left motor */
    if(0 <= l_pwm)
    {
        HAL_GPIO_WritePin(MOTOR_AIN1_GPIO_Port, MOTOR_AIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_AIN2_GPIO_Port, MOTOR_AIN2_Pin, GPIO_PIN_RESET);
    }
    else
    {   l_pwm = -l_pwm;
        HAL_GPIO_WritePin(MOTOR_AIN1_GPIO_Port, MOTOR_AIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_AIN2_GPIO_Port, MOTOR_AIN2_Pin, GPIO_PIN_SET);
    }
    /* right motor */
    if(0 <= r_pwm)
    {
        HAL_GPIO_WritePin(MOTOR_BIN1_GPIO_Port, MOTOR_BIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_BIN2_GPIO_Port, MOTOR_BIN2_Pin, GPIO_PIN_SET);
    }
    else
    {
        r_pwm = -r_pwm;
        HAL_GPIO_WritePin(MOTOR_BIN1_GPIO_Port, MOTOR_BIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_BIN2_GPIO_Port, MOTOR_BIN2_Pin, GPIO_PIN_SET);
    }
    /* set pwm */
    __HAL_TIM_SET_COMPARE(l_motor.htim, l_motor.Channel, l_pwm);
    __HAL_TIM_SET_COMPARE(r_motor.htim, r_motor.Channel, r_pwm);
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
