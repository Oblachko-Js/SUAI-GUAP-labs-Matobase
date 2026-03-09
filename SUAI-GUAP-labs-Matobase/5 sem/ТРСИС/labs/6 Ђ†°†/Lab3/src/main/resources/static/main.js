var app = angular.module("les",[]);

app.controller("lessonController",function($scope,$http){
    $scope.lessonsList = [];

    $scope.getLessons = function(){
        $http.get("/lessons").success(function(data){
            $scope.lessonsList = data;
        }).error(function(data){
            if(data.message === "Time is out"){
                $scope.finishByTimeout();
            }
        });
    };

    $scope.deleteLesson = function(id){
        $http.delete("/lessons/" + id).success(function(data){
            for(var i=0;i<$scope.lessonsList.length;++i){
                if($scope.lessonsList[i].id === id){
                    $scope.lessonsList.splice(i,1);
                    break;
                }
            }
        }).error(function(data){
             console.log("Error")
          });
    };

    $scope.addLesson = function(){
        $http.post("lessons/"+$scope.group + "/"+$scope.audience + "/"+$scope.teacher + "/" +$scope.name + "/" +$scope.number)
        .success(function(data){
            $scope.lessonsList.push(data);
        }).error(function(data){
            console.log("Error");
        });
        $scope.getLessons();
    };
});