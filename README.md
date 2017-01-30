# ESP-Lightify-Dimmer
A simple implementation of a dimmer switch on the esp8266 to control the *tuneable white OSRAM lightify bulbs*. This will control all lights conncted to the gateway throught a local connection. 

## Hardware
The middle of a potentiometer is conncted to A0 and the on-off switch to pin 4. I recycled the required switch/potentometer from a 230v dimmer module, which also has the advantage of this project fitting nicely to most wall plates.

## Indivdual Control
Individual bulbs can be controleld by changing the FF:FF:FF:FF:FF:FF string to the MAC Address of your bulb in reverse. (e.g MAC of bulb 12:34:56:78:9A:BC:DE then, 0xed, 0xcb, 0xa9, 0x87, 0x65, 0x43, 0x21). I'd like to extend this to control groups of bulbs however, the documentation of the local API does not currently include this.
