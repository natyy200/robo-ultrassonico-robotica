#include <Ultrasonic.h>
/* Define os pinos para o sensor ultrassônico. */
#define pino_Trig 11
#define pino_Echo 12
/* Define a potência dos motores: 0 a 255. */
int potencia = 200;
/* Definições dos pinos IN1 a IN4 da ponte H. */
/* Para controlar a velocidade dos motores, esses pinos */
/* deverão ser conectados em portas com o recurso PWM. */
#define IN1 10 // Porta PWM ~10
#define IN2 9 // Porta PWM ~9
#define IN3 6 // Porta PWM ~6
#define IN4 5 // Porta PWM ~5
/* Cria o objeto Sensor que realizará a leitura do sensor. */
Ultrasonic Sensor(pino_Trig, pino_Echo);
/* Variável que armazenará as medidas. */
int distancia;
/* Criando as funções de controle dos motores. */
/* Move para frente. */
void Frente(int Vel_A, int Vel_B) {
 /* Motor A */
 analogWrite(IN1, Vel_A);
 analogWrite(IN2, 0);
 /* Motor B */
 analogWrite(IN3, Vel_B);
 analogWrite(IN4, 0);
}
/* Move vpara trás. */
void Re(int Vel_A, int Vel_B) {
 /* Motor A */
 analogWrite(IN1, 0);
 analogWrite(IN2, Vel_A);
/* Motor B */
 analogWrite(IN3, 0);
 analogWrite(IN4, Vel_B);
}
/* Giro no sentido horário. */
void GiroHorario(int vel_A, int vel_B) {
 /* Motor A */
 analogWrite(IN1, vel_A);
 analogWrite(IN2, 0);
 /* Motor B */
 analogWrite(IN3, 0);
 analogWrite(IN4, vel_B);
}
/* Giro no sentido anti-horário. */
void GiroAntiHorario(int Vel_A, int Vel_B) {
 /* Motor A */
 analogWrite(IN1, 0);
 analogWrite(IN2, Vel_A);
 /* Motor B */
 analogWrite(IN3, Vel_B);
 analogWrite(IN4, 0);
}
/* Para o chassi. */
void Pare() {
 /* Motor A */
 analogWrite(IN1, 0);
 analogWrite(IN2, 0);
 /* Motor B */
 analogWrite(IN3, 0);
 analogWrite(IN4, 0);
}
/* Função parar manobrar o robô. */
void Manobre() {
 if (random(1, 3) == 1) {
 GiroAntiHorario(potencia * 0.5, potencia * 0.5);
 } else {
 GiroHorario(potencia * 0.5, potencia * 0.5);
 }
 delay(250);
}
void setup() {
 /* Inicia com os motores parados. */
 Pare();
 /* Aguarda 3 segundos antes de começar os movimentos. */
  delay(3000);
}
void loop() {
 /* Armazena a distância na variável “distancia”. */
 distancia = Sensor.read();
 /* Se a distância for menor ou igual a 40cm, realize a */
 /* manobra do robô. */
 if (distancia <= 40) {
 /* Chama a função responsável pela manobra. */
 Manobre();
 }
 /* Senão siga em frente. */
 else {
 /* Chama a função mover para frente. */
 Frente(potencia, potencia);
 }
}