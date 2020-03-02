/**
  ******************************************************************************
  * @file    hc595.c
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    28-09-2019
  * @brief   HC595 Serial-In / Paralel-Out Driver
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
#define   HC595_I
#include  "hc595.h"

//TO-DOs
/*
  [] in init function in case of any pin init error reset configured pins
*/

/** @defgroup HC595
  * @brief HC595 Driver Functions
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup HC595_Private_Variables HC595 Private Variables
  * @brief HC595 Private Variables
  * @{
  */
/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/** @defgroup HC595_Private_Functions HC595 Private Functions
  * @brief HC595 Private Functions
  * @{
  */
void pOS_HC595_Put(hc595_t *p)
{
  uint32_t d_counter=0;
  uint32_t b_counter=0;
  uint8_t data = 0;
  for(d_counter = 1; d_counter <= p->chip_no; d_counter++)
  {
    data = p->buffer[ p->chip_no - d_counter ];   //may need protection
    for(b_counter = 1; b_counter <= HC595_NUM_GPIOS; b_counter++)
    {
      if(( data & (1 << (HC595_NUM_GPIOS - b_counter))) != 0)
        mHC595_DATA_ON(p);
      else
        mHC595_DATA_OFF(p);
      mHC595_CLOCK_ON(p);
      mHC595_CLOCK_OFF(p);
    }
  }
  mHC595_LATCH_ON(p);
  mHC595_LATCH_OFF(p);
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HC595_Exported_Functions
  * @{
  */

/**
  * @brief  Periodic Func. of HC595
  * @param  arg : determines which HC595 object
  * @retval None
  */
void pOS_HC595_Periodic(uint32_t arg)
{
  hc595_t *p = (hc595_t*)arg;
  if( p == NULL )
    return;
  if( p->pending )
  {
    p->pending = 0;
    pOS_HC595_Put(p);
  }
}

/**
  * @brief  Inits OS Core variables
  * @note   Should be Called at startup
  * @param  None
  * @retval None
  */
int32_t pOS_HC595_Init(hc595_t *p)
{
  if( (p == NULL ) || (p->chip_no == 0) ||
      (p->chip_no > HC595_MAX_CHIPS) )
    return -1;
  // Init GPIO
  if( 1 != pOS_GPIO_Init( p->latch_pin, osGPIOMode_Output_PushPull ) )
    return -1;
  if( 1 != pOS_GPIO_Init( p->clock_pin, osGPIOMode_Output_PushPull ) )
    return -1;
  if( 1 != pOS_GPIO_Init( p->data_pin, osGPIOMode_Output_PushPull ) )
    return -1;
  if( -1 == pOS_StartPeriodicFunc(pOS_HC595_Periodic,
                                  (uint32_t)p,
                                  osTimerInfinite,
                                  TENMILISECTIMEOUT) )
  {
    return -1;
  }
  // Clear All Outputs at Startup
  memset(p->buffer, 0x00, sizeof(p->buffer));
  pOS_HC595_Put(p);
  return 1;
}

int32_t pOS_HC595_WritePin(hc595_t *p, uint32_t pin, uint8_t val)
{
  uint32_t port, port_pin;
  if( (p == NULL ) || (pin >= (p->chip_no*HC595_NUM_GPIOS)) )
    return -1;
  port =  pin / HC595_NUM_GPIOS;
  port_pin = pin % HC595_NUM_GPIOS;
  if( val )
    mBITSET( p->buffer[ port ] , port_pin );
  else
    mBITRESET( p->buffer[ port ] , port_pin );
  p->pending = 1;
  return 1;
}

int32_t pOS_HC595_WritePort(hc595_t *p, uint32_t port, uint8_t val)
{
  if( (p == NULL ) || (port >= p->chip_no) )
    return -1;
  p->buffer[ port ] = val;
  p->pending = 1;
  return 1;
}

int32_t pOS_HC595_Write(hc595_t *p,int32_t offset,uint8_t* val,uint32_t count)
{
  if( (p == NULL ) || ((offset + count) >= p->chip_no) ||
      (val == NULL) || (count == 0) )
    return -1;
  memcpy( &p->buffer[offset], val, count );
  p->pending = 1;
  return 1;
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** END OF FILE ***********************************/
