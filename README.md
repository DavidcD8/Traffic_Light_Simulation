# Traffic Light Simulation in C++

This project simulates a simple traffic light controller using C++.  
It demonstrates key programming concepts such as:

- **State management** with an enum-based finite state machine (RED, GREEN, YELLOW)
- **Multithreading** for non-blocking user input detection using `std::thread`
- **Atomic flags** for safe communication between threads
- **Asynchronous input handling** to simulate a pedestrian button press without freezing the program

## Features

- Red light waits up to 8 seconds for a pedestrian to press Enter (simulating a crossing request).
- If the button is pressed, the red light extends for 5 extra seconds to allow pedestrian crossing.
- Light transitions are printed to the console for easy visualization.
- Pedestrian button press can be simulated manually via code or interactively by pressing Enter.

## Credits

- **Concept & design of the `TrafficLightController` and state machine:** by David (project author)  
- **AI-assisted implementation** of pedestrian button logic using threads and atomic flags for non-blocking input handling: ChatGPT (OpenAI)

Together, this creates an educational example of concurrency, input handling, and state management in C++.

## How to run

Compile with a C++11 (or later) compatible compiler:

```bash
g++ -std=c++11 traffic_light.cpp -o traffic_light -pthread
./traffic_light
