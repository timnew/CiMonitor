require('chai').should()

describe 'ci test', ->
  it 'should pass', ->
    true.should.be.ok
    
  xit 'should fail', ->
    null.should.be.ok