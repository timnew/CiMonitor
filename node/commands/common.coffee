require('../Console').setup ->
  @syncCmd 'exit', ->
    process.exit(0)

  displayHelp = ->
     """
     Help
     """

  @syncCmd '?', displayHelp
  @syncCmd 'help', displayHelp

