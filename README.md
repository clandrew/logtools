# logtools

This repository has some lightweight tools for altering or extracting information from CPU logs for a couple different platform debuggers.

Contents:
* **stripirq** - Operates on SNES 65816 logs. Strips out logged interrupts, e.g., IRQ and NMI.
* **DumbAndCheapDiff** - Operates on any pair of text files. Unlike many programs, won't choke on files that are 100k+ lines long.
* **TruncateTextFile** - Operates on any one, or pair of text files to a given start and end line numbers. Unlike many programs, won't choke on files that are 100k+ lines long.
* **FindDivergentPC** - Operates on Foenix 65816 logs. Reports any program counter values which are in one log and not the other, or vice versa.

Tools are for personal use, so in a lot of cases the arguments are compiled-in instead of passed by command line.
