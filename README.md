# 🏫 Sistema de Reserva de Aulas Universitarias

> Sistema desarrollado en **C++** para gestionar la reserva de aulas universitarias mediante estructuras de datos como **listas enlazadas** y **colas FIFO**.

---

## 📋 Descripción

Este sistema permite a los usuarios reservar aulas universitarias de forma eficiente. Cada aula tiene su propia cola de espera independiente, garantizando que las solicitudes se gestionen de manera ordenada y sin conflictos de horario.

---

## ⚙️ Funcionalidades

| Función | Descripción |
|---|---|
| 📝 **Reservar un aula** | Reserva un aula validando capacidad y disponibilidad horaria |
| 📊 **Consultar estado de aulas** | Muestra todas las aulas con su estado actual y personas en cola |
| 👤 **Ver mis reservas** | Lista todas las reservas activas del usuario |
| ❌ **Cancelar una reserva** | Cancela una reserva y asigna el aula al siguiente en cola |

---

## 🏗️ Estructuras de Datos

```
PrincipalSystem
│
├── Lista Enlazada de Aulas (infoAulas)
│   ├── nombre
│   ├── capacidad
│   ├── disponible
│   └── Cola FIFO (colas)
│       └── Nodos de Reserva (aulasReserva)
│           ├── nombreUsuario
│           ├── fecha
│           ├── hora
│           ├── duracion
│           └── asignado
```

---

## 🧠 Lógica del Sistema

```
Solicitud de reserva
        │
        ▼
¿Aula existe? ──No──► Aula no encontrada
        │
       Sí
        ▼
¿Personas ≤ Capacidad? ──No──► Capacidad insuficiente
        │
       Sí
        ▼
¿Aula disponible?
   │           │
  Sí           No
   │            │
   ▼            ▼
Asignar    ¿Conflicto de horario?
directamente    │            │
               Sí            No
                │             │
                ▼             ▼
         ¿Encolarse o    Encolar con
         ver horarios?   nuevo horario
```

---

## 🚀 Cómo ejecutar

### Requisitos
- Compilador C++ (g++ recomendado)
- Estándar C++11 o superior

### Compilación

```bash
g++ -std=c++11 main.cpp -o sistema
```

### Ejecución

```bash
./sistema
```

---

## 🗂️ Estructura del proyecto

```
📁 Parcial_1/
├── 📄 main.cpp
└── 📄 PrincipalSystem.h
```

---

## 💡 Características clave

- **Validación de conflictos horarios** — Detecta solapamiento entre reservas usando lógica de intervalos
- **Cola FIFO por aula** — Cada aula gestiona su propia lista de espera de forma independiente
- **Asignación automática** — Al cancelar una reserva, el sistema asigna el aula al siguiente en cola automáticamente
- **Búsqueda por usuario** — Permite consultar todas las reservas activas de un usuario recorriendo la estructura completa

---

## 👨‍💻 Autor

Jeronimo Jaramillo Agudelo - Estudiante de Ingenieria En Sistemas - Tercer Semestre
Desarrollado como proyecto de estructuras de datos — **2026**
