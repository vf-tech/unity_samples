/**
  ******************************************************************************
  * @file    os_gpio.h
  * @author  Mehmet Alinbay
  * @version V0.0.1
             Initial Release
  * @date    18-09-2019
  * @brief   OS GPIO Driver Header File
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 </center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OS_GPIO_H
#define __OS_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/** @addtogroup Project
  * @{
  */
/** @addtogroup OS
  * @{
  */
/* OS GPIO Exported Constants ------------------------------------------------*/
/** @defgroup OS_GPIO_Exported_Constants OS GPIO Exported Constants
  * @brief OS GPIO Releated Constants
  * @{
  */
/**
  * @}
  */
/* OS GPIO Exported types ----------------------------------------------------*/
/** @defgroup OS_GPIO_Exported_Types OS GPIO Exported Types
  * @{
  */
typedef enum
{
  osGPIOMode_Input_NoPull,
  osGPIOMode_Input_PullUp,
  osGPIOMode_Input_PullDown,
  osGPIOMode_Output_OpenDrain,
  osGPIOMode_Output_PushPull
}osGPIOMode_t;
/**
  * @}
  */

/* OS GPIO Exported Macros ---------------------------------------------------*/
/** @defgroup OS_GPIO_Exported_Macros OS GPIO Exported Macros
  * @{
  */
/**
  * @}
  */

/* OS GPIO Exported Functions ------------------------------------------------*/
/** @addtogroup OS_GPIO_Exported_Functions OS GPIO Exported Functions
  * @{
  */
int32_t pOS_GPIO_Init(uint32_t gpio, osGPIOMode_t mode);
uint32_t pOS_GPIO_Read(uint32_t gpio);
void pOS_GPIO_Write(uint32_t gpio, uint32_t val);

/**
  * @}
  */

#ifdef OS_GPIO_I
/* OS GPIO Private types -----------------------------------------------------*/
/** @defgroup OS_GPIO_Private_Types OS GPIO Private Types
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
