fs = require('fs')
path = require('path')

files = fs.readdirSync(__dirname)
for file in files when file != 'index.coffee'
  name = path.basename(file, '.coffee')
  exports[file] = require("./#{file}")
  
