/**
  ******************************************************************************
  * @file    os_uart.h
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    18-09-2019
  * @brief   OS UART Driver Header File
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 </center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OS_UART_H
#define __OS_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "os_common.h"
/** @addtogroup Project
  * @{
  */
/** @addtogroup OS
  * @{
  */
/* OS UART Exported Constants ------------------------------------------------*/
/** @defgroup OS_UART_Exported_Constants OS UART Exported Constants
  * @brief OS UART Releated Constants
  * @{
  */
#ifdef  STM32F030x8
  #define MAX_UART  2
#endif

#define OS_UART_TXSIZE  256
#define OS_UART_RXSIZE  256
/**
  * @}
  */
/* OS UART Exported types ----------------------------------------------------*/
/** @defgroup OS_UART_Exported_Types OS UART Exported Types
  * @{
  */

typedef struct
{
  uint32_t  baudrate;
  uint8_t   stop_bits;
  uint8_t   data_bits;
  uint8_t   parity;
  uint8_t   flow;
}osUartConfig_t;

typedef struct osUart
{
  uint8_t           port;
  osUartConfig_t    mode;
  uint8_t           rxBuff[OS_UART_RXSIZE];
  uint8_t           txBuff[OS_UART_TXSIZE];
  osCirBuf          rxCirBuff;
  osCirBuf          txCirBuff;
  uint32_t          rxOverFlow;
  struct osUart     *next;
  //PRIV AREA
#ifdef  STM32F030x8
  uint32_t          base;
#endif
}osUart_t;

/**
  * @}
  */

/* OS UART Exported Macros ---------------------------------------------------*/
/** @defgroup OS_UART_Exported_Macros OS UART Exported Macros
  * @{
  */
/**
  * @}
  */

/* OS UART Exported Functions ------------------------------------------------*/
/** @addtogroup OS_UART_Exported_Functions OS UART Exported Functions
  * @{
  */
osStatus_t pOS_UART_Init(osUart_t *uart);
int pOS_UART_Read(osUart_t *uart, uint8_t *bytes, uint32_t len);
int pOS_UART_Write(osUart_t *uart, uint8_t *bytes, uint32_t len);
void pOS_UART_ISR(uint8_t port);

/**
  * @}
  */

#ifdef OS_UART_HAL
/* OS UART HAL functions -----------------------------------------------------*/
/** @defgroup OS_UART_HAL_Functions OS UART HAL Functions
  * @{
  */
uint32_t pOS_UART_HAL_GetBase(uint8_t port);
uint32_t pOS_UART_HAL_CheckRXInt(osUart_t *hUart);
uint32_t pOS_UART_HAL_CheckTXInt(osUart_t *hUart);
uint16_t pOS_UART_HAL_Get(osUart_t *hUart);
void pOS_UART_HAL_Put(osUart_t *hUart, uint8_t value);
void pOS_UART_HAL_EnableTXInt(osUart_t *hUart);
void pOS_UART_HAL_DisableTXInt(osUart_t *hUart);
uint32_t pOS_UART_HAL_GetSendReady(osUart_t *hUart);
/**
  * @}
  */
#endif

#ifdef OS_UART_I
/* OS UART HAL functions -----------------------------------------------------*/
/** @defgroup OS_UART_HAL_Functions OS UART HAL Functions
  * @{
  */
/**
  * @}
  */
#endif

/**
  * @}
  */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __os_common_H */

/*****************************END OF FILE**************************************/
