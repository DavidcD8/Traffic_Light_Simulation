#include <iostream> // For printing output to console using std::cout
#include <thread>   // For using std::this_thread::sleep_for
#include <chrono>   // For defining time durations like seconds
#include <atomic>

std::atomic<bool> buttonPressed(false);

void waitForButtonPress() {
    std::string input;
    std::getline(std::cin, input);  // Wait for Enter
    buttonPressed = true;
}

void redLightWithButtonWait() {
    std::cout << "Red light ON. Press Enter within 8 seconds to request pedestrian crossing..." << std::endl;

    buttonPressed = false;
    std::thread inputThread(waitForButtonPress);

    // Wait up to 8 seconds or until button pressed
    for (int i = 0; i < 80; ++i) {  // 80 * 100ms = 8 seconds
        if (buttonPressed) {
            std::cout << "Pedestrian button pressed!" << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (!buttonPressed) {
        std::cout << "No pedestrian button press detected. Continuing normal cycle." << std::endl;
    } else {
        std::cout << "Pedestrians crossing... extended red light" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // crossing time
    }

    // Detach or join thread to avoid issues
    if (inputThread.joinable()) {
        // If button was pressed, inputThread finished naturally.
        // If no press, inputThread is stuck waiting — detach to avoid blocking
        if (!buttonPressed) inputThread.detach();
        else inputThread.join();
    }
}

// 🚦 Define the possible states for a traffic light
enum class TrafficLightState
{
    RED,
    GREEN,
    YELLOW
};

class OutputPin
{
    bool state;       // true = ON, false = OFF
    std::string name; // Label of the pin: "Red", "Green", or "Yellow"

public:
    // Constructor that assigns a name and sets initial state to OFF
    OutputPin(std::string label) : state(false), name(label) {}

    // Set the pin state and print its status
    void set(bool s)
    {
        state = s;
        std::cout << name << " light is " << (state ? "ON" : "OFF") << std::endl;
    }

    // Helper methods to turn the light ON and OFF
    void turnOff()
    {
        set(false);
    }

    void turnOn()
    {
        set(true);
    }
};

class TrafficLightController
{
    // We simulate 3 LEDs
    OutputPin red{"Red"};
    OutputPin yellow{"Yellow"};
    OutputPin green{"Green"};
    TrafficLightState state;    // Keep track of current state

    bool pedestrianWaiting; // flag to indicate pedestrian button pressed

public:
    // Constructor: starts in RED state
    TrafficLightController() : state(TrafficLightState::RED), pedestrianWaiting(false) {}


    // simulate pedestrian pressing the button
    void pressPedestrianButton() {
        pedestrianWaiting =true;
        std::cout << "Pedestrian button pressed!" << std::endl;
    }


    void nextState()
    {
        // Turn off all lights before changing
        red.turnOff();
        yellow.turnOff();
        green.turnOff();

        // Switch logic based on current state
        switch (state) {
            case TrafficLightState::RED:
                redLightWithButtonWait();  // Call the function
                state = TrafficLightState::GREEN;
                break;


            case TrafficLightState::GREEN:
                green.turnOn();                                        // Turn on green
                std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait 3 seconds
                state = TrafficLightState::YELLOW;                     // Next state is YELLOW
                break;

            case TrafficLightState::YELLOW:
                yellow.turnOn();                                       // Turn on yellow
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait 1 second
                state = TrafficLightState::RED;                        // Loop back to RED
                break;
            }
    }
    void run(int cycles)
    {
        for (int i = 0; i < cycles; ++i) {
            // For demo: simulate a pedestrian button press during 2nd cycle
            if (i == 1){
                pressPedestrianButton();
            }
            nextState(); // Each cycle = one light switch
        }
    }
};

int main()
{
    TrafficLightController controller;
    controller.run(6); // Run for 6 transitions (2 full red→green→yellow cycles)
    return 0;
}