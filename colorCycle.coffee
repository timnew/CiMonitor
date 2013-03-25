LedLamp = require('./LedLamp')

LedLamp.findUsbPort (err, port) ->
  if err?
    console.error err
    return process.exit(1)
  
  console.log "Led is found on port #{port.comName}"
  
  new LedLamp(port.comName).ready (led) ->
    console.log "LED is Ready"
    h = 0;
    s = 100;
    v = 100;

    updateColor = ->
      h = (h + 1) % 360
      led.setColorHSV(h, s, v)
      process.stdout.write "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
      process.stdout.write "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
      process.stdout.write "Color(HSV): [#{h}, #{s}, #{v}]"

    setInterval updateColor, 10