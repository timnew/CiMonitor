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