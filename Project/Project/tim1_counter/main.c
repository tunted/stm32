/**
  ******************************************************************************
  * @file    TIM/TIM1_Synchro/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_TIM1_Synchro
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef       TIM_OCInitStructure;
TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;

int debug_upate_timer_1   = 0,
    debug_upate_timer_1_cnt,
    debug_upate_timer_16  = 0;

int	debug_oc1 = 0,
		debug_oc2 = 0,
		debug_oc3 = 0,
		debug_oc4 = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM1_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
       
  /* System Clocks Configuration */

  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();

	/* TIM1 Configuration */
  TIM1_Configuration();

  while (1)
  {}
}

/**
  * @brief  Configures the different system clocks.iel
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* TIM1, GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures TIM1, TIM3 and TIM4 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA Configuration: TIM1 Channel1 and TIM3 Channel1 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM1_Configuration(void)
{
  TIM1->CCMR1 |= TIM_CCMR1_CC1S_0;
  TIM1->CCMR1 |= TIM_CCMR1_IC1F_2;
  TIM1->CCER  &= (uint16_t)(~(uint16_t)TIM_CCER_CC1P);
  TIM1->CCMR1 &= (uint16_t)(~(uint16_t)TIM_CCMR1_IC1PSC);
  TIM1->CCER  |= TIM_CCER_CC1E;
  TIM1->DIER  |= TIM_DIER_CC1IE;
  TIM1->CR1   |= TIM_CR1_CEN;
}

void TIM1_UP_TIM16_IRQHandler(void)
{
  if (SET == TIM_GetITStatus(TIM1, TIM_IT_Update))
  {
    debug_upate_timer_1 += 1;
    debug_upate_timer_1_cnt = (int)(TIM1->CNT);
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  }

  if (SET == TIM_GetITStatus(TIM16, TIM_IT_Update))
  {
    debug_upate_timer_16 += 1;
    TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
  }
}

void TIM1_CC_IRQHandler(void)
{
	if (SET == TIM_GetITStatus(TIM1, TIM_IT_CC1))
	{
		debug_oc1 += 1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
	}

	if (SET == TIM_GetITStatus(TIM1, TIM_IT_CC2))
	{
		debug_oc2 += 1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
	}
	
	if (SET == TIM_GetITStatus(TIM1, TIM_IT_CC3))
	{
		debug_oc3 += 1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
	}
	
	if (SET == TIM_GetITStatus(TIM1, TIM_IT_CC4))
	{
		debug_oc4 += 1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
