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

PTRFUNC pFunc = NULL;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief 
 * @details data frame are below list:
 *        1178.54's data frame is: :p:117854
 *        -1178.54's data frame is: :p:-117854
 * @param pdata 
 * @param len 
 */
f32 f32ParseFloatFromString(const u8 *pdata, u8 len)
{
    s8 valSign = 1;
    u8 lenOfInteger = len - 3 - 2;      /*!< 3 is the length of the command part,
                                             2 is the length of the fractional part */
    u16 integerPart = 0, fractionPart = 0;

    /* Check if it is a negative value */
    if (pdata[3] == '-')
    {
        lenOfInteger--;                 /* Length contains "-" */
        valSign = -1;
    }
    else
    {
        /* it is positive, do nothing */
    }

    /* parsing integer part */
    for (u8 i = 0, tenPower = 1; i < lenOfInteger; i++)
    {
        /**
         * 2 is the length of the fractional part
         * Minus 1 is used to get the index
         */
        integerPart += ((*(pdata+((len-2-1)-i))-ASCII_VALUE_0) * tenPower);
        tenPower *= 10;
    }

    /* parsing fractional part */
    for (u8 i = 0, tenPower = 1; i < 2; i++)
    {
        fractionPart += ((*(pdata+((len-1)-i))-ASCII_VALUE_0) * tenPower);
        tenPower *= 10;
    }

    return (valSign*((f32)integerPart + (fractionPart*0.01F)));
}

/* Exported functions --------------------------------------------------------*/

void PARAMS_vRegisterCallBackFunc(PTRFUNC pf)
{
    pFunc = pf;
}

s32 PARAMS_vSetParams(const u8 *pdata, u8 len)
{
    s32 res = -1;

    if (pFunc != NULL)
    {
        if (len > 3)
        {
            if ((pdata[0] == ':')
            && (pdata[2] == ':'))
            {
                f32 value = f32ParseFloatFromString(pdata, len);
                switch (pdata[1])
                {
                case 'p':
                case 'P':
                case 'i':
                case 'I':
                case 'd':
                case 'D':
                    (*pFunc)(pdata[1], value);
                    break;
                default:
                    break;
                }
            }
            else
            {
                /* pdata is not command, do nothing */
                /* res = -1; */
            }
        }
        else
        {
            /* do nothing */
            /* res = -1; */
        }
    }
    else
    {
        /* pFunc is not initialized, do nothing */
    }
    return res;
}

/**
  * @}
  */

/**
  * @}
  */
