#include <ADC.h>
ADC *adc = new ADC(); // adc object;

const int readPin = A9; // ADC0
const int readPin2 = A2; // ADC1


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(readPin, INPUT_PULLUP);
    pinMode(readPin2, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("Begin setup");
    
    adc->setAveraging(16); // set number of averages
    adc->setResolution(16); // set bits of resolution
    adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED); // change the conversion speed
    adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed

    adc->setAveraging(16, ADC_1); // set number of averages
    adc->setResolution(16, ADC_1); // set bits of resolution
    adc->setConversionSpeed(ADC_CONVERSION_SPEED::MED_SPEED, ADC_1); // change the conversion speed
    adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED, ADC_1); // change the sampling speed

    Serial.println("End setup");
}

int value;
int value2;

void loop() {
    value = adc->analogRead(readPin); // read a new value, will return ADC_ERROR_VALUE if the comparison is false.
    Serial.print("Pin: ");
    Serial.print(readPin);
    Serial.print(", value ADC0: ");
    Serial.println(value*3.3/adc->getMaxValue(ADC_0), DEC);

    value2 = adc->analogRead(readPin2, ADC_1);
    Serial.print("Pin: ");
    Serial.print(readPin2);
    Serial.print(", value ADC1: ");
    Serial.println(value2*3.3/adc->getMaxValue(ADC_1), DEC);

    // Print errors, if any.
    adc->printError();
    digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
    delay(50);
}
