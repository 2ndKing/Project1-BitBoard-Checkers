# BitBoard Checkers — CS 3503 Project 1

**Author:** Leandro Cherulli  
**Course:** CS 3503 — Computer Organization & Architecture  
**Project Type:** Individual Programming Assignment  
**Language:** C (C11 Standard)  
**Topic:** Bitboard Game Engine / Bitwise Manipulation  

---

## Overview

This project implements a **checkers game engine** using **bitboards**, a data-representation technique where each square on an 8×8 board corresponds to one bit in a 64-bit integer.  

---

## Features

### Phase 1 — Bit Manipulation Library
Implemented in [`bitops.c`](./bitops.c) / [`bitops.h`](./bitops.h):

- `SetBit`, `ClearBit`, `ToggleBit`, `GetBit` — basic bit operations  
- `ShiftLeft`, `ShiftRight` — move bits efficiently  
- `CountBits` — count 1s in a 64-bit integer  
- `PrintBinary64` — debug bit patterns  

All functions are built **exclusively with bitwise operators**

---

### Phase 2 — BitBoard Checkers Game

Implemented in [`board.c`](./board.c) / [`game.c`](./game.c):

| Feature | Description |
|----------|-------------|
| **Bitboard Representation** | Each color has a 64-bit bitboard for normal and king pieces. |
| **Display** | Renders a full 8×8 ASCII board with coordinates A–H / 1–8. |
| **Movement** | Diagonal one-step moves, forward only for regular men. |
| **Captures** | Two-step diagonal jumps automatically remove the opponent’s piece. |
| **Promotion** | Red pieces become kings at row 8; black pieces at row 1. |
| **Scoring** | Uses bit counting (`CountBits`) to track live scores. |
| **Win Detection** | Declares a winner when one side has no pieces left. |

---

## Files

- bitops.c / bitops.h
- board.c  / board.h      
- game.c   / game.h  
- main.c   
- CMakeLists.txt
- README.md

---

## Gameplay Instructions

The board prints after every turn.  
Enter moves as two numbers **(0–63)** separated by a space:  
**Example:** RED’s move (enter from and to positions 0–63): 41 50  

Bit 0 = A1 (bottom-left)  
Bit 63 = H8 (top-right)  
Red starts from the bottom and moves up; black starts from the top and moves down.  
The score updates automatically.  
 
--

## Notes

The board uses bit indexing from 0 (A1) at the bottom-left to 63 (H8) at the top-right.  
Only dark squares are used for piece placement and movement.  
All board operations (move, capture, scoring, promotion) are implemented using bitwise operators only.  
Scoring is calculated from live board state; no counters are incremented manually.  
This project avoids all arrays and dynamic memory, relying purely on 64-bit integers for efficiency.  
Designed, implemented, and tested on macOS ARM64 using Clang and CMake.  
Compatible with Linux and Windows using GCC or Clang.  
