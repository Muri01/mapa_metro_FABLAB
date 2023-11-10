#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

#define PIN_LED 12   // Pino ao qual a fita de LED está conectada
#define NUM_LEDS 58       // Número total de LEDs na fita
#define ROWS 4             // Número de linhas do teclado
#define COLS 4             // Número de colunas do teclado
#define ESTACAO_INICIAL 14  // Número correspondente a estação atual

#define SE 12
#define REPUBLICA 14
#define BARRA_FUNDA 18
#define PEDRO_II 27
#define LIBERDADE 28
#define PARAISO 31
#define ANA_ROSA 32
#define JABAQUARA 40
#define BRIGADEIRO 45
#define VILA_PRUDENTE 52

Adafruit_NeoPixel pixeles = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

// Define a disposição das teclas no teclado
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define os pinos do teclado
byte rowPins[ROWS] = {9, 8, 7, 6}; // Conecte os pinos do teclado às linhas 9, 8, 7 e 6
byte colPins[COLS] = {5, 4, 3, 2}; // Conecte os pinos do teclado às colunas 5, 4, 3 e 2

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Criar as variaveis da estação em numero inteiro (para a fita de LED) e em string(texto que é lido do teclado)
int estacaoDestino = 0;
String estacaoDigitada = "";

void setup() {
  pixeles.begin();
  pixeles.show(); // Inicialmente, todos os LEDs estão apagados
  
  pixeles.setPixelColor(REPUBLICA, 255, 0, 0); // Vermelho (R, G, B)
  pixeles.show();

  Serial.begin(9600); // Inicializa a comunicação com o monitor serial
}

void loop() {
  

  char key = keypad.getKey(); //criar variavel que lê o teclado
  
  if (key) { // Se existir algum valor na variavel key, então executa isso
    if (key >= '0' && key <= '9') { // Se o valor que exite na variavel estiver entre 0 e 9, então executa isso
      estacaoDigitada += key; // Adiciona o dígito ao número final
      Serial.print("estacaoDigitada: ");
      Serial.println(estacaoDigitada);
    } else if (key == '#') { // Se o valor que existir na variavel for '#', então:
      estacaoDestino = estacaoDigitada.toInt(); // converte a string(texto) para um número inteiro
      Serial.print("estacao de Destino: ");
      Serial.println(estacaoDestino);
      if (estacaoDestino > 0 && estacaoDestino <= NUM_LEDS) {
        pixeles.clear();// apagar os LEDs
        pixeles.show();
        acenderEstacao(estacaoDestino);
      }
      // Reseta a string para o próximo número
      estacaoDigitada = ""; 
      estacaoDestino = 0;
      Serial.println("fim");
    }
  }
}

void acenderEstacao(int estacaoDestino) {
  
  if(estacaoDestino <= BARRA_FUNDA){ //esta na linha vermelha
    
    if(estacaoDestino<ESTACAO_INICIAL){//vai pro lado direito (1-itaquera)
      for (int i = ESTACAO_INICIAL; i >= (estacaoDestino-1); i--) {
        pixeles.setPixelColor(i, 255, 0, 0); // Vermelho (R, G, B)
        pixeles.show();
        delay(200);
      }
    }else{ //vai pro lado esquerdo (18-barra funda)
      for (int i = ESTACAO_INICIAL; i < estacaoDestino; i++) {
        pixeles.setPixelColor(i, 255, 0, 0); // Vermelho (R, G, B)
        pixeles.show();
        delay(200);
      }
    }
    
  } else if(estacaoDestino <=JABAQUARA){ //esta na linha azul
      // Vai até a Sé
      for (int i = ESTACAO_INICIAL; i >= SE; i--) {
        pixeles.setPixelColor(i, 255, 0, 0); // Vermelho (R, G, B)
        pixeles.show();
        delay(200);
      }
      pixeles.setPixelColor(SE, 0, 0, 255); // azul (R, G, B)
        pixeles.show();
        delay(200);
      
      if(estacaoDestino < PEDRO_II){ //Vai para cima (19-Tucuruvi)
        for (int i = PEDRO_II; i >= (estacaoDestino-1); i--) {
          pixeles.setPixelColor(i, 0, 0, 255); // azul (R, G, B)
          pixeles.show();
          delay(200);
        }
        
      }else{ //Vai para baixo (jabaquara)
        for (int i = LIBERDADE; i < estacaoDestino; i++) {
          pixeles.setPixelColor(i, 0, 0, 255); // azul (R, G, B)
          pixeles.show();
          delay(200);
        }
      }
  } else if(estacaoDestino <= VILA_PRUDENTE){ // esta na linha verde
    //vai até a 13-SÉ 
    for (int i = ESTACAO_INICIAL; i >= (SE); i--) {
        pixeles.setPixelColor(i, 255, 0, 0); // Vermelho (R, G, B)
        pixeles.show();
        delay(200);
      }
      pixeles.setPixelColor(SE, 0, 0, 255); // azul (R, G, B)
        pixeles.show();
        delay(200);
    
    //vai até o 33-Paraiso
    for (int i = LIBERDADE; i <= PARAISO; i++) {
       pixeles.setPixelColor(i, 0, 0, 255); // azul (R, G, B)
       pixeles.show();
       delay(200);
    }
    pixeles.setPixelColor(PARAISO, 0, 255, 0); // verde (R, G, B)
    pixeles.show();
    delay(200);
    
    if(estacaoDestino <= BRIGADEIRO+1){ // vai pra esquerda (41-vila mariana)
      for (int i = BRIGADEIRO; i >= (estacaoDestino-1); i--) {
          pixeles.setPixelColor(i, 0, 255, 0); // verde (R, G, B)
          pixeles.show();
          delay(200);
        }
      
    } else{ // vai para direita (55-Vila prudente)
      //vai pra linha verde
      pixeles.setPixelColor(ANA_ROSA, 0, 255, 0); // verde (R, G, B)
      pixeles.show();
      delay(200);
      
      for (int i = BRIGADEIRO+1; i < estacaoDestino; i++) {
          pixeles.setPixelColor(i, 0, 255, 0); // verde (R, G, B)
          pixeles.show();
          delay(200);
      }
    }
  }
}
