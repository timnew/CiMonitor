class @ProjectInfo
  status: ->
    return 'building' if @activity == 'building'
    @status

ProjectInfo.parseDate = (dateString) ->
  result = new Date()
  result.setTime(Date.parse(dateString))
  result

ProjectInfo.parseStatus = (activity, status) ->
  return 'building' if activity.toLowerCase() == 'building'

  status.toLowerCase()

ProjectInfo.parse = (xml) ->
  result = new ProjectInfo()
  $xml = $(xml)

  $.extend result,
    buildNumber: $xml.attr('lastBuildLabel')
    name: $xml.attr('name')
    status: ProjectInfo.parseStatus($xml.attr('activity'), $xml.attr('lastBuildStatus'))
    buildTime: ProjectInfo.parseDate($xml.attr('lastBuildTime'))

  result

ProjectInfo.getOverallStatus = (projectInfos) ->
  return 'unknown' unless projectInfos && projectInfos.length > 0

  for projectInfo in projectInfos
    switch projectInfo.status
      when 'building', 'failure', 'exception', 'pending', 'unknown'
        return lastStatus
      when 'success'
        break

  return 'success'