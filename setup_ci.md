# Setup CI Job
Ask CI to tracking the repository:

**Repository:** [https://github.com/timnew/CiMonitor.git](https://github.com/timnew/CiMonitor.git)  
**Branch:** ci_test

Then add a step to execute shell script:  
`/usr/bin/env node ./node_modules/mocha/bin/mocha spec`

To make it successful, a node.js must be installed on the CI server first