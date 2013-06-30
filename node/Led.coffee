serialport = require('serialport')
EventEmitter = require('events').EventEmitter

class CommandParser
  constructor: (@led) ->
    @buffer = new Buffer()

  onData: (data) ->
    @buffer = Buffer.concat(@buffer, new Buffer(data))
    @parseDataLoop()

  parseDataLoop: ->
    while (length = @buffer.readUInt16BE(0)) <= @buffer.length
      dataBuffer = @buffer.slice 2, length
      @parseData(dataBuffer.toString())
      @buffer = @buffer.slice 2 + length

  parseData: (json) ->
    response = JSON.parse(json)
    @led.emit response.type, response.data

class Led extends EventEmitter
  consturctor: (@portName) ->

  start: ->
    @port = new serialport.SerialPort @portName

    @parser = new CommandParser(this)

    @port.on 'data', @parser.onData

    @port.on 'error', (error) =>
      @emit 'error', error



