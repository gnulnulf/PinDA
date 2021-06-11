Arduino Mega -> 6809 socket

```
PA0-7 A0-A7
PC0-7 A8-A15
PL0-7 D0-D7
PF0   R /W
PF1   E
PF2   Q
PF3   /RESET
PF4   /HALT
PF5   /FIRQ
PF6   /IRQ
PF7   /NMI
PK0 /DMA-BREQ
PK1 BS
PK2 BA
PK3 MRDY


PK7 I/O *not a 6809 line


```

6809pin | 6809 | atmel2560  | arduinopin |
|--:| -----|  -------: | -----: |
|8| A0 | PA0 | D22 |
|9| A1 | PA1 | D23 |
|10| A2 | PA2 | D24 |
|11| A3 | PA3 | D25 |
|12| A4 | PA4 | D26 |
|13| A5 | PA5 | D27 |
|14| A6 | PA6 | D28 |
|15| A7 | PA7 | D29 |
|16| A8 | PC0 | D37 |
|17| A9| PC1 | D36 |
|18| A10| PC2 | D35 |
|19| A11| PC3 | D34 |
|20| A12| PC4 | D33 |
|21| A13| PC5 | D32 |
|22| A14| PC6 | D31 |
|23| A15 | PC7 | D30 |
|31| D0 | PL0 | D49 |
|30| D1 | PL1 | D48 |
|29| D2 | PL2 | D47 |
|28| D3 | PL3 | D46 |
|27| D4 | PL4 | D45 |
|26| D5 | PL5 | D44 |
|25| D6 | PL6 | D43 |
|24| D7 | PL7 | D42 |
|32|R/W| PF0| A0|
|34|E |PF1|A1|
|35|Q |PF2  |A2|
|37| /RESET | PF3   |A3|
|40| /HALT | PF4   |A4|
|4| /FIRQ | PF5  |A5|
|3| /IRQ | PF6  |A6|
|2| /NMI| PF7 |A7 |
