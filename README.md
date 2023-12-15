
# Sistema de Gerenciamento de Estacionamento Inteligente

## Introdução e Ideia do Projeto
O objetivo deste projeto é desenvolver um sistema inteligente de gerenciamento de estacionamento que utiliza tecnologia de sensores para monitorar a ocupação de vagas de estacionamento. Utilizando um Arduino Uno como plataforma de hardware e o sistema operacional em tempo real ChibiOS, o sistema é capaz de indicar se uma vaga está ocupada ou livre por meio de um LED e fornecer informações de distância via comunicação serial.

## Componentes
- **Arduino Uno**: Serve como o microcontrolador central do sistema.
- **Sensor Ultrassônico HC-SR04**: Usado para medir a distância e detectar a presença de um veículo na vaga.
- **LED**: Fornece indicação visual do estado da vaga (ocupada ou livre).
- **Resistores**: Para proteção e controle de corrente para o LED.

## Funcionalidades do Sistema
- **Medição de Distância**:  O sensor ultrassônico mede a distância até o objeto mais próximo (neste caso, um carro). Se a distância medida for inferior a um limite pré-definido (por exemplo, 10 cm), o sistema interpreta que a vaga está ocupada.
- **Indicação Visual**: Um LED é usado para fornecer uma indicação visual do estado da vaga. Se a vaga estiver ocupada (distância menor que o limite), o LED acende.
- **Comunicação de Dados**: O sistema envia a distância medida em tempo real para um terminal serial, permitindo o monitoramento da ocupação das vagas.

## Programação com ChibiOS
- **ChibiOS**: Um sistema operacional em tempo real (RTOS) que facilita a execução de várias tarefas (threads) simultaneamente e de forma eficiente.
- **Tarefas Implementadas**:
  - **SensorTask**: Monitora continuamente a distância medida pelo sensor ultrassônico.
  - **LEDTask**:  Controla o estado do LED com base na informação da distância medida.
  - **CommTask**: Envia dados de distância para um terminal serial para monitoramento.

## Sincronização e Segurança de Dados
- **Mutex**: Um mecanismo de sincronização (mutex) é utilizado para garantir que o acesso à variável compartilhada `distancia` seja feito de forma segura, evitando conflitos ou condições de corrida entre as diferentes tarefas.

## Simulação no Proteus
- **Propósito da Simulação:** Antes da implementação física, o sistema foi simulado no Proteus para validar o funcionamento e a lógica do projeto.
- **Componentes no Proteus:** O Arduino Uno, o sensor ultrassônico HC-SR04 e o LED foram simulados no Proteus, replicando o comportamento do sistema real.
- **Testes e Ajustes:** A simulação permitiu testar diferentes cenários, como a presença e ausência de veículos nas vagas, e ajustar o código conforme necessário.

## Conclusão
Este projeto de Sistema de Gerenciamento de Estacionamento Inteligente demonstra a aplicação prática de sistemas operacionais em tempo real na automação e monitoramento de tarefas. O uso do ChibiOS no Arduino Uno oferece uma solução eficiente e de baixo custo para o gerenciamento de estacionamentos, com potencial para expansão e adaptação a sistemas mais complexos e abrangentes.
