require('chai').should()

describe 'ci test', ->
  it 'should pass', ->
    true.should.be.ok
    
  it 'should fail', (done) ->
    callback = ->
      done()
      
    setTimeout callback, 1900
      
    