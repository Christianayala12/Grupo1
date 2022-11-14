//Display 7 Segmentos Catodo Común
int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
//Delcaración de Los Pines del Display
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;
byte inc=9;    //Pulsador Incremento 
byte dec=10;   //Pulsador Decremento 
int contador=0;
int IRF = 11;

float temperatura;
void puerto(int bits,int ini,int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i,bitRead(bits,i-ini));
  }
}
void setup() {
  //Configura los 8 Pines digitales como SALIDAS
  for(int i=a;i<=g;i++){
    pinMode(i,OUTPUT);
  }
  pinMode(inc,INPUT);
  pinMode(dec,INPUT);
  Serial.begin(9600);          // configuración del puerto serie a 9600 baudios
  pinMode(IRF, OUTPUT);
}

void loop() {
  if(digitalRead(inc)){
    delay(100);
    while(digitalRead(inc)); //Anti-Rebote
    delay(100);
    if(contador>=5){
      contador=0;
      delay(20);      
      }
    else{
      contador++;
      Serial.println(contador);
    }
  }
  if(digitalRead(dec)){
    delay(100);
    while(digitalRead(dec)); //Anti-Rebote
    delay(100);
    if(contador<=0){
      contador=5;
      delay(20);      
      }
    else{
      contador--;
       Serial.println(contador);
    }
  }
  analogWrite(IRF, contador*51);
  puerto(display7c[contador],a,g);
  int sensor= analogRead(A0);
  temperatura = ((sensor*5000.0)/1023)/10;
  Serial.println(temperatura,1);
  delay(1000);
}
