#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "string.h"
#include "stdio.h"

/**
**===========================================================================
**
**  Abstract: first try into using freeRTOS
**
**===========================================================================
*/

extern "C"{
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
}

#define mainDELAY_LOOP_COUNT   ( 0xfffff )

TaskHandle_t t1;

void vTask1( void *pvParameters);

void vTask2( void *pvParameters);

//void vPrintString( const portCHAR *pcString );

int main(void){
  int i = 0;

  /* Initialize LEDs */
 // STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  /* Turn on LEDs */
  //STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED5);
  STM_EVAL_LEDOn(LED6);

  xTaskCreate(	vTask1, //ponteiro para a função que implementa a tarefa
		  "Task 1", 	//nome da função. Para facilitar o debug.
		  1000, 		//stack depth
		  NULL, 		//nao usa task parameter
		  1,			//prioridade 1
		  NULL);		//nao usa task handler
  xTaskCreate(vTask2,
		  "Task 2",
		  1000,
		  NULL,
		  1,
		  NULL);

  vTaskStartScheduler();

  /* Infinite loop */
  while (1)
  {
	//i++;
  }
}

void vTask1( void *pvParameters){
	const char *pcTaskName = "Task 1 is running \r\n";
	volatile uint32_t ul;

	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	//a tarefa tem implementada nela um loop infinito.
	for(;;){
		//vPrintString(pcTaskName);
		for(ul=0;ul<mainDELAY_LOOP_COUNT;ul++){
			//implementação burra de um delay.
		}
	}
}

void vTask2( void *pvParameters){
	const char *pcTaskName = "Task 2 is running \r\n";
	volatile uint32_t ul;

	//a tarefa tem implementada nela um loop infinito.
	for(;;){
		//vPrintString(pcTaskName);
		for(ul=0;ul<mainDELAY_LOOP_COUNT;ul++){
			//implementação burra de um delay.
		}
	}
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}

extern "C" void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName ){
	( void ) pcTaskName;
	( void ) pxTask;
	for( ;; );
}

extern "C" void vApplicationIdleHook( void ){
	volatile size_t xFreeStackSpace;
	xFreeStackSpace = xPortGetFreeHeapSize();
}

extern "C" void vApplicationTickHook( void ){
}

extern "C" void vApplicationMallocFailedHook( void ){
	for( ;; );
}
