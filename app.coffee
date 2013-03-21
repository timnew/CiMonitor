require('colors')
SerialPort = require('serialport').SerialPort

serialPort = new SerialPort "/dev/tty.usbmodemfa131", 
    baudrate: 57600
    
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
          
