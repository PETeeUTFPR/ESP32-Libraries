#include <Arduino.h>
#include <Wire.h>
#include "LCD_I2C.h"

LCD_I2C lcd(0x27, 16, 2); // (endereço do lcd normalmente 0x20 ou 0x27, colunas, linhas)

void setup() {
	lcd.iniciar(); // inicia o display
	lcd.limpar(); // limpa a tela para prevenir cache antigo
	lcd.escrever(0, 0, "Eletronica"); // escreve na tela (coluna, linha, texto) nesse caso coluna 0 linha 0
	lcd.escrever(2, 1, "UTFPR 2025"); // escreve na tela (coluna, linha, texto) nesse caso coluna 2 linha 1
}

void loop() {
}
