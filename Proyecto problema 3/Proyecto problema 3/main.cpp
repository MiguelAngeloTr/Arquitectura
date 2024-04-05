#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define Pul (1 << PC4)
#define op 0

void Pulsador(const uint8_t* Tabla, uint8_t& Bpul, uint8_t& Contador) {
	if (!(PINC & Pul) && Bpul == 1) {
		Contador++;
		if (Contador == 16) {
			Contador = 0;
		}
		Bpul = 0;
		PORTD = Tabla[Contador];
		} else {
		Bpul = 1;
	}
}

int main(void) {
	DDRC &= ~(1<<PINC); // Configurar Pin C4 como entrada (Pulsador)
	PORTD &= ~(0x01); // Habilitar resistencia de pull-down en el pin PB0
	DDRD |= 0xFF;   // Pines PB0-PB7 como salidas
	uint8_t Contador = 0;

	const uint8_t Tabla[16] = {
		0b00111111, // 0
		0b00000110, // 1
		0b01011011, // 2
		0b01001111, // 3
		0b01100110, // 4
		0b01101101, // 5
		0b01111101, // 6
		0b00000111, // 7
		0b01111111, // 8
		0b01101111, // 9
		0b01110111, // A
		0b01111100, // B
		0b00111001, // C
		0b01011110, // D
		0b01111001, // E
		0b01110001  // F
	};
	uint8_t Bpul = 1;

	while (1) {
		Pulsador(Tabla, Bpul, Contador);
		_delay_ms(5);
	}
}
