#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define SPI_DDR DDRB
#define SPI_PORT PORTB	//si4432 CS, SCK & MOSI pin config
#define CS_PIN 2
#define MOSI_PIN 3
#define SCK_PIN 5

/*command codes for atmega*/
#define ACK 0xAA
#define NAK 0xCC


enum {ADDR, CHECK_ADDR, NUM, CHECK_NUM, READING,
	 BYTES_OUT, BYTES_IN, WRITING, RESET};			//states

/*global variables*/
uint8_t data_in[128];	//buffers for data; length for burst r/w
uint8_t data_out[128];

uint8_t data_in_begin;	//data array endmarks
uint8_t data_out_begin;
uint8_t data_in_end;
uint8_t data_out_end;

uint8_t addr;		//address and R/W flag for SPI manipulations
uint8_t byte_count;	//byte counter

uint8_t state;
uint8_t waiting;
uint8_t first_byte;

/*interrupt routines*/
ISR(SPI_STC_vect) {	//SPI end of transmission interrupt
	PORTC ^= 1;
	switch(state) {
	case READING:
		data_out[data_out_end] = SPDR;
		data_out_end++;
		break;

	case WRITING:
		if(data_in_begin < byte_count) {
			SPDR = data_in[data_in_begin];
			data_in_begin++;
		}
		break;

	default:
		break;

	}

	PORTC ^= 1;
}

ISR(USART_RX_vect) {	//USART data received interrupt
	switch(state) {
	case ADDR:
		addr = UDR0;
		state = CHECK_ADDR;
		break;

	case CHECK_ADDR:
		if(UDR0 == ACK) {
			state = NUM;
			waiting = 0;
		}
		else
			state = RESET;
		break;

	case NUM:
		byte_count = UDR0;
		state = CHECK_NUM;
		break;

	case CHECK_NUM:
		if(UDR0 == ACK) {
			waiting = 0;
			if(addr & (1<<7))	//if writing
				state = BYTES_IN;
			else
				state = READING;
			}
		else
			state = RESET;
		break;

	case BYTES_IN:
		data_in[data_in_end] = UDR0;
		data_in_end++;
		break;

	default:
		break;
	}
}

ISR(USART_UDRE_vect) {	//USART nothing to transmit interrupt
	switch(state) {
	case CHECK_ADDR:
	case CHECK_NUM:
		UCSR0B &= ~(1<<UDRIE0);
		break;

	case BYTES_OUT:
		if(first_byte)
			first_byte = 0;
		if(data_out_begin < byte_count) {
			UDR0 = data_out[data_out_begin];
			data_out_begin++;
		}
		else {
			UCSR0B &= ~(1<<UDRIE0);
			state = RESET;
		}
		break;

	default:
		break;

	}
}


int main() {

/*software init*/
	data_in_end = 0;	//flush buffers
	data_out_end = 0;
	data_in_begin = 0;
	data_out_begin = 0;

	addr = 0;		//zeroing everything (just to be sure)
	byte_count = 0;

	state = ADDR;
	waiting = 0;
	first_byte = 1;

/*hardware init*/
/*debugging GPIO*/
	DDRC = 0x03;		//pins PC0 & PC1 outputs
	PORTC|= 1;		//initial PC0

/*USART*/
	UBRR0L = 51;		//baudrate = 9600
	UCSR0B = (1<<RXCIE0)|	//RXC interrupt enabled
		(1<<RXEN0)|(1<<TXEN0);		//RX/TX enable

/*SPI*/
	SPI_DDR = (1<<CS_PIN)|(1<<MOSI_PIN)|(1<<SCK_PIN);	//out

	SPCR = (1<<SPE)|(1<<SPIE)|		//SPI & SPI interrupt
		(1<<MSTR)|			//master mode
		(0<<CPOL)|(0<<CPHA)|		//clk phase & polarity
		(1<<SPR1)|(1<<SPR0);		//clk divider = 128

	SPI_PORT |= (1 << CS_PIN);	//set CS high

/*all init done*/

	sei();			//now it's goin'

	while(1) {
		switch(state) {

		case CHECK_ADDR:
			if(!waiting) {
				UDR0 = addr;
				UCSR0B |= (1<<UDRIE0);	//enable UDRE interrupt
				waiting = 1;
			}

		case CHECK_NUM:
			if(!waiting) {
				UDR0 = byte_count;
				UCSR0B |= (1<<UDRIE0);
				waiting = 1;
			}
			break;

		case READING:
			if(first_byte) {
				first_byte = 0;
				SPI_PORT &= ~(1 << CS_PIN);	//CS low
				SPDR = addr;
			}
			else if(data_out_end < byte_count)
				SPDR = 0x5A;	//for debugging purposes
			else {
				SPI_PORT |= (1 << CS_PIN);
				state = BYTES_OUT;
			}
			break;

		case BYTES_OUT:
			if(first_byte) {
				first_byte = 0;
				UCSR0B |= (1<<UDRIE0);
			}
			break;

		case BYTES_IN:
			if(data_in_end >= byte_count)
				state = WRITING;
			break;

		case WRITING:
			if(first_byte) {
				first_byte = 0;
				SPI_PORT &= ~(1 << CS_PIN);	//CS low
				SPDR = addr;
			}
			if(data_in_begin >= byte_count) {
				SPI_PORT |= (1<<CS_PIN);
				state = RESET;
			}
			break;

		case RESET:
			UCSR0B &= ~(1<<UDRIE0);
			addr = 0;
			byte_count = 0;
			data_in_begin = 0;
			data_in_end = 0;
			data_out_begin = 0;
			data_out_end = 0;
			waiting = 0;
			first_byte = 1;
			state = ADDR;
			break;

		default:
			break;

		}

	}
}
