/**
  ******************************************************************************
  * @file    os_gpio.c
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    28-09-2019
  * @brief   OS GPIO Driver
  *
  @verbatim
  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 </center></h2>
  *
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#define   OS_GPIO_I
#include  "os_common.h"
#include  "os_gpio.h"

//TO-DOs
/*
  [] Check Valid Pin in every exported function
*/
/** @addtogroup Project
  * @{
  */
/** @defgroup OS_GPIO OS GPIO
  * @brief OS GPIO Functions
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup OS_GPIO_Private_Variables OS GPIO Private Variables
  * @{
  */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup OS_GPIO_Private_Function_Prototypes OS GPIO Private Function Prototypes
  * @{
  */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup OS_GPIO_Private_Functions OS GPIO Private Functions
  * @{
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OS_GPIO_Exported_Functions OS GPIO Exported Functions
  * @{
  */

/**
  * @brief  GPIO Init Function
  * @param  *gpio : GPIO Object
  * @param  mode  : GPIO Mode (Output/Input)
  * @retval Status Flag enumeration value:
  *          - OK:    Signal placed
  *          - ERROR: Not applicable
  */
__WEAK int32_t pOS_GPIO_Init(uint32_t gpio, osGPIOMode_t mode)
{
  return 1;
}

__WEAK uint32_t pOS_GPIO_Read(uint32_t gpio)
{
  return 1;
}

__WEAK void pOS_GPIO_Write(uint32_t gpio, uint32_t val)
{
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

/****************************** END OF FILE ***********************************/
