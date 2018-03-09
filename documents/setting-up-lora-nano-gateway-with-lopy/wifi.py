import machine
from network import WLAN
wlan = WLAN(mode=WLAN.STA)
nets = wlan.scan()
for net in nets:
    if net.ssid == 'Incubator':
        print('Network found!')
        wlan.connect(net.ssid, auth=(net.sec, 'Incubator#2013'), timeout=5000)
        while not wlan.isconnected():
            machine.idle() # save power while waiting
        print('WLAN connection succeeded!')
        break
