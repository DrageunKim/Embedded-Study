# 23.07.20 - FreeRTOS

[참고 블로그](https://m.cafe.daum.net/easyflow/F13G/51?listURI=%2Feasyflow%2FF13G)



## [기본 소개]

> **[Free RTOS]** - [공식 홈페이지](https://www.freertos.org/index.html) 
>
> : 오픈 소스 실시간 내장현 운영체제 중 하나로 단순함, 뛰어난 이식성, 간결함을 목표로 설계되었음!
>
>   대부분의 Code가 C언어로 작성되어 이식성이 뛰어남!



- #### 제공하는 기능

  1. Multi-Tasking

     - 선점형 & 비선점형 선택 가능
     - Task 수 제한 없음

     - 동적으로 Task 생성 가능

     - Priority 수 제한 없음

     - 두개 이상의 Task에 같은 Priority 할당 가능

  2. Co-Routine

  3. Message Queue

  4. Semaphore

  5. Memory Management



## 1. Multi-Tasking

- **정의**
  - 여러 개의 Task를 동시에 실행 시킬 수 있는 기능
    - 실제로 여러 개의 Task가 동시에 수행되는 것은 아님
    - 여러 개의 Task를 아주 짧은 시간 간격으로 번갈아 실행시켜 사용자가 그렇게 느끼도록 해줌
- **Scheduling 방식**
  - NonPreemption 방식과 Preemption - Priority Based Round Robin Scheduling 방식을 모두 지원함
    - 생성되는 Task 수와 Priority 수의 제한이 없으며, 실행 중에 동적으로 Task 를 생성할 수도 있음

> **여러 개의 Task 중 어느 Task를 언제 얼마동안 실행 시킬 것인지를 결정하는 것을 Scheduling 이라고 함**
>
> - Scheduling 방식은 크게 2가지로 분류
>
>   1. 현재 수행중인 Task 가 자발적으로 수행 권한은 양보할 때 다른 Task 가 수행 권한을 얻을 수 있는 NonPreemption 방식
>      - Voluntary Scheduling 방식이라고도 함
>
>   2. Scheduler 가 필요에 따라 강제적으로 수행 권한을 다른 Task 에게 양도할 수 있는 Preemption 방식
>      - Preemption 방식에는 여러가지가 있는데 그 중 가장 많이 사용하는 방식이  Priority Scheduling + Round Robin Scheduling 방식을 혼합한 것	
>        - 기본적으로 Priority Scheduling 방식을 따르되 같은 Priority를 가진 Task들은 Round Robin 방식으로 Scheduling 하는 것
>        - 이 방식을 Priority Based Round Robin Scheduling 방식이라고 함

- Library 형태로 지원하며, 대표 API 는 아래와 같음
  1. xTaskCreate - 새로운 Task를 생성
  2. xTaskDelete - Task를 삭제
  3. vTaskDelay - 주어진 Clock Tick 동안 Task를 지연시킴
  4. vTaskDelayUntil - 명시된 시점까지 Task를 지연시킴
  5. uxTaskPriorityGet - Task의 우선순위를 돌려줌
  6. vTaskPrioritySet - Task의 우선순위를 지정함
  7. vTaskSuspend - Task를 중지시킴
  8. vTaskResume(FromISR) - 중지된 Task를 다시 시작시킴



## 2. Co-Routine

- **정의**
  - 여러 개의 Entry Point를 가질 수 있고, 임의의 지점에서 Suspending과 Resuming이 가능한 Sub-Routine을 말함
- **장점**
  - 작은 자원으로 Multi-Tasking 효과를 낼 수 있음
    - Task들과는 달리 Co-Routine간에 제어권 전환이 이루어질 때 Context Switching을 하지 않으며,
      Co-Routine들이 Stack을 공유하기 때문
- **단점**
  - Voluntary Scheduling만 지원 가능하고, Local 변수 활용이 힘들다는 단점이 있음

- Library 형태로 지원하며, 대표 API 는 아래와 같음
  1. xCoRoutineCreate - 새로운 Co-Routine을 생성함
  2. crDELAY - 주어진 Clock Tick 동안 Co-Routine을 지연시킴



## 3. Message Queue

- **정의**
  - Task들이 작은 크기의 데이터인 Message를 비동기(Asynchronous)적으로 서로 주고 받을 수 있도록 해줌
- Library 형태로 지원하며, 대표 API 는 아래와 같음
  1. xQueueCreate - 새로운 Queue 생성
  2. xQueueDelete - Queue 삭제함
  3. xQueueSend(FromISR) - Queue에 Message를 넣음
  4. xQueueReceive(FromISR) - Queue로부터 Message를 가져옴
  5. uxQueueMessagesWaiting - Queue에 저장된 Message의 개수를 돌려줌
  6. crQUEUE_SEND(_FROM_ISR) - Message Queue로 Message를 보냄 (Co-Routine에서 사용)
  7. crQUEUE_RECEIVE(_FROM_ISR) - Message Queue로부터 Message를 받음 (Co-Routine에서 사용)



## 4. Semaphore

- **정의**
  - Multi-Tasking 환경에서 한 순간에 하나의 Task만이 사용할 수 있도록 공유 자원을 보호해야 할 피룡가 있는 경우 사용하는 대표적인 자료 구조
- Library 형태로 지원하며, 대표 API 는 아래와 같음
  - vSemaphoreCreateBinary - Semaphore를 생성
  - xSemaphoreTake(FromISR) - Semaphore를 획득함 / Semaphore의 P Operation 역할을 함
  - xSemaphoreGive(FromISR) - Semaphore를 풀어줌 / Semaphore의 V Operation 역할을 함



## 5. Memory Management

- Library 형태로 지원하며, 대표 API 는 아래와 같음
  - pvPortMalloc - 주어진 크기만큼 동적으로 메모리를 할당
  - vPortFree - 할당받은 메모리를 해제



***

# [기본 구조]

- #### Contents

  1. Tasks

     1-1. Task의 상태

     1-2. Task의 우선순위

     1-3. Task의 구현

     1-4. Task 생성 매크로

     1-5. Idle Task

     1-6. Idle Task 훅

     1-7. TCB

     ​	1-7-1. Task가 가지고 있어야만 하는 정보들

     ​	1-7-2. Task 제어 블록 (TCB)

     1-8. Task의 생성과 삭제

     ​	1-8-1. Task의 생성

     ​	1-8-2. Task의 삭제



# 1. Tasks

### 1-1. Task의 상태

- Task는 아래의 상태 중 하나로 존재
  - Running / 실행
    - Task가 실제로 실행될 때 이것을 실행중이라 함
    - Task가 현재 프로세서를 사용하고 있음
  - Ready / 준비
    - Task는 실행 가능하지만 우선순위가 같거나 더 높은 다른 Task가 현재 이미 실행중인 상태에 있기 때문에 실행될 수 없는 상태
  - Blocked / 대기
    - 만약 Task가 시간적 또는 외부적 이벤트를 위해 기다리고 있다면 이것은 대기 상태
      - 만약, Task가 vTaskDelay() 함수를 호출한다면 이것은 지연 시간이 종료될 때까지 대기중인 상태가 됨
      - 또한, Task는 Queue와 Semaphore Event를 기다릴 때 대기 상태가 될 수 있음
    - 대기 중인 상태에 있는 Task는 항상 '제한 시간'을 가지고 있음
      - 이 제한 시간이 지나면 Task는 대기 상태에서 벗어남 (UnBlocked)
    - 대기중인 Task는 Scheduling 대상에서 제외됨
  - Suspended / 중지



### 1-2. Task의 우선순위

- 각각의 Task에는 0 ~ (configMAX_PRIORITIES - 1) 까지의 우선순위 할당 가능
  - configMAX_PRIORITIES는 FreeRTOSConfig.h에 정의되어 있고, 응용 프로그램에 따라 다른 값으로 지정될 수 있음
  - 하지만, configMAX_PRIORITIES에 더 큰 값을 지정할수록 FreeRTOS 커널은 더 많은 RAM을 소비함
- 숫자가 작을수록 낮은 우선순위의 Task를 의미
- Idle Task의 우선순위는 tskIDLE_PRIORITY로 정의되어 있고 기본적으로 0임
- 항상 대기 또는 실행중인 Task 중에서 가장 높은 우선순위의 Task를 실행함



### 1-3. Task의 구현

- Task는 아래와 같은 방식으로 구현할 수 있음

```c
void vATaskFunction (void *pvParameters) {
	for( ;; ) {
	}
}
```

- pdTASK_CODE형은 void를 반환하고 매개변수로 void 포인터를 받는 함수로써 정의됨
  - Task를 구현하는 모든 함수는 이런 형식으로 작성되어야 함
  - void 포인터 매개변수는 어떤 형의 정보라도 Task에 전달할 수 있도록 해줌
- Task 함수는 반환하지 않음
  - 그래서 보통 무한루프로 작성됨
- Task 응용 프로그램 코드가 For문 안에 해당함
  - 이렇게 구현된 Task는 xTaskCreate()함수를 호출함으로써 생성되고 vTaskDelete()함수를 호출함으로써 삭제됨



### 1-4. Task 생성 매크로

- Task 함수는 portTASK_FUNCTION | portTASK_FUNCTION_PROTO 매크로를 사용하여 정의될 수도 있음

- 매크로들을 사용하면 컴파일러의 특정 문법을 써서 함수 정의와 원형(ProtoType) 각각을 추가할 수 있게 해줌

  - 이식 환경에서 특별히 요구하지 않는 한 사용되지 않음

- 함수의 원형은 아래의 두가지 방법으로 정의될 수 있음

  ```c
  - void vATaskFunction (void *pvParameters);
  1. portTASK_FUNCTION_PROTO (vATaskFunction, pvParameters);
  2. portTASK_FUNCTION_PROTO (vATaskFunction, pvParameters) {
         for (;;) {
         }
     }
  ```

  - 응용 프로그램 코드는 For문에 넣어주면 됨



### 1-5. Idle Task

- Idle Task는 Scheduler가 시작될 때 자동으로 생성됨
- Idle Task는 삭제된 Task에게 할당된 메모리를 해제시켜주는 기능을 함
  - 그래서, vTaskDelete() 함수를 사용할 때는 Idle Task가 CPU 처리 시간을 받지 못하는 상황 (Starvation)이 되지 않도록 주의할 필요가 있음
- Idle Task는 다른 기능이 없음
  - 그래서, 어떠한 상황에서든지 CPU 처리 시간을 다른 Task에게 빼앗겨도 상관없음
  - 일반 응용 프로그램 Task가 Idle Task와 같은 우선순위(tskIDLE_PRIORITY)를 가지는 것도 가능함



### 1-6. Idle Task 훅

- Idle Task 각각의 주기동안 호출되는 함수

  - 만약, 응용 프로그램의 기능이 Idle Task의 우선순위와 같게 동작하기를 원한다면 두가지 방법이 있음
    1. Idle Task 훅 안에서 기능을 구현
       - 항상 적어도 하나의 Task는 준비 상태에 있어야만 함
       - 그래서, 훅 함수가 Task를 대기 상태로 만드는 vTaskDelay() 같은 API를 호출하는 것은 바람직하지 못함
       - 다만, Co-Routine의 경우는 훅 함수 내부에서 그러한 API를 호출하는 것이 허용됨
    2. Idle Task와 같은 우선순위를 가지는 Task를 생성
       - 이것이 1번째 방법보다 더욱 유연한 해결책이 되지만, 더 많은 RAM을 사용하기에 오버헤드가 있음

- Idle Task 훅을 생성하기 위해서는 'FreeRTOSConfig.h'에 있는 'configUSE_IDLE_HOOK'를 1로 설정한 후 아래의 원형을 가지는 함수를 정의

  ```c
  void vApplicationIdleHook (void);
  ```

  - Idle 훅을 사용하면 간단하게 프로세서를 절전 상태로 만들 수 있음



### 1-7. TCB (Task Control Block)

#### 1-7-1. Task가 가지고 있어야만 하는 정보들

- Stack에 관련된 정보
  - Task를 수행하기 위해서는 자신만의 Stack 영역이 필요함
    - 이 영역에는 지역변수, 프로그램 카운터, 레지스터 정보 등을 저장하여 문맥 전환이 일어날 때 정보를 잃어버리지 않도록 함
    - 이를 위해, Task 제어 블록은 Stack의 시작 지점 / 끝 지점 / 스택의 크기에 관한 정보를 알아야 함
- Queue에 관련된 정보
  - Task의 상태에서 준비 / 대기 / 실행 / 중지 가 있음
    - 이 상태를 구분하기 위하여 Task는 각각의 상태에 해당하는 Queue에 들어가기에, 이런 Queue를 위한 구조를 가지고 있어야 함
- Task 우선순위
  - FreeRTOS는 우선순위 기반의 Scheduling을 하기 때문에 각 Task는 반드시 우선순위를 가져야 함
    - 이를 위해, Task 제어 블록은 우선순위에 관한 정보를 가져야 함
- 기타 정보
  - Debugging을 편리하게 하기 위해서는 Task마다 고유의 이름과 번호를 가지는 것이 좋음
    - 이를 위해, 위에서 언근한 것들과는 달리 필수 요소는 아니지만 TAsk 제어 블록이 Task의 이름과 번호에 관한 정보를 가질 수 있음

#### 1-7-2. Task 제어 블록 (TCB)

- Task가 필요로 하는 여러가지 정보들을 가지고 있는 Block

  - 위에서 언급한 Task가 가져야할 여러가지 정보를 실제로 구현해 놓은 것이라고 할 수 있음

  > **<TCB를 구현하는 예제 소스 코드>**
  >
  > ```c
  > # taskTaskControlBlock - TASKS.c
  > 
  > typedef struct tskTaskControlBlock {
  > 	volatile portSTACK_TYPE *pxTopOfStack;
  >     xListItem xGenericListItem;
  >     xListItem xEventListItem;
  >     unsigned portBASE_TYPE uxPriority;
  >     portSTACK_TYPE *pxStack;
  >     unsigned portBASE_TYPE uxTCBNumber;
  >     signed portCHAR pcTaskName[ configMAX_TASK_NAME_LEN ];
  >     unsigned portSHORT usStackDepth;
  > } tskTCB;
  > ```
  >
  > - 위와 같이 TCB는 구조체로 정의되어 있으며, Task가 필요한 정보를 모두 가지고 있음



### 1-8. Task 생성과 삭제

- Task를 생성하는 함수인 xTaskCreate()와 vTaskDelete() API의 원형만 알아도 응용 프로그램을 구현할 수는 있지만 
  함수 내부 구조를 알아야 더욱 안정적인 프로그램을 만들 수 있음
  - xTaskCrate() & xTaskDelete() 내부 구조를 간단히 살펴보고 대략적으로 어떤 방식으로 구현이 되어있는지를 소개
  - FreeRTOS 내부적으로 Task가 어떻게 생성되고 삭제되는지 알아볼 필요가 있음

#### 1-8-1. Task의 생성

```c
# xTaskCreate() - TASKS.C

signed portBASE_TYPE xTaskCreate (pdTASK_CODE pvTaskCode,
                                  const signed portCHAR * const pcName,
                                  unsigned portSHORT usStackDepth,
                                  void *pvParameters,
                                  unsigned portBASE_TYPE uxPriority,
                                  xTaskHandle *pxCreatedTask) {
    signed portBASE_TYPE xReturn;
    tskTCB *pxNewTCB;
    static unsigned portBASE_TYPE uxTaskNumber = 0;
    
    pxNewTCB = prvAllocateTCBAndStack(usStackDepth);
	
    if (pxNewTCB != NULL) {
        portSTACK_TYPE *pxTopOfStack;
        
        prvInitialiseTCBVariables(pxNewTCB, usStackDepth, pcName, uxPriority);

        #if portSTACK_GROWTH < 0 {
        	pxTopOfStack = pxNewTCB->pxStack + (pxNewTCB->usStackDepth - 1);
    	} #else {
			pxTopOfStack = pxNewTCB->pxStack; 
		}
		#endif
    
    	pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pvTaskCode, pvParameters);
    
    	portENTER_CRITICAL(); {
			uxCurrentNumberOfTasks++;
		
            if (uxCurrentNumberOfTasks == (unsigned portBASE_TYPE)1) {
                pxCurrentTCB = pxNewTCB; 
                
                prvInitialiseTaskLists();
            } else {
                if (xSchedulerRunning == pdFALSE) {
                    if (pxCurrentTCB->uxPriority <= uxPriority) {
                        pxCurrentTCB = pxNewTCB; 
                    }
                }
            } 

            if (pxNewTCB->uxPriority > uxTopUsedPriority) {
                uxTopUsedPriority = pxNewTCB->uxPriority;
            }

            pxNewTCB->uxTCBNumber = uxTaskNumber;
            uxTaskNumber++;

            prvAddTaskToReadyQueue(pxNewTCB); 
            
            xReturn = pdPASS;
        }
    	portEXIT_CRITICAL();
	} else {
		xReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	} 

	if (xReturn == pdPASS) {
		if ((void *)pxCreatedTask != NULL) {
			*pxCreatedTask = (xTaskHandle) pxNewTCB;
        }

        if (xSchedulerRunning != pdFALSE) {
			if (pxCurrentTCB->uxPriority < uxPriority) {
				taskYIELD();
			}
		}
	}

	return xReturn;
}
```

1. Task에 대한 초기 정보 설정

2. Task를 위한 Stack 생성

3. xTaskCreate()는 먼저 Task 제어 블록을 생성하기 위해 'tskTCB* pxNewTCB' 라는 TCB에 대한 포인터 변수를 선언

4. 매개변수로 전달 받은 Task에 관련된 정보(Stack 크기, Task 이름, Task 우선순위)를 TCB에 저장

5. 명시된 Stack 크기만큼 생성하고 Task로 넘어온 매개변수와 Task가 수행될 지점으미 주소를 스택에 저장 '

6. Critical Section 시작

7. 준비된 Queue에 Task를 추가

8. Critical Section 끝

9. 현재 생성되는 Task를 우선순위에 따라 Ready Queue에 넣음

10. Task 생성에 성공하면 Handle을 저장함

11. 생성된 Task가 현재 실행중인 Task보다 우선순위가 높을 경우에는 문맥 전환을 함

12. Task 생성에 성공하면 Handle을 저장함

13. TaskYIELD() 함수를 호출하여 문맥 전환이 일어남

#### 1-8-2. Task의 삭제

```c
# vTaskDelete() - TASKS.C

#if (INCLUDE_vTaskDelete == 1)
void vTaskDelete (xTaskHandle pxTaskToDelete) {
	tskTCB *pxTCB; 
	taskENTER_CRITICAL(); {
		if (pxTaskToDelete == pxCurrentTCB) {
			pxTaskToDelete = NULL;
		} 

        pxTCB = prvGetTCBFromHandle(pxTaskToDelete);
		vListRemove(&(pxTCB->xGenericListItem));
	
        if (pxTCB->xEventListItem.pvContainer) {
			vListRemove( &( pxTCB->xEventListItem ) );
		}

        vListInsertEnd((xList *) &xTasksWaitingTermination, &(pxTCB->xGenericListItem));
		++uxTasksDeleted;
	}
    taskEXIT_CRITICAL();
    
	if (xSchedulerRunning != pdFALSE) {
        if ((void *)pxTaskToDelete == NULL) {
			taskYIELD();
        }
    }
}
#endif
```

1. 인자로 삭제되어야 할 Task의 Handle이 넘어옴

2. 삭제될 Task가 현재 실행중인 Task인지를 판별

3. 자신을 삭제하기 위한 Handle을 받아옴

4. 삭제할 Task를 준비 리스트에서 제거

5. 삭제 대상이 Event를 기다리고 있는 중일 경우 Event List에서도 제거

6. 할당된 메모리를 앞으로 해제하기 위한 해제 대기 리스트에 TCB를 올려놓음

   > vTaskDelete() 함수는 Task의 Handle을 매개변수로 받음
   >
   > 그리고,이 Handle을 이용하여 TCB에 대한 포인터를 얻어옴
   >
   > 얻어온 TCB를 이용하여 모든 대기 Queue에서 Task를 삭제하고, xTaskWaitingTerminantion 리스트에 Task를 추가함
   >
   > 그래서 나중에 실제로 메모리를 해제 시켜주는 작업을 따로 해줘야 함
   >
   > → 모든 작업이 끝날 후 taskYIELD() 함수를 호출해서 새로운 Task가 실행 중인 상태에 들어가도록 해줌