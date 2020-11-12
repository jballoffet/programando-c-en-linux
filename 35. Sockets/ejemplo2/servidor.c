/*!
 * @file   main.c
 * @brief  35. Sockets - 01. Cliente-Servidor TCP
 * @author Javier Balloffet <javier.balloffet@gmail.com>
 * @date   Nov 11, 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "sockets.h"

int main(int argc, char* argv[]) {
    int listen_socket_fd, client_socket_fd, message_size; 
    char client_ip[16];

    // Obtengo el número de puerto pasado como argumento del main.
    if (argc < 2) {
        printf("Debe ingresar el puerto como parametro.\n");
        printf("Uso: %s <PUERTO>\n", argv[0]);
        return -1;
    }

    // Creo el socket de escucha, con configuración para IPv4 y TCP.
    listen_socket_fd = abrir_socket_tcp_servidor(atoi(argv[1]));
    if (listen_socket_fd < 0) {
        printf("Error abriendo el socket: %d.\n", listen_socket_fd);
        return -1;
    }

    // Servidor corriendo esperando conexiones entrantes.
    printf("Servidor corriendo en el puerto: %d.\n", atoi(argv[1]));
    while (1) {
        // Acepto la conexión entrante.
        client_socket_fd = aceptar_conexion_entrante(listen_socket_fd, client_ip);
        if (client_socket_fd < 0) {
            printf("Error aceptando conexión entrante: %d.\n", client_socket_fd);
            return -1;
        }

        // Muestro la IP del cliente.
        printf("Se obtuvo una conexion desde la IP: %s.\n", client_ip);

        // Envío mensaje de bienvenida al cliente.
        message_size = enviar_datos_tcp(client_socket_fd, "Bienvenido! Conectado al servidor!", 34);
        if (message_size < 0) {
            printf("Error enviando datos al cliente.\n");
            return -1; 
        }

        // Cierro el socket del cliente.
        cerrar_socket_tcp(client_socket_fd);
        printf("Conexion con cliente finalizada.\n");
    }

    // Cierro el socket de escucha.
    cerrar_socket_tcp(listen_socket_fd);
    printf("Servidor finalizado.\n");

    return 0;
}
