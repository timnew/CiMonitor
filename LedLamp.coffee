_ = require('lodash')
serialport = require('serialport')
colorConvert = require('color-convert')

class LedLamp
  constructor: (portName) ->
    @port = new serialport.SerialPort portName

    @port.on 'data', @onData

    @port.on 'error', @onError

  onData: (data) =>
    process.stdout.write data
    
  onError: (error) =>
    process.stderr.write data
  
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
    
  
