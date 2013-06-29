fs = require('fs')
path = require('path')

fs.readdirSync(__dirname).forEach (file) ->
  require("./#{file}")

