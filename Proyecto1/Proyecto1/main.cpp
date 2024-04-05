#define F_CPU 16000000UL // Definir la frecuencia del reloj para el uso del delay

#include <avr/io.h>
#include <util/delay.h>

#define D1 PD6
#define D2 PD2
#define PUL PC4

void toggleLED(uint8_t ledPin) {
	PORTD ^= (1 << ledPin); // Cambia el estado del pin especificado
}

int main(void) {
	uint8_t cont = 0;
	uint8_t band = 0;

	// Configurar D1 y D2 como salidas y PUL como entrada
	DDRD |= (1 << D1) | (1 << D2); // Configura los pines de los LEDs como salidas
	DDRC &= ~(1 << PUL); // Configura el pin del pulsador como entrada
	PORTC |= (1 << PUL); // Habilitar la resistencia de pull-up en el pulsador

	while (1) {
		
		cont++;
		if (cont == 140) { // Conmuta D1 cada 0.7 segundos
			toggleLED(D1);
			cont = 0;
		}

		// Leer el estado del pulsador
		if (!(PINC & (1 << PUL))) { // Si el pulsador está presionado (asumiendo configuración de pull-up)
			if (band == 0) {
				toggleLED(D2); // Conmutar D2
				band = 1;
			}
		}
		if ((PINC & (1 << PUL))) {
			band = 0; // Restablecer band cuando el pulsador no está presionado
		}
		_delay_ms(000.5);
	}
}