void amp_volt_setup()
{
  pinMode(ammeterPin, INPUT);
  pinMode(voltmeterPin, INPUT);
}

void amm_volt_read()
{
  sensorValue1 = analogRead(ammeterPin);   
  sensorValue2 = analogRead(voltmeterPin);
  
  get_current();
  get_voltage();
  get_speed();
}

void get_current()
{
  //CURRENT SHUNT
  
  // Set shunt factor as MAX_AMPERAGE (A) / VOLTAGE_OUTPUT (V)
  // (ie. if shunt outputs 50mV at 200A, then shunt factor = 200 / 0.05 = 4000)
  //
  // Set amp_factor as 1 + 49.4/Gain_Resistance (may be determined with greater precision if measured directly)
  
  //  float shunt_factor = 4000;
  //  float amp_factor = 50.53;
  // raw_current = sensorValue1 * (5.0/1023.0) * (shunt_factor) / (amp_factor);

  // HALL EFFECT SENSOR

  float current_factor = 100;
  raw_current = sensorValue1 * (5.0/1023.0) * (current_factor);

  // OUTPUT
  current_out[0] = (raw_current - AMM_OFFSET) * AMM_SCALE;
}

void get_voltage()
{
  // Voltage divider factor chosen according to F = R2 / (R1 + R2), where the measured voltage is across R2
  
  float voltage_factor = 10;
  raw_voltage = sensorValue2 * (5.0/1023.0) * (voltage_factor);

  // OUTPUT
  voltage_out[0] = (raw_voltage - VOLT_OFFSET) * VOLT_SCALE;
}

void get_speed()
{
  // Count impulses for TS
  TS_state_0 = digitalRead(speedPin);
  if (TS_state_0 != TS_state_1) {
    TS_state_1 = TS_state_0;
    if (TS_state_1) {
//        TS_out[0] = 3000 / (millis()-TS_time);
        TS_out[0] = (millis()-TS_time);
        TS_time = millis();
    }
  }
}

