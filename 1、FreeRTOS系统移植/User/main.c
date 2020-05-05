/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "bsp_led.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



#define SOFT_DELAY Delay(0x0FFFFF);
void Delay(__IO uint32_t nCount);

TaskHandle_t xHandleTaskLED1;

void vTaskLed1(void *pvParameters)
{
    /* 任务都是一个无限，不能返回 */
    while(1)
    {
        LED1_ON;			  // 亮
				SOFT_DELAY;
				LED1_OFF;		   // 灭

				LED2_ON;			 // 亮
				SOFT_DELAY;
				LED2_OFF;		   // 灭
    }    
}


static void AppTaskCreate(void)
{
    xTaskCreate(vTaskLed1,           /* 任务函数名 */
                "Task Led1",         /* 任务名，字符串形式，方便调试 */
                 512,                /* 栈大小，单位为字，即4个字节 */
                 NULL,               /* 任务形参 */
                 5,                  /* 优先级，数值越大，优先级越高 */
                 &xHandleTaskLED1);  						 /* 任务句柄 */
}

int main(void)
{	
		/* LED 端口初始化 */
		LED_GPIO_Config();	 

	  /*创建任务*/
    AppTaskCreate();
	
    /*启动任务调度器，任务开始执行*/
    vTaskStartScheduler();

		while (1)
    {

    }
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
