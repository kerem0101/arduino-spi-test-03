# include <SPI.h>

#define OP_R_RX1_STTS 0x90
#define OP_W_TX_FIFO 0x0C

unsigned char data1;
unsigned char data2;
unsigned char data3;
unsigned char data4;

void setup() 
{
Serial.begin(115200); // set baud rate to 115200 for usart
SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV8); //divide the clock by 8
Serial.println("Hello I'm SPI Mega_Master");
} 

void loop (void)
{
 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(0x38);
 SPI.transfer(55);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(0x10);
 SPI.transfer(122);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(0x14);
 SPI.transfer(150);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(0xD4);
 SPI.transfer(18);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
 digitalWrite(SS, LOW);
 data1=SPI.transfer(0);
 digitalWrite(SS, HIGH);
 Serial.println(data1);
 
 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(0x94);
 SPI.transfer(17);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
 digitalWrite(SS, LOW);
 data2=SPI.transfer(0);
 digitalWrite(SS, HIGH);
 Serial.println(data2);
 
 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(0x84);
 SPI.transfer(11);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
 digitalWrite(SS, LOW);
 data3=SPI.transfer(0);
 digitalWrite(SS, HIGH);
 Serial.println(data3);

 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(OP_R_RX1_STTS);
 SPI.transfer(32);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);

 digitalWrite(SS, LOW);
 data4=SPI.transfer(0);
 digitalWrite(SS, HIGH);
 Serial.println(data4);

 digitalWrite(SS, LOW); // enable Slave Select
 SPI.transfer(OP_W_TX_FIFO);
 SPI.transfer(15);
 delay(2);
 SPI.transfer(7);
 delay(2);
 SPI.transfer(3);
 delay(2);
 SPI.transfer(1);
 digitalWrite(SS, HIGH); // disable Slave Select
 delay(2000);
 
}
