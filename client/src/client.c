#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger,"Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");

	// Loggeamos el valor de config

	log_info(logger,"Los valores leidos del config son: Clave: %s, IP: %s y PUERTO: %s",valor,ip,puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);		 // creación del socket de conexión

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log","LOGGER_TP0",1,LOG_LEVEL_INFO);
	if (nuevo_logger == NULL) {
		printf("¡No se pudo crear el logger!");
		exit(EXIT_FAILURE);  // Terminemos el programa en caso de que no se pueda crear el logger
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");
	if (nuevo_config == NULL) {
		printf("¡No se pudo crear el config!");
		exit(EXIT_FAILURE);  // Terminemos el programa en caso de que no se pueda crear el config
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	while (strcmp(leido,"") != 0){
		log_info(logger,">> %s",leido);
		free(leido);                     // Libera la memoria usada antes de registrar una linea nueva
		leido = readline("> ");
	}

	// ¡No te olvides de liberar las lineas antes de regresar!

	free(leido);   // Libera la memoria usada en caso de que nunca entre al while
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	
	log_destroy(logger);
	config_destroy(config);
}
