## Arduino Mega -> 6802 socket

```
PA0-7 A0-A7
PC0-7 A8-A15
PL0-7 D0-D7
PF0   R /W
PF1   E
PF2   VMA
PF3   /RESET
PF4   /HALT
PF5   MR
PF6   /IRQ
PF7   /NMI
```

6802pin | 6802 | atmel2560  | arduinopin |
|--:| -----|  -------: | -----: |
|9| A0 | PA0 | D22 |
|10| A1 | PA1 | D23 |
|11| A2 | PA2 | D24 |
|12| A3 | PA3 | D25 |
|13| A4 | PA4 | D26 |
|14| A5 | PA5 | D27 |
|15| A6 | PA6 | D28 |
|16| A7 | PA7 | D29 |
|17| A8 | PC0 | D37 |
|18| A9| PC1 | D36 |
|19| A10| PC2 | D35 |
|20| A11| PC3 | D34 |
|22| A12| PC4 | D33 |
|23| A13| PC5 | D32 |
|24| A14| PC6 | D31 |
|25| A15 | PC7 | D30 |
|33| D0 | PL0 | D49 |
|32| D1 | PL1 | D48 |
|31| D2 | PL2 | D47 |
|30| D3 | PL3 | D46 |
|29| D4 | PL4 | D45 |
|28| D5 | PL5 | D44 |
|27| D6 | PL6 | D43 |
|26| D7 | PL7 | D42 |
|34|R/W| PF0| A0|
|37|E |PF1|A1|
|5|VMA |PF2  |A2|
|40| /RESET | PF3   |A3|
|2| /HALT | PF4   |A4|
|3| MR | PF5  |A5|
|4| /IRQ | PF6  |A6|
|6| /NMI| PF7 |A7 |
|1|VSS
|8|VCC
|21|VSS
