#include <Wire.h>
#include "LCD_I2C.h"
#include <DHT_Lib.h> // Biblioteca correta incluída

// --- Constantes ---
#define DHT_PIN 5 // Defina aqui o pino GPIO onde o DHT está conectado

// --- Inicialização dos Objetos ---

// Inicializa o objeto DHT (usando a classe DHT_Lib e passando o pino)
DHT_Lib dht(DHT_PIN);

// Inicializa o Display LCD I2C
// (endereço, colunas, linhas)
LCD_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);

    // Configuração do LCD
    lcd.iniciar();
    lcd.limpar();
    lcd.escrever(0, 0, "DHT + LCD I2C");
    lcd.escrever(0, 1, "Iniciando...");

    // Configuração do DHT (usando a função do exemplo)
    dht.iniciar(); // CORRIGIDO: A função é 'iniciar()'
    Serial.println("DHT inicializado.");

    // Pequeno delay para mostrar a mensagem de inicialização
    delay(2000);
    lcd.limpar();
}

void loop() {
    // CORRIGIDO: A lógica de leitura desta biblioteca é diferente.
    // Primeiro, chamamos dht.ler()
    if (dht.ler()) {
        // Se a leitura for bem-sucedida (retornou true):

        // 1. Obtemos os valores
        float h = dht.umidade();
        float t = dht.temperatura();

        // --- Formatação das Saídas ---

        // Buffer para as strings formatadas (aumentei para 17 por segurança)
        char buffer_temp[17];
        char buffer_umid[17];

        // Formata a string de Temperatura: 'Temp: XX.X C'
        // (char)223 é o símbolo de grau (°)
        snprintf(buffer_temp, sizeof(buffer_temp), "Temp: %.1f%cC", t, (char)223);

        // Formata a string de Umidade: 'Umid: XX.X %'
        snprintf(buffer_umid, sizeof(buffer_umid), "Umid: %.1f %%", h);

        // --- Exibição no LCD ---
        lcd.limpar(); // Limpa o display para a nova leitura

        // Linha 0: Temperatura
        lcd.escrever(0, 0, buffer_temp);

        // Linha 1: Umidade
        lcd.escrever(0, 1, buffer_umid);

        // --- Exibição no Serial Monitor ---
        Serial.print("Temperatura: ");
        Serial.print(t);
        Serial.print("°C | Umidade: ");
        Serial.print(h);
        Serial.println("%");

    } else {
        // CORRIGIDO: Se dht.ler() retornar false (falha na leitura)
        Serial.println("Erro ao ler do sensor DHT!");
        lcd.limpar();
        lcd.escrever(0, 0, "Erro de Leitura");
        lcd.escrever(0, 1, "Verifique o DHT!");
    }

    // Delay de 2 segundos entre as leituras
    delay(2000);
}
