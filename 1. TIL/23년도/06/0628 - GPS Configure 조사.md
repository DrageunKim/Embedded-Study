# 23. 06. 28



## 1. GPS Configure 설정

- UBlox

| Name | Description                                                  |
| ---- | ------------------------------------------------------------ |
| HDOP | 수평면에서의 위치 정확도 (값이 낮으면 정확도 높아짐)         |
| VDOP | 수직면에서의 위치 정확도 (값이 낮으면 정확도 높아짐)         |
| PDOP | 수평 및 수직 정확도를 종합적으로 고려한 전체 위치 정확도     |
| TDOP | 시간 정확도                                                  |
| HNR  | 수신기의 위치 및 타이밍 업데이트 속도                        |
| C/NO | 수신기에서 수신된 위성 신호의 수신 세기 대 잡음 밀도를 나타내는 값 |

1. Configure View
   - GPS 수신감도 관련
     - NAV5 (Navigation5)
       - Navigation Mode : 사용 환경 설정
       - Navigation Input Filters : 수신 필터 설정
       - Navigation Output Filters : 송신 필터 설정
     - PMS (Power Management Setup) : 칩에서 사용하는 전류값을 제어 (전류에 따라 송/수신에 영향을 줌)
