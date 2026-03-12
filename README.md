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
- ✅ Mode DMA — `DMAprintchaine()` / `DMAreadchaine()`
- ✅ Support de USART1, USART2 et USART3 (sélection automatique selon la pin TX)
- ✅ Débit, parité, bits de stop, longueur de mot et contrôle de flux configurables
- ✅ Séparation claire entre les couches OO, Wrapper et HAL

---

## 🗂️ Structure du projet

```
├── Serial.h                   # Définition de la classe OO (namespace OOlayer)
├── Serial_Mode_Name.h         # Énumérations & définitions de types
├── stm32_wrapper_Serial.h     # Prototypes des fonctions Wrapper
├── stm32_wrapper_Serial.c     # Implémentations des fonctions Wrapper
├── stm32map.h                 # Définitions des adresses de base GPIO/RCC
├── stm32f10x_conf.h           # Configuration de la bibliothèque STM32
├── stm32f10x_it.h             # Prototypes des gestionnaires d'interruptions
└── main.cpp                   # Exemples d'utilisation & tests
```

---

## ⚙️ Mapping des pins USART (STM32F1)

Le périphérique USART est déterminé **automatiquement** par le numéro de la pin TX passée au constructeur :

| Interface | PinName TX | PinName RX | Valeur hex TX |
|-----------|------------|------------|---------------|
| USART1    | `PA_9`     | `PA_10`    | `0x09`        |
| USART2    | `PA_2`     | `PA_3`     | `0x02`        |
| USART3    | `PB_10`    | `PB_11`    | `0x1A`        |

> ⚠️ Le paramètre `UartComport` du constructeur **ne sélectionne pas** le périphérique USART ; il configure le **contrôle de flux matériel** (voir tableau ci-dessous).

---

## 📋 Référence des énumérations

### `UartSpeed` — Vitesse de communication

| Valeur         | Baud rate |
|----------------|-----------|
| `Low`          | 9 600     |
| `Medium`       | 19 200    |
| `High`         | 115 200   |
| `UartSpeedDefault` | `Low` (9 600) |

### `UartComport` — Contrôle de flux matériel

| Valeur           | Contrôle de flux HAL               |
|------------------|------------------------------------|
| `Com1`           | `USART_HardwareFlowControl_RTS`    |
| `Com2`           | `USART_HardwareFlowControl_None`   |
| `Com3`           | `USART_HardwareFlowControl_CTS`    |
| `ComportDefault` | `Com2` — aucun contrôle de flux    |

### `UartConfig` — Format de trame (WordLength / Parity / StopBits)

| Valeur       | Bits de données | Parité | Bits de stop |
|--------------|-----------------|--------|--------------|
| `C8N1`       | 8               | Aucune | 1            |
| `C8N2`       | 8               | Aucune | 2            |
| `C8E1`       | 8               | Paire  | 1            |
| `C8E2`       | 8               | Paire  | 2            |
| `C8O1`       | 8               | Impaire| 1            |
| `C8O2`       | 8               | Impaire| 2            |
| `C9N1`       | 9               | Aucune | 1            |
| `C9N2`       | 9               | Aucune | 2            |
| `C9E1`       | 9               | Paire  | 1            |
| `C9E2`       | 9               | Paire  | 2            |
| `C9O1`       | 9               | Impaire| 1            |
| `C9O2`       | 9               | Impaire| 2            |
| `ConfDefault`| `C8N1`          |        |              |

### `UartMode` — Direction de transfert

| Valeur        | Direction            |
|---------------|----------------------|
| `TXMode`      | Émission uniquement  |
| `RXMode`      | Réception uniquement |
| `TxRxMode`    | Full-duplex          |
| `ModeDefault` | `TxRxMode`           |

---

## 🚀 Démarrage rapide

### Mode Polling
```cpp
#include "Serial.h"
using namespace OOlayer;

int main() {
    // Constructeur par défaut : USART1 (PA_9/PA_10), 9600 bauds, 8N1, full-duplex, sans contrôle de flux
    Serial port = Serial();

    char msg[] = "Bonjour!";
    port.printchaine(msg, 8);        // Emission de 8 caractères (bloquant)
    char* recv = port.readchaine(8); // Réception de 8 caractères (bloquant)
    while(1) { }
}
```

### Mode Interruptions
```cpp
#include "Serial.h"
using namespace OOlayer;

int main() {
    Serial port = Serial();
    char msg[] = "Bonjour!";
    port.ITprintchaine(msg, 8);        // Configure l'IT TXE et démarre l'émission
    char* recv = port.ITreadchaine(8); // Configure l'IT RXNE et démarre la réception
    while(1) { }
}
```

### Mode DMA
```cpp
#include "Serial.h"
using namespace OOlayer;

int main() {
    Serial port = Serial();
    char msg[] = "Bonjour!";
    port.DMAprintchaine(msg, 8);        // Configure DMA1 pour l'émission et démarre le transfert
    char* recv = port.DMAreadchaine(8); // Configure DMA1 pour la réception et démarre le transfert
    while(1) { }
}
```

### Constructeur avec configuration complète (USART2 via PA_2, 115 200 bauds, 8N1, full-duplex, sans contrôle de flux)
```cpp
// PA_2 → USART2 sélectionné automatiquement ; Com2 = HardwareFlowControl_None
Serial port(Com2, PA_2, PA_3, High, C8N1, TxRxMode);
```

---

## 🔧 Surcharges des constructeurs

```cpp
// Par défaut : USART1, PA_9/PA_10, 9600 bauds, 8N1, full-duplex, sans contrôle de flux
Serial();

// Pins et port personnalisés (vitesse/config/mode par défaut)
Serial(UartComport flowCtrl, PinName TX, PinName RX);

// + Vitesse personnalisée
Serial(UartComport flowCtrl, PinName TX, PinName RX, UartSpeed speed);

// + Format de trame personnalisé
Serial(UartComport flowCtrl, PinName TX, PinName RX, UartSpeed speed, UartConfig config);

// Configuration complète
Serial(UartComport flowCtrl, PinName TX, PinName RX, UartSpeed speed, UartConfig config, UartMode mode);
```

> Le périphérique USART (USART1/2/3) est sélectionné **automatiquement** selon la valeur numérique de `PinName TX` :
> `PA_9` → USART1 | `PA_2` → USART2 | `PB_10` → USART3

---

## 📡 Méthodes publiques

| Méthode | Mode | Description |
|---------|------|-------------|
| `void printchaine(char* chaine, int length)` | Polling | Envoie `length` octets en attente active sur `TXE` |
| `char* readchaine(int length)` | Polling | Reçoit `length` octets en attente active sur `RXNE` |
| `void ITprintchaine(char* chaine, int length)` | Interruption | Envoie via l'IT `USART_IT_TXE` |
| `char* ITreadchaine(int length)` | Interruption | Reçoit via l'IT `USART_IT_RXNE` |
| `void DMAprintchaine(char* chaine, int length)` | DMA | Envoie via DMA1 (canal selon USART) |
| `char* DMAreadchaine(int length)` | DMA | Reçoit via DMA1 (canal selon USART) |
| `GPIO_TypeDef* get_GPIO()` | — | Retourne `GPIOA` pour USART1/2, `GPIOB` pour USART3 |

---

## 🔁 Canaux DMA1 utilisés

| USART  | Direction | Canal DMA1 |
|--------|-----------|------------|
| USART1 | TX        | Canal 4    |
| USART1 | RX        | Canal 5    |
| USART2 | TX        | Canal 7    |
| USART2 | RX        | Canal 6    |
| USART3 | TX        | Canal 2    |
| USART3 | RX        | Canal 3    |

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
