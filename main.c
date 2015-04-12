/**
  ******************************************************************************
  * @file    SysTick/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
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
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#define STUDENTS_LIM 10
#define DIP_ACCESS_NUM 4

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup SysTick_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;

struct studente 
{
  char *nomeCognome;
  char codice[5];
  int dipAccess[DIP_ACCESS_NUM];
  int countAccess[DIP_ACCESS_NUM];
  int valid;
} utenti[STUDENTS_LIM];
  
  int utenti_counter = 0;
  int dip = 1;



/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
void addUser(struct studente *s, char *nomeCognome, char *codice, char *dipAccess, int val);
int checkStudent(struct studente *s, char *code);

main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */     
  
  /* Initialize Leds mounted on STM32F4-Discovery board */
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED3);
  
  char *p = malloc(256);

  
  /* add two users */
  addUser(utenti,"Damiano Di Stefano","A0001","11",1);
  addUser(utenti,"Walter White","A0002","10",1);
  
  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    /* Capture error */ 
    while (1);
  }

  while (1)
  {
    STM_EVAL_LEDToggle(LED5);
    printf("Insert student code:\n");
    scanf("%s",p);
    if(checkStudent(utenti,p))
    {
      STM_EVAL_LEDToggle(LED5);
      Delay(1000000);
      STM_EVAL_LEDToggle(LED6);
      Delay(1000000);
      STM_EVAL_LEDToggle(LED6);
    }
    else
    {
      STM_EVAL_LEDToggle(LED5);
      Delay(1000000);
      STM_EVAL_LEDToggle(LED3);
      Delay(1000000);
      STM_EVAL_LEDToggle(LED3);
    }
  }
}

int checkStudent(struct studente *s, char *code)
{
  for(int i = 0; i < STUDENTS_LIM; i++)
  {
    if((s+i)->valid && (strcmp((s+i)->codice, code) == 0))
    {
      return ((s+i)->dipAccess[dip]) ? 1 : 0;
    }
  }
  return 0;
        
}

void addUser(struct studente *s, char *nomeCognome, char *codice, char *dipAccess, int val)
{
  if(utenti_counter < STUDENTS_LIM)
  {
    (s+utenti_counter)->nomeCognome = nomeCognome;
    strcpy((s+utenti_counter)->codice, codice);
    
    for(int i = 0; i < DIP_ACCESS_NUM; i++)
      (s+utenti_counter)->dipAccess[i] = (!isdigit(*(dipAccess + i))) ? 0 : *(dipAccess + i) - '0';
    
    (s+utenti_counter)->valid = val;
    
    utenti_counter++;
  }
  else
    printf("Students array full\n");
  
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
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

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
