/* Modificar este archivo para cambiar qué comandos se muestran en la statusbar, y recompilar con make. */
static const Block blocks[] = {

/*Icono*/	/*Comando*/		/*Intervalo de actualización*/	/*Señal de actualización*/
  {"",  "volume",  1,  10},
  {"",  "clock",   1,  1},
  {" ",  "internet", 5, 4},
  {"",  "cputemp", 5,  4},
};

/* separador entre bloques. NULL ('\0') significa sin separador. */
static char delim[] = "  ";
static unsigned int delimLen = 2;
