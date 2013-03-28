class Blink
  constructor: (@led, options) ->
    @color = options.color 

    duration = options.duration ? 200
    portion = options.portion ? .5

    @onDuration = duration * portion
    @offDuration = duration - @onDuration

  turnOn: =>
    @led.setColorRGB(@color)
    @token = setTimeout @turnOff, @onDuration
    
  turnOff: =>
    @led.setColorRGB([0, 0, 0])
    @token = setTimeout @turnOn, @offDuration

  start: ->
    @stop() if @token?
    @turnOn()    
    
  stop: ->
    @led.turnOff()
    return unless @token?
    clearTimeout @token
    @token = null

exports = module.exports = Blink