#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LOW 0
#define LED1 PD6
#define LED2 PD2
#define BUTTON1 PC4
#define BUTTON2 PC5

uint8_t counterLED1 = 0;
uint8_t counterLED2 = 0;
uint8_t mode = 0; // 0 = mode1, 1 = mode2

void mode1(void);
void mode2(void);

int main(void) {
	DDRD |= (1 << LED1) | (1 << LED2); // Set LED ports as output
	PORTD &= ~((1 << LED1) | (1 << LED2)); // Turn off LEDs initially
	DDRC &= ~((1 << BUTTON1) | (1 << BUTTON2)); // Set BUTTON1 and BUTTON2 ports as input

	while (1) {
		if ((PINC & (1 << BUTTON1)) == LOW && (PINC & (1 << BUTTON2)) != LOW) {
			mode = 0; // Switch to mode1
			} else if ((PINC & (1 << BUTTON1)) != LOW && (PINC & (1 << BUTTON2)) == LOW) {
			mode = 1; // Switch to mode2
		}

		if (mode == 0) {
			mode1();
			} else {
			mode2();
		}
		_delay_ms(5);
	}
}

void mode1(void) {
	counterLED1++;
	counterLED2++;

	if (counterLED1 == 80) { // 0.4s
		PORTD ^= (1 << LED1); // Toggle LED1
		counterLED1 = 0;
	}

	if (counterLED2 == 140) { // 0.7s
		PORTD ^= (1 << LED2); // Toggle LED2
		counterLED2 = 0;
	}
}

void mode2(void) {
	counterLED1++;
	counterLED2++;

	if (counterLED1 == 180) { // 0.9s
		PORTD ^= (1 << LED1); // Toggle LED1
		counterLED1 = 0;
	}

	if (counterLED2 == 40) { // 0.2s
		PORTD ^= (1 << LED2); // Toggle LED2
		counterLED2 = 0;
	}
}