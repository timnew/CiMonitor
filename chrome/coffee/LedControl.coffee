class @LedControl
  constructor: ->

  update: (status) ->
    if this[status]?
      this[status]()
    else
      @unknown()

  building: ->
  success: ->
  failure: ->
  unknown: ->
