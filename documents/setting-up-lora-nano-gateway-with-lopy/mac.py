import machine
import ubinascii
WIFI_MAC = ubinascii.hexlify(machine.unique_id()).upper()
print(WIFI_MAC)
