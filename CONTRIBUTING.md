# Sesame

Feel free to colaborate on this project by opening an issue to discus the changes.

## Hacking

Every configuration used during build and upload can be found here: [tsk/env](tsk/env).

### Requirements

* Microcontroller with [EEPROM](https://www.arduino.cc/en/Reference/EEPROM).
* Unix-like system

### Setup

After cloning the repository, run the following command:

```
make setup
```

It's going to initialize the project's submodules.
<br>
After that, you'll be able to list all available tasks with:

```
make help
```

### Running

To build the project, run the following command:

```
make build
```

Then, upload the binary to the board with:

```
make upload
```
