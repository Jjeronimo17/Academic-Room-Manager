
---

# 🏫 University Classroom Reservation System

> System developed in **C++** to manage classroom reservations using data structures such as **linked lists** and **FIFO queues**.

---

## 📋 Description

This system allows users to efficiently reserve university classrooms. Each classroom has its own independent waiting queue, ensuring that reservation requests are handled in an orderly manner and without scheduling conflicts.

---

## ⚙️ Features

| Function                      | Description                                                               |
| ----------------------------- | ------------------------------------------------------------------------- |
| 📝 **Reserve a classroom**    | Reserves a classroom while validating capacity and time availability      |
| 📊 **Check classroom status** | Displays all classrooms with their current status and waiting queues      |
| 👤 **View my reservations**   | Lists all active reservations for a specific user                         |
| ❌ **Cancel a reservation**    | Cancels a reservation and assigns the classroom to the next user in queue |

---

## 🏗️ Data Structures

```
PrincipalSystem
│
├── Linked List of Classrooms (infoAulas)
│   ├── name
│   ├── capacity
│   ├── availability
│   └── FIFO Queue (colas)
│       └── Reservation Nodes (aulasReserva)
│           ├── userName
│           ├── date
│           ├── time
│           ├── duration
│           └── assigned
```

---

## 🧠 System Logic

```
Reservation request
        │
        ▼
Does classroom exist? ──No──► Classroom not found
        │
       Yes
        ▼
People ≤ Capacity? ──No──► Insufficient capacity
        │
       Yes
        ▼
Is classroom available?
   │           │
  Yes          No
   │            │
   ▼            ▼
Assign       Schedule conflict?
directly         │            │
                Yes           No
                 │             │
                 ▼             ▼
         Join queue or     Enqueue with
         check schedules   new schedule
```

---

## 🚀 How to Run

### Requirements

* C++ compiler (g++ recommended)
* C++11 standard or higher

### Compilation

```bash
g++ -std=c++11 main.cpp -o system
```

### Execution

```bash
./system
```

---

## 🗂️ Project Structure

```
📁 Parcial_1/
├── 📄 main.cpp
└── 📄 PrincipalSystem.h
```

---

## 💡 Key Features

* **Schedule conflict validation** — Detects overlapping reservations using interval logic
* **FIFO queue per classroom** — Each classroom manages its own waiting list independently
* **Automatic assignment** — When a reservation is canceled, the system assigns the classroom to the next user in queue
* **User-based search** — Allows querying all active reservations by traversing the entire structure

---

## 👨‍💻 Author

**Jeronimo Jaramillo Agudelo**
Systems Engineering Student — Third Semester

Developed as a **Data Structures project — 2026**

---
