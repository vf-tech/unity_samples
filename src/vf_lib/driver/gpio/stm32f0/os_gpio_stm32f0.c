/**
  ******************************************************************************
  * @file    os_gpio_stm32f0.c
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    14-11-2019
  * @brief   OS GPIO HAL STM32F0 Driver
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
#define   OS_UART_GPIO
#include  "os_common.h"
#include  "os_gpio.h"
#include  "stm32f0xx_ll_gpio.h"
#include  "stm32f0xx_ll_bus.h"

//TO-DOs
/*
  [] Check Valid Pin in every exported function
*/
/** @addtogroup Project
  * @{
  */
/** @defgroup OS_GPIO_STM32F0 OS GPIO STM32F0
  * @brief OS GPIO STM32F0 Functions
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup OS_GPIO_STM32F0_Private_Variables OS GPIO STM32F0 Private Variables
  * @{
  */
#define GPIO_PORT_MAX  16
#define mGetPortMask(gpio)  (GPIO_TypeDef*)( GPIOA_BASE + ( (gpio / GPIO_PORT_MAX) * (0x00000400) ) )
#define mGetPinMask(gpio)   ( 1 << (gpio % GPIO_PORT_MAX) )
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup OS_GPIO_STM32F0_Private_Function_Prototypes OS GPIO STM32F0 Private Function Prototypes
  * @{
  */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup OS_GPIO_STM32F0_Private_Functions OS GPIO STM32F0 Private Functions
  * @{
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OS_GPIO_STM32F0_Exported_Functions OS GPIO STM32F0 Exported Functions
  * @{
  */

    /**
  * @brief  GPIO Init Function
  * @param  *gpio : GPIO Object
  * @param  mode  : GPIO Mode (Output/Input)
  * @retval  - 1 : OK
  *          - -1: Error
  */
int32_t pOS_GPIO_Init(uint32_t gpio, osGPIOMode_t mode)
{
  GPIO_TypeDef *port = mGetPortMask(gpio);
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  switch( (uint32_t)port )
  {
    case GPIOA_BASE : LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); break;
    case GPIOB_BASE : LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB); break;
    case GPIOC_BASE : LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC); break;
    case GPIOD_BASE : LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD); break;
    case GPIOF_BASE : LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF); break;
    default: return -1;
  };
  switch(mode)
  {
    case  osGPIOMode_Input_NoPull:
          GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
          GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    break;
    case  osGPIOMode_Input_PullDown:
          GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
          GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    break;
    case  osGPIOMode_Input_PullUp:
          GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
          GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    break;
    case  osGPIOMode_Output_OpenDrain:
          GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
          GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    break;
    case  osGPIOMode_Output_PushPull:
          GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
          GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    break;
    default: return -1;
  }
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pin = mGetPinMask(gpio);
  LL_GPIO_Init( port, &GPIO_InitStruct );
  return 1;
}

uint32_t pOS_GPIO_HAL_Read(uint32_t gpio)
{
  GPIO_TypeDef *port = mGetPortMask(gpio);
  uint32_t pin = mGetPinMask(gpio);
  return ( LL_GPIO_IsInputPinSet( port, pin ) );
}

void pOS_GPIO_Write(uint32_t gpio, uint32_t val)
{
  GPIO_TypeDef *port = mGetPortMask(gpio);
  uint32_t pin = mGetPinMask(gpio);
  if( val )
    LL_GPIO_SetOutputPin( port, pin );
  else
    LL_GPIO_ResetOutputPin( port, pin );
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
