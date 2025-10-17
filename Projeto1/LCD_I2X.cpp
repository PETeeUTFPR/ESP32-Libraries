#include "LCD_I2C.h"

#define LCD_ENABLE    0x04
#define LCD_COMANDO   0x00
#define LCD_DADO      0x01
#define LCD_BACKLIGHT 0x08

LCD_I2C::LCD_I2C(uint8_t endereco, uint8_t colunas, uint8_t linhas) {
    _endereco = endereco;
    _colunas = colunas;
    _linhas = linhas;
}

void LCD_I2C::iniciar() {
    Wire.begin();
    delay(50);

    enviarComando(0x33);
    enviarComando(0x32);
    enviarComando(0x28); // 4 bits, 2 linhas, 5x8 fonte
    enviarComando(0x0C); // Display ligado, cursor desligado
    enviarComando(0x06); // Auto incremento
    limpar();
}

void LCD_I2C::limpar() {
    enviarComando(0x01);
    delay(2);
}

void LCD_I2C::escrever(uint8_t coluna, uint8_t linha, const String &texto) {
    static const uint8_t deslocamento_linha[] = {0x00, 0x40, 0x14, 0x54};
    if (linha >= _linhas) linha = 0;
    enviarComando(0x80 | (coluna + deslocamento_linha[linha]));

    for (uint8_t i = 0; i < texto.length(); i++) {
        enviarDado(texto[i]);
    }
}

void LCD_I2C::enviarComando(uint8_t comando) {
    enviar(comando, LCD_COMANDO);
}

void LCD_I2C::enviarDado(uint8_t dado) {
    enviar(dado, LCD_DADO);
}

void LCD_I2C::enviar(uint8_t valor, uint8_t modo) {
    uint8_t nibble_alto = valor & 0xF0;
    uint8_t nibble_baixo = (valor << 4) & 0xF0;

    Wire.beginTransmission(_endereco);
	
	Wire.write((nibble_alto | modo) | LCD_BACKLIGHT);
	Wire.write(((nibble_alto | modo) | LCD_ENABLE) | LCD_BACKLIGHT);
	Wire.write(((nibble_alto | modo) & ~LCD_ENABLE) | LCD_BACKLIGHT);

	Wire.write((nibble_baixo | modo) | LCD_BACKLIGHT);
	Wire.write(((nibble_baixo | modo) | LCD_ENABLE) | LCD_BACKLIGHT);
	Wire.write(((nibble_baixo | modo) & ~LCD_ENABLE) | LCD_BACKLIGHT);
	
    Wire.endTransmission();
}

void LCD_I2C::pulsoEnable(uint8_t dado) {
    Wire.beginTransmission(_endereco);
    Wire.write(dado | LCD_ENABLE);
    Wire.write(dado & ~LCD_ENABLE);
    Wire.endTransmission();
    delayMicroseconds(1);
}
