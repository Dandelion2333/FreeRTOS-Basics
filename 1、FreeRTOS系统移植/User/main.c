/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����led
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
    /* ������һ�����ޣ����ܷ��� */
    while(1)
    {
        LED1_ON;			  // ��
				SOFT_DELAY;
				LED1_OFF;		   // ��

				LED2_ON;			 // ��
				SOFT_DELAY;
				LED2_OFF;		   // ��
    }    
}


static void AppTaskCreate(void)
{
    xTaskCreate(vTaskLed1,           /* �������� */
                "Task Led1",         /* ���������ַ�����ʽ��������� */
                 512,                /* ջ��С����λΪ�֣���4���ֽ� */
                 NULL,               /* �����β� */
                 5,                  /* ���ȼ�����ֵԽ�����ȼ�Խ�� */
                 &xHandleTaskLED1);  						 /* ������ */
}

int main(void)
{	
		/* LED �˿ڳ�ʼ�� */
		LED_GPIO_Config();	 

	  /*��������*/
    AppTaskCreate();
	
    /*�������������������ʼִ��*/
    vTaskStartScheduler();

		while (1)
    {

    }
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
