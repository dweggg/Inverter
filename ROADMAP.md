# Roadmap del inverter propio de e-Tech

## Septiembre 2024
### Objetivo 1: Inicio [HW/SW]
- [X] Tener el hardware existente en el taller
- [ ] Forkear repo a e-Tech y clonar en locales
- [ ] Aprender sobre control, firmware y hardware en líneas generales
- [ ] Que quien haga el hardware tenga unos mínimos de firmware/control: cuando haga pruebas de hardware debe ser capaz de controlar el inverter desde el debugger de ST
- [ ] Que quien haga el firmware haga también el control y tenga unos mínimos de hardware: para no liarla debe ser consciente del setup y limitaciones físicas
- [ ] Saber sacarle los parámetros a un motor rápido rápido

### Objetivo 2: Puesta en marcha [HW/SW]
- [ ] Repetir algún ensayo de los que aparecen en la memoria
- [ ] Hacer un open loop (V/f) con los motores que tenéis o con los antiguos
- [ ] Implementar trips / otros errores que me haya dejado

### Objetivo 3: Aprovisionamiento [HW]
- [ ] Comparar pérdidas de los dos semiconductores (casi seguro que os quedaréis con los de Wolfspeed, pero haced la comparación bien hecha)
- [ ] Conseguir semiconductores (hablad con Angelo Sgura de Wolfspeed)
- [ ] Conseguir más film caps de DC-link y fuentes de drivers (hablad con Mireia de Murata)
- [ ] Conseguir drivers/LDOs (hablad con Marcos de Texas Instruments)
- [ ] Conseguir micros (unos cuantos F7s para prevenir desastres y mirar otros micros como alternativa, idealmente más baratos y más rápidos)
- [ ] Hablar fabricación y montaje de las placas con varios fabricantes a ver si os sale todo gratis


## Octubre - Noviembre 2024
### Objetivo 3: Lectura del encoder incremental [SW]
- [ ] Implementar algoritmo cedido por CITCEA-UPC para la lectura del encoder incremental (pedir simulación y ENCODER.c/.h)
- [ ] Mejorar el algoritmo para la adquisición de la posición en el instante inicial
- [ ] Aplicar corrección de la dirección (si gira el motor al revés pues le giras el signo de la consigna)
- [ ] Añadir errores de lectura del encoder

### Objetivo 4: Cerrar lazo de corriente (carga RL) [HW/SW]
- [ ] Mejorar el bus de 5V del hardware existente, asegurando una buena referencia para los sensores de corriente. Hacer los apaños necesarios para que la medida sea muy muy buena
- [ ] Verificar el orden del lazo de control (medida, en el EOC se calcula la consigna y en el segundo underflow se conmuta)
- [ ] Preparar varias opciones para la lectura de corriente
- [ ] Verificar escalados, signos y offsets con corriente DC (una sola rama por ejemplo)
- [ ] Verificar la medida en open loop con una carga trifásica RL (consignas una tensión vq, y mides corriente con scope (verificas con cálculos o simulación), y luego miras las corrientes id e iq que mides y que cuadre todo)  
- [ ] Cerrar el lazo de corriente consignando iq positiva y negativa, e id = 0

### Objetivo 5: Iteración del hardware (SCH) [HW]
- [ ] Revisar los valores de componentes y mejoras propuestas en la memoria
- [ ] Hacer símbolos / footprints de aquellos componentes nuevos que haya que meter
- [ ] Mejorar mucho el bus de 5V usando un DCDC de unos 20W de 20/30V a 5.5V o así y luego recortar y filtrar muy bien usando LDO de 5.5V a 5V + filtro Pi o similar. Medir el rizado y minimizarlo todo lo posible
- [ ] Añadir un front-end de alta impedancia (aunque sea un ampli seguidor) a las medidas de corriente
- [ ] Mirar un ampli diferencial bueno bonito y barato para la medida de tensión con el ISO224 que iba muy bien
- [ ] Diseñarle una coldplate y una caja que se integre bien con el coche (esto se lo puedes rular a algún mecánico pero estando encima todo el rato, que te la lían)


## Diciembre 2024
### Objetivo 6: Iteración del hardware (PCB) [HW]
- [ ] Hacer el layout y enrutado de las cosas nuevas
- [ ] Generar archivos de fabricación y mandar a fabricar
- [ ] Release de las PCBs con changelog, hacedlo en el instante en el que se manden a fabricar


### Objetivo 7: Lectura de posición verificada (open loop con motor) [SW]
- [ ] Girar un motor en open loop y leer la posición con el encoder, verificando unidades y tal

### Objetivo 8: Cerrar lazo de corriente con motor [SW]
- [ ] Mirar el tema de la arrancada pre-Z (hasta que no tengas un pulso de Z no sabes la posición del rotor)
- [ ] Verificar en lazo cerrado de corriente consignando iq positiva (giro antihorario) y negativa (giro horario)


## Enero - Febrero 2025
### Objetivo 9: CAN + control [SW]
- [ ] Verificar COBIDs / frames con el database
- [ ] Implementar MTPA rápido para pasar de Torque a id-iq
- [ ] Consignas de par + enableSW por CAN
- [ ] Enviar todo con las unidades guays
- [ ] Comprobar que va con Left y Right (hasta ahora con una sola placa de potencia buena te debería bastar)

### Objetivo 10: Assembly / validación inicial [HW]
- [ ] Montar unas pocas unidades de cada placa
- [ ] Verificas rápido que todo lo que ya estaba sigue funcionando y que lo que has puesto va como toca

### Objetivo 11: Control dual [HW/SW]
- [ ] Montar setup con dos motores y control por CAN
- [ ] Consignar par a los dos motores por CAN y ver el tema de las direcciones/etc. Evaluar tiempo de ejecución

## Marzo - Julio 2025
### Objetivo 12: Preparar para competis (si os sale a cuenta, si no tirais con el Bamocar) [HW/SW]
- [ ] Montar hardware bueno y de recambio
- [ ] Puebas de fiabilidad y térmicas con cooling y tal
- [ ] Pruebas de control (verificar que el par que consignas es el que generas)
- [ ] Ir implementando (con mucho cuidadito) el lazo de tensión + trayectorias adicionales, es decir debilitamiento de campo
