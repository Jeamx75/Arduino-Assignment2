// ====================================================================
// Arduino Countdown Timer with 7-Segment Display and Buzzer Alerts
// ====================================================================

// Array mapping Arduino digital pins to the segments of the display
int segmentPins[] = {2, 3, 4, 5, 6, 7, 9};

// 2D array storing the binary states (0 = OFF, 1 = ON) for digits 0 to 9
// Rows = numbers 0-9; Columns = the 7 individual segment states
byte digits[10][7] = {
    {0, 1, 1, 1, 1, 1, 1},   // Code to display '0'
    {0, 0, 0, 1, 0, 0, 1},   // Code to display '1'
    {1, 0, 1, 1, 1, 1, 0},   // Code to display '2'
    {1, 0, 1, 1, 0, 1, 1},   // Code to display '3'
    {1, 1, 0, 1, 0, 0, 1},   // Code to display '4'
    {1, 1, 1, 0, 0, 1, 1},   // Code to display '5'
    {1, 1, 1, 0, 1, 1, 1},   // Code to display '6'
    {0, 0, 1, 1, 0, 0, 1},   // Code to display '7'
    {1, 1, 1, 1, 1, 1, 1},   // Code to display '8'
    {1, 1, 1, 1, 0, 1, 1},   // Code to display '9'
};

int buzzerPin = 8; // Digital pin connected to the piezo buzzer
int numSegments = 7;

// Function to light up the correct segments for a given digit
void showDigit(int n) {
    // Safety check: if the number is out of bounds (not 0-9), exit the function
    if (n < 0 || n > 9) return;
 
    // Loop through each of the 7 pins and set it HIGH or LOW based on the digits matrix
    for (int i = 0; i < numSegments; i++) {
        digitalWrite(segmentPins[i], digits[n][i]);
    }
}
 
void setup() {
    // Initialize serial communication for tracking progress via the Serial Monitor
    Serial.begin(9600);
 
    // Configure the buzzer pin as an output
    pinMode(buzzerPin , OUTPUT);
 
    // Loop through and configure all 7 segment pins as outputs
    for (int i = 0; i < numSegments; i++) {
        pinMode(segmentPins[i], OUTPUT); 
    }
 
    Serial.println("=== Beeping Countdown Starting ===");
 
    // Initialize the countdown starting at 9
    int count = 9;
    
    // Main countdown loop running from 9 down to 0
    while (count >= 0) {
        // Print the current step to the Serial Monitor
        Serial.print("Counting: ");
        Serial.println(count);
 
        // Update the 7-segment display with the current number
        showDigit(count);
      
        tone(buzzerPin, 1000, 200);
        
        // Wait for 1 second before moving to the next number
        delay(1000);
        
        // Decrement the counter by 1
        count = count - 1;
    }

    // Call showDigit with the final value of count (which is now -1). 
    // This triggers the safety guard in showDigit() and keeps the display safe.
    showDigit(count);
    
    tone(buzzerPin, 1500, 1000);    

    Serial.println("=== Countdown Complete ===");
}

void loop(){ 
    // Left empty because the entire countdown sequence runs exactly once inside setup()
}
