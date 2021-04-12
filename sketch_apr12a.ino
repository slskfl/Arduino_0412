#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //핀번호, 타입
float h,t,f; //습도, 섭씨온도, 화씨온도
float hic, hif; //보정된 섭씨온도, 화씨 온도
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); //온도습도 센서 초기화 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  h=dht.readHumidity(); //습도를 측정
  t=dht.readTemperature(); //섭씨 온도를 측정
  f=dht.readTemperature(true); //화씨 온도를 측정(true)필요
  if(isnan(h) || isnan(t) || isnan(f)){
    Serial.println("온도 습도 센서 작동 오류");
    return;
  }
  hic=dht.computeHeatIndex(t,h,false); //보정된 섭씨 온도 값
  hif=dht.computeHeatIndex(f,h); //보정된 화씨 온도 값
  Serial.println(String("현재 습도 : ") +h);
  Serial.println(String("현재 섭씨 온도 :") +t);
  Serial.println(String("현재 화씨 온도 :")+f);
  Serial.println(String("현재 보정된 섭씨 온도 :")+hic);
  Serial.println(String("현재 보정된 화씨 온도 :")+hif);
}
