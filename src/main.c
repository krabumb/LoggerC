#include "../include/logger.h"

int main() {
	logger_info("%s", "Info World !");
	logger_warning("%s", "Warning World !");
	logger_error("%s", "Error World !");
	return 0;
}
