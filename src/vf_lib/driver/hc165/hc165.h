/**
  ******************************************************************************
  * @file    hc595.h
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    18-09-2019
  * @brief   HC165 Serial-In / Paralel-Out Driver Header File
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 </center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OS_HC165_H
#define __OS_HC165_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "os_common.h"
#include  "os_gpio.h"

/** @addtogroup HC165
  * @{
  */
/* HC165 Exported Constants --------------------------------------------------*/
/** @defgroup HC165_Exported_Constants HC165 Exported Constants
  * @brief HC165_Exported_Constants : HC165 Releated Constants
  * @{
  */
#define HC165_MAX_CHIPS   8
#define HC165_NUM_GPIOS   8
/**
  * @}
  */
/* HC165 Exported types ------------------------------------------------------*/
/** @defgroup HC165_Exported_Types HC165 Exported Types
  * @{
  */

typedef struct
{
  osStatus_t  status;
  uint32_t    latch_pin;
  uint32_t    clock_pin;
  uint32_t    data_pin;
  uint32_t    chip_no;
  uint8_t     buffer[HC165_MAX_CHIPS];
}hc165_t;
/**
  * @}
  */
/* HC165 Exported Macros -----------------------------------------------------*/
/** @defgroup HC165_Exported_Macros HC165 Exported Macros
  * @{
  */
/**
  * @}
  */
/* HC165 Functions -----------------------------------------------------------*/
/** @addtogroup HC165_Exported_Functions HC165 Exported Functions
  * @{
  */
osStatus_t pOS_HC165_Init(hc165_t *p);
osStatus_t pOS_HC165_Read(hc165_t *p);
/**
  * @}
  */

#ifdef HC165_I

/* HC165 Private Constants ---------------------------------------------------*/
/** @defgroup HC165_Private_Constants HC165 Private Constants
  * @{
  */

/**
  * @}
  */
/* HC165 Private types -------------------------------------------------------*/
/** @defgroup HC165_Private_Types HC165 Private Types
  * @{
  */
/**
  * @}
  */
/* HC165 Private Macros ------------------------------------------------------*/
/** @defgroup HC165_Private_Macros HC165 Private Macros
  * @{
  */
#define mHC165_CLOCK_ON(p)      pOS_GPIO_Write(p->clock_pin,1)
#define mHC165_CLOCK_OFF(p)     pOS_GPIO_Write(p->clock_pin,0)
#define mHC165_LATCH_ON(p)      pOS_GPIO_Write(p->latch_pin,1)
#define mHC165_LATCH_OFF(p)     pOS_GPIO_Write(p->latch_pin,0)
#define mHC165_DATA_READ(p,val) ( val = pOS_GPIO_Read(p->data_pin) )
/**
  * @}
  */
/**
  * @}
  */

#endif

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __OS_HC165_H */

/*****************************END OF FILE**************************************/
