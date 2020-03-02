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
#define   OS_UART_I
#define   OS_UART_HAL
#include  "os_common.h"
#include  "os_uart.h"

//TO-DOs
/*
*/
/** @addtogroup Project
  * @{
  */
/** @defgroup OS_UART OS UART
  * @brief OS UART Functions
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup OS_UART_Private_Variables OS UART Private Variables
  * @{
  */
osUart_t  *osUartList = NULL;
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup OS_UART_Private_Function_Prototypes OS UART Private Function Prototypes
  * @{
  */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup OS_UART_Private_Functions OS UART Private Functions
  * @{
  */

/**
  * @brief  UART Get List Item
  * @param  port  : PORT Number of Search Object
  * @retval List Item or NULL
  */
struct osUart *osUart_list_find(uint8_t port)
{
  struct osUart *cur = osUartList;
  while(cur)
  {
    if(cur->port == port)
      return cur;
    cur = cur->next;
  }
  return NULL;
}

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OS_UART_Exported_Functions OS UART Exported Functions
  * @{
  */

/**
  * @brief  UART Init Function
  * @param  *uart : UART Object
  * @param  mode  : UART Mode (Output/Input)
  * @retval Status Flag enumeration value:
  *          - OK:    Signal placed
  *          - ERROR: Not applicable
  */
osStatus_t pOS_UART_Init(osUart_t *uart)
{
  if( ( uart == NULL ) || ( uart->port >= MAX_UART ) )
    return osError;
  // Init Buffers
  uart->rxCirBuff.ptr = uart->rxBuff;
  uart->rxCirBuff.bufsize = sizeof(uart->rxBuff);
  if( osCirBufClear(&uart->rxCirBuff) == -1 )
    return osError;
  uart->txCirBuff.ptr = uart->txBuff;
  uart->txCirBuff.bufsize = sizeof(uart->txBuff);
  if( osCirBufClear(&uart->txCirBuff) == -1 )
    return osError;
  //USART INIT DONE by CUBEMX just Load Private Area
  uart->base = pOS_UART_HAL_GetBase(uart->port);
  //Add to List
  if( osUartList == NULL )
  {
    osUartList = uart;
    osUartList->next = NULL;
  }
  else
  {
    while(osUartList->next != NULL)
    {
      osUartList = osUartList->next;
    }
    osUartList->next = uart;
    osUartList->next->next = NULL;
  }
  return osOK;
}

/**
  * @brief  UART Read Function
  * @param  *uart : UART Object
  * @param  mode  : UART Mode (Output/Input)
  * @retval Status Flag enumeration value:
  *          - OK:    Signal placed
  *          - ERROR: Not applicable
  */
int pOS_UART_Read(osUart_t *uart, uint8_t *bytes, uint32_t len)
{
  if( ( uart == NULL ) || ( uart->port >= MAX_UART ) || (bytes == NULL) )
    return -1;
  return osCirBufRead(&uart->rxCirBuff, bytes, len);
}

/**
  * @brief  UART Read Function
  * @param  *uart : UART Object
  * @param  mode  : UART Mode (Output/Input)
  * @retval Status Flag enumeration value:
  *          - OK:    Signal placed
  *          - ERROR: Not applicable
  */
int pOS_UART_Write(osUart_t *uart, uint8_t *bytes, uint32_t len)
{
  int tx_len = 0;
  uint8_t tx_data = 0;
  if( ( uart == NULL ) || ( uart->port >= MAX_UART ) || (bytes == NULL) )
    return -1;
  tx_len = osCirBufWrite(&uart->txCirBuff, bytes, len);
  if( tx_len > 0 )
  {
    if( pOS_UART_HAL_GetSendReady(uart) )
    {
      osCirBufRead(&uart->txCirBuff, &tx_data, sizeof(tx_data));
      pOS_UART_HAL_Put(uart, tx_data);
      pOS_UART_HAL_EnableTXInt(uart);
    }
  }
  return tx_len;
}

/**
  * @brief  UART ISR Function
  * @param  port  : UART Port
  */
void pOS_UART_ISR(uint8_t port)
{
  osUart_t *hUart = osUartList;
  uint8_t  data = 0;
  if( port >= MAX_UART )
    return; //TODO error
  hUart = osUart_list_find(port);
  if( hUart == NULL )
    return; //TODO error
  if( pOS_UART_HAL_CheckRXInt(hUart) )
  {
    data = pOS_UART_HAL_Get(hUart);
    if( 1 != osCirBufWrite(&hUart->rxCirBuff, (uint8_t*)&data, sizeof(data) ) )
      hUart->rxOverFlow++;
  }
  if( pOS_UART_HAL_CheckTXInt(hUart) )
  {
    if( 1 != osCirBufRead(&hUart->txCirBuff, (uint8_t*)&data, sizeof(data) ) )
    {
      pOS_UART_HAL_DisableTXInt(hUart);
      //while( pOS_UART_HAL_WaitTransmitComplete(&hUart) == 0 );
    }
    else
    {
      pOS_UART_HAL_Put(hUart, data);
    }
  }
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
