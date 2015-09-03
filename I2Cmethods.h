#define F_SCL         100000L           // I2C clock speed 100 kHz

#include <avr/io.h>

void I2CInit(void)					//Init I2C
{
	//set SCL to 400kHz
	TWSR = 0x00;
	TWBR = ((F_CPU/F_SCL)-16)/2;
	//enable TWI
	TWCR = (1<<TWEN);
}

void I2CStart(void)					//Start I2C
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2CStop(void)					//Stop I2C
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}


void I2CWrite(uint8_t u8data)		//Write to I2C
{
	TWDR = u8data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

unsigned char I2CRead(void)		//Read I2C
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
