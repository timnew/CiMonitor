_ = require('lodash')
serialport = require('serialport')
colorConvert = require('color-convert')

EventEmitter = require('events').EventEmitter

class LedLamp extends EventEmitter
  constructor: (@portName) ->
    @port = new serialport.SerialPort @portName

    parseData = (data) =>
      @emit 'data', data
      
      if data.length >= 2 and data[0..1] == 'AT' # TODO replace with regex
        @emit 'command', data
      else if data.trim() == 'LED+Ready'
        @emit 'ready', this
      else if data.length >= 10? and data[0..9] == 'LED+Color='
        components = /LED\+Color=\[(\d+),(\d+),(\d+)\]/.exec(data)
        
        @emit 'colorChanged', [parseInt(components[1], 10), parseInt(components[2], 10), parseInt(components[3], 10)]
      else
        @emit 'unknownData', data

    buffer = ''      
    @port.on 'data', (data) ->
      buffer += data.toString('ascii')
      if buffer[buffer.length - 2] == '\r' and buffer[buffer.length - 1] == '\n'
        parseData(buffer)
        buffer = ''

    @port.on 'error', (error) =>
      @emit 'error', error

  ready: (callback) ->
    pingToken = null;
    
    ping = =>
      @sendCommand "LED+Connect"
      pingToken = setTimeout(ping, 500);
    
    @once 'ready', callback
    @once 'ready', ->
      clearTimeout(pingToken) if pingToken?

    ping();
  
  sendCommand: (command) ->
    @port.write command
    @port.write ";"

  sendRaw: (rawData) ->
    @port.write rawData 
    
  close: ->
    @port.close()

  setColorRGB: (rgb) ->
    @sendCommand "LED+Color"
    @sendRaw rgb
  
  setColorHSL: (hsl) ->
    rgb = colorConvert['hsl']['rgb'](hsl)
    @setColorRGB rgb
    
  setColorHSV: (hsv) ->
    rgb = colorConvert['hsv']['rgb'](hsv)
    @setColorRGB rgb
    
  setColorKeyword: (keyword) ->
    rgb = colorConvert['keyword']['rgb'](keyword)
    @setColorRGB rgb
  
  turnOff: ->
    @setColorRGB [0, 0, 0]
    
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
      
  findOrSetByName: (portName, callback) ->
    if portName?
      try
        led = new LedLamp(portName)
        callback(null, led)
      catch ex
        callback(ex)
    else
      LedLamp.findUsbPort (err, port) ->
        if err?
          return callback(err)
          
        try
          led = new LedLamp(port.comName)
          callback(null, led)
        catch ex
          callback(ex)
  
_.extend LedLamp, ClassMethods  
  
exports = module.exports = LedLamp
    
  
