# Sesame

Access control project for my home.

## Components

* Arduino Leonardo
* MFRC522 based RFID module
* Solid-state relay module
* Electric strike
* RGB LED module

## Flow

```
                            ╔═══════════╗
                            ║ CARD READ ║
                            ╚═════╤═════╝
                       yes ╭┄┄┄┄┄┄┴┄┄┄┄┄┄╮ no
               ╭───────────┤ ADMIN MODE? ├──────╮
               │           ╰┄┄┄┄┄┄┄┄┄┄┄┄┄╯      │
        ╭┄┄┄┄┄┄┴┄╮                            ╭┄┴┄┄┄┄┄┄╮
    yes │ MASTER │ no                     yes │ MASTER │ no
  ╭─────┤ CARD?  ├─────╮                ╭─────┤ CARD?  ├─────╮
  │     ╰┄┄┄┄┄┄┄┄╯     │                │     ╰┄┄┄┄┄┄┄┄╯     │
╭─┴─────╮          ╭┄┄┄┴┄┄┄╮          ╭─┴─────╮          ╭┄┄┄┴┄┄┄╮
│ ADMIN │      yes │ KNOWN │ no       │ ADMIN │      yes │ KNOWN │ no
│ MODE  │    ╭─────┤ CARD? ├─────╮    │ MODE  │    ╭─────┤ CARD? ├─────╮
│ OFF   │    │     ╰┄┄┄┄┄┄┄╯     │    │ ON    │    │     ╰┄┄┄┄┄┄┄╯     │
╰───────╯  ╭─┴──────╮      ╭─────┴─╮  ╰───────╯  ╭─┴──────╮     ╭──────┴─╮
           │ DELETE │      │ STORE │             │ ALLOW  │     │ DENY   │
           ╰────────╯      ╰───────╯             │ ACCESS │     │ ACCESS │
                                                 ╰────────╯     ╰────────╯
```
