#include <SPI.h>

#define CS_PIN 5         // Chip select pin for the slave device
#define SPI_READ_CMD 0x80  // Read command for SPI (bit 7 = 1)

uint8_t data_array_8a[23]; // Array to store the response from register 0x8a
uint8_t data_array_e1[14]; // Array to store the response from register 0xe1

void setup() {
    Serial.begin(115200);   // Initialize serial communication
    pinMode(CS_PIN, OUTPUT); // Set chip select pin as output
    SPI.begin();           // Initialize SPI communication

    writeRegister(0xE0, 0xb6); //reset 


    writeRegister(0x73, 0b00000000);
    writeRegister(0x74, 0b00000001);

    writeRegister(0x73, 0b00010000);
    writeRegister(0x72, 0b00000001);
    writeRegister(0x74, 0b01010101);
    writeRegister(0x74, 0b00000001);


    writeRegister(0x64, 0b01011001);
    writeRegister(0x5A, 0b00000000);
    writeRegister(0x71, 0b00100000);


    // Example: Read from the register at address 0x8a
    //uint8_t data_array_8a[23]; // Array to store the response from register 0x8a
    //uint8_t data_array_e1[14]; // Array to store the response from register 0xe1
    
    readRegister(0x8a, data_array_8a, 23); // Read from register 0x8a and store response in data_array_8a
    readRegister(0xe1, data_array_e1, 14); // Read from register 0xe1 and store response in data_array_e1

    Serial.println("Data read from register 0x8a:");
    for (int i = 0; i < 23; i++) {
        Serial.print("0x");
        Serial.print(data_array_8a[i], HEX); // Print each element of the data array in hexadecimal format
        Serial.print(" ");
    }
    Serial.println();

    Serial.println("Data read from register 0xe1:");
    for (int i = 0; i < 14; i++) {
        Serial.print("0x");
        Serial.print(data_array_e1[i], HEX); // Print each element of the data array in hexadecimal format
        Serial.print(" ");
    }
    Serial.println();
}

void loop() {
    writeRegister(0xE0, 0xb6); //reset 


    writeRegister(0x73, 0b00000000);
    writeRegister(0x74, 0b00000001);

    writeRegister(0x73, 0b00010000);
    writeRegister(0x72, 0b00000001);
    writeRegister(0x74, 0b01010101);
    writeRegister(0x74, 0b00000001);


    writeRegister(0x64, 0b01011001);
    writeRegister(0x5A, 0b00000000);
    writeRegister(0x71, 0b00100000);


    readRegister(0x8a, data_array_8a, 23); // Read from register 0x8a and store response in data_array_8a
    readRegister(0xe1, data_array_e1, 14); // Read from register 0xe1 and store response in data_array_e1

    Serial.println("Data read from register 0x8a:");
    for (int i = 0; i < 23; i++) {
        Serial.print("0x");
        Serial.print(data_array_8a[i], HEX); // Print each element of the data array in hexadecimal format
        Serial.print(" ");
    }
    Serial.println();

    Serial.println("Data read from register 0xe1:");
    for (int i = 0; i < 14; i++) {
        Serial.print("0x");
        Serial.print(data_array_e1[i], HEX); // Print each element of the data array in hexadecimal format
        Serial.print(" ");
    }
    Serial.println();

    uint8_t data_01 = data_array_8a[0];
    uint8_t data_02 = data_array_8a[1];
    uint8_t data_03 = data_array_8a[2];

    uint8_t data_04 = data_array_e1[8];
    uint8_t data_05 = data_array_e1[9];


    uint16_t par_t1 = (uint16_t)((data_04 << 8) | data_05);
    uint16_t par_t2 = (uint16_t)((data_02 << 8) | data_01);
    uint16_t par_t3 = data_03;


    uint16_t data_06 = readRegister_01(0x22);
    uint16_t data_07 = readRegister_01(0x23);

    long temp_adc = data_06 << 8 | data_07; 

    long var1 = (((double)temp_adc / 16384.0) - ((double)par_t1 / 1024.0)) * (double)par_t2;
    long var2 = ((((double)temp_adc / 131072.0) - ((double)par_t1 / 8192.0)) *  (((double)temp_adc / 131072.0) - ((double)par_t1 / 8192.0))) * ((double)par_t3 * 16.0);

    long t_fine = var1 + var2;
    double temp_comp = t_fine / 5120.0 ;

    Serial.print("Compensated temperature value in degree celsius : ");
    Serial.println(temp_comp, DEC);

    Serial.println(" ");
    delay(1000);
}

uint16_t readRegister_01(uint16_t regAddress)
{
  digitalWrite(CS_PIN, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  uint16_t controlByte = regAddress | SPI_READ_CMD;
  SPI.transfer(controlByte);
  uint16_t data = SPI.transfer(0x00);
  SPI.endTransaction();
  digitalWrite(CS_PIN, HIGH);

  return data;
}

void writeRegister(uint8_t regAddress, uint8_t data) {
    digitalWrite(CS_PIN, LOW); // Select the slave device by bringing CSB low
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // Start SPI transaction

    uint8_t controlByte = regAddress & 0x7F; // Clear the MSB for write operation
    SPI.transfer(controlByte); // Send control byte (register address with write command)
    SPI.transfer(data);        // Send the data byte

    SPI.endTransaction();      // End SPI transaction
    digitalWrite(CS_PIN, HIGH); // Deselect the slave device by bringing CSB high

    Serial.print("Data written to register 0x");
    Serial.print(regAddress, HEX);
    Serial.print(": 0x");
    Serial.println(data, HEX);  // Print the written data in hexadecimal format
}

void readRegister(uint8_t regAddress, uint8_t *data, uint8_t length) {
    digitalWrite(CS_PIN, LOW); // Select the slave device by bringing CSB low
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // Start SPI transaction

    uint8_t controlByte = regAddress | SPI_READ_CMD; // Set the MSB for read operation
    SPI.transfer(controlByte); // Send control byte (register address with read command)
    for (int i = 0; i < length; i++) {
        data[i] = SPI.transfer(0x00); // Receive data from the register and store in data array
    }

    SPI.endTransaction();      // End SPI transaction
    digitalWrite(CS_PIN, HIGH); // Deselect the slave device by bringing CSB high
}
