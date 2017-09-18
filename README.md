# Sesame

Access control project for my home. Check it out on [Arduino Project Hub](https://create.arduino.cc/projecthub/gibatronic/sesame-130ae7).

[![Check it out on YouTube](etc/youtube.png)](https://www.youtube.com/watch?v=wosOB2mCduo)

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
│   DENY │ │ STORE │  │  ALLOW │ │ REMOVE │
│ ACCESS │ │ CARD  │  │ ACCESS │ │ CARD   │
╰────────╯ ╰───────╯  ╰────────╯ ╰────────╯
```

## Breadboard

[![Fritzing circuit](etc/sesame-breadboard.png)](etc/sesame.fzz)
