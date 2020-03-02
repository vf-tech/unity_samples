/**
  ******************************************************************************
  * @file    hc595.h
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    18-09-2019
  * @brief   HC595 Serial-In / Paralel-Out Driver Header File
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 </center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OS_HC595_H
#define __OS_HC595_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "os_common.h"
#include  "os_gpio.h"

/** @addtogroup HC595
  * @{
  */
/* HC595 Exported Constants --------------------------------------------------*/
/** @defgroup HC595_Exported_Constants HC595 Exported Constants
  * @brief HC595 Releated Constants
  * @{
  */
#define HC595_MAX_CHIPS   8
/**
  * @}
  */
/* HC595 Exported types ------------------------------------------------------*/
/** @defgroup HC595_Exported_Types HC595 Exported Types
  * @brief HC595 Exported Types
  * @{
  */

typedef struct
{
  uint32_t    latch_pin;
  uint32_t    clock_pin;
  uint32_t    data_pin;
  uint32_t    chip_no;
  uint8_t     buffer[HC595_MAX_CHIPS];
  uint8_t     pending;
}hc595_t;
/**
  * @}
  */
/* HC595 Exported Macros -----------------------------------------------------*/
/** @defgroup HC595_Exported_Macros HC595 Exported Macros
  * @{
  */

/**
  * @}
  */
/* HC595 Functions -----------------------------------------------------------*/
/** @defgroup HC595_Exported_Functions HC595 Exported Functions
  * @brief HC595 Exported Functions
  * @{
  */
int32_t pOS_HC595_Init(hc595_t *p);
int32_t pOS_HC595_WritePin(hc595_t *p, uint32_t pin, uint8_t val);
int32_t pOS_HC595_WritePort(hc595_t *p, uint32_t port, uint8_t val);
int32_t pOS_HC595_Write(hc595_t *p, int32_t offset,uint8_t* val,uint32_t count);
/**
  * @}
  */

#ifdef HC595_I

/* HC595 Private Constants ---------------------------------------------------*/
/** @addtogroup HC595_Private_Constants HC595 Private Constants
  * @{
  */
#define HC595_NUM_GPIOS   8
/**
  * @}
  */

/* HC595 Private types -------------------------------------------------------*/
/** @addtogroup HC595_Private_Types HC595 Private Types
  * @{
  */
/**
  * @}
  */


/* HC595 Private Macros ------------------------------------------------------*/
/** @addtogroup HC595_Private_Macros HC595 Private Macros
  * @{
  */
#define mHC595_CLOCK_ON(p)  pOS_GPIO_Write(p->clock_pin,1)
#define mHC595_CLOCK_OFF(p) pOS_GPIO_Write(p->clock_pin,0)
#define mHC595_LATCH_ON(p)  pOS_GPIO_Write(p->latch_pin,1)
#define mHC595_LATCH_OFF(p) pOS_GPIO_Write(p->latch_pin,0)
#define mHC595_DATA_ON(p)   pOS_GPIO_Write(p->data_pin,1)//pOS_GPIO_Write(p->data_pin,1)
#define mHC595_DATA_OFF(p)  pOS_GPIO_Write(p->data_pin,0)//pOS_GPIO_Write(p->data_pin,0)
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

#endif /* __OS_HC595_H */

/*****************************END OF FILE**************************************/
