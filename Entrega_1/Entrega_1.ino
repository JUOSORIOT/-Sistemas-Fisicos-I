bool sonIguales(char *claveCorrecta, char *claveIngresada)
{
  int auxiliar = 0;
  for (int i = 0; i < 6; i++) {
    if (claveCorrecta[i] == claveIngresada[i])
    {
      auxiliar = auxiliar + 1;
    }
  }
  if (auxiliar == 6)
  {
    return true;
  }
  else
  {
    return false;
  }
}
void setup() {
  Serial.begin(115200);
}

void tarea2() {
  static uint32_t previousMillis = 0;
  static const uint32_t interval = 500;
  static bool taskInit = false;
  static const uint8_t ledPin =  3;
  static uint8_t ledState = LOW;
  if (taskInit == false) {
    pinMode(ledPin, OUTPUT);
    taskInit = true;
  }
  uint32_t currentMillis = millis();
  if ( (currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}
void tarea1() {
  static int estado = 1;
  static int conteo = 20;
  static unsigned long previousMillis = 0;

  static unsigned long intervalo = 1000;
  static int8_t rxData[10];
  static char codigoCorrecto[6] = {'d', 'u', 'd', 'd', 'u', 'a'};
  static char codigoIngresado[6];
  static int contador = 0;

  unsigned long currentMillis = millis();


  switch (estado) {
    case 1: {
        if (Serial.available() > 0)
        {
          char dato = Serial.read();
          if ((char)dato == 'd' && conteo >= 11)
          {
            conteo = conteo - 1;
            Serial.println(conteo);
          }
          else if ((char)dato == 'u' && conteo <= 59)
          {
            conteo = conteo + 1;
            Serial.println(conteo);
          }
          else if ((char)dato == 'a')
          {
            estado = 2;
            previousMillis = millis();
            contador = 0;

          }
        }

        break;
      }
    case 2: {
        if (Serial.available() > 0) {
          codigoIngresado[contador] = Serial.read();
          contador++;
          if (contador == 6) {
            if (sonIguales(codigoCorrecto, codigoIngresado))
            {
              estado = 1;
              conteo = 20;
            }
            contador = 0;
          }
        }
        if ( (millis() - previousMillis) >= intervalo)
        {
          previousMillis = millis();
          if (conteo > 0)
          {
            conteo = conteo - 1;
            Serial.println(conteo);
          }
          else
          {
            Serial.println("Boom");
            estado = 1;
            conteo = 20;

          }
        }

        break;
      }
    default:
      Serial.println("Error");
      break;
  }
}
void loop() {
  tarea1();
  tarea2();
}
