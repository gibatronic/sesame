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
                         ╭──────┴──────╮
                   ✕ ╭───┤ MASTER CARD ├───╮ ✓
                     │   ╰─────────────╯   │
                 ╭───┴───╮             ╭───┴───╮
                 │ KNOWN │             │ FLIP  │
        ✕ ╭──────┤ CARD? ├──────╮ ✓    │ ADMIN │
          │      ╰───────╯      │      │ MODE  │
      ╭───┴───╮             ╭───┴───╮  ╰───────╯
      │ ADMIN │             │ ADMIN │
  ✕ ╭─┤ MODE? ├─╮ ✓     ✕ ╭─┤ MODE? ├─╮ ✓
    │ ╰───────╯ │         │ ╰───────╯ │
╭───┴────╮ ╭────┴──╮  ╭───┴────╮ ╭────┴───╮
│   DENY │ │ STORE │  │ REMOVE │ │ ALLOW  │
│ ACCESS │ │ CARD  │  │   CARD │ │ ACCESS │
╰────────╯ ╰───────╯  ╰────────╯ ╰────────╯
```
