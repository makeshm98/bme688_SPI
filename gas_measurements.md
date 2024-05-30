## Gas measurement summary for BME688

- **Configure Heater Parameters**: Set initial current and target resistance for the heater.
- **Configure Heater-On Time**: Set the duration for which the heater remains on.
- **Select Heater Profile**: Choose the heater profile for the sensor.
- **Start Gas Measurements**: Initiate gas conversions.
- **Heating and Measurement**: Heat the gas sensor hot plate and measure the resistance of the gas-sensitive layer.
- **Calculate Gas Resistance**: Convert ADC values into compensated gas resistance.

1.  **Heater Current (idac_heat_x)**:
  - Registers: idac_heat_x<7:0>
  - Address Range: 0x50 to 0x59 for steps 0 to 9.
  - Purpose: Sets the initial current for the heater to speed up reaching the target temperature.

2.  **Target Heater Resistance (res_heat_x)**:
  - Registers: res_heat_x<7:0>
  - Address Range: 0x5A to 0x63 for steps 0 to 9.
  - Purpose: Sets the target heater resistance corresponding to the desired heater temperature.

3. In the "Configure Heater-On Time" step, the following register is used:

  1. **Gas Sensor Heater-On Time (`gas_wait_x`)**:
   - Registers: `gas_wait_x<7:0>`
   - Address Range: 0x64 to 0x6D for steps 0 to 9.
   - Purpose: Sets the duration for which the heater remains on.

   This register allows you to specify the duration for which the gas sensor heater remains activated during each heating cycle.

4. In the "Select Heater Profile" step, the following register is used:

  1. **Heater Profile Selection (`nb_conv`)**:
   - Register: `ctrl_gas_1`
   - Address: 0x71
   - Bit Position: `nb_conv<3:0>`
   - Purpose: Sets the heater profile for the sensor, indicating the index of the heater step to be used in forced mode or the sequence of up to 10 heater steps in parallel mode.

   This register controls which heater profile the sensor will use for gas sensing operations.

5. In the "Start Gas Measurements" step, the following register is used:

  1. **Start Gas Measurement (`run_gas`)**:
   - Register: `ctrl_gas_1`
   - Address: 0x71
   - Bit Position: `run_gas<5>`
   - Purpose: Initiates gas conversions in appropriate modes when set to `1`.

   Setting this register to `1` triggers the start of gas measurements according to the configured settings.

6. In the "Heating and Measurement" step, there are no specific registers mentioned for this process in the provided information. However, the heating and measurement process likely involves the following steps:

  1. **Heating the Gas Sensor Hot Plate**:
   - This process likely involves controlling the heater parameters set in the previous steps, such as the heater current and target resistance, to raise the hot plate temperature to the desired level.

  2. **Measuring the Resistance of the Gas-Sensitive Layer**:
   - After reaching the target temperature, the resistance of the gas-sensitive layer is typically measured using internal circuits or ADC (Analog-to-Digital Converter) readings.

  The specific registers involved in these processes may vary depending on the implementation details of the sensor and are not explicitly mentioned in the provided information. Typically, the sensor datasheet would provide details on the internal registers and procedures for these operations.

7. In the "Calculate Gas Resistance" step, the following registers are involved in reading the gas ADC value and gas ADC range:

  1. **Gas ADC Value (`gas_adc`)**:
   - Registers: Field 0 - 0x2D<7:6> / 0x2C, Field 1 - 0x3E<7:6> / 0x3D, Field 2 - 0x4F<7:6> / 0x4E
   - Purpose: Stores the raw gas resistance output data obtained from the Analog-to-Digital Converter (ADC).

  2. **Gas ADC Range (`gas_range`)**:
   - Registers: Field 0 - 0x2D<3:0>, Field 1 - 0x3E<3:0>, Field 2 - 0x4F<3:0>
   - Purpose: Stores the ADC range of the measured gas resistance.

  These registers are essential for reading the raw gas ADC value and its corresponding range, which are then used to calculate the compensated gas resistance.
