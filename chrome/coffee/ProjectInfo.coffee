class @StatusMonitor
  constructor: (@url, @pollInterval, @callback) ->

  start: ->
    stop();
    @refresh()
    @pollToken = setInterval(@refresh, @pollInterval);

  stop: ->
    return unless @pollToken?
    clearInterval(@pollToken);
    @pollToken = null;

  refresh: =>
    jQuery
    .get(@url)
    .done(@onData)
    .fail(@onError)

  onData: (dom) =>
    projectInfos = $(dom).find('Project').map (i, projectDom) ->
      ProjectInfo.parse(projectDom)

    @callback(null, projectInfos.toArray())

  onError: =>
    @callback(arguments)

class @ProjectInfo

ProjectInfo.parseDate = (dateString) ->
  result = new Date()
  result.setTime(Date.parse(dateString))
  result

ProjectInfo.parse = (xml) ->
  result = new ProjectInfo()
  $xml = $(xml)

  $.extend result,
    buildNumber: $xml.attr('lastBuildLabel')
    name: $xml.attr('name')
    status: $xml.attr('lastBuildStatus')
    activity: $xml.attr('activity')
    buildTime: ProjectInfo.parseDate($xml.attr('lastBuildTime'))

  result


