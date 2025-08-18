2022-04-19

- 191203_R1 -> 201017_R2 버전 따라 화면 및 기능 수정
  
  - 최신본은 소스가 없어 구버전 소스에서 실행파일 및 펌웨어 참고해서 작업......
  
  - 하단 메뉴 선택 및 버튼 위치 변경
  
  - System Menu 버튼 삭제
  
  - Set Function 구역 및 Set Flicker 버튼 추가
  
  - funcMakeCtrlIOFusingPacket 메소드 인수 추가 (flicker 관련)
  
  - MODEL_INFO struct Flicker 관련 변수 추가
  
  - Check ModelName 창 열기 단축키('T') 삭제

2022-04-21

- FW 업데이트 - 펌웨어 파일 경로 세팅 수정
  
  - '.\FW 폴더' 고정 -> 파일 위치 상관없이  읽도록 수정

- Set Flicker 창 추가
  
  - Dialog 및 Dialog 클래스 생성
  
  - 화면 레이아웃 설정 및 컨트롤 추가(201017_R2 버전 기준)
  
  - 화면 컨트롤 변수 생성 및 데이터 규칙 세팅 (데이터 길이, 10진수, 16진수)
  
  - Model 정보 및 화면 컨트롤 변수 연동
  
  - VCom Mode 선택에 따라 컨트롤 Enable 관리

- Model 정보 및  저장, 불러오기 메소드 수정
  
  - Flicker 관련 옵션 11종 추가

- Model 정보 변수 위치 이동
  
  - CTS_WR_HS_FUSINGDlg -> CTS_WR_HS_FUSING Class

- CTS_WR_HS_FUSINGDlg::funcMakeCtrlIOFusingPacket 메소드 수정
  
  - Flicker 관련 옵션 11종 추가
  
  - 옵션별 패킷 길이 설정(펌웨어 최종 버전 참고)

- 타이틀바 프로그램 버전 표기 ("TS_MA_HS_FUSING_v{프로그램 버전}")

2022-05-11

- 모델 정보 Horizon Total, Vertical Total 값 안바뀌는 버그 수정
  
  - 모델 정보 Save 전, Load 후 Total 값 계산 메소드 추가

2022-07-06

- Rs232 Port 설정 변경
  
  - Buffer Size 4096 -> 65535
  
  - Buffer Size 상수 등록: COM_LENGTH

- System, Pattern, Ctrl, Voltage Fusing 메소드 메시지 버퍼 사이즈 수정
  
  - Buffer Size -> 65535

2022-10-18

- 232 buffer size 변경 누락 수정 -> 65535

- fusing string count 자리수 02d => 03d, power_id 삭제

2022-10-19

- op box fusing string count 변경 누락 수정

2022-10-24

- op box fusing power type 변경 누락 수정

- 
