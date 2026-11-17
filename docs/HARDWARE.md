# Hardware Notes

## Operating principle

The TMP36 outputs approximately 0.5 V at 0 °C and rises by 10 mV per °C. The firmware reads this signal through the Arduino Nano ADC and uses:

```text
temperature_c = (voltage - 0.5) × 100
```

The fan turns on at or above the threshold configured in the firmware (`25 °C` by default).

## Connections

| Device | Connection |
| --- | --- |
| TMP36 | `VOUT → A1`, `VCC → 5 V`, `GND → GND` |
| Relay driver | `D9 → base resistor → 2N2222 base`; emitter to GND; collector to relay coil |
| Relay coil | External 12 V supply with flyback diode across the coil |
| Fan | Powered through the relay contacts from the 12 V supply |
| Red LED | `D7` through a current-limiting resistor |
| Green LED | `D6` through a current-limiting resistor |
| OLED | Parallel interface as configured by the Proteus design and sketch |

## Safety

- Do not power a relay coil or fan directly from an Arduino output pin.
- Use a flyback diode across the relay coil.
- Keep the high-current fan supply separate from the Nano's 5 V logic rail, while sharing a suitable reference ground for the driver stage.
- Confirm component and relay-contact ratings before connecting a real load.
