/**
 * Created by lind on 5/20/2015.
 */
var phonecatServices=angular.module("phonecatServices",['ngResource']);
phonecatServices.factory('Phone',['$resource',
    function($resource){
        return $resource('phones/:phoneId.json',{},{
            query: {method:'GET', params:{phoneId:'phones'}, isArray:true}
        });
    }
])