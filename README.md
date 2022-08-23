# SSD_PJT

## 가상 SSD 제작

### 0. 개요

#### 1. SSD

- HW를 SW로 구현한다.

#### 2. Test Shell Application

- 테스트 프로그램

#### 3. Test Script

- 테스트 프로그램 내 Test Code 작성

### 1. SSD 사전 지식

![Untitled](https://dolomite-knife-a29.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F7e238010-baf3-4814-8fb2-8e49bb9041e7%2FUntitled.png?table=block&id=ceed505b-f0de-4eae-a038-bffe6aa17429&spaceId=b7f25594-5c31-4fde-96db-3a66df49e5a6&width=900&userId=&cache=v2)

1. 저장할 수 있는 최소 공간의 사이즈는 4KB (한 글자 = 약 1Byte로 간주했을 때, 4096글자 저장 가능 공간)
2. 각 공간마다 LBA(Logical Block Address)라는 주소를 가진다.
3. SSD는 OS로부터 Read/Write/Unmap 등 다양한 명령어를 전달받는다.
4. 컨트롤러 역할
   1. OS는 Filesystem을 거쳐 LBA 주소에 특정 값 R/W 요청
   2. 컨트롤러가 이 명령들을 받아 Nand Flash Memory에 저장
5. NAND Flash Memory
   1. 실제로 값들이 저장되는 곳
   2. 컨트롤러에 의해 값이 저장 된다.

### 2. 구현해야 할 가상 SSD

- 최소화된 기능 수행
  - Read 명령어와 Write 명령어만 존재한다.
  - LBA 단위는 4 Byte(실제로는 4KB이지만, 가상 SSD 최소 저장공간 사이즈는 4Byte로 제작)
  - LBA 0~99까지 100칸을 저장할 수 있다.
- 총 400 Byte를 저장할 수 있는 가상 SSB를 구현한다.

### 3. Write 명령어 동작 예시

1. Write 명령어 사용 예시 1

   - ssd W 3 0x1298CDEF : 3번 LBA 영역에 값 0x1298CDEF를 저장한다.

   ![Untitled](https://dolomite-knife-a29.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F89376696-0b73-432e-a31a-e65cc2d8f3fc%2FUntitled.png?table=block&id=eeb6266d-948e-4d58-87b1-910bbdb3f1a3&spaceId=b7f25594-5c31-4fde-96db-3a66df49e5a6&width=1160&userId=&cache=v2)

2. Write 명령어 사용 예시 2

   - ssd W 2 0xAAAABBBB
   - ssd W 97 0x9988FFFF
   - 출력결과 없음(저장만 수행)

   ![Untitled](https://dolomite-knife-a29.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F06eecfe8-ae04-4143-a56e-2a7a716a8c3d%2FUntitled.png?table=block&id=03306a13-8e94-48d2-8fcf-67ce8b897f90&spaceId=b7f25594-5c31-4fde-96db-3a66df49e5a6&width=1170&userId=&cache=v2)

### 4. Read 명령어 동작 예시

1. Read 명령어 사용 예시
   - ssd R 2
     - 출력결과 : 0xAAAABBBB
   - ssd R 97
     - 출력결과 : 0x9988FFFF

### 5. 실제로 저장하는 위치

- nand.txt 파일을 생성한다.
  - 사용자가 Write 할 때마다, SSD 내부 (Nand)에 기록이 된다.
  - 이를 모사하여, nand.txt 파일에 값을 저장해 둔다.
- 화면 출력하지 않고 result.txt 파일에 결과를 저장한다.
  - Write 명령어 수행시
    - result.txt 파일 건드리지 않는다.
    - Write는 내부적으로 기록만 수행한다.
  - Read 명령어 수행시
    - result.txt 파일 내용이 교체 된다.
- 즉, Read 명령어 실행시 결과값이 result.txt 파일에 저장
- Write 명령어 실행시 nand.txt 파일에 값을 저장

![Untitled](https://dolomite-knife-a29.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F83f2b0a0-407c-4eeb-b485-8c8d9fc0b044%2FUntitled.png?table=block&id=e2bec9a2-7153-4cb7-8a3a-37e71c224af5&spaceId=b7f25594-5c31-4fde-96db-3a66df49e5a6&width=1390&userId=&cache=v2)

### 6. 세부 규정

- 데이터 범위
  - LBA : 0 ~ 99, 10진수
  - 값 : 항상 0x가 붙으며 10 글자로 표기한다. ( 0x00000000 ~ 0xFFFFFFFF )
- Read 명령어
  - ssd R [LBA]
  - result.txt 에 읽은 값이 적힌다. (기존 데이터는 사라진다.)
  - 한번도 안적은 곳은 0x00000000 으로 읽힌다.
- Write 명령어
  - ssd W [LBA] [값]
  - nand.txt 에 저장한 값이 기록된다.

## Test Shell Application

### 0. 개요

- SSD를 테스트 할 수 있는 프로그램
  - Shell이 동작하여 사용자 입력을 받는다.
  - 사용 가능 명령어
    - write
    - read
    - exit
    - help
    - fullwrite
    - fullread
  - read / write 명령어 수행시, 제작한 “ssd” app을 실행시켜 값 읽기 / 저장 명령을 수행한다.

### 1. Test Shell 동작 예시

- 사용자 입력 예시
  - write 3 0xAAAABBBB
    - 3번 LBA 에 0xAAAABBB 를 기록한다.
    - ssd 에 명령어를 전달한다.
    - read 3
    - 3번 LBA 를 읽는다.
    - ssd 에 명령어를 전달한다.
    - result.txt 에 적힌 결과를 화면에 출력한다.
- exit/help
  - exit 명령어는 shell을 종료시킨다
  - help 명령어는 각 명령어당 사용 방법을 출력한다.
- fullwrite/fullread
  - fullwrite 명령어
    - LBA 0번부터 99번까지 Write를 수행한다
    - ssd 전체에 값이 써진다.
    - ex) fullwrite 0xABCDFFFF
      → 모든 LBA 값 0xABCDFFFF가 적힌다.
  - fullread 명령어
    - LBA 0번부터 99번까지 Read를 수행한다.
    - ssd 전체 값을 모두 화면에 출력한다.
    - ex) fullread
      → 모든 LBA의 값들이 화면에 출력된다.

### 2. 기능 구현시 유의사항

- 입력받은 매개변수가 유효성 검사를 수행한다
  - 파라미터의 Format이 정확해야 함
  - LBA 범위는 0 ~ 99
  - A ~ F, 0 ~ 9 까지 숫자 범위만 허용
- 없는 명령어를 수행하는 경우 “INVALID COMMAND”을 출력
  - 어떠한 명령어를 입력하더라도 segment fault가 나오면 안된다.

## Test Script 작성하기

### 1. 실제 Test 수행 프로그램 제작

- Test를 수행하는 명령어의 집합
- 주로 검증 팀에서 Test Script 제작한다.

### 2. TestApp1 제작하기

- Test Shell에서 “testapp1” 명령어를 입력하면 Script가 수행된다.
- 먼저 fullwrite를 수행한다.
- fullread를 하면서, write한 값대로 read가 되는지 확인한다.
  - SSD 정상 동작하는지 확인하는 프로그램

### 3. TestApp2 제작하기

- 0~5번 LBA에 0xAAAABBBB 값으로 총 30번 Write를 수행한다,
- 0~5번 LBA에 0x12345678 값으로 1회 Over Write를 수행한다.
- 0~5번 LBA Read 했을 때 정상적으로 값이 읽히는지 확인한다.
