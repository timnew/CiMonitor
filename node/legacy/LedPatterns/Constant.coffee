class Constant 
  constructor: (@led, options) ->
    @color = options.color
  start: ->
    @led.setColorRGB(@color)
  stop: ->
    # Do Nothing

exports = module.exports = Constant