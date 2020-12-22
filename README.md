 ![image](https://github.com/Hardy-PDi/ePaper_PervasiveDisplays/blob/master/Pervasive%20Displays%20Line-up.png)
 
 * The example codes are for the iTC ([internal timing controller](https://www.pervasivedisplays.com/products/epd-product-selection/)) driver of EPDs made by Pervasive Displays (PDi) for 1.54"/2.13"/2.66"/2.71"/2.87"/3.7"/4.2"/4.37"/5.8"/7.4"/9.7"/12.2" with [EXT2 board](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-2-ext2/). The codes are worked with Arduino M0 Pro/TI Launchpad EK-TM4C123GXL.
 * And it should be able to run on [Arduino](https://www.arduino.cc/en/software) and [Energia](https://energia.nu/download/) IDE supported boards, such as Arduino Due, Arduino Uno(needs a level shifter 5V -> 3V for EXT2 board) and TI LaunchPads. Check the 3rd-party boards from [this link](https://github.com/arduino/arduino/wiki/unofficial-list-of-3rd-party-boards-support-urls).

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
//#define CSS_PIN 6    //EXT2 BOARD J5 pin 2 Slave CSB only required of 9.7"/12" with one 24pin FPC operation
//#define CSS_PIN 5    // EXT2 BOARD J5 pin 13 Slave CSB only required of 9.7/12" with 34pin FFC connection board(2 FPCs design) operation
                       //EXT2 BOARD J5 pin 20 connecte to GND
                       //EXT2 BOARD J5 pin 17 connecte to GND for 4 wire SPI
                       //EXT2 BOARD J5 pin 12 connecte to GND for stablize/off the discharge circuit
                       //EXT2 BOARD J5 pin 1 connecte to 3V3 
 ```
 
 * There is direct socket to stack on TI LaunchPads. The pin assignment can be found in each of sketch code.
 * For driving with eTC of EPD, please download the TI CCStudio source project from [EXT2 webpage on Pervasive Displays](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-2-ext2/).
 
 
 ### EXT2 Board DIP Switch(J7) configuration
 
| Driver type and EPD size | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| (eTC) 1.44/ 2.0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | - |
| (eTC) 1.9/ 2.60/ 2.71 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | - |
| (iTC) 2.15 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | - |
| (iTC) 1.54/ 2.13/ 2.66/ 2.71/ 2.87/ 3.7/ 4.2/ 4.37/ 5.8/ 7.4/ 9.7/ 12.0 | 0 | 1 | 0 | 1 | 0 | 1 | 0 | - |

 #  Technical Support
 *  For more information about PDi EPDs and EXT2 board, please visit [Pervasive Displays, inc. (龍亭新技股份有限公司)](https://www.pervasivedisplays.com/)
 *  [PDi Product Line up (iTC EPD)](https://www.pervasivedisplays.com/products/)
 *  [EPD Extension Kit Gen 2 (EXT2)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-2-ext2/)
 *  [24/7 Support Service](https://www.pervasivedisplays.com/technical-support/)
