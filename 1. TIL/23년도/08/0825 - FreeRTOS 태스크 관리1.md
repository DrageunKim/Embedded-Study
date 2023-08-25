# 23.08.25 - FreeRTOS > 태스크 관리1

#### [목차]

- FreeRTOS를 사용하는 방법
  1. FreeRTOS가 응용 프로그램 내의 각 태스크에 처리 시간을 할당하는 방법
  2. FreeRTOS가 주어진 시간에 어떤 태스크를 실행할지 선택하는 방법
  3. 각 태스크의 상대적 우선 순위가 시스템 동작에 미치는 영향
  4. 태스크가 존재할 수 있는 상태

- FreeRTOS 응용 프로그램이 작동하는 방법을 기본 이해

  1. 태스크를 구현하는 방법

  2. 하나 이상의 태스크 인스턴스를 만드는 방법

  3. task 매개 변수를 사용하는 방법

  4. 이미 생성 된 태스크의 우선 순위를 변경하는 방법

  5. 태스크를 삭제하는 방법

  6. 태스크를 사용하여 정기적인 처리를 구현하는 방법. 자세한 내용은 software_tier_management를 참조하십시오.

  7. 유휴 (idle)작업이 실행되고 어떻게 사용될 수 있는지



***

#### 1. Task 함수

- 각 태스크는 그 자체로 작은 프로그램

  - 엔트리 포인트가 있으며 무한루프 내에서 영원히 계속 실행되며 종료되지 않음
  - FreeRTOS 작업은 어떤식으로든 구현 기능에서 return 할 수 없어야 함
    - ✏️ **Return 문을 포함해서는 안되며 함수의 끝을 지나서 실행할 수 없도록 해야 함!**
    - 더이상 필요하지 않은 태스크는 명시적으로 삭제해야 함
  - 단일 태스크 함수 정의를 사용하여 원하는 수의 태스크를 작성할 수 있음
  - 생성된 각 태스크는 자체 실행 스택과 자체 태스크 내에서 정의된 자동(스택) 변수의 자체 복사본을 가진 별도의 실행 인스턴스

  ```c
  void ATaskFunction(void *pvParameters) {
  /* 변수는 일반 함수와 마찬가지로 선언할 수 있습니다. 이 예제 함수를 사용하여 생성 된 각 작업 인스턴스에는 lVariableExample 변수의 자체 복사본이 있습니다. 변수가 정적으로 선언된 경우에는 하나의 변수 사본 만 존재하며 이 사본은 작성된 각 태스크 인스턴스에서 공유됩니다. 변수 이름에 추가된 접두사는 데이터 유형 및 코딩 스타일 안내서에 설명되어 있습니다.*/
  int32_t lVariableExample = 0;
  
  /* 태스크는 일반적으로 무한루프로 구성됩니다. */
  for( ;; ) {
  /* 태스크 기능을 구현하는 코드는 여기에 입력합니다. /
  }
  
  /* 태스크 구현이 위의 루프에서 벗어나면 구현 기능이 끝나기 전에 태스크를 삭제해야합니다. vTaskDelete () API 함수에 전달 된 NULL 매개 변수는 삭제할 작업이 호출 (this) 작업임을 나타냅니다. API 함수를 명명하는데 사용되는 규칙은 데이터 유형 및 코딩 스타일 안내서에 설명되어 있습니다. */
  vTaskDelete(NULL);
  }
  ```

***

#### 2. 최상위 Task 상태

- 응용 프로그램은 많은 태스크로 구성 될 수 있음
- 응용 프로그램을 실행하는 프로세서에 단일 코어가 포함되어 있으며 주어진 시간에 하나의 작업만 실행할 수 있음
  - 이는 Running 상태와 Not Running 상태 중 하나에 작업이 존재할 수 있음을 의미
    - 지나치게 단순화하여 설명한 것임
    - 실제로는 Not Running 상태에서 여러 하위 상태가 있음을 알 수 있음
- 태스크가 Running 상태이면 프로세서가 태스크 코드를 실행 중
- 태스크가 Not Running 상태에 있을 경우 태스크는 휴면 상태
  - 태스크에 동작 명령을 송신했을 때 Not Running이면 즉각 실행이 되지 않고 아래 단계를 거쳐서 실행 됨
    - 태스크 상태를 Running 으로 전환
    - 태스크에 다시 한번 동일 명령을 송신
    - 태스크가 Running 상태로 전환된 후 명령을 받았기 때문에 실행 시작
- Running → Not Running 전환 : 스왑된 상태
- Not Running → Running 전환 : 스왑 아웃된 상태

***

#### 3. 태스크 생성

##### a. xTaskCreate() API 함수

```c
/* xTaskCreate() 매개 변수와 반환 값의 목록 */
BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char * const pcName, uint16_t usStackDepth, void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask);
```

- pvTaskCode : 태스크는 절대 종료하지 않고 일반적으로 무한 루프로 구현되는 함수
  - 매개변수 : 작업을 구현하는 함수에 대한 포인터
- pcName : 작업을 설명하는 이름 (FreeRTOS에서 거의 사용하지 않음, 디버깅 용도로 사용되긴 함)
  - configMAX_TASK_NAME_LEN : NULL 종결자를 포함하여 작업 이름이 취할 수 있는 최대 길이를 정의 (최대 값보다 긴 문자열은 자동으로 잘림)

- usStackDepth : 각 작업이 생성될 때 커널이 작업에 할당하는 고유한 스택이 존재하기에 스택의 크기를 설정하여 커널에 알려줌
  - 스택이 보유할 수 있는 Words 수를 지정하며 바이트 수는 지정하지 않음
  - ex) 스택의 크기가 32Bit  & usStackDepth가 100으로 전달되면 400Byte의 스택 공간이 할당 됨
    - 계산식 : 32Bit x 100 = 3200Bit / 8 = 400Byte (4Byte x 100)
  - 유휴 작업에 사용되는 스택의 크기는 configMINIMAL_STACK_SIZE 에 의해 정의 됨
  - **작업에 필요한 스택 공간을 쉽게 결정할 수 있는 방법은 없음**
    - **계산을 할 수도 있지만 대부분의 사용자는 합리적인 값이라고 생각하는 값을 할당한 다음 사용하면서 합리적인 값을 찾아나감**
- pvParameters : 포인터 유형의 매개 변수를 태스크에 전달해주는 함수
- uxPriority : 태스크를 실행할 우선 순위를 정의
  - 가장 낮은 우선 순위 = 0
  - 가장 높은 우선 순위 = -1 (자동으로 최대 높은 값으로 제한됨)
  - configMAX_PRIORITIES 에서 우선 순위의 단계를 설정할 수 있음
- pxCreatedTask : 생성되는 작업에 대한 핸들을 전달하는데 사용할 수 있음
  - ex) 태스크 우선 순위를 변경하거나 태스크를 삭제하는 API 호출에서 태스크를 참조할 수 있음
    - 응용 프로그램에서 작업 핸들을 사용하지 않으면 pxCreatedTask 을 NULL 로 설정할 수 있음
  - 반환값은 두가지 존재
    - pdPASS : 태스크가 성공적으로 생성되었음
    - pdFAIL : 태스크 데이터 구조와 스택을 보유하기에 충분한 RAM을 할당하기 부족한 힙 메모리가 있기 때문에 태스크가 작성되지 않았음



##### b. Task 생성 (예제 1)

- 주기적인 문자열을 주기적으로 출력하고, 주기적인 지연 루프를 사용하여 기간 지연을 만듬, 두 작업 모두 동일한 우선 순위를 가짐

  - Task1

    ```c
    void vTask1( void *pvParameters ) {
        const char *pcTaskName = "Task 1 is running\r\n";
        volatile uint32_t ul; /* volatile to ensure ul is not optimized away.*/
    
     	/* As per most tasks, this task is implemented in an infinite loop. */
        for( ;; ) {
         	/* Print out the name of this task. */
            vPrintString( pcTaskName );
         
        	 /* Delay for a period. */
            for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {
            /* This loop is just a very crude delay implementation. There is nothing to do in here. Later examples will replace this crude loop with a proper delay/sleep function. */
            }
        }
    }
    ```

  - Task2

    ```c
    void vTask2( void *pvParameters ) {
    	const char *pcTaskName = "Task 2 is running\r\n";
    	volatile uint32_t ul; /* volatile to ensure ul is not optimized away.*/
    
        /* As per most tasks, this task is implemented in an infinite loop. */
        for( ;; ) {
            /* Print out the name of this task. */
            vPrintString( pcTaskName );
    
    		/* Delay for a period. */
    		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) {
    		/* This loop is just a very crude delay implementation. There is nothing to do in here. Later examples will replace this crude loop with a proper delay/sleep function. */
    		}
    	}
    }
    ```

  - Main

    ```c
    int main(void) {
    /* Create one of the two tasks. Note that a real application should check the return value of the xTaskCreate() call to ensure the task was created successfully. */
    xTaskCreate(vTask1, /* Pointer to the function that implements thetask. */ "Task 1",/* Text name for the task. This is to facilitate debugging only. */ 1000, /* Stack depth - small microcontrollers will use much less stack than this. */ NULL, /* This example does not use the task parameter. */ 1, /* This task will run at priority 1. */ NULL); /* This example does not use the task handle. */
    
    /* Create the other task in exactly the same way and at the same priority. */
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
    
    /* Start the scheduler so the tasks start executing. */
    vTaskStartScheduler();
    
    /* If all is well then main() will never reach here as the scheduler will now be running the tasks. If main() does reach here then it is likely that there was insufficient heap memory available for the idle task to be created. For more information, see Heap Memory Management. */
    for( ;; );
    
    }
    ```

    - 두 작업이 동시에 실행되는 것 느껴질 것이지만, 실제 그렇지는 않음

      - 실제로는 두 가지 작업은 모두 실행 상태로 빠르게 빠져 나감
      - 두 작업 모두 동일한 우선 순위로 실행되므로 동일한 프로세서 코에서 시간을 공유하여 동작
        - Task 1 Running & Task2 Not Running
        - Task 1 Not Runnign & Task1 Running
          - 위 2가지 동작의 반복으로 실행 중인 상태

    - Task2를 Task1에서 생성할 수 있음

      ```c
      void vTask1(void *pvParameters) {
          const char *pcTaskName = "Task 1 is running\r\n";
          volatile uint32_t ul; /* volatile to ensure ul is not optimized away.*/
      
          /* If this task code is executing then the scheduler must already have been started. Create the other task before entering the infinite loop. */
          xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
      
          for( ;; ) {
          	/* Print out the name of this task. */
              vPrintString(pcTaskName);
      
              /* Delay for a period. */
              for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {
              /* This loop is just a very crude delay implementation. There is nothing to do in here. Later examples will replace this crude loop with a proper delay/sleep function. */
              }
          }
      }
      ```



##### c. Task 파라미터 사용

- 예제 1에서 생성된 두 태스크와 거의 동일하지만, 출력하는 문자열을 다르게 가져감

  - 태스크 파라미터를 사용하여 출력해야하는 문자열을 각 태스크에 전달할 수 있음

- 단일 태스크 구현의 인스턴스를 작성하여 제거할 수 있음

- 단일 태스크 함수 (vTaskFunction)의 코드를 포함

  - vTaskFunction (예제 1에서 사용한 Task1 & Task2를 대체)

  ```c
  void vTaskFunction(void *pvParameters) {
      char *pcTaskName;
      volatile uint32_t ul; /* volatile to ensure ul is not optimized away.*/
      /* The string to print out is passed in via the parameter. Cast this to a character pointer. */
      pcTaskName = (char *) pvParameters;
  
      /* As per most tasks, this task is implemented in an infinite loop. */
      for( ;; ) {
          /* Print out the name of this task. */
          vPrintString(pcTaskName);
  
          /* Delay for a period. */
          for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {
          /* This loop is just a very crude delay implementation. There is nothing to do in here. Later exercises will replace this crude loop with a delay/sleep function. */
          }
      }
      
  }
  ```

  - Main

  ```c
  /* Define the strings that will be passed in as the task parameters. These are defined const and not on the stack to ensure they remain valid when the tasks are executing. */
  static const char *pcTextForTask1 = "Task 1 is running\r\n";
  static const char *pcTextForTask2 = "Task 2 is running\r\n";
  
  int main(void) {
      /* Create one of the two tasks. */
      xTaskCreate(vTaskFunction, /* Pointer to the function that implements the task. */ "Task 1", /* Text name for the task. This is to facilitate debugging only. */ 1000, /* Stack depth - small microcontrollers will use much less stack than this. */ (void*)pcTextForTask1, /* Pass the text to be printed into the task using the task parameter. */ 1, /* This task will run at priority 1. */ NULL);
      /* The task handle is not used in this example. */
  
      /* Create the other task in exactly the same way. Note this time that multiple tasks are being created from the SAME task implementation (vTaskFunction). Only the value passed in the parameter is different. Two instances of the same task are being created. */
      xTaskCreate(vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 1, NULL);
  
      /* Start the scheduler so the tasks start executing. */
      vTaskStartScheduler();
  
      /* If all is well then main() will never reach here as the scheduler will now be running the tasks. If main() does reach here then it is likely that there was insufficient heap memory available for the idle task to be created. For more information, see Heap Memory Management. */
      for( ;; );
  }
  ```

***

#### 4. Task 우선 순위

- xTaskCreate() 함수의 unPriority 매개 변수는 생성되는 작업에 초기 우선 순위를 설정함
  - vTaskPrioritySet() 함수를 사용하여 스케줄러가 시작된 후에 우선 순위를 변경할 수 있음
- 사용 가능한 최대 우선 순위 수는 configMAX_PRIORITYIES compile-time configuration 상수에 의해 설정됨
  - 범위는 0 ~ -1 (MAX)
- 일반적인 방법
  - configMAX_PRIORITIES 의 최대 값을 제한하지 않음
    - 하지만, 값이 높을수록 더 많은 RAM이 소모되고 최악의 경우 실행 시간이 길어지므로 최소 값으로 유지하는 것이 좋음
- 아키텍처에 최적화 된 방법
  - 적은 양의 어셈블러 코드를 사용하여 일반적인 방법보다 빠름
    - configMAX_PRIORITIES 설정은 최악의 실행 시간에는 영향을 주지 않음
  - 이 방법을 사용하면 configMAX_PRIORITIES는 32보다 클 수 없음
    - 하지만 동일하게, 최소 값을 유지하는 것이 가장 좋음!
  - 사용 방법은 configUSE_PORT_OPTIMISED_TASK_SELECTION 값을 1로 변경해주면 됨



