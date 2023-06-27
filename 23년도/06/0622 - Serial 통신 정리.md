# 23. 06. 22



## 1. UART vs I2C vs SPI

|                 | **UART**             | **I2C**                    | **SPI**                     |
| --------------- | -------------------- | -------------------------- | --------------------------- |
| **동기/비동기** | 비동기               | 동기                       | 동기                        |
| **관계 수**     | 1:1                  | N:N                        | 1:N                         |
| **선 수**       | 2 (TX, RX)           | 2 (SDA,SCL)                | 4 (SCK,MISO,MOSI,SS)        |
| **이중통신**    | 전이중               | 반이중                     | 전이중                      |
| **전송 거리**   | 김                   | UART 대비 짧음             | UART 대비 짧음              |
| **전송 속도**   | 느림                 | SPI 대비 느림              | 빠름                        |
| **용도**        | **외부 장치에 사용** | **다수의 센서 (제어용도)** | **프로세서, 메모리 (고속)** |

- #### UART

  - 보내는 쪽(TX)와 받는 쪽(RX)에서 **데이터를 보내는 속도를 보율(Baud Rate)**로 정함

    ![UART](C:\YG\101. 개인메모\ETC\UART.png)

    - TX 은 항상 데이터를 보내는 것이 아니며, 필요한 경우에만 데이터를 보냄

      > **RX 는 언제 TX가 데이터를 보내는지, 어디서부터가 TX가 보낸 데이터의 시작인지 알아낼 수 있는 방법이 필요**

    - **Write & Read 동작**

      ![UART-동작](C:\YG\101. 개인메모\ETC\UART-동작.png)

      - HIGH 상태 유지 (Idle) → LOW (Start) → 8Data Bits → HIGH (Stop & Idle)
      - 상단 그림은 'no Parity' 이지만, Parity가 있을 경우에는 Bit 7 뒤에 Parity Bit가 추가됨 (오류 확인 Bit)

    

- #### I2C

  - I2C 동작을 위해서는 HW적으로 Pull-Up 저항을 사용하여 Floating 방지 및 High 신호 유지를 시켜주어야 함

  - 데이터를 송/수신은 Master에서 주도, 데이터 송/수신할 때는 반드시 Slave Address를 Master에 알려주어야 함

  - UART와는 달리 동기화 통신이기에 통신속도(BaudRate)를 정해주지 않아도 됨

  - ##### Write＆Read 동작

    - SDA(LOW) → SCL(LOW) : 통신 시작 신호

      → 8Bits Data (7Bit:Slave Address & 1Bit:Write/Read Bit) → Ack Bit → 8Bits Data → Ack Bit →

      SCL(HIGH) → SDA(HIGH) : 통신 종료 신호

    ![I2C-Write동작](C:\YG\101. 개인메모\ETC\I2C-Write동작.png)

![I2C-Read동작](C:\YG\101. 개인메모\ETC\I2C-Read동작.png)



- #### SPI

  - MISO(Master In & Slave Out)과 MOSI(Master Out & Slave In) 을 통한 양방향 통신이 가능

  - SS (Chip Select) 를 통해 통신하고자 하는 Slave 선택 가능 (HIGH-동작 안함, LOW-동작)

  - Master가 요청을 해야 Slave에서 동작을 수행

  - SCLK(Serial Clock)을 통해 통신주기 설정 가능

  - ##### Write & Read 동작

    - Master에서 통신하고 싶은 Slave-SS에 LOW 신호를 보내 Enable시킨 뒤 Clock을 생성하여 동기화한 다음 Data를 주고 받음 (1개만 통신 가능)

    - 통신방식은 Mode1~4 중에 Slave에서 필요로 하는 Mode에 맞게 설정하면 됨

      ![SPI-Mode](C:\YG\101. 개인메모\ETC\SPI-Mode.png)

      ![SPI-Mode별CPOL](C:\YG\101. 개인메모\ETC\SPI-Mode별CPOL.png)