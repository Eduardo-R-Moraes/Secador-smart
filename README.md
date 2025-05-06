# Secador Inteligente com Redundância de Sensores

## 📋 Descrição do Projeto

Este projeto simula um **secador de cabelo inteligente** que utiliza dois sensores ultrassônicos HC‑SR04 para detectar a presença de um objeto (como a cabeça de uma pessoa) e controlar seu funcionamento de maneira eficiente, segura e com tolerância a falhas.

### ⚙️ Funcionamento Geral

* **Sensor primário** realiza a medição da distância.
* **Sensor secundário (redundante)** é acionado caso haja falha no primário (simulada por um botão).
* O estado do sistema é representado por **LEDs**:

  * **Verde (LED\_ON)** → sistema ligado.
  * **Vermelho (LED\_OFF)** → sistema desligado.
  * **Amarelo (LED\_REDUND)** → sensor de backup ativado.

### 🧠 Máquina de Estados (FSM)

O sistema utiliza uma FSM com quatro estados:

| Estado    | Condição de Entrada                                | Ação                                 | Consumo |
| --------- | -------------------------------------------------- | ------------------------------------ | ------- |
| `IDLE`    | Sem objeto detectado ou fora do alcance (≥ 100 cm) | LED vermelho aceso                   | 1       |
| `PARTIAL` | Objeto entre 35 cm e 100 cm                        | LEDs piscando (sinal intermitente)   | 3       |
| `TOTAL`   | Objeto a menos de 35 cm                            | LED verde aceso                      | 5       |
| `FAULT`   | Sensor primário com falha ou sem leitura válida    | LED amarelo aceso, usa sensor backup | 4       |

Além disso, o sistema imprime os dados no **monitor serial** no seguinte formato:

```
State,Consumption,RedundantOn,Distance,IsOn
```

Exemplo:

```
TOTAL,5,0,20,1
```

## 🎯 Objetivos

* Demonstrar o uso de **redundância de sensores** em sistemas embarcados.
* Controlar e otimizar o **consumo de energia** com base em distância.
* Utilizar FSM para organização de **lógica de controle**.
* Praticar montagem de circuitos e **programação em Arduino**.

## 🧰 Lista de Componentes

* 1× Arduino Uno (ou compatível)
* 2× Sensores ultrassônicos HC‑SR04
* 1× LED verde (ligado)
* 1× LED vermelho (desligado)
* 1× LED amarelo (sensor redundante ativo)
* 1× Botão de pressão (push-button)
* 2× Resistores de 220 Ω (para LEDs)
* 1× Resistor de 10 kΩ (pull-up interno usado via `INPUT_PULLUP`)
* Jumpers (fios macho‑macho)
* 1× Protoboard

> *Nota:* o botão de falha usa `INPUT_PULLUP`, portanto não precisa de resistor externo se o botão for ligado ao GND.

## 🔌 Esquema de Ligação

![Circuito](assets/Circuito.png)

### Pinos Utilizados

| Componente        | Pinos Arduino   |
| ----------------- | --------------- |
| Sensor Principal  | TRIG 3, ECHO 2  |
| Sensor Redundante | TRIG 12, ECHO 8 |
| LED Verde         | 5               |
| LED Vermelho      | 4               |
| LED Amarelo       | 7               |
| Botão de Falha    | 6               |

## FSM Finite State Machine

1. **Sem objeto próximo**: LED vermelho aceso (`IDLE`).
2. **Objeto entre 35 cm e 100 cm**: sistema entra em modo parcial, LED verde pisca (`PARTIAL`).
3. **Objeto < 35 cm**: sistema ligado totalmente, LED verde aceso (`TOTAL`).
4. **Sensor com falha ou botão pressionado**: LED amarelo aceso, ativa sensor redundante (`FAULT`).

## 🧪 Teste e Validação

1. **Sistema saudável (sem falha)**:

   * Aproxime um objeto: abaixo de 35 cm → LED verde.
   * Afastando para > 35 cm mas < 100 cm → pisca.
   * Distância ≥ 100 cm ou sem objeto → LED vermelho.

2. **Sensor com falha (botão pressionado)**:

   * LED amarelo acende.
   * Leitura feita via sensor redundante.
   * FSM se adapta conforme a distância lida pelo sensor backup.

3. **Monitor Serial**:

   * Acompanhe o comportamento da FSM e os dados de consumo/ligado.

---

**Projeto desenvolvido como atividade de aula para demonstrar redundância e controle de consumo de energia em sistemas embarcados.**