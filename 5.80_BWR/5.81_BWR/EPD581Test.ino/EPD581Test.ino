/* 
 *  This example code is for PDi 5.8" BWR EPD on EXT2 board which is verified by Arduino M0 Pro/TI Launchpaad EK-TM4C123GXL.
 *  This Sketch uses 52112 bytes of program storage space. TI Launchpaad EK-TM4C123GXL(Maximum is 262144 bytes).
 *  And it sould be able to be compile on Arduino/Energia IDE supported Board.
 *  Like Arduino Due or Arduino Uno(Need a level shifter 5V -> 3V for EXT2 board)  
 *  For more information about PDi EPD and EXT2 board, please visit 
 *  http://www.pervasivedisplays.com/
 *  https://www.pervasivedisplays.com/product/epd-extension-kit-gen-2-ext2/
 */
#include <SPI.h>
#if defined(ENERGIA)
// Valid pins for LaunchPad on Energia
#define SCL_PIN 7  // EXT2 BOARD J5 pin 7
#define SDA_PIN 15  // EXT2 BOARD J5 pin 15
#define CS_PIN 19  // EXT2 BOARD J5 pin 19
#define DC_PIN 9   // EXT2 BOARD J5 pin 9
#define RESET_PIN 10 // EXT2 BOARD J5 pin 10
#define BUSY_PIN 8  // EXT2 BOARD J5 pin 8
#define PNLON_PIN 11 // EXT2 BOARD J5 pin 11
#define BS_PIN 17        //EXT2 BOARD J5 pin 17
//#define CSS_PIN 2     // EXT2 BOARD J5 pin 2 Slave CSB only required of 9.7"/12" with one 24pin FPC operation
//#define CSS_PIN 13     // EXT2 BOARD J5 pin 13 Slave CSB only required of 9.7/12" with 34pin FFC bridge board(2FPC design) operation

// SPI protocl setup
void sendIndexData( uint8_t index, const uint8_t *data, uint32_t len ) {
  SPI.begin (); 
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.setBitOrder(MSBFIRST);
  digitalWrite( DC_PIN, LOW );      //DC Low
  digitalWrite( CS_PIN, LOW );      //CS Low
  delayMicroseconds(500);
  SPI.transfer( index );
  delayMicroseconds(500);
  digitalWrite( CS_PIN, HIGH );     //CS High
  digitalWrite( DC_PIN, HIGH );     //DC High
  digitalWrite( CS_PIN, LOW );      //CS Low
  delayMicroseconds(500);
  for ( int i = 0; i < len; i++ ) SPI.transfer( data[ i ] );
  delayMicroseconds(500);
  digitalWrite( CS_PIN, HIGH );     //CS High
}

#else
// Valid pins for Arduino board, like M0 Pro
#define SCL_PIN 13   //EXT2 BOARD J5 pin 7
#define SDA_PIN 12   //EXT2 BOARD J5 pin 15
#define CS_PIN 11    //EXT2 BOARD J5 pin 19 Master CSB
#define DC_PIN 10    //EXT2 BOARD J5 pin 9
#define RESET_PIN 9  //EXT2 BOARD J5 pin 10
#define BUSY_PIN 8   //EXT2 BOARD J5 pin 8
#define PNLON_PIN 7  //EXT2 BOARD J5 pin 11
#define BS_PIN 4        //EXT2 BOARD J5 pin 17
//#define CSS_PIN 6    //EXT2 BOARD J5 pin 2 Slave CSB
//#define CSS_PIN 5     // EXT2 BOARD J5 pin 13 Slave CSB only required of 9.7/12" with 34pin FFC bridge board(2FPC design) operation

//EXT2 BOARD J5 pin 20 connected to GND
//EXT2 BOARD J5 pin 1 connected to 3V3

// Software SPI setup
void softwareSpi( uint8_t data ) {
  for ( int i = 0; i < 8; i++ ) {
    if ((( data >> (7 - i) ) & 0x01 ) == 1 ) digitalWrite( SDA_PIN, HIGH );
    else digitalWrite( SDA_PIN, LOW );
    digitalWrite( SCL_PIN, HIGH );
    digitalWrite( SCL_PIN, LOW );
  }
}

// Software SPI protocl setup
void sendIndexData( uint8_t index, const uint8_t *data, uint32_t len ) {
  digitalWrite( DC_PIN, LOW );      //DC Low
  digitalWrite( CS_PIN, LOW );      //CS Low
  softwareSpi( index );
  digitalWrite( CS_PIN, HIGH );     //CS High
  digitalWrite( DC_PIN, HIGH );     //DC High
  digitalWrite( CS_PIN, LOW );      //CS High
  for ( int i = 0; i < len; i++ ) softwareSpi( data[ i ] );
  digitalWrite( CS_PIN, HIGH );     //CS High
}
#endif

#include "Images/Image_581_frame_01.c"
#include "Images/Image_581_frame_02.c"
#include "Images/Image_581_frame_W.c"
#include "Images/Image_581_frame_B.c"
#define Frame1        (uint8_t *)&Image_581_frame_01
#define Frame2        (uint8_t *)&Image_581_frame_02
#define FrameW        (uint8_t *)&Image_581_frame_W
#define FrameB        (uint8_t *)&Image_581_frame_B

extern const uint8_t blackBuffer [];
extern const uint8_t redBuffer [];
extern const uint8_t WBuffer [];

//setup function runs once on startup
void setup() {            
  Serial.begin( 115200 ); //begin a Serial link
  pinMode( PNLON_PIN, OUTPUT);
  pinMode( SCL_PIN, OUTPUT );
  pinMode( SDA_PIN, OUTPUT );
  pinMode( CS_PIN, OUTPUT );
  pinMode( DC_PIN, OUTPUT );
  pinMode( RESET_PIN, OUTPUT );
  pinMode( BS_PIN, OUTPUT );  
  digitalWrite( PNLON_PIN, HIGH );    //PANEL_ON# = 1
  digitalWrite( BS_PIN, LOW );
  pinMode( BUSY_PIN, INPUT );         //All Pins 0
  delay( 200 );                          //Delay 200ms
  digitalWrite( RESET_PIN, HIGH );       //RES# = 1
  delay( 20 );                           //Delay 20ms
  digitalWrite( RESET_PIN, LOW );        //RES# = 0
  delay( 200 );                          //Delay 200ms
  digitalWrite( RESET_PIN, HIGH );       //RES# = 1
  delay( 50 );                           //Delay 50ms
  digitalWrite( CS_PIN, HIGH );       //CS# = 1

// Send image data
  uint8_t data1[] = { 0x00, 0x1f, 0x50, 0x00, 0x1f, 0x03 };         
  sendIndexData( 0x13, data1, 6 );    //DUW 0x16 ~ 0x1B of MTP
  uint8_t data2[] = { 0x00, 0x1f, 0x00, 0xc9 };         
  sendIndexData( 0x90, data2, 4 );    //DRFW 0x0C ~ 0x0F of MTP
  uint8_t data3[] = { 0x1f, 0x50, 0x14 };         
  sendIndexData( 0x12, data3, 3 );    //RAM_RW 0x13 ~ 0x15 of MTP
  sendIndexData( 0x10, Frame1, 23040 ); //First frame
  sendIndexData( 0x12, data3, 3 );    //RAM_RW
  sendIndexData( 0x11, Frame2 , 23040 );   //Second frame



//Initial COG
  uint8_t data4[] = { 0x7d};         
  sendIndexData( 0x05, data4, 1 );
  delay(200);
  uint8_t data5[] = { 0x00};         
  sendIndexData( 0x05, data5, 1 );
  delay( 10 );
  uint8_t data6[] = { 0x3f};         
  sendIndexData( 0xc2, data6, 1 );
  delay( 1 );
  uint8_t data7[] = { 0x00};         
  sendIndexData( 0xd8, data7, 1 );    //MS_SYNC 0x1D of MTP
  uint8_t data8[] = { 0x00};         
  sendIndexData( 0xd6, data8, 1 );    //BVSS 0x1E of MTP
  uint8_t data9[] = { 0x10};         
  sendIndexData( 0xa7, data9, 1 );
  delay( 100 );  
   sendIndexData( 0xa7, data5, 1 );
  delay( 100 );
  uint8_t data10[] = { 0x00, 0x01 };         
  sendIndexData( 0x03, data10, 2 );    //OSC 0x12 of MTP
    sendIndexData( 0x44, data5, 1 );    
  uint8_t data11[] = { 0x80 };         
  sendIndexData( 0x45, data11, 1 );
    sendIndexData( 0xa7, data9, 1 );
    delay( 100 );
    sendIndexData( 0xa7, data7, 1 );
    delay( 100 );
   uint8_t data12[] = { 0x06 };
   sendIndexData( 0x44, data12, 1 );
   uint8_t data13[] = { 0x82 };
   sendIndexData( 0x45, data13, 1 );    //Temperature 0x82@25C
    sendIndexData( 0xa7, data9, 1 );
    delay( 100 );
    sendIndexData( 0xa7, data7, 1 );
    delay( 100 );
   uint8_t data14[] = { 0x25 };
   sendIndexData( 0x60, data14, 1 );    //TCON 0x0B of MTP
   uint8_t data15[] = { 0x00 };
   sendIndexData( 0x61, data15, 1 );    //STV_DIR 0x1C of MTP
   uint8_t data16[] = { 0x00 };
   sendIndexData( 0x01, data16, 1 );    //DCTL 0x10 of MTP
   uint8_t data17[] = { 0x00 };
   sendIndexData( 0x02, data17, 1 );    //VCOM 0x11 of MTP

//DCDC soft-start
  uint8_t  Index51_data[]={0x50,0x01,0x0a,0x01};
  sendIndexData( 0x51, &Index51_data[0], 2 );
  uint8_t  Index09_data[]={0x1f,0x9f,0x7f,0xff};
///*
  for(int value=1;value<=4;value++){
      sendIndexData(0x09,&Index09_data[0],1);
      Index51_data[1]=value;
      sendIndexData(0x51,&Index51_data[0],2);
      sendIndexData(0x09,&Index09_data[1],1);
      delay(2);
    }
//*
  for(int value=1;value<=10;value++){
      sendIndexData(0x09,&Index09_data[0],1);
      Index51_data[3]=value;
      sendIndexData(0x51,&Index51_data[2],2);
      sendIndexData(0x09,&Index09_data[1],1);
      delay(2);
    }
  for(int value=3;value<=10;value++){
      sendIndexData(0x09,&Index09_data[2],1);
      Index51_data[3]=value;
      sendIndexData(0x51,&Index51_data[2],2);
      sendIndexData(0x09,&Index09_data[3],1);
      delay(2);
    }
  for(int value=9;value>=2;value--){
    sendIndexData(0x09,&Index09_data[2],1);
    Index51_data[2]=value;
    sendIndexData(0x51,&Index51_data[2],2);
    sendIndexData(0x09,&Index09_data[3],1);
    delay(2);
  }
  sendIndexData(0x09,&Index09_data[3],1);
  delay(10);
  Serial.println("3");

//Display Refresh Start 
  while( digitalRead( BUSY_PIN ) != HIGH );
  uint8_t data18[] = { 0x3c };
  sendIndexData( 0x15, data18, 1 );    //Display Refresh
  delay( 5 );
  
// DCDC off
  while( digitalRead( BUSY_PIN ) != HIGH );
  uint8_t data19[] = { 0x7f };
  sendIndexData( 0x09, data19, 1 );    
  uint8_t data20[] = { 0x7d };
  sendIndexData( 0x05, data20, 1 ); 
  sendIndexData( 0x09, data5, 1 );
  delay(200);       
  while( digitalRead( BUSY_PIN ) != HIGH );
  digitalWrite( DC_PIN, LOW );
  digitalWrite( CS_PIN, LOW );
  digitalWrite( SDA_PIN, LOW );
  digitalWrite( SCL_PIN, LOW );
  digitalWrite( RESET_PIN, LOW );
  Serial.println("4");
}

void loop() {
}

const uint8_t blackBuffer [] = { 
};
const uint8_t redBuffer [] = {
};
const uint8_t WBuffer [] = {
};
