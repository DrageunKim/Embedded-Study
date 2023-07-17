# 23.07.15 - UART Setting & 용어 정리



## 1. UART Setting

1) System Register Unlock - Register값 셋팅을 위해 System Unlock
2) UART Module Setting - 몇번 UART를 사용할 것인지 설정
3) UART Clock Setting - 몇번 UART의 Clock 설정 (HIRC를 사용)
4) UART Interrupt Setting - Interrupt 사용 설정
5) UART RDAIEN Mask Setting - Data를 받기 위한 상태 확인 Bit 설정
6) UART Open Setting - UART Open & BaudRate 설정
7) System Register Lock - Register값 셋팅 완료하여 System Lock



※ RDAIEN - Received Data Available Interrupt Enable Bit

※ HIRC - High-Speed Internal RC(Resistor-Capacitor) Oscillator

- 장치에 안정적이고 정확한 클록 신호를 제공하는 내부 클록 소스

※ LIRC - High-Speed Internal RC(Resistor-Capacitor) Oscillator

- 장치에 안정적이고 정확한 클록 신호를 제공하는 내부 클록 소스

