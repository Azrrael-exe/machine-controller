# Makefile para proyecto PlatformIO

# Variables
PIO = platformio
ENV = uno_r4

# Targets
.PHONY: all build upload clean monitor test

all: build

build:
	$(PIO) run -e $(ENV)

upload:
	$(PIO) run -e $(ENV) -t upload

clean:
	$(PIO) run -e $(ENV) -t clean

monitor:
	$(PIO) device monitor -e $(ENV)

test:
	$(PIO) test -e $(ENV) -v

# Combinar tareas comunes
upload-and-monitor: upload monitor

build-and-upload: build upload

# Ayuda
help:
	@echo "Uso del Makefile:"
	@echo "  make build            - Compila el proyecto"
	@echo "  make upload           - Carga el firmware al dispositivo"
	@echo "  make clean            - Limpia los archivos compilados"
	@echo "  make monitor          - Inicia el monitor serial"
	@echo "  make test             - Ejecuta las pruebas"
	@echo "  make upload-and-monitor - Carga el firmware y luego inicia el monitor"
	@echo "  make build-and-upload   - Compila y luego carga el firmware"
	@echo "  make help             - Muestra esta ayuda"