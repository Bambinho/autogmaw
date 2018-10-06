

// OUTPUT OPTIONS
/*****************************************************************/
// Set your serial port baud rate used to send out data here!
#define OUTPUT__BAUD_RATE 57600

// Sensor data output interval in milliseconds
// This may not work, if faster than 20ms (=50Hz)
// Code is tuned for 20ms, so better leave it like that
#define OUTPUT__DATA_INTERVAL 10  // in milliseconds

#define OUTPUT__MODE_KINEMATICS 1 //

#define OUTPUT__FORMAT_TEXT 1 //
#define OUTPUT__FORMAT_BINARY 2 //


// Select your startup output mode and format here!
int output_mode = OUTPUT__MODE_KINEMATICS;
int output_format = OUTPUT__FORMAT_TEXT;

// Select if serial continuous streaming output is enabled per default on startup.
#define OUTPUT__STARTUP_STREAM_ON true  // true or false

// If set true, an error message will be output if we fail to read sensor data.
// Message format: "!ERR: reading <sensor>", followed by "\r\n".
boolean output_errors = false;  // true or false


// Ammeter and Voltmeter calibration
/*****************************************************************/

// AMMETER CALIBRATION USING TWO READINGS COMAPRED TO KNOWN VALUES
#define EXPECT_CURRENT_1 ((float) 30)
#define MEASURED_CURRENT_1 ((float) 30)

#define EXPECT_CURRENT_2 ((float) 20)
#define MEASURED_CURRENT_2 ((float) 20)

// VOLTMETER CALIBRATION USING TWO READINGS COMAPRED TO KNOWN VALUES
#define EXPECT_VOLTAGE_1 ((float) 5.00)
#define MEASURED_VOLTAGE_1 ((float) 5.00)

#define EXPECT_VOLTAGE_2 ((float) 20.00)
#define MEASURED_VOLTAGE_2 ((float) 20.00)


#include <Wire.h>

// Voltmeter and Ammeter calibration scale and offset values
#define AMM_SCALE ((EXPECT_CURRENT_1 - EXPECT_CURRENT_2) / (MEASURED_CURRENT_1 - MEASURED_CURRENT_2))
#define AMM_OFFSET (MEASURED_CURRENT_1 - (EXPECT_CURRENT_1 / AMM_SCALE))

#define VOLT_SCALE ((EXPECT_VOLTAGE_1 - EXPECT_VOLTAGE_2) / (MEASURED_VOLTAGE_1 - MEASURED_VOLTAGE_2))
#define VOLT_OFFSET (MEASURED_VOLTAGE_1 - (EXPECT_VOLTAGE_1 / VOLT_SCALE))


// Stuff
#define STATUS_LED_PIN 13  // Pin number of status LED

// Ammeter and Voltmeter variables
int voltmeterPin = A1;
int ammeterPin = A0;
int speedPin = 7;

int sensorValue1 = 0;   // variable to store the value coming from the ammeter
int sensorValue2 = 0;   // variable to store the value coming from the voltmeter

int TS_state_0 = 0;   // variable to store the value coming from the velocity transducer
int TS_state_1 = 0;   // variable to store the value coming from the velocity transducer
float TS_time = 0;
int impulses = 0;
float TS_out[1] = {0};

float raw_voltage;
float raw_current;
float voltage_out[1] = {0};
float current_out[1] = {0};

// More output-state variables
boolean output_stream_on;
boolean output_single_on;
int curr_calibration_sensor = 0;
boolean reset_calibration_session_flag = true;
int num_accel_errors = 0;
int num_magn_errors = 0;
int num_gyro_errors = 0;

// Define timestamp
float timestamp = millis();
float timestamp_old;
float G_Dt;

void read_sensors() {
  amm_volt_read(); // Read ammeter and voltmeter
}

// Read every sensor and record a time stamp
// Init DCM with unfiltered orientation
// TODO re-init global vars?
void reset_sensor_fusion() {
  read_sensors();
  timestamp = millis();
}

void turn_output_stream_on()
{
  output_stream_on = true;
  digitalWrite(STATUS_LED_PIN, HIGH);
}

void turn_output_stream_off()
{
  output_stream_on = false;
  digitalWrite(STATUS_LED_PIN, LOW);
}

// Blocks until another byte is available on serial port
char readChar()
{
  while (Serial.available() < 1) { } // Block
  return Serial.read();
}

void setup()
{
  // Init serial output
  Serial.begin(OUTPUT__BAUD_RATE);
  
  // Init status LED
  pinMode (STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, LOW);

  // Init sensors
  delay(50);  // Give sensors enough time to start
  
  // Read sensors, init DCM algorithm
  delay(20);  // Give sensors enough time to collect data
  reset_sensor_fusion();

  // Init output
  turn_output_stream_on();

  // Initialize voltmeter and ammeter
  amp_volt_setup();

  pinMode(speedPin, INPUT); 
}

// Main loop
void loop()
{
  // Read incoming control messages
  if (Serial.available() >= 2)
  {
    if (Serial.read() == '#') // Start of new control message
    {
      int command = Serial.read(); // Commands
      if (command == 's') // _s_ynch request
      {
        // Read ID
        byte id[2];
        id[0] = readChar();
        id[1] = readChar();
        
        // Reply with synch message
        Serial.print("#SYNCH");
        Serial.write(id, 2);
        Serial.println();
      }
    }
  }

  // Count impulses for TS
//  TS_state_0 = digitalRead(speedPin);
//  if (TS_state_0 != TS_state_1) {
//    TS_state_1 = TS_state_0;
//    if (TS_state_1) {
//        //TS_out[0] = 3000 / (millis()-TS_time);
//        TS_out[0] = millis()-TS_time;
//        TS_time = millis();
//    }
//  }

  // Time to read the sensors again?
  if((millis() - timestamp) >= OUTPUT__DATA_INTERVAL)
  {
    timestamp_old = timestamp;
    timestamp = millis();
//    if (timestamp > timestamp_old)
//      G_Dt = (float) (timestamp - timestamp_old) / 1000.0f; // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
//    else G_Dt = 0;

    // Update sensor readings
    read_sensors();
    output_kinematics();
  
    output_single_on = false;
    
#if DEBUG__PRINT_LOOP_TIME == true
    Serial.print("loop time (ms) = ");
    Serial.println(millis() - timestamp);
#endif
  }
#if DEBUG__PRINT_LOOP_TIME == true
  else
  {
    Serial.println("waiting...");
  }
#endif
}


