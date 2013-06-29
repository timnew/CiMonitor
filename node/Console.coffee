#!/usr/bin/env coffee
coffee = require('coffee-script')

readline = require('readline')

class Console
  commands: {}

  context: {}

  prompt: []

  parseInput: (input) ->
    args = input.split /[\s\n]+/
    cmd = args.shift()

    [cmd, args]

  interpret: (input, callback) ->
    [cmd, args] = @parseInput(input)

    return callback(null, undefined) if cmd == ''

    if @commands[cmd]?
      @commands[cmd](@context, args, callback)
    else
      callback("Unknown command: #{cmd}")

  converters:
    int: (value) ->
      parseInt(value, 10)
    float: (value) ->
      parseFloat(value)
    number: (value) ->
      Number(value)
    bool: (value) ->
      Boolean(value)
    json: (value) ->
      JSON.parse(value)
    base64: (value) ->
      new Buffer(value, 'base64')
    hex: (value) ->
      new Buffer(value, 'hex')

  convertArgs: (argDefs, args) ->
    for index in [0..args.length - 1]
      converter = @converters[argDefs[index]]
      if converter?
        converter(args[index])
      else
        args[index]

  newArgConverter: (name, converter) ->
    @converters[name] = converter

  addSyncCmd: (cmd, argDefs, action) ->
    wrapper = (context, rawArgs, callback) =>
      try
        args = @convertArgs(argDefs, rawArgs)
        result = action.apply(context, args)
        callback(null, result)
      catch ex
        callback(ex)

    @commands[cmd] = wrapper

  addAsyncCmd = (cmd, argDefs, action) ->
    wrapper = (context, rawArgs, callback) =>
      try
        args = @convertArgs(argDefs, rawArgs)
        args.unshift(callback)
        action.apply(context, args)
      catch ex
        callback(ex)

    @commands[cmd] = wrapper

  start: (welcomeMessage = new Date()) ->
    @interface = readline.createInterface
      input: process.stdin
      output: process.stdout
      completer: @completer

    @interface.on 'line', @onLine
    @interface.on 'close', @onClose

    @writeOutput(null, welcomeMessage)

  writeOutput: (err, output) =>
    if err?
      console.log("ERROR: #{err}")
    else
      console.log(output) unless output == undefined

    @interface.resume()
    @interface.prompt()

  onLine: (input) =>
    @interface.pause()
    @interpret(input.trim(), @writeOutput)

  onClose: =>
    process.exit()

  completer: (input) =>
    [cmd, args] = @parseInput(input)

    hits = Object.keys(@commands).filter (command) ->
      command.indexOf(cmd) == 0

    [hits, input]

exports = module.exports = new Console()
exports.Console = Console

