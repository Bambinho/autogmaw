void output_kinematics(void)
{
  float timestamp_vector[1];
  timestamp_vector[0] = timestamp / 1000.0f;
  
  if (output_format == OUTPUT__FORMAT_BINARY)
  {
    Serial.write((byte*) current_out, 4);
    Serial.write((byte*) voltage_out, 4);
    Serial.write((byte*) TS_out, 4);
    Serial.write((byte*) timestamp_vector, 4);
  }
  else if (output_format == OUTPUT__FORMAT_TEXT)
  {
//    Serial.print("TravelSpeed:  "); Serial.print(TS_out[0]); Serial.print(" mm/s");
    Serial.print("Current:  "); Serial.print(current_out[0]); Serial.println(" A");
    Serial.print("Voltage:  "); Serial.print(voltage_out[0]); Serial.println(" V");
    Serial.print("Timestamp: "); Serial.println(timestamp_vector[0]);

  }
}

