#!/usr/bin/env coffee
coffee = require('coffee-script')

REPLServer = require('repl').REPLServer

class Console
  commands: {}

  context: {}

  interpret: (input, _, filename, callback) ->
    # remove the wrapping ()
    input = input[1..-2]

    args = input.split /[\s\n]+/
    args.pop()

    cmd = args.shift()

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

  start: =>
    @repl = new REPLServer
      prompt: '>'
      ignoreUndefined: true
      eval: @interpret

    @context.console = this
    @repl.context = @context
    @rli = @repl.rli

exports = module.exports = new Console()
exports.Console = Console

