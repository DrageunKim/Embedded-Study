# 23.07.21 - Interrupt



## [Interrupt]

> **컴퓨터 작동 중에 예기치 않은 문제가 발생한 경우라도 업무 처리가 계속될 수 있도록 하는 컴퓨터 운영체계의 한 기능**

##### 컴퓨터 프로그램이 작동 중에 어떤 문제가 발생했을 경우, 문제를 해결하고 다시 돌아와 원래 수행하던 프로그램을 다시 수행하도록 만드는 매커니즘



- ##### 사용자 관점

  - 스마트폰을 이용해서 유튜브를 시청하고 있다가 갑자기 전원 버튼을 누르면 화면이 꺼지면서 대기 상태로 들어가게 됨
    - **'전원을 누르는 행위'** - 프로그램의 입장에서  **'예기치 않은 문제'**
      - 인터럽트를 발생시킬 수 있는 **'인터럽트 소스'**가 될 수 있음



- ##### 컴퓨터 관점

  - 진행중인 작업 순서 

    1. 모뎀 또는 와이파이에서 유튜브 홈페이지 정보를  가져오게 하여 GPU에 전달하도록 명령

    2. GPU는 받은 Data를 Rendering하여 영상을 만든 다음 DisPlay System에 Data 전달

    3. DisPlay System에서 화면에 출력

  - 인터럽트 발생

    - 프로그램 동작을 위해 명령어를 하나씩 메모리에 가져와서 실행하다가 인터럽트가 발생하게 되면!

      1. Interrupt Controller가 미리 Mapping 시켜 놓은 Interrupt Source로부터 Interrupt가 발생했음을 받고 CPU에 Interrupt 처리 요청
         - 이 작업을 IRQ (Interrupt Request)라고 함

      2. 현재 수행하던 프로그램과 프로세서의 상태를 저장하고 **Interrupt Handler** 라고 하는 인터럽트 처리기로 이동

      3. 인터럽트 처리기가 **Interrupt Service Routine (ISR)** 이라는 인터럽트 처리 동작을 수행

      4. 인터럽트 처리 동작이 완료되면 인터럽트 처리기가 다시 원래 수행하던 프로그램으로 Return

      5. 이전 상태로 프로그램과 프로세서 상태를 가져와서 다시 프로그램 수행



- ##### Interrupt의 종류

  1. External Interrupt (외부 인터럽트)

     - System과 연결되는 외부 I/O (PCIe, UART, I2C, USB 등)으로부터 전송되는 Data의 시작이나 종료를 알리는 경우

     - 기타 버튼에 의해 제어되는 경우

       → 이 경우는 H/W 적으로 수행되는 것이기에 H/W Interrupt 범주에 들어감

  2. Hardware Interrupt (H/W적으로 필요한 기능을 구현해 놓은 인터럽트)

     - 어떤 동작의 수행을 위해 Watchdog Timer나 다른 Timer 를 Setting 해두고 정해진 시간이 되었을 때 Interrupt를 발생 시키는 경우

  3. Software Interrupt (S/W에서 특정 동작을 위해 구현해 높은 인터럽트)

     - 특정 Application Program에서 메모리 접근 권한이나 기타 I/O Device의 자원 할당을 위해 접근 권한을 요청 하는 경우
       - 카메라 App을 실행 했을 때 카메라 접근 권한을 요청하는 팝업이 해당됨
         - 이를 Supervisor Call, SVC 라고 함
         -  Application은 System의 자원에 접근할 수 없기 때문에 운영체제(OS)를 통해 Application이 사용할 자원을 할당해 주는 일을 수행