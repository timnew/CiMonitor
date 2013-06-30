serialport = require('serialport')
sf = require('sf')
require('../Console').setup ->
  @asyncCmd 'listport', (callback) ->
    serialport.list (err, ports) ->
      return callback(err) if err?

      for port in ports
        console.log sf('{comName,-15} {pnpId,-20} {manufacturer,-20} {productId}', port)

      callback(null)
