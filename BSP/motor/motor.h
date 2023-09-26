/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_H
#define __MOTOR_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup MOTOR_Exported_Functions MOTOR Exported Functions
  * @{
  */
void initMotor();
void stopMotor();
void setMotorPWM(int l_pwm, int r_pwm);
/**
  * @}
  */
#endif /* __MOTOR_H__ */
