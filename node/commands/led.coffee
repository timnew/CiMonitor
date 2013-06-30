Led = require('../legacy/LedLamp')
console = require('../Console')
util = require('util')
_ = require('lodash')

console.setup ->
  @asyncCmd 'connect', ['string'], (callback, portName) ->
    Led.findOrSetByName portName, (err, led) ->
      return callback(err) if err?
      led.ready ->
        console.context.led = led
        console.pushPrompt(led.portName)

        callback(null, "LED connected")

  @asyncCmd 'color', ['int', 'int', 'int'], (callback, r, g, b) ->
    led = console.context.led
    led.once 'colorChanged', (ledStatus) ->
      callback(null, "Color: #{util.inspect(ledStatus)}")

    led.setColorRGB([r, g, b])

  @asyncCmd 'off', (callback) ->
    led = console.context.led

    led.once 'colorChanged', (ledStatus) ->
      result = _.every ledStatus, (n) ->
        n == 0
      if result
        callback(null, "Turned Off")
      else
        callback("Unknown Error #{util.inspect(ledStatus)}")

    led.turnOff()
