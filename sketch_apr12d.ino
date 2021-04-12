#define PLUS 11
#define MINUS 12
boolean lastButton[2]={LOW, LOW}; //이전 눌림 상태를 저장
boolean currentButton[2]={LOW, LOW}; //현재 눌림 상태를 저장
int number=0; //세그먼트 숫자 표시
byte digits[10][7]={
    {1,1,1,1,1,1,0}, //숫자 0=>0,0,0,0,0,0,1
    {0,1,1,0,0,0,0}, //숫자 1=> 1,0,0,1,1,1,1
    {1,1,0,1,1,0,1}, //0,0,1,0,0,1,0
    {1,1,1,1,0,0,1}, //0,0,0,0,1,1,0
    {0,1,1,0,0,1,1}, //1,0,0,1,1,0,0
    {1,0,1,1,0,1,1}, //0,1,0,0,1,0,0
    {1,0,1,1,1,1,1}, //0,1,0,0,0,0,0
    {1,1,1,0,0,0,0}, //0,0,0,1,1,1,1
    {1,1,1,1,1,1,1}, //0,0,0,0,0,0,0
    {1,1,1,0,0,1,1}  //0,0,0,1,1,0,0
  };

void setup() {
  for(int i=2; i<10; i++){
    pinMode(i, OUTPUT);
  }
  digitalWrite(9, LOW);
  pinMode(PLUS, INPUT);
  pinMode(MINUS, INPUT);
}

void loop() {
  //플러스 버튼 처리
  currentButton[0]=debounce(lastButton[0],0);
  if(lastButton[0]==LOW && currentButton[0]==HIGH){
    number++;
    if(number>9){
      number=0;
    }
  }
  lastButton[0]=currentButton[0];
  //마이너스 버튼 처리
  currentButton[1]=debounce(lastButton[1],1);
  if(lastButton[1]==LOW && currentButton[1]==HIGH){
    number--;
    if(number<0){
      number=9;
    }
  }
  lastButton[1]=currentButton[1];
  //숫자 표시 메서드 호출
  displayDigit(number);
}

//숫자를 표시하기 위한 메서드
void displayDigit(int num){
  int pin=2;
  for(int i=0; i<7; i++){
    digitalWrite(pin+i, digits[num][i]);
  }
}
//디바운스 처리 메서드
//매개변수( last = 이전 눌림 상태, pm = 0:플러스 버튼, 1:마이너스 버튼)
boolean debounce(boolean last, int pm){
  if(pm==0){
    //플러스 버튼 눌림>>버튼 읽어옴
    boolean current=digitalRead(PLUS);
    if(last!=current){
      //이전 눌림상태와 현재 상태가 같지 않으면>> 눌렀다는 뜻
      delay(5);
      current=digitalRead(PLUS);
    }
    return current;
  }else{
    //마이너스 버튼 눌림>>버튼 읽어옴
    boolean current=digitalRead(MINUS);
    if(last!=current){
      //이전 눌림상태와 현재 상태가 같지 않으면>> 눌렀다는 뜻
      delay(5);
      current=digitalRead(MINUS);
    }
    return current;
  }
}
