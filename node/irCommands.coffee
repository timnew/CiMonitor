buildCommand = (value, length) ->
  result = new Buffer(6)
  result.writeUInt32LE(value, 0)
  result.writeUInt16LE(length, 4)
  result
    
exports.building = buildCommand(0x20DF00FF, 32) #up
exports.failure = buildCommand(0x20DF807F, 32) #down
exports.success = buildCommand(0x20DFC03F, 32) #left
exports.exception = buildCommand(0x20DF40BF, 32) #right
exports.unknown = buildCommand(0x20DF906F, 32) #mute