_ = require('lodash')
serialport = require('serialport')

serialport.list (err, results) ->
  console.error err if err?
  
  port = _.find results, (port) ->
    port.manufacturer == 'Arduino (www.arduino.cc)'
  
  unless port?  
    console.error "No Arduino found"
    process.exit(1)
  
  console.log port
  
  serialPort = new serialport.SerialPort port.comName
    
  serialPort.on 'data', (data) ->
    process.stdout.write data

  serialPort.on 'error', (data) ->
    process.stderr.write data

  process.stdin.resume();
  process.stdin.setRawMode(true);
  process.stdin.on 'data', (data) ->
    switch(data[0])
      when 0x03
        serialPort.close()
        process.exit(0)
      when 0x0d
        console.log '\n'
      else
        serialPort.write data, (err) ->
          process.stderr.write data if err?
          
