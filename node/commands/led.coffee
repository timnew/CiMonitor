Led = require('../legacy/LedLamp')
console = require('../Console')

console.setup ->
  @asyncCmd 'connect', ['string'], (callback, portName) ->
    Led.findOrSetByName portName, (err, led) ->
      return callback(err) if err?
      led.ready ->
        console.context.led = led
        console.pushPrompt(led.portName)

        callback(null, "LED connected")
