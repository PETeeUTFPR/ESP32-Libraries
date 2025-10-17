#include <Arduino.h>
#include <Wire.h>
#include "LCD_I2C.h"
#include "DHT.h" // Incluindo a biblioteca do sensor DHT

// Definições do Sensor DHT
#define DHTPIN 4        // Pino do ESP32 conectado ao pino de dados do DHT.
#define DHTTYPE DHT11  

// Inicializa o objeto DHT
DHT dht(DHTPIN, DHTTYPE);

// Inicializa o Display LCD I2C
// (endereço do lcd normalmente 0x20 ou 0x27, colunas, linhas)
LCD_I2C lcd(0x27, 16, 2); 

void setup() {
	Serial.begin(115200);
	
	// Configuração do LCD
	lcd.iniciar(); 
	lcd.limpar(); 
	lcd.escrever(0, 0, "DHT + LCD I2C");
	lcd.escrever(0, 1, "Iniciando..."); 

	// Configuração do DHT
	dht.begin();
	Serial.println("DHT inicializado.");

	// Pequeno delay para mostrar a mensagem de inicialização
	delay(2000);
	lcd.limpar();
}

void loop() {
	// A leitura do sensor pode demorar um pouco (até 2s),
	// então usamos um delay entre as leituras.
	delay(2000); 

	// Leitura da umidade (Humidity)
	float h = dht.readHumidity();
	// Leitura da temperatura em Celsius (Temperature)
	float t = dht.readTemperature();

	// Verifica se a leitura falhou (NaN)
	if (isnan(h) || isnan(t)) {
		Serial.println("Erro ao ler do sensor DHT!");
		lcd.limpar();
		lcd.escrever(0, 0, "Erro de Leitura");
		lcd.escrever(0, 1, "Verifique o DHT!");
		return;
	}

	// --- Formatação das Saídas ---
	
	// Buffer para as strings formatadas
	char buffer_temp[16];
	char buffer_umid[16];

	// Formata a string de Temperatura: 'Temp: XX.X °C'
	snprintf(buffer_temp, sizeof(buffer_temp), "Temp: %.1f%cC", t, (char)223); // 223 é o símbolo de grau (°)

	// Formata a string de Umidade: 'Umid: XX.X %'
	snprintf(buffer_umid, sizeof(buffer_umid), "Umid: %.1f %%", h);

	// --- Exibição no LCD ---
	
	lcd.limpar(); // Limpa o display para a nova leitura
	
	// Linha 0: Temperatura
	lcd.escrever(0, 0, buffer_temp); 
	
	// Linha 1: Umidade
	lcd.escrever(0, 1, buffer_umid); 

	Serial.print("Temperatura: ");
	Serial.print(t);
	Serial.print("°C | Umidade: ");
	Serial.print(h);
	Serial.println("%");
}
