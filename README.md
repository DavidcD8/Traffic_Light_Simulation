# Traffic Light Simulation in C++

This project simulates a simple traffic light system using C++ classes and state transitions. It was created as part of my learning journey into embedded systems and C++ programming.

## Features

- Simulates a traffic light with Red, Green, and Yellow LEDs
- Uses enums to represent states
- Uses delays to simulate real-time transitions
- Organized code with object-oriented principles

## Why This Project?

I built this project with the help of ChatGPT as a step-by-step guide to better understand how real embedded systems might control components like LEDs. Every part of the code was explained to me and modified so I could fully understand how it works.

## Structure

- `TrafficLightState` enum: Defines RED, GREEN, and YELLOW states.
- `OutputPin` class: Simulates an LED with `turnOn()` and `turnOff()` methods.
- `TrafficLightController` class: Manages transitions between states.
- `main()` function: Runs the simulation for a fixed number of cycles.

## Example Output

```
Red light is ON
Red light is OFF
Green light is ON
Green light is OFF
Yellow light is ON
Yellow light is OFF
...
```

## Notes

- This simulation runs on a standard C++ environment (no hardware required).
- Built as a stepping stone towards understanding embedded programming.

## License

This is a learning project. Feel free to use or adapt it for educational purposes.