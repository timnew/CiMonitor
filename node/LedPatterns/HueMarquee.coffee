class HueMarquee
  constructor: (@led, options) ->
    @hue = options.hue ? options.h ? 0
    @saturation = options.saturation ? options.s ? 100
    @value = options.value ? options.v ? 100
    @step = options.step ? 10
    @stepDuration = options.stepDuration ? (@step * 10)
  
  stepColor: =>  
    @hue = (@hue + @step) % 360
    @led.setColorHSV [@hue, @saturation, @value]
    
  start: ->
    @stop() if @token?
    @led.setColorHSV [@hue, @saturation, @value]
    @token = setInterval @stepColor, @stepDuration
    
  stop: ->
    @led.turnOff()
    return unless @token?
    clearInterval @token
    @token = null

exports = module.exports = HueMarquee