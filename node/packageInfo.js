var fs = require('fs');

var packageJson = fs.readFileSync('./package.json');
var pacakgeInfo = JSON.parse(packageJson);

exports = module.exports = pacakgeInfo;

