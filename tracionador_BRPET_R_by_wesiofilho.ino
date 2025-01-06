#include <AccelStepper.h>
#include <Bounce2.h>

#define STEP_PIN_Z 4
#define DIR_PIN_Z 7
#define EN_PIN 8
#define BUTTON_ON_OFF_PIN 11
#define BUTTON_THERMOSTAT_PIN 10
#define RELAY_PIN 9

const int velocidade = 4;
const float gearRatio = 25.2;
const int stepsPerRevolution = 200;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN_Z, DIR_PIN_Z);
Bounce2::Button buttonOnOff = Bounce2::Button();
Bounce2::Button buttonThermostat = Bounce2::Button();

bool motorOn = false;
bool thermostatOn = false;

void bootSequence() {
    // ... (código existente)
}

void setup() {
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    buttonOnOff.attach(BUTTON_ON_OFF_PIN, INPUT_PULLUP);
    buttonOnOff.interval(25);
    buttonThermostat.attach(BUTTON_THERMOSTAT_PIN, INPUT_PULLUP);
    buttonThermostat.interval(25);

    float motorSpeed = velocidade * gearRatio * stepsPerRevolution / 60.0;
    stepper.setMaxSpeed(motorSpeed);
    stepper.setSpeed(motorSpeed);

    digitalWrite(DIR_PIN_Z, HIGH);

    bootSequence();
}

void loop() {
    buttonOnOff.update();
    buttonThermostat.update();

    if (buttonOnOff.pressed()) {
        motorOn = !motorOn;
        digitalWrite(EN_PIN, motorOn ? LOW : HIGH);
    }

    if (buttonThermostat.pressed()) {
        thermostatOn = !thermostatOn;
        digitalWrite(RELAY_PIN, thermostatOn ? HIGH : LOW);
    }

    if (motorOn) {
        stepper.runSpeed();
    }
}
