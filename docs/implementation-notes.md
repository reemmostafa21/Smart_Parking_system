# Implementation notes: sketch vs. presentation

This note records differences between the Arduino sketch supplied for the repository and the 18-slide project presentation.

| Item | Supplied sketch | Presentation |
|---|---|---|
| Servo signal | D4 | D4 |
| Servo open position | 47 degrees | 47 degrees |
| Servo closed position | 142 degrees | 142 degrees |
| Gate close delay | 1,000 ms | 2,000 ms in code screenshots / flowchart annotations |
| LED outputs | D7 declared; activation block commented out | D7 and D8 shown in wiring diagram and code screenshots |
| LED duration | Not implemented in supplied sketch | 4 seconds shown in slides/code screenshots |
| Exit count upper bound | No upper bound | Screenshot code checks `Slot <= 4` before incrementing, which can still permit the count to reach 5 |
| Buzzer condition | `Slot > 4` | `Slot > 4` |

## What this means

- The supplied sketch is the source of truth for the `.ino` file in this repository until it is replaced with the exact final sketch used in the physical demonstration.
- The presentation PDF is retained as supporting project documentation. Its screenshots should not be assumed to match the repository sketch line for line.
- The presentation's buzzer behavior is described as a trespassing/abnormal-condition alarm. In the supplied sketch, the buzzer only checks whether the software counter is greater than four.
- The supplied sketch's exit path can increment the counter beyond the nominal capacity. Consider constraining the counter to the range 0–4 and adding sensor debounce / clear-state logic in a future code revision.

## Before release checklist

- [ ] Confirm the `.ino` file is the exact code running in the demo.
- [ ] Confirm whether one LED or two LED control outputs are part of the final implementation.
- [ ] Confirm the gate-open duration shown in the demo.
- [ ] Test the full-capacity condition and repeated sensor activations.
- [ ] Update the wiring table and this note after any code or wiring changes.
