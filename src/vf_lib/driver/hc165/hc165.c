/**
  ******************************************************************************
  * @file    hc165.c
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    28-09-2019
  * @brief   HC165 Paralel-In / Serial-Out Driver
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
#define   HC165_I
#include  "hc165.h"

//TO-DOs
/*
  [] in init function in case of any pin init error reset configured pins
*/

/** @defgroup HC165 HC165
  * @brief HC165 Driver Functions
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup HC165_Private_Variables HC165 Private Variables
  * @{
  */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup HC165_Private_Functions HC165 Private Functions
  * @{
  */
void pOS_HC165_Get(hc165_t *p)
{
  uint32_t d_counter=0;
  uint32_t b_counter=0;
  uint32_t val=0;
  //
  mHC165_LATCH_OFF(p);
  mHC165_LATCH_ON(p);
  for(d_counter = 0; d_counter < p->chip_no; d_counter++)
  {
    for(b_counter = HC165_NUM_GPIOS; b_counter > 0; b_counter--)
    {
      mHC165_DATA_READ(p,val);
      if(val)
        mBITSET( p->buffer[d_counter], b_counter - 1 );
      else
        mBITRESET( p->buffer[d_counter], b_counter - 1 );
      mHC165_CLOCK_ON(p);
      mHC165_CLOCK_OFF(p);
    }
  }
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HC165_Exported_Functions HC165 Exported Functions
  * @{
  */

osStatus_t pOS_HC165_Init(hc165_t *p)
{
  // Check Config
  if( (p == NULL ) || (p->status == osBusy) ||
      (p->chip_no == 0) || (p->chip_no > HC165_MAX_CHIPS) )
    return osError;
  //
  p->status = osBusy;
  // Init GPIO
  if( 1 != pOS_GPIO_Init( p->latch_pin , osGPIOMode_Output_PushPull ) )
    return osError;
  if( 1 != pOS_GPIO_Init( p->clock_pin , osGPIOMode_Output_PushPull ) )
    return osError;
  if( 1 != pOS_GPIO_Init( p->data_pin , osGPIOMode_Input_NoPull ) )
    return osError;
  // Clear All Values at Startup
  memset(p->buffer, 0x00, sizeof(p->buffer));
  p->status = osOK;
  return osOK;
}

osStatus_t pOS_HC165_Read(hc165_t *p)
{
  // Check Config
  if( (p == NULL ) || (p->status != osOK) )
    return osError;
  //
  p->status = osBusy;
  pOS_HC165_Get(p);
  p->status = osOK;
  return osOK;
}

/**
  * @}
  */

/**
  * @}
  */


/****************************** END OF FILE ***********************************/
