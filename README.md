# RS485-SoundLevelMeter

## Details
-Microcontroller: LPC1769 CORTEX M3<br/>
-Libraries: Bare-Metal Code <br/>
-Implemented: RS485, RS232, ADC, debounce, lcd display etc.
<br/>

## Brief
The master device send a request one by one to every slave connected. Before a timeout happens, each slave have to answer with the last value reported, this value is represented in "dbA" wich represent the quantity of audio energy in the current environment. based in a "ponderation A curve", its means, a curve adapted with the way we perceive different mechanical waves in the audible spectrum.
<br/>At the end the master send all the information to a computer through a RS232 protocol, and with a c++ developed desktop program, we construct all the curves based in the information received from each slave

## Hardware schematic
![Screenshot from 2023-05-04 13-53-10](https://user-images.githubusercontent.com/117228370/236272676-06ed68a1-c775-46a9-aced-9a77222f243b.png)

## Screenshots
![DSC_0157](https://user-images.githubusercontent.com/117228370/230679732-be9da2af-40c8-44f6-8c16-d810022ac609.JPG)
