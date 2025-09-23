#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <Arduino.h>
#include <Wire.h>

class LCD_I2C {
public:
    LCD_I2C(uint8_t endereco, uint8_t colunas, uint8_t linhas);

    void iniciar();
    void limpar();
    void escrever(uint8_t coluna, uint8_t linha, const String &texto);

private:
    void enviarComando(uint8_t comando);
    void enviarDado(uint8_t dado);
    void enviar(uint8_t valor, uint8_t modo);
    void pulsoEnable(uint8_t dado);

    uint8_t _endereco;
    uint8_t _colunas;
    uint8_t _linhas;
};

#endif
