#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 
#include <max6675.h>  // Biblioteca para o termopar

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x3F // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

#define ktcSO 8 //PINO DIGITAL (SO)
#define ktcCS 9 //PINO DIGITAL (CS)
#define ktcCLK 10 //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)

#define rele 11 
float temperatura, temperaturaLimite;

const int pot = A3; 


void setup() {

  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); // Serve para limpar a tela do display
  pinMode(pot, INPUT);
  pinMode(rele, OUTPUT);

  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS

}

void loop() {

   temperatura = ktc.readCelsius(); 
   temperaturaLimite = (map(analogRead(pot), 0, 1023, 0, 20))*10;

   Serial.print("TemperaturaLimite: "); //IMPRIME O TEXTO NO MONITOR SERIAL
   Serial.print(temperaturaLimite); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
   Serial.print("  Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
   Serial.print(temperatura); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
   Serial.println("°C"); //IMPRIME O TEXTO NO MONITOR SERIAL
   lcd.setCursor(0,0); // Coloca o cursor do display na coluna 0 e linha 0
   lcd.print("TEMP.:     "); 
   lcd.print(round(temperatura)); 
   lcd.print(" C ");
   lcd.setCursor(0,1); // Coloca o cursor do display na coluna 0 e linha 1
   lcd.print("TEMP.LIM.: ");
   lcd.print(round(temperaturaLimite)); 
   lcd.print(" C ");

   if(temperatura < temperaturaLimite){

     digitalWrite(rele, HIGH);
    
   }
   else{

     digitalWrite(rele,LOW);
     
   }
   
   delay(500);  // delay de 3 segundos com todas as mensagens na tela
   //lcd.clear(); // Limpa o display até o loop ser reiniciado 

}
