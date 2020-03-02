/**
  ******************************************************************************
  * @file    os_uart.c
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    28-09-2019
  * @brief   OS UART Driver
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
#define   OS_UART_HAL
#include  "os_common.h"
#include  "os_uart.h"
#include  "stm32f0xx.h"
#include  "stm32f0xx_ll_usart.h"


//TO-DOs
/*
*/
/** @addtogroup Project
  * @{
  */
/** @defgroup OS_UART_STM32F0 OS UART STM32F0
  * @brief OS UART STM32F0 Functions
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup OS_UART_STM32F0_Private_Variables OS UART Private STM32F0 Variables
  * @{
  */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup OS_UART_STM32F0_Private_Function_Prototypes OS UART STM32F0 Private Function Prototypes
  * @{
  */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup OS_UART_STM32F0_Private_Functions OS UART STM32F0 Private Functions
  * @{
  */



/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OS_UART_STM32F0_Exported_Functions OS UART STM32F0 Exported Functions
  * @{
  */

uint32_t pOS_UART_HAL_GetBase(uint8_t port)
{
  if( port >= MAX_UART )
    return NULL;
  switch(port)
  {
    case 0  : return USART1_BASE;
  }
  return NULL;
}

uint32_t pOS_UART_HAL_CheckRXInt(osUart_t *hUart)
{
  return( LL_USART_IsActiveFlag_RXNE((USART_TypeDef *)hUart->base) &&
          LL_USART_IsEnabledIT_RXNE((USART_TypeDef *)hUart->base) );
}

uint32_t pOS_UART_HAL_CheckTXInt(osUart_t *hUart)
{
  return( LL_USART_IsActiveFlag_TXE((USART_TypeDef *)hUart->base) &&
          LL_USART_IsEnabledIT_TXE((USART_TypeDef *)hUart->base) );
}

uint16_t pOS_UART_HAL_Get(osUart_t *hUart)
{
  return( LL_USART_ReceiveData8((USART_TypeDef *)hUart->base) );
}

void pOS_UART_HAL_Put(osUart_t *hUart, uint8_t value)
{
  LL_USART_TransmitData8((USART_TypeDef *)hUart->base, value);
}

void pOS_UART_HAL_EnableTXInt(osUart_t *hUart)
{
  LL_USART_EnableIT_TXE((USART_TypeDef *)hUart->base);
}

void pOS_UART_HAL_DisableTXInt(osUart_t *hUart)
{
  LL_USART_DisableIT_TXE((USART_TypeDef *)hUart->base);
}

uint32_t pOS_UART_HAL_GetSendReady(osUart_t *hUart)
{
  return( LL_USART_IsActiveFlag_TXE((USART_TypeDef *)hUart->base) );
}

uint32_t pOS_UART_HAL_WaitTransmitComplete(osUart_t *hUart)
{
  return( LL_USART_IsActiveFlag_TC((USART_TypeDef *)hUart->base) );
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
