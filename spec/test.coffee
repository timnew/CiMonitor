require('chai').should()

describe 'ci test', ->
  it 'should pass', ->
    true.should.be.ok
    
  it 'should fail', (done) ->
    callback = ->
      false.should.be.ok      
      done()
      
    setTimeout callback, 1500
      
    