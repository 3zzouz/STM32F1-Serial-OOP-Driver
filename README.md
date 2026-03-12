# 🔌 STM32F1-Serial-OOP-Driver

> Une couche d'abstraction C++ orientée objet pour la communication série USART sur microcontrôleurs STM32F1 — construite au-dessus de la bibliothèque ST HAL.

---

## 📖 Présentation

Ce projet fournit une classe `Serial` entièrement orientée objet qui simplifie la communication USART sur les microcontrôleurs STM32F103. Au lieu de manipuler directement les registres HAL, il suffit d'instancier un objet `Serial` pour envoyer ou recevoir des chaînes de caractères — avec support des modes **polling**, **interruptions** et **DMA**.

L'architecture suit une conception en trois couches bien séparées :

```
main.cpp
   └── Couche OO       → Classe Serial (Serial.h, Serial_Mode_Name.h)
         └── Couche Wrapper  → stm32_wrapper_Serial.c/.h
               └── Couche HAL      → stm32f10x_usart / gpio / rcc
                     └── MATÉRIEL
```

---

## ✨ Fonctionnalités

- ✅ Classe `Serial` orientée objet avec plusieurs surcharges de constructeurs
- ✅ Mode polling — `printchaine()` / `readchaine()`
- ✅ Mode interruptions — `ITprintchaine()` / `ITreadchaine()`
- ✅ Mode DMA — `DMAprintchaine()` / `DMAreadchaine()` *(bonus)*
- ✅ Support de USART1, USART2 et USART3
- ✅ Débit, parité, bits de stop, longueur de mot et contrôle de flux configurables
- ✅ Séparation claire entre les couches OO, Wrapper et HAL

---

## 🗂️ Structure du projet

```
├── Serial.h                   # Définition de la classe OO
├── Serial_Mode_Name.h         # Énumérations & définitions de types
├── stm32_wrapper_Serial.h     # Prototypes des fonctions Wrapper
├── stm32_wrapper_Serial.c     # Implémentations des fonctions Wrapper
└── main.cpp                   # Exemples d'utilisation & tests
```

---

## ⚙️ Mapping des pins USART (STM32F1)

| Interface | TX   | RX    |
|-----------|------|-------|
| USART1    | PA9  | PA10  |
| USART2    | PA2  | PA3   |
| USART3    | PB10 | PB11  |

---

## 🚀 Démarrage rapide

### Mode Polling
```cpp
#include "Serial.h"
using namespace OOlayer;

int main() {
    Serial port = Serial();              // Config par défaut : USART1, 9600 bauds
    port.printchaine("Bonjour!", 8);     // Transmission
    char* msg = port.readchaine(8);      // Réception de 8 caractères max
}
```

### Mode Interruptions
```cpp
Serial port = Serial();
port.ITprintchaine("Bonjour!", 8);      // Transmission non bloquante
char* msg = port.ITreadchaine(8);       // Réception non bloquante
while(1) { }
```

### Mode DMA
```cpp
Serial port = Serial();
port.DMAprintchaine("Bonjour!", 8);     // Transmission par DMA
char* msg = port.DMAreadchaine(8);      // Réception par DMA
while(1) { }
```

---

## 🔧 Surcharges des constructeurs

```cpp
Serial();                                                                      // Par défaut
Serial(UartComport, PinName TX, PinName RX);                                   // Pins personnalisées
Serial(UartComport, PinName TX, PinName RX, UartSpeed);                        // + Vitesse
Serial(UartComport, PinName TX, PinName RX, UartSpeed, UartConfig);            // + Configuration
Serial(UartComport, PinName TX, PinName RX, UartSpeed, UartConfig, UartMode);  // Config complète
```

---

## 🧪 Tests & Validation

Tous les modes de transfert ont été validés sous le **simulateur Keil µVision** avec un script `funcsim` personnalisé :

| Test | Mode | Résultat |
|------|------|----------|
| Réception de "BONJOUR" | Polling | ✅ Succès |
| Envoi de "bonjour" | Polling | ✅ Succès |
| Réception avec interruptions | Interruptions | ✅ Succès |
| Envoi avec interruptions | Interruptions | ✅ Succès |
| Réception avec DMA | DMA | ✅ Succès |
| Envoi avec DMA | DMA | ✅ Succès |

---

## 🛠️ Dépendances

- Bibliothèque standard STM32F10x (ST HAL)
- Keil MDK-ARM v5 (ou toolchain ARM compatible)
- Cible : STM32F103xx

---

## 👥 Auteurs

- Dhouibi Mohamed Aziz
- Chaabani Mayar
- Guerami Oussema
- Ghimaji Khalil

*Institut National des Sciences Appliquées et de Technologie (INSAT) — Département Mathématiques & Informatiques*
