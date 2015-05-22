/**
 * Created by lind on 5/15/2015.
 */
//var phonecatApp = angular.module('phonecatApp',[]);
//phonecatApp.controller('PhoneListCtrl',function($scope){
//    $scope.phones = [
//        {'name':'Nexus S','snippet':'Fast just got faster with Nexus S','age':1},
//        {'name':'Motorola XOOM? with Wi-Fi','snippet':'The Next Generation tablet','age':2},
//        {'name':'MOTOROLA XOOM?','snippet':'The Next, Next Generation tablet.','age':3}
//    ];
//
//    $scope.name = "World";
//    $scope.orderProp='age';
//});
//
//var phonecatApp= angular.module("phonecatApp",[]);
//phonecatApp.controller("PhoneListCtrl",['$scope','$http',function($scope, $http){
//    $scope.orderProp='age';
//    $http.get("phones/phones.json").success(function(data)
//    {
//        $scope.phones = data;
//    });
//}]);

var phonecatControllers = angular.module('phonecatControllers',[]);
phonecatControllers.controller('PhoneListCtrl',['$scope','Phone',
    function($scope, Phone){
        $scope.phones=Phone.query();
    }]);

phonecatControllers.controller("PhoneDetailCtrl",['$scope',"$routeParams","Phone",
    function($scope, $routeParams, Phone){
        $scope.phoneId = $routeParams.phoneId;
        //$http.get('phones/'+ $routeParams.phoneId + '.json').success(function(data){
        //    $scope.phone = data;
        //    $scope.mainImageUrl = data.images[0];
        //});

        $scope.phone=Phone.get({phoneId: $routeParams.phoneId},function(phone){
            $scope.mainImageUrl = phone.images[0];
        });

        $scope.setImage=function(imageUrl){
            $scope.mainImageUrl=imageUrl;
        }
    }]);