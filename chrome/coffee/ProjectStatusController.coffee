class @ProjectStatusController
  constructor: ($scope) ->
    monitor = new StatusMonitor '/cc.xml', 1000, (err, projectInfos) ->
      return $scope.projectInfos = [] if err?

      $scope.projectInfos = projectInfos
      $scope.$apply()

    monitor.refresh()
