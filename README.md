 ![image](https://github.com/Hardy-PDi/ePaper_PervasiveDisplays/blob/master/e-paper-displays-low-temperature-PDI033-768x487.png)
 
 * The example code is for PDi iTC EPD(1.54"/2.13"/2.66"/2.71"/2.87"/3.7"/4.2"/4.37"/5.8"/7.4"/9.7"/12") on EXT2 board, it's verified by Arduino M0 Pro/TI Launchpaad EK-TM4C123GXL.
 * And it sould be able to run on Arduino IDE supported Board, such as Arduino Due or Arduino Uno(Need a level shifter 5V -> 3V for EXT2 board)
 *  https://github.com/arduino/arduino/wiki/unofficial-list-of-3rd-party-boards-support-urls

 #  Hardware Connection
 ![image](https://github.com/Hardy-PDi/ePaper_PervasiveDisplays/blob/master/arduino_w_EXT2.jpg)
 * In case of you only have 5V host controller, the lever shifter is required for these I/Os on EXT2 board
 ![image](https://github.com/Hardy-PDi/ePaper_PervasiveDisplays/blob/master/3_5V_LevelShifter.png)
  
 ### Arduino Pin assignment for EXT2 Board
 ```bash
#define SCL_PIN 13   //EXT2 BOARD J5 pin 7
#define SDA_PIN 12   //EXT2 BOARD J5 pin 15
#define CS_PIN 11    //EXT2 BOARD J5 pin 19 Master CSB
#define DC_PIN 10    //EXT2 BOARD J5 pin 9
#define RESET_PIN 9  //EXT2 BOARD J5 pin 10
#define BUSY_PIN 8   //EXT2 BOARD J5 pin 8
#define PNLON_PIN 7  //EXT2 BOARD J5 pin 11
#define BS_PIN 4     // EXT2 Baord J5 pin 17
#define CSS_PIN 6    //EXT2 BOARD J5 pin 2 Slave CSB only required of 9.7"/12" with one 24pin FPC operation
//#define CSS_PIN 5     // EXT2 BOARD J5 pin 13 Slave CSB only required of 9.7/12" with 34pin FFC bridge board(2FPC design) operation
                      //EXT2 BOARD J5 pin 20 connecte to GND
                      //EXT2 BOARD J5 pin 17 connecte to GND for 4 wire SPI
                      //EXT2 BOARD J5 pin 12 connecte to GND for stablize/off the discharge circuit
                      //EXT2 BOARD J5 pin 1 connecte to 3V3 
 ```
 
 ### EXT2 Board DIP Switch(J7) configuration
 
| Driver type and EPD size | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| (eTC) 1.44/ 2.0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | - |
| (eTC) 1.9/ 2.60/ 2.71 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | - |
| (iTC) 2.15 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | - |
| (iTC) 1.54/ 2.13/ 2.66/ 2.71/ 2.87/ 2.9 hr/ 3.7/ 4.2/ 4.37/ 5.65/ 5.8/ 7.4/ 9.7/ 12.0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 | - |

 #  Support
 *  For more information about PDi EPD and EXT2 board, please visit [PERVASIVE DISPLAYS, INC. (龍亭新技股份有限公司)](http://www.pervasivedisplays.com/)
 *  [PDi Product Line up(iTC EPD)](https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc)
 *  [EPD Extension Kit Gen 2 (EXT2)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-2-ext2/)
 *  [24/7 Service](https://www.pervasivedisplays.com/technical-support/)
