# 23.07.14 - Double Free / Pointer, ifndef



## 1. Double Free

- 업무를 하다보니 메모리 문제로 재부팅되는 문제가 확인되었음

  - 확인결과, Free된 메모리를 다시 한번 Free 동작을 수행하면서 재부팅 발생

    > "더블 프리(double free)"는 프로그래밍에서 발생하는 일반적인 오류로, 
    > 이미 메모리 해제(free 또는 delete)가 이루어진 메모리 블록에 대해 다시 메모리 해제를 시도하는 것을 의미합니다.
    >
    > 이는 다음과 같은 상황에서 발생할 수 있습니다:
    >
    > 동일한 포인터에 대해 두 번 free()나 delete를 호출하는 경우.
    > 두 개 이상의 포인터가 같은 메모리 블록을 가리키고, 각 포인터에 대해 free()나 delete를 호출하는 경우.
    > 더블 프리는 심각한 문제를 일으킬 수 있습니다. 일단 메모리 블록이 해제되면, 운영 체제나 메모리 관리자는 그 메모리 블록을 재사용할 수 있게 되므로, 블록을 다시 해제하려고 시도하면 메모리 관리자의 내부 데이터 구조를 손상시킬 수 있습니다. 이로 인해 메모리 관리자가 불안정해지거나 프로그램이 비정상적으로 종료될 수 있습니다.
    >
    > 더블 프리를 피하려면 다음과 같은 기법을 사용할 수 있습니다:
    >
    > 메모리를 해제한 후에는 해당 포인터를 NULL로 설정합니다. 이렇게 하면 다시 메모리를 해제하려는 시도가 무시됩니다.
    > 메모리를 가리키는 포인터를 공유하지 않도록 합니다. 이렇게 하면 두 개의 포인터가 동일한 메모리를 해제하려는 상황을 피할 수 있습니다.
    > 이러한 기법들은 더블 프리를 방지하는 데 도움이 될 수 있지만, 이것들이 모든 경우에 완벽하게 작동하는 것은 아닙니다. 따라서 메모리 관리에 대한 철저한 이해와 정확한 메모리 사용 기법이 중요합니다.



## 2. C언어 특징

- 포인터 개념이 있기 때문에 함수를 설계할 때, 포인터 개념을 활용하면 주소값을 이용한 수행이 가능해짐

  - 메모리 주소를 받아 함수내에서 Free 동작을 시켜줄 수 있음

  

## 3. 파일 분할

-  Header파일들을 보다보니 아래 3가지 명령어들이 보여 무슨 기능을 하는지 찾아보았음

  - ##### #ifndef

  - ##### #define

  - ##### #endif

    - Header파일을 Include하면서 발생할 수 있는 중복현상을 방지하기 위해 사용하는 명령어