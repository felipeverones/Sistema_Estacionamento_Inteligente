// Example to demonstrate thread definition, semaphores, and thread sleep.
#include "ChRt.h"

// Definições dos pinos para o HC-SR04
const int pinTrigger = 8; 
const int pinEcho = 10; 

// Pino do LED
const int pinLED = 13; 

// Variável para armazenar a distância medida
volatile float distancia = 0.0;
MUTEX_DECL(mutexDistancia);

// Função para medir a distância usando o HC-SR04
float medirDistancia() {
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(1);
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);
    long duracao = pulseIn(pinEcho, HIGH);
    float constanteDeErro = 1.0223;
    //float constanteDeErro = 1;
    float distanciaCalculada = (constanteDeErro * duracao * 0.034029) / 2; // Velocidade do som: 340 m/s
    return distanciaCalculada;
}

// Tarefa para monitorar o sensor ultrassônico
static THD_WORKING_AREA(waSensorTask, 128);
static THD_FUNCTION(SensorTask, arg) {
    (void)arg;
    while (true) {
        float distanciaAtual = medirDistancia();
        chMtxLock(&mutexDistancia);
        distancia = distanciaAtual;
        chMtxUnlock(&mutexDistancia);
        chThdSleepMilliseconds(1000);
    }
}

// Tarefa para controlar o LED
static THD_WORKING_AREA(waLEDTask, 128);
static THD_FUNCTION(LEDTask, arg) {
    (void)arg;
    while (true) {
        chMtxLock(&mutexDistancia);
        float distanciaAtual = distancia;
        chMtxUnlock(&mutexDistancia);

        if (distanciaAtual < 10.0) { // Suponha que < 10 cm significa vaga ocupada
            digitalWrite(pinLED, HIGH);
        } else {
            digitalWrite(pinLED, LOW);
        }

        chThdSleepMilliseconds(1000);
    }
}

// Tarefa para enviar informações para o terminal serial
static THD_WORKING_AREA(waCommTask, 128);
static THD_FUNCTION(CommTask, arg) {
    (void)arg;
    while (true) {
        chMtxLock(&mutexDistancia);
        float distanciaAtual = distancia;
        chMtxUnlock(&mutexDistancia);

        Serial.print("Distancia: ");
        Serial.print(distanciaAtual);
        Serial.println("cm");

        chThdSleepMilliseconds(1000);
    }
}

void setup() {
    pinMode(pinTrigger, OUTPUT);
    pinMode(pinEcho, INPUT);
    pinMode(pinLED, OUTPUT);
    Serial.begin(9600);
    chBegin(mainThread);
}

void mainThread() {
    chThdCreateStatic(waSensorTask, sizeof(waSensorTask), NORMALPRIO, SensorTask, NULL);
    chThdCreateStatic(waLEDTask, sizeof(waLEDTask), NORMALPRIO, LEDTask, NULL);
    chThdCreateStatic(waCommTask, sizeof(waCommTask), NORMALPRIO, CommTask, NULL);

    while (true) {
        //chThdSleepMilliseconds(5000);
    }
}

// loop() is the main thread.  Not used in this example.
void loop() {
}