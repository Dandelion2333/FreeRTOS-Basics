	
#include "stm32f10x.h"
#include "bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

TaskHandle_t CreateGreen_Handler = NULL;
TaskHandle_t CreateBlue_Handler = NULL;
TaskHandle_t CreateRed_Handler = NULL;

void vTaskLedRed(void *pvParameters)
{
	int i = 0;
	while(1)
	{		
		//vTaskDelay( 500 );
		
		vTaskDelay( 1000 );
		i++;

		if (i > 5000)
			i = 0;
	}
}	

void vTaskGreen( void * pvParameters )
{
	int x = 0;
	while(1)
	{
		x++;
		//macLED2_ON ();			  // ¡¡
		vTaskDelay( 4000 );
		
		if (CreateRed_Handler != NULL)
		{
			vTaskDelete(CreateRed_Handler);
			vTaskDelete(CreateBlue_Handler);
			
			CreateRed_Handler = NULL;
			CreateBlue_Handler = NULL;
			vTaskDelay( 500 );
		}
	}
	
}

void vTaskLedBlue(void *pvParameters)
{
	int j = 0;
	while(1)
	{					
		//macLED3_ON();	// µ„¡¡¿∂µ∆		
		j++;
		
		if(j > 5000)
			j = 0;
		
		vTaskDelay( 500 );	
	}
}	

int main ( void )
{	
	int error = 0;
	LED_Init ();	          //≥ı ºªØ LED

	if(xTaskCreate(vTaskGreen, "Green", 64, NULL, 3, &CreateGreen_Handler) != pdPASS)
	{
		error = 1;
	}

	if(xTaskCreate(vTaskLedRed, "Red", 64 , NULL, 3, &CreateRed_Handler) != pdPASS)
	{
		error = 1;
	}
	
	if(xTaskCreate(vTaskLedBlue, "Blue", 64 , NULL, 3, &CreateBlue_Handler) != pdPASS)
	{
		error = 1;
	}
	
  vTaskStartScheduler();

}



/*********************************************END OF FILE**********************/












