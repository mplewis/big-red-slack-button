platformio run
esptool --port /dev/cu.wchusbserial142* --baud 230400 write_flash -fs 32m -ff 80m 0x0000 .pioenvs/esp12e/firmware.bin
