PinDA (Pinball Direct Access) is a framework to access pinball machines (based on 68xx CPU's)

it's no game emulator. The original roms are not used.

The framework will be used to access:

    lamps
    solenoids
    switches
    roms (for diagnose only)
    ram (for diagnose only)
    (optional) sound
    (optional) display

Due to speed concerns on the arduino, the arduino is only used to interface with the IO. The rest of the controls are done on a seperate platform like raspberry pi or PC.
Targets

As this is a framework several targets are planned or optional.

    Access the pinball through the original hardware (using directIO/SPI/I2C)
    control your own hardware

Uses

    create own games
    diagnose machines

Warning

Wrong usage will break things! Turning Original inputs into outputs will create shorts, hopefully only harm fuses. Leaving coils and flashers on too long will burn or melt them with potential risk of fire!

Don't use this if you cannot repair your own pinball, or cannot afford a pinball engineer.

We are in no way responsible for any damage like breaking or burning. 