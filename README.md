# 🍇 Vinheria Inteligente com Arduino – Monitoramento Ambiental

> Projeto de simulação na plataforma **Tinkercad** com Arduino UNO, para monitoramento em tempo real das condições ambientais de uma vinheira.  
> Inclui alertas visuais (LEDs) e sonoros (buzzer) conforme faixas ideais de temperatura, umidade e luminosidade.

---

## 📋 Descrição

Este projeto simula um sistema de **monitoramento ambiental** para uma vinheria, desenvolvido na plataforma **Tinkercad** utilizando um **Arduino UNO**.  
O objetivo é garantir a **conservação ideal dos vinhos**, monitorando:

- 🌡️ Temperatura  
- 💧 Umidade relativa do ar  
- 💡 Luminosidade  

O sistema aciona **LEDs indicadores** e um **buzzer** sempre que as variáveis ultrapassam os limites seguros.

---

## 🔧 Componentes Utilizados

| Componente                      | Função                                           |
|--------------------------------|-------------------------------------------------|
| Arduino UNO                    | Microcontrolador principal                        |
| LCD 16x2 (modo paralelo)       | Exibição das informações dos sensores            |
| Sensor de Temperatura (simulado) | Monitora a temperatura do ambiente              |
| Sensor de Umidade (simulado)   | Monitora a umidade relativa do ar                |
| Sensor de Luminosidade (LDR)   | Monitora a luz no ambiente                        |
| LEDs (vermelho, amarelo, verde)| Indicam o estado de cada variável                |
| Buzzer                         | Alerta sonoro em condições críticas              |
| Resistores e fios              | Interligação dos componentes                      |

---

## 🌡️ Parâmetros Monitorados e Regras

### ✅ Temperatura (°C)
- Ideal: **10°C a 15°C**  
- ⚠️ Fora da faixa: **LED amarelo + buzzer ativo**

### ✅ Umidade (%)
- Ideal: **50% a 70%**  
- ⚠️ Fora da faixa: **LED vermelho + buzzer ativo**

### ✅ Luminosidade (%)
- 0%–30%: Ambiente escuro → **LED verde**  
- 31%–70%: Meia luz → **LED amarelo**  
- 71%–100%: Muito claro → **LED vermelho + buzzer ativo**

---

## 🧠 Lógica do Sistema

- 📈 Leituras a cada **100 ms**, com média de **5 amostras** para suavização  
- 🔁 LCD alterna entre as variáveis a cada **3 segundos**  
- ⚠️ LEDs e buzzer acionados conforme faixas definidas  
- 💻 Código modularizado em classes
  
## 🖥️ Demonstração no Tinkercad

🔗 [Clique aqui para abrir o projeto no Tinkercad](https://www.tinkercad.com/things/kaD5Fi6HVXv-copy-of-projeto-de-automacao/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=700ikRfXQ2nDYp5AfDFZ7Q-XyQoMfPm5SJ9WXYZR7Mw)

---

## ▶️ Como Usar

- Acesse o link acima;  
- Clique em **“Iniciar Simulação”**;  
- Observe as leituras no display LCD;  
- Ajuste os sliders dos sensores para testar os alertas.

---

## 📌 Observações

- Sensores simulados via entradas analógicas.  
- Valores exibidos são aproximados.  
- Buzzer e LEDs simulam alertas reais de uma vinheria física.

---

## 🎬 Vídeo Explicativo

📹 [Assista ao vídeo explicativo no Google Drive](https://drive.google.com/file/d/1a8XfqEQcdIq232U4SVPE0qWybLqsY-iN/view?usp=drive_link)

---

## 👨‍💻 Desenvolvedores

- Atilio Almeida Costa  
- Bruno Souza da Costa  
- Gabriela Otilia Wandenkolk Monteiro  
- Leandro Felix Nunes  

---

## 🎓 Informações Acadêmicas

- Curso: Análise e Desenvolvimento de Sistemas  
- Disciplina: Introdução à Automação de Ambientes e Processos  
- Professor: Anderson Alves de Oliveira  
- Instituição: Instituto Federal de São Paulo, Campus Cubatão
- Data: Junho de 2025
