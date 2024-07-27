/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "set_params.h"

/** @addtogroup APP
  * @{
  */

/** @defgroup PARAMETERS PARAMETERS
  * @brief PARAMETERS APP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ASCII_VALUE_0   48u
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

s32 vSetParams(const u8 *pdata, u8 len)
{
    s32 res = 0;
    if (len > 3)
    {
        /** data frame is:
         *  :p:100
         *  :i:5
         */
        if ((pdata[0] == ':')
         && (pdata[2] == ':'))
        {
            u8 paramsLen = len - 3;
            u16 param = 0, tenPower = 1;
            for (u8 i = 0; i < paramsLen; i++)
            {
                param += ((*(pdata+((len-1)-i))-ASCII_VALUE_0) * tenPower);
                tenPower *= 10;
            }
            switch (pdata[1])
            {
            case 'p':
            case 'P':
                res = param;
                break;
            case 'i':
            case 'I':
                res = param;
                break;
            case 'd':
            case 'D':
                res = param;
                break;
            default:
                break;
            }
        }
        else
        {
            /**
             * pdata is not command
             */
            res = -1;
        }
    }
    else
    {
        /* do nothing */
        res = -1;
    }
    return res;
}

/**
  * @}
  */

/**
  * @}
  */
