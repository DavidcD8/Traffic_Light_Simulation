#include <iostream> // For printing output to console using std::cout
#include <thread>   // For using std::this_thread::sleep_for
#include <chrono>   // For defining time durations like seconds

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

    // Keep track of current state
    TrafficLightState state;

public:
    // Constructor: starts in RED state
    TrafficLightController() : state(TrafficLightState::RED) {}

    void nextState()
    {
        // Turn off all lights before changing
        red.turnOff();
        yellow.turnOff();
        green.turnOff();

        // Switch logic based on current state
        switch (state)
        {
        case TrafficLightState::RED:
            red.turnOn();                                          // Turn on red
            std::this_thread::sleep_for(std::chrono::seconds(60)); // Wait 3 seconds
            state = TrafficLightState::GREEN;                      // Next state is GREEN
            break;

        case TrafficLightState::GREEN:
            green.turnOn();                                        // Turn on green
            std::this_thread::sleep_for(std::chrono::seconds(60)); // Wait 3 seconds
            state = TrafficLightState::YELLOW;                     // Next state is YELLOW
            break;

        case TrafficLightState::YELLOW:
            yellow.turnOn();                                       // Turn on yellow
            std::this_thread::sleep_for(std::chrono::seconds(60)); // Wait 1 second
            state = TrafficLightState::RED;                        // Loop back to RED
            break;
        }
    }
    void run(int cycles)
    {
        for (int i = 0; i < cycles; ++i)
        {
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