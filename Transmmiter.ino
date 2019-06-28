#define LED_TX 8
#define TIME_SLOT 50
#define END_WORD 126

void setup() {
  Serial.begin(9600);
  pinMode(LED_TX, OUTPUT);
}

void loop() {
  while(!Serial.available()) {}
  String message = Serial.readString();
  digitalWrite(LED_TX, HIGH);
  delay(TIME_SLOT);
  digitalWrite(LED_TX, LOW); //WAKE UP
  send(message);
}

void send(String message){
  message.concat(char(END_WORD));
  for(int i = 0; i < message.length(); i++){
    for(int j = 0; j < 8; j++){
      if(bitRead(message.charAt(i), j) == 1){
        digitalWrite(LED_TX, HIGH);
      }else{
        digitalWrite(LED_TX, LOW);
      }
      delay(TIME_SLOT);
    }
  }
}
