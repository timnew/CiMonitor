class @ProjectStatusController
  constructor: ($scope) ->
    $scope.ledControl = new LedControl()

    monitor = new StatusMonitor '/cc.xml', 1000, (err, projectInfos) ->
      $scope.projectInfos = if err? then [] else projectInfos
      $scope.overallStatus = ProjectInfo.getOverallStatus(projectInfos)

      $scope.ledControl.update $scope.overallStatus

      $scope.$apply()

    monitor.refresh()
