#include <SPI.h>

#define CS_PIN 5
#define SPI_READ_CMD 0x80

void printRegisterBits(uint8_t regAddress, uint8_t regValue);

void setup() {
  Serial.begin(115200);
  pinMode(CS_PIN, OUTPUT);
  SPI.begin();

  writeRegister(0x72, 0b001);
  writeRegister(0x74, 0b01010101);  


  writeRegister(0x64, 0x59);
  writeRegister(0x5A, 0x00);
  writeRegister(0x71, 0b0000);
  writeRegister(0x71, 0b00000100);

/*
  uint16_t data_01 = readRegister(0x72);
  uint16_t data_02 = readRegister(0x74);
  uint16_t data_03 = readRegister(0x20);
  uint16_t data_04 = readRegister(0x1F);
  uint16_t data_05 = readRegister(0x22);
  uint16_t data_06 = readRegister(0x23);
  uint16_t data_07 = readRegister(0x25);
  //uint16_t data_08 = readRegister(0x26);


  Serial.print("Data from register 0x72: 0x");
  Serial.println(data_01, HEX);

  Serial.print("Data from register 0x74: 0x");
  Serial.println(data_02, HEX);

  Serial.print("Data from register pressure msb 1F: 0x");
  Serial.println(data_04, HEX);

  Serial.print("Data from register pressure lsb 20: 0x");
  Serial.println(data_03, HEX);

  Serial.print("Data from register temp msb 22: 0x");
  Serial.println(data_05, HEX);

  Serial.print("Data from register temp lsb 23: 0x");
  Serial.println(data_06, HEX);

  Serial.print("Data from register humidity msb 25: 0x");
  Serial.println(data_07, HEX);

  //Serial.print("Data from register humidity lsb 26: 0x");
  //Serial.println(data_08, HEX);
*/


  uint16_t par_p1 = readRegister(0x8E);
  uint16_t par_p2 = readRegister(0x90);
  uint16_t par_p3 = readRegister(0x92);
  uint16_t par_p4 = readRegister(0x94);
  uint16_t par_p5 = readRegister(0x96);
  uint16_t par_p6 = readRegister(0x99);
  uint16_t par_p7 = readRegister(0x98);
  uint16_t par_p8 = readRegister(0x9C);
  uint16_t par_p9 = readRegister(0x9E);
  uint16_t par_p10 = readRegister(0xA);

  Serial.print("par_p1: ");
  Serial.println(par_p1, HEX);

  Serial.print("par_p2: ");
  Serial.println(par_p2, HEX);

  Serial.print("par_p3: ");
  Serial.println(par_p3, HEX);

  Serial.print("par_p4: ");
  Serial.println(par_p4, HEX);

  Serial.print("par_p5: ");
  Serial.println(par_p5, HEX);

  Serial.print("par_p6: ");
  Serial.println(par_p6, HEX);

  Serial.print("par_p7: ");
  Serial.println(par_p7, HEX);

  Serial.print("par_p8: ");
  Serial.println(par_p8, HEX);

  Serial.print("par_p9: ");
  Serial.println(par_p9, HEX);

  Serial.print("par_p10: ");
  Serial.println(par_p10, HEX);
}

uint16_t readRegister(uint16_t regAddress)
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

void writeRegister(uint8_t regAddress, uint16_t value)
{
  digitalWrite(CS_PIN, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(regAddress);
  SPI.transfer(value);
  SPI.endTransaction();
  digitalWrite(CS_PIN, HIGH);
}

void printRegisterBits(uint16_t regAddress, uint16_t regValue)
{
  Serial.print("Register address 0x");
  Serial.print(regAddress, HEX);
  Serial.println(" bit values:");

  for (int i = 7; i >= 0; i--) 
  {
    Serial.print("bit ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println((regValue >> i) & 0x01);
  }
}

void loop() {
  uint16_t data_01 = readRegister(0x72);
  uint16_t data_02 = readRegister(0x74);
  uint16_t data_03 = readRegister(0x20);
  uint16_t data_04 = readRegister(0x1F);
  uint16_t data_05 = readRegister(0x22);
  uint16_t data_06 = readRegister(0x23);
  uint16_t data_07 = readRegister(0x25);
  uint16_t data_08 = readRegister(0x26);
  uint16_t data_09 = readRegister(0x2C);


  Serial.print("Data from register 0x72: 0x");
  Serial.println(data_01, HEX);

  Serial.print("Data from register 0x74: 0x");
  Serial.println(data_02, HEX);

  Serial.print("Data from register pressure msb 1F: 0x");
  Serial.println(data_04, HEX);

  Serial.print("Data from register pressure lsb 20: 0x");
  Serial.println(data_03, HEX);

  Serial.print("Data from register temp msb 22: 0x");
  Serial.println(data_05, HEX);

  Serial.print("Data from register temp lsb 23: 0x");
  Serial.println(data_06, HEX);

  Serial.print("Data from register humidity msb 25: 0x");
  Serial.println(data_07, HEX);

  Serial.print("Data from register humidity lsb 26: 0x");
  Serial.println(data_08, HEX);

  Serial.print("Data from gas register 2C: 0x");
  Serial.println(data_09, HEX);

  Serial.println(" ");

  delay(5000);


  writeRegister(0x73, 0b00010000); //This line is used for page selection in SPI memory map for bme688 sensor
  writeRegister(0x72, 0b00000001); //Humidity selection of passing 0b001
  writeRegister(0x74, 0b01010101); //This line is for pressure, temperature oversampling and forced mode selection 
  //writeRegister(0x74, 0b00000001); 

/*
  writeRegister(0x64, 0x59);
  writeRegister(0x5A, 0x00);
  writeRegister(0x71, 0b0000);
  writeRegister(0x71, 0b00000100);
*/

  writeRegister(0x64, 0b01011001);
  writeRegister(0x5A, 0b00000000);
  writeRegister(0x71, 0b00100000);
  //writeRegister(0x71, 0b00000100);
  //writeRegister(0x74, 0b00000001); //Forced mode triggered through this line

  //Here it ends the data extraction part 








  uint16_t data_10 = readRegister(0xE9);
  uint16_t data_11 = readRegister(0xEA);
  uint16_t data_12 = readRegister(0x8A);
  uint16_t data_13 = readRegister(0x8B);
  uint16_t data_14 = readRegister(0x8C);


  Serial.print("Data from register LSB 0xE9: 0x");
  Serial.println(data_10, HEX);

  Serial.print("Data from register MSB 0xEA: 0x");
  Serial.println(data_11, HEX);

  Serial.print("Data from register LSB 0x8A: 0x");
  Serial.println(data_12, HEX);

  Serial.print("Data from register MSB 0x8B: 0x");
  Serial.println(data_13, HEX);

  Serial.print("Data from register 0x8C: 0x");
  Serial.println(data_14, HEX);

  //uint16_t temp_adc = data_05 + data_06 << 8; 
  //uint16_t par_t1 = data_11 + data_10 << 8;
  //uint16_t par_t2 = data_13 + data_12 << 8;

  double temp_adc = data_05 << 8 | data_06; 
  double par_t1 = data_11 << 8 | data_10;
  double par_t2 = data_13 << 8 | data_12;
  double par_t3 = data_14;
  Serial.println(" ");

  double var1 = (((double)temp_adc / 16384.0) - ((double)par_t1 / 1024.0)) * (double)par_t2;
  double var2 = ((((double)temp_adc / 131072.0) - ((double)par_t1 / 8192.0)) *  (((double)temp_adc / 131072.0) - ((double)par_t1 / 8192.0))) * ((double)par_t3 * 16.0);

  double t_fine = var1 + var2;
  double temp_comp = (t_fine / 5120.0) * 10000;

  Serial.print("Compensated temperature value in degree celsius : ");
  Serial.println(temp_comp, DEC);

  Serial.println(" ");

}
