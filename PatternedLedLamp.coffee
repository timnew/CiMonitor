LedLamp = require('./LedLamp')

class PatternedLedLamp extends LedLamp
  constructor: (portName, pattern) ->
    super(portName)
    if pattern?
      @applyPattern(pattern)
    
  applyPattern: (pattern, options) ->
    if typeof(pattern) is 'function'
      pattern = new pattern(this, options)
      
    @clearPattern() if @currentPattern?
    @currentPattern = pattern
    pattern.start()
  
  clearPattern: ->
    @currentPattern.stop() if @currentPattern?
    @currentPattern = null
  
PatternedLedLamp.findOrSetByName = (portName, callback) ->
  if portName?
    try
      led = new PatternedLedLamp(portName)
      callback(null, led)
    catch ex
      callback(ex)
  else
    LedLamp.findUsbPort (err, port) ->
      if err?
        return callback(err)
        
      try
        led = new PatternedLedLamp(port.comName)
        callback(null, led)
      catch ex
        callback(ex)
  
exports = module.exports = PatternedLedLamp