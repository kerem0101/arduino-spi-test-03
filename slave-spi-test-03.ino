# include <SPI.h>
#include "RingBuf.h"


volatile unsigned char isMessageOPcode=1;
volatile unsigned char dummy;
volatile unsigned char data1;
volatile unsigned char data2;
volatile unsigned char data3;
volatile unsigned char setData1Flag=0;
volatile unsigned char isDataRecieved=0;
volatile unsigned char setData2Flag=0;
volatile unsigned char setData3Flag=0;
volatile unsigned char setData4Flag=0;
volatile unsigned char setData5Flag=0;
volatile unsigned char setData6Flag=0;
volatile unsigned char setData7Flag=0;
volatile unsigned char setData8Flag=0;
volatile uint32_t txfifo;
volatile unsigned char txfifo1;
volatile unsigned char txfifo2;
volatile unsigned char txfifo3;
volatile unsigned char txfifo4;
volatile unsigned char rx1_stts=1;
volatile int count = 1;

struct Event
{
  int index;
  unsigned long timestamp;
  unsigned char c;
};

// Declare as volatile, since modofied in ISR
volatile unsigned int index = 0;

// Create a RinBuf object designed to hold a 20 Event structs
RingBuf *buf = RingBuf_new(sizeof(struct Event), 20);

struct Event e;

void* result = RingBufPeek(buf, 20);


void setup()
 {
  Serial.begin (115200);   // set baud rate to 115200 for usart
  Serial.println("Hello I'm SPI UNO_SLAVE");
  pinMode(MISO, OUTPUT); // have to send on Master in so it set as output
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  SPI.attachInterrupt();     // turn on interrupt
}

void loop(){

 // Print the number of elements
//  Serial.print("There are: ");
//  Serial.print(buf->numElements(buf));
//  Serial.println(" element(s) in the ring buffer");

  // Check if empty
//  if (buf->isEmpty(buf))
//  {
//    Serial.println("The ring buffer is currently empty");
//  }
//  else if (buf->isFull(buf))
//  {
//    Serial.println("The ring buffer is currently full");
//  }
Serial.print("res:");
Serial.println((unsigned int)(result));

if((buf->isEmpty(buf) != 1)){

  if(isMessageOPcode){
//    isDataRecieved=0;
    if(e.c==56){
      setData1Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0x10){
      setData2Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0x14){
      setData3Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0xD4){
      setData4Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0x94){
      setData5Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0x84){
      setData6Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0x90){
      setData7Flag=1;
      isMessageOPcode=0;
    }
    else if(e.c==0x0C){
      setData8Flag=1;
      isMessageOPcode=0;
    }
  }
  else{
//    isDataRecieved=0;
    if(setData1Flag==1){
      data1=e.c;
      isMessageOPcode=1;
      setData1Flag=0;
    }
    else if(setData2Flag==1){
      data2=e.c;
      isMessageOPcode=1;
      setData2Flag=0;
    }
    else if(setData3Flag==1){
      data3=e.c;
      isMessageOPcode=1;
      setData3Flag=0;
    }
    else if(setData4Flag==1){
      dummy=e.c;
      isMessageOPcode=1;
      setData4Flag=0;
      SPDR = data1;
    }
    else if(setData5Flag==1){
      dummy=e.c;
      isMessageOPcode=1;
      setData5Flag=0;
      SPDR = data2;
    }
    else if(setData6Flag==1){
      dummy=e.c;
      isMessageOPcode=1;
      setData6Flag=0;
      SPDR = data3;
    }
    else if(setData7Flag==1){
      dummy=e.c;
      isMessageOPcode=1;
      setData7Flag=0;
      SPDR = rx1_stts;
    }
    else if(setData8Flag==1){
      if(count==1){
        txfifo1=(e.c);
        count++;
      }else if(count==2){
        txfifo2=(e.c);
        count++;
      }else if(count==3){
        txfifo3=(e.c);
        count++;
      }else if(count==4){
        txfifo4=(e.c);
        isMessageOPcode=1;
        setData8Flag=0;
        count=1;
      }
      
    }
  }
  
}
  
 

  // If any message sent through serial monitor, dump buffer
  if ((buf->isFull(buf)) == 1)
  {
    // Print contents of buffer
    //print_buf_contents();

    //empty serial buffer
    while (Serial.read() > 0);
  }

  //Serial.println();

  //delay(200);

  Serial.print("data1: ");
  Serial.println(data1);
  Serial.print("data2: ");
  Serial.println(data2);
  Serial.print("data3: ");
  Serial.println(data3);
  Serial.print("dummy: ");
  Serial.println(dummy);
  Serial.print("txfifo: ");
  Serial.println(txfifo1);
  Serial.println(txfifo2);
  Serial.println(txfifo3);
  Serial.println(txfifo4);
  

//  delay(200);
}

// Interrupt function
ISR (SPI_STC_vect) 
{
//  isDataRecieved=1;
  e.index = index++;
  e.c=SPDR;
  e.timestamp = millis();
  // Add it to the buffer
  buf->add(buf, &e);
// unsigned char c = SPDR;        // read byte from SPI Data Register
//
//  if(isMessageOPcode){
//    if(c==0x38){
//      setData1Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0x10){
//      setData2Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0x14){
//      setData3Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0xD4){
//      setData4Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0x94){
//      setData5Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0x84){
//      setData6Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0x90){
//      setData7Flag=1;
//      isMessageOPcode=0;
//    }
//    else if(c==0x0C){
//      setData8Flag=1;
//      isMessageOPcode=0;
//    }
//  }
//  else{
//    if(setData1Flag==1){
//      data1=c;
//      isMessageOPcode=1;
//      setData1Flag=0;
//    }
//    else if(setData2Flag==1){
//      data2=c;
//      isMessageOPcode=1;
//      setData2Flag=0;
//    }
//    else if(setData3Flag==1){
//      data3=c;
//      isMessageOPcode=1;
//      setData3Flag=0;
//    }
//    else if(setData4Flag==1){
//      dummy=c;
//      isMessageOPcode=1;
//      setData4Flag=0;
//      SPDR = data1;
//    }
//    else if(setData5Flag==1){
//      dummy=c;
//      isMessageOPcode=1;
//      setData5Flag=0;
//      SPDR = data2;
//    }
//    else if(setData6Flag==1){
//      dummy=c;
//      isMessageOPcode=1;
//      setData6Flag=0;
//      SPDR = data3;
//    }
//    else if(setData7Flag==1){
//      dummy=c;
//      isMessageOPcode=1;
//      setData7Flag=0;
//      SPDR = rx1_stts;
//    }
//    else if(setData8Flag==1){
//      if(count==1){
//        txfifo1=(c);
//        count++;
//      }else if(count==2){
//        txfifo2=(c);
//        count++;
//      }else if(count==3){
//        txfifo3=(c);
//        count++;
//      }else if(count==4){
//        txfifo4=(c);
//        isMessageOPcode=1;
//        setData8Flag=0;
//        count=1;
//      }
//      
//    }
//  }
}


void print_buf_contents()
{
  struct Event e;

  Serial.println("\n______Dumping contents of ring buffer_______");

  // Keep looping until pull() returns NULL
  while (buf->pull(buf, &e))
  {
    //
    Serial.print("Event index: ");
    Serial.println(e.index);

    Serial.print("Event c: ");
    Serial.println(e.c);

    Serial.print("Timestamp (ms): ");
    Serial.println(e.timestamp);

    Serial.println();
  }

  Serial.println("______Done dumping contents_______");

}
