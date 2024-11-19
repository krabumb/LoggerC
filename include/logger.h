#ifndef LOGGER_C_LOGGER_H
#define LOGGER_C_LOGGER_H

/**
 * Chaque define permet ici d'obtenir la couleur associée
 */
#define RED       "\x1B[31m"
#define GREEN     "\x1B[32m"
#define YELLOW    "\x1B[33m"
#define BLUE      "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN      "\x1B[36m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1B[0m"


/**
 * Chaque define permet ici d'obtenir le code de la card
 */
#define INFO      1
#define WARNING   2
#define ERROR     3
#define EXCEPTION 4

/**
 * Cette fonction permet d'afficher un log sous forme d'information
 * @param string_to_print
 * @param ...
 */
void logger_info(const char *string_to_print, ...);

/**
 * Cette fonction permet d'afficher un log sous forme de warning
 * @param string_to_print
 * @param ...
 */
void logger_warning(const char *string_to_print, ...);

/**
 * Cette fonction permet d'afficher un log sous forme d'erreur
 * @param string_to_print
 * @param ...
 */
void logger_error(const char *string_to_print, ...);

/**
 * Cette fonction permet d'afficher un log sous forme d'exception\n
 * Cette fonction va automatiquement arrêter le programme avec exit(error_code)
 * @param string_to_print
 * @param ...
 */
void logger_exception(const char *string_to_print, int error_code, ...);

#endif
