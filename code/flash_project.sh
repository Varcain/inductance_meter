#!/bin/sh
IMAGE_PATH=out/main.elf
IMAGE_ADDR="0x00000000"
openocd \
	-f board/stm32vldiscovery.cfg \
	-c "init" \
	-c "reset init" \
	-c "flash probe 0" \
	-c "flash write_image erase $IMAGE_PATH $IMAGE_ADDR" \
	-c "reset run" -c shutdown
