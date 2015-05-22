/**
 * Created by lind on 5/15/2015.
 */
//describe('PhoneListCtrl',function(){
//        beforeEach(module('phonecatApp'));
//        beforeEach(inject(function($controller){
//          scope={};
//          ctrl=$controller("PhoneListCtrl",{$scope:scope});
//        }
//        ));
//
//        it('should create phone module with 3 phones', function(){
//            expect(scope.phones.length).toBe(3);
//            expect(scope.name).toBe("World");
//        });
//
//        it("it should set the default value of orderProp model", function(){
//            expect(scope.orderProp).toBe("age");
//        });
//    }
//);
'use strict'
describe("PhoneCat Controllers", function(){
    describe("phoneListCtrl", function(){
        var scope, ctrl, $httpBackend;

        beforeEach(module('phonecatApp'));
        beforeEach(inject(function(_$httpBackend_, $rootScope, $controller){
           $httpBackend = _$httpBackend_;
           $httpBackend.expectGET('phones/phones.json').respond([{name: 'Nexus S'},{name: 'Motorola DROID'}]);

            scope = $rootScope.$new();
            ctrl = $controller("PhoneListCtrl", {$scope: scope});
        }));

        it('should create phones', function(){
            expect(scope.phones).toBeUndefined();

            $httpBackend.flush();
            expect(scope.phones).toEqual([{name: 'Nexus S'},{name: 'Motorola DROID'}]);
        });

        it('should set default order', function(){
            expect(scope.orderProp).toBe('age');
        });
    })
})