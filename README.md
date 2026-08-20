# Minstastic: Altoids Tin Meshtastic Node
**Mintastic is a low-cost LoRa meshtastic node built as an**
[**Altoids tin gadget**](https://www.instructables.com/10-Projects-for-Altoids-Tins "Other examples")**.**

![Mintastic PCB Renger image](Images\pcb_render.png)

## Abstract
**Note: this project is still a work in progress. I plan on updating and finishing this project by early September.**

This project presents the design and implementation of a compact, low-cost Meshtastic mesh networking node packaged in an everyday Altoids tin enclosure. Motivated by the need for a fully standalone node on a campus mesh network, the device integrates a custom PCB featuring an ESP32 microcontroller, SX1262 LoRa transceiver operating at 915 MHz, GPS module, navigation buttons, and LCD display for a custom user interface. Power is supplied by a 3.7 V 1500 mAh LiPo battery with on-board charging circuitry, while an external whip antenna supports long-range communication. <!-- The completed node achieves approximately 6 miles of unobstructed range (mountain-to-mountain) with an average current draw of 0.150 mA. --> The design demonstrates practical RF system integration, efficient power management, and mechanical packaging constraints, resulting in a portable, inexpensive, and self-contained mesh node suitable for campus and outdoor applications.

## 1. Requirements
|  | Requirement |
|--------------------|-------------|
| Power | 3.7V 1500mAh LiPo battery with JST connector, approx 1x2 inches. |
| Size | <58mm width. I've gone with 55x75mm to leave room for battery. |
| Bluetooth | Connects via bluetooth to mobile phone with Meshtastic app |
| GPS | Built-in GPS capability for off-grid use |
| Cost | As cheap as possible for me to prototype, <$50/unit "build it yourself" cost |
| Personal Learning Goals | Learn RF and digital PCB design, and build first highly documented project. |

**Preferred Qualities:**
|  | Goal |
|--------------------|-------------|
| Standalone | Usable without external bluetooth device through built-in user interface |
| Range | ~ 6 mile unobscured |
| Battery Life | >10 hours / <150mA average consumption |


## 2. Design
### Power
The first design concern is being able to both power the board using the LiPo battery, and recharge it. Luckily, most all ESP32, LoRa, and GPS chips support 3.3V VCC, so I only need one regulator chip. I've decided on the **LM2575S-3.3** switching regulator for its efficiency and availability.

For charging and off-board power, I've chosen the **TP4056**, a common charging chip which is powered by 5V via USB-C and outputs 3.7V. This will connect to VBAT which connects to the battery as well as VIN on the regulator.

The circuits surrounding these respective components have been copied mostly from their datasheets.

### MCU
Mintastic will use an ESP32 due to their native bluetooth features. Most could handle this job, I have chosen the **ESP32 S3 N16R8**. Although it costs slightly more than other modules, its large flash memory gives me a lot of room to add features in the future without needing to upgrade hardware.

**Full MCU Pinout**
| ESP32 Pin | Connection | Pulled high/low/NA |
| - | - | - |
| EN | Reset Button | High |
| IO0 | Boot Button | High |
| IO1 | Battery Divider | |
| IO2 | User Button | High |
| IO3 | User Button | High |
| IO4 | GPS Reset | High |
| IO5 | GPS On/Off | High |
| IO6 | User Button | High |
| IO7 | User Button | High |
| IO8 | LoRa SCK | |
| IO9 | LoRa MISO | |
| IO10 | LoRa MOSI | |
| IO11 | LCD Reset | |
| IO12 | LCD SDA | |
| IO13 | LCD SCL | |
| IO14 | LCD CS | |
| IO15 | LCD DC | |
| IO16 | User Button | High |
| IO17 | GPS Tx | |
| IO18 | GPS Rx | |
| USB+ | USB D+ | |
| USB- | USB D- | |
| IO38 | LoRa RF Switch | |
| IO39 | LoRa DIO1 | |
| IO40 | LoRa Busy | |
| IO41 | LoRa NSS | |
| IO42 | LoRa Reset | |
| IO46 | | unconnected/low |
| IO48 | Red LED | |

Note: The periferal connections were decided (mostly) arbitrarily or based on firmware defaults.

All other pins are unconnected.

### Periferals
#### I. LoRa Module
The Semtech SX1262 is the LoRa IC used almost universally for Mesh nodes. For simplicity, I will use the [**Wio-SX1262**](https://wiki.seeedstudio.com/wio_sx1262/) module by Seeed Studio. This compact module features an onboard filter, switch, and IPEX connector, making it ideal for this. (I will be using a separate SMA connector rather than the IPEX for LoRa.)

#### II. GPS Module
I do not want to be reliant on a mobile phone's internet connection for location information, so I plan to use an on-board GPS chip. I've selected the cheap chinese [**ATGM336H**](https://www.alldatasheet.com/html-pdf/2250270/ZHONGKE/ATGM336H/2443/7/ATGM336H.html) module to support GPS for this module.

#### III. 2.4 Inch TFT LCD Display
I've selected a generic ST7789 display for this with a built-in controller. I will simply connect it through a 1x8 pin socket.

### PCB
To fit design constraints, I've set the width of the PCB to be just under the inner lip diameter of the Altoids tin, 55mm, and its height to be ~ 40 mm less than the length of the tin, 75mm, to leave room for the battery. I've also rounded 2 of the board's edges to match the curvature of the tin.

To lower costs, I've decided to use a 2-layer board over a simpler 4-layer design. For this reason, I will need to separate UHF from digital signals so that they can have a solid ground plane beneath each trace.

The dielectric between the layers is far too thick for impedance controlled microstrip traces, so I will use the GCPW (Grounded Coplanar Waveguide) technique.

**Impedance control**

To calculate impedance values, I am using an [online calculator](https://impedancecalculator.com/). 
UHF signal traces will need to be impedance controlled to 50 Ohms. Using GCPW, this requires a 1 mm trace and 0.2 mm gap. This gets us down to 55.7 Ohms, resulting in 0.556 dB/inch loss at 900 MHz. Close enough for this ~0.1 inch line.

I've determined the microstrip traces to have a reasonable impedance for digital signals.

### UI Design


## 3. Manufacturing
Prototype fabricated through JLCPCB. All components were ordered through AliExpress. I assembled the PCB myself using SMT tools at UD.

**Prototype cost breakdown:**
| Item | Cost ($) | Note |
| ---- | ---- | ---- |
| PCB | 4.95 | 24.75/5, includes shipping |
| [Capacitors](https://www.aliexpress.com/item/3256810330121955.html?spm=a2g0o.order_list.order_list_main.10.21ef1802iwNV2p) | 0.20 | 3.19/320 * 20 |
| [Resistors](https://www.aliexpress.com/item/3256810577510361.html?spm=a2g0o.order_list.order_list_main.32.21ef1802iwNV2p) | 0.07 | 2.37/660 * 19 |
| [Inductors](https://www.aliexpress.com/item/3256808828460642.html?spm=a2g0o.order_list.order_list_main.78.21ef1802iwNV2p) | 0.03 | 4.35/300 * 0.029 |
| [LEDs](https://www.aliexpress.com/item/2251800651687366.html?spm=a2g0o.order_list.order_list_main.114.21ef1802iwNV2p) | 0.05 | 1.51/100 * 3 |
| [Resettable Fuses](https://www.aliexpress.com/item/3256805049615392.html?spm=a2g0o.order_list.order_list_main.44.21ef1802iwNV2p) | 0.33 | 3.32/20 * 2 |
| [SS14 Diode](https://www.aliexpress.com/item/3256806391314857.html?spm=a2g0o.order_list.order_list_main.26.21ef1802iwNV2p) | 0.03 | 1.47/50 |
| [IN5819 Diode](https://www.aliexpress.com/item/3256801365779334.html?spm=a2g0o.order_list.order_list_main.425.21ef1802iwNV2p) | 0.02 | 0.91/50
| [USB-C Connector](https://www.aliexpress.com/item/3256804454151365.html?spm=a2g0o.order_list.order_list_main.435.21ef1802iwNV2p) | 0.22 | 2.19/10 |
| [Battery JST connector](https://www.aliexpress.com/item/3256807568732637.html?spm=a2g0o.order_list.order_list_main.102.21ef1802iwNV2p) | 0.09 | 1.77/20 |
| [LiPo Battery](https://www.aliexpress.com/item/3256808031709894.html?spm=a2g0o.order_list.order_list_main.84.21ef1802iwNV2p) | 6.73 | |
| [TP4056](https://www.aliexpress.com/item/2251832528051428.html?spm=a2g0o.order_list.order_list_main.96.21ef1802iwNV2p) | 0.10 | 0.94/10 |
| [LM2575S-3.3](https://www.aliexpress.com/item/3256806770889152.html?spm=a2g0o.order_list.order_list_main.50.21ef1802iwNV2p) | 0.28 | 5.54/20 |
| [ESP32-S3-N16R8](https://www.aliexpress.com/item/3256806005505510.html?spm=a2g0o.order_list.order_list_main.90.21ef1802iwNV2p) | 4.79 | |
| [WIO-SX1262](https://www.aliexpress.com/item/3256808235584580.html?spm=a2g0o.order_list.order_list_main.451.21ef1802iwNV2p) | 4.97 | |
| [ATGM336H](https://www.aliexpress.com/item/3256804828510067.html?spm=a2g0o.order_list.order_list_main.66.21ef1802iwNV2p) | 3.04 | |
| [IPEX connector](https://www.aliexpress.com/item/3256801185019750.html?spm=a2g0o.order_list.order_list_main.108.21ef1802iwNV2p) | 0.15 | 1.50/10 |
| [SMA connector](https://www.aliexpress.com/item/3256807238600626.html?spm=a2g0o.order_list.order_list_main.475.21ef1802iwNV2p) | 0.77 | 3.86/5  |
| [SMA Cable](https://www.aliexpress.com/item/3256803838912502.html?spm=a2g0o.order_list.order_list_main.38.21ef1802iwNV2p) | 2.34 | |
| [2.4in TFT LCD Display](https://www.aliexpress.com/item/3256811879116899.html?spm=a2g0o.order_list.order_list_main.125.21ef1802iwNV2p) | 5.57 | |
| [8-pin socket](https://www.aliexpress.com/item/3256804056304729.html?spm=a2g0o.order_list.order_list_main.72.21ef1802iwNV2p) | 0.19 | 1.94/10 |
| [2-pin headers](https://www.aliexpress.com/item/3256807300285852.html?spm=a2g0o.order_list.order_list_main.140.21ef1802iwNV2p) | 0.05 | 1.63/180 * 5 |
| [Push Buttons](https://www.aliexpress.com/item/3256808033339761.html?spm=a2g0o.order_list.order_list_main.510.21ef1802iwNV2p) | 0.05 | 0.99/100 * 5 |
| [UHF Whip Antenna](https://www.aliexpress.us/item/3256804421300249.html) | 4.60 | |
| [GPS Antenna](https://www.aliexpress.com/item/2251832500323977.html?spm=a2g0o.order_list.order_list_main.20.21ef1802iwNV2p) | 1.59 | |
| Altoids tin | 0.00 | Everyone has one somewhere
| Total | 41.20 | |

Note on above calculations: This is a rough estimate of how much each unit costs at a small scale to self-assemble. Many components, such as resistors, I had to buy in kits. In these cases, I took the cost of the kit, divided it by the total number of pieces included, and multiplied by the number of that component per unit. $40 is about the lowest you will find a mesh node for on Amazon, so this is a reasonable cost. It goes without saying that I would use PCBA for production at scale, but for this project it would have cost ~$193.

## 4. Measurement Setup
...

## 5. Results
| Spec | Target | Simulated | Measured |
| ---- | ------ | --------- | -------- |
|
[Plots]

## 6. Discussion & Lessons Learned
...

## 7. Conclusion
...

## References
I was inspired by Martin Held's [Altoids tin CW radio](https://www.youtube.com/watch?v=zBLEqTVUgEY&list=WL&index=7&pp=iAQBsAgC) project.