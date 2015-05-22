/**
 * Created by lind on 5/20/2015.
 */
'use strict'
angular.module('phonecatFilters',[]).filter('checkmark',function(){
    return function(input){
        return input?'\u2713':'\u2718';
    }
})