codes =
  on: 0xFFE01F
  off: 0xFF609F

  brighter: 0xFFA05F
  darker: 0xFF20DF

  flash: 0xFFF00F
  strobe: 0xFFE817
  fade: 0xFFD827
  smooth: 0xFFC837

  white: 0xFFD02F
  red: 0xFF906F
  green: 0xFF10EF
  blue: 0xFF50AF

  colors: [
    0xFFB04F,
    0xFF30CF,
    0xFF708F,
    0xFFA857,
    0xFF28D7,
    0xFF6897,
    0xFF9867,
    0xFF18E7,
    0xFF58A7,
    0xFF8877,
    0xFF08F7,
    0xFF48B7
  ]


buildCommand = (code, length) ->
  result = new Buffer(6)
  result.writeUInt32LE(code, 0)
  result.writeUInt16LE(length, 4)
  result

exports.on = buildCommand(codes.on, 32)
exports.off = buildCommand(codes.off, 32)
exports.building = buildCommand(codes.fade, 32)
exports.failure = buildCommand(codes.red, 32)
exports.success = buildCommand(codes.green, 32)
exports.exception = buildCommand(codes.white, 32)
exports.unknown = buildCommand(codes.white, 32)