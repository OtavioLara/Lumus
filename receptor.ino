#define LDR_RX A0
#define TIME_SLOT 50
#define TRASHOLD 400
#define END_WORD 126


void setup() {
  Serial.begin(9600);
  pinMode(LDR_RX, INPUT);
}

void loop() {
    int LDR_value = analogRead(LDR_RX);
//    Serial.println(LDR_value); //ativar para ajustar com o ambiente
    if(LDR_value > TRASHOLD){
        delay(TIME_SLOT+(TIME_SLOT/2)); //coleta no meio de cada bit, uma vez que o LDR tem tem uma decida amortizada
        receive();
    }
}

void receive(){
    String message = "";
    char x;
    int LDR_value;
    do{
        x = 0;
        for(int i = 0; i < 8; i++){
            LDR_value = analogRead(LDR_RX);
            if(LDR_value > TRASHOLD){
                bitSet(x, i);
            }
            delay(TIME_SLOT);
        }
        if(int(x) != END_WORD){
            message.concat(x);
        }
    }while(int(x) != END_WORD);
  Serial.println(message);
}
