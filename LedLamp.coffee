_ = require('lodash')
serialport = require('serialport')
colorConvert = require('color-convert')

EventEmitter = require('events').EventEmitter

class LedLamp extends EventEmitter
  constructor: (portName) ->
    @port = new serialport.SerialPort portName

    parseData = (data) =>
      if data.length >= 2 and data[0..1] == 'AT'
        @emit 'command', data
      else if data.trim() == 'CT+Ready'
        @emit 'ready', this
      else
        @emit 'data', data

    buffer = ''      
    @port.on 'data', (data) ->
      buffer += data.toString('ascii')
      if buffer[buffer.length - 2] == '\r' and buffer[buffer.length - 1] == '\n'
        parseData(buffer)
        buffer = ''

    @port.on 'error', (error) =>
      @emit 'error', error
  
  ready: (callback) ->
    @once 'ready', callback
    
  close: ->
    @port.close()

  setColorRGB: (rgb) ->
    @port.write new Buffer(rgb)
  
  setColorHSL: (h, s, l) ->
    rgb = colorConvert['hsl']['rgb']([h, s, l])
    @setColorRGB rgb
    
  setColorHSV: (h, s, v) ->
    rgb = colorConvert['hsv']['rgb']([h, s, v])
    @setColorRGB rgb
    
ClassMethods = 
  findUsbPort: (callback) ->
    serialport.list (err, results) ->
      if err?
        console.error err
        return callback(err);

      port = _.find results, (currentPort) ->
        currentPort.manufacturer == 'Arduino (www.arduino.cc)'

      return callback("No Arudio Found") unless port?  

      callback(null, port)
  
_.extend LedLamp, ClassMethods  
  
exports = module.exports = LedLamp
    
  
