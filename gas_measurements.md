## Gas measurement summary for BME688

- **Configure Heater Parameters**: Set initial current and target resistance for the heater.
- **Configure Heater-On Time**: Set the duration for which the heater remains on.
- **Select Heater Profile**: Choose the heater profile for the sensor.
- **Start Gas Measurements**: Initiate gas conversions.
- **Heating and Measurement**: Heat the gas sensor hot plate and measure the resistance of the gas-sensitive layer.
- **Calculate Gas Resistance**: Convert ADC values into compensated gas resistance.

- **Heater Current (idac_heat_x)**:
  - Registers: idac_heat_x<7:0>
  - Address Range: 0x50 to 0x59 for steps 0 to 9.
  - Purpose: Sets the initial current for the heater to speed up reaching the target temperature.

- **Target Heater Resistance (res_heat_x)**:
  - Registers: res_heat_x<7:0>
  - Address Range: 0x5A to 0x63 for steps 0 to 9.
  - Purpose: Sets the target heater resistance corresponding to the desired heater temperature.

