# 🦠 Stockholm 

## Descripción
Este proyecto consiste en la desarroyación de un programa malware hecho en C que afecta a sistemas basados en Linux. Ten cuidado con su
uso ya que puedes encriptar ficheros no deseados y no poder desencriptarlos. Todos los ficheros que se ven afectados por [WannaCry](https://es.wikipedia.org/wiki/WannaCry) seran encriptados mediante [AES-256](https://es.wikipedia.org/wiki/Advanced_Encryption_Standard) agregando la extension .ft a los archivos.

## Uso

◦ Para compilar el programa: gcc stockholm.c -o stockholm

◦ Cambiar el path en el fichero stockholm.c (lineas 194 && 299) para que la encriptacion y la desencriptacion se puedan hacer.
 
◦ Si quieres información sobre los comandos que debes usar para llevar a cabo la encriptacion y la desencriptacion deberas ejecutar el programa seguido de la flag -h o -help. Ejemplo-> ./stockholm -h 
