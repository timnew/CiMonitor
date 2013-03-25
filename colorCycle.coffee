LedLamp = require './LedLamp'

LedLamp.findUsbPort (err, port) ->
  if err?
    console.error err
    return process.exit(1)
  
  led = new LedLamp(port.comName)
  
  h = 0;
  s = 100;
  v = 100;
  
  updateColor = ->
    h = (h + 10) % 360
    led.setColorHSV(h, s, v)
  
  setInterval updateColor, 100