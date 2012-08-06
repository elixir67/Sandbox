function Test() {
    var bTest = false;

    this.change = function () {
        bTest = true;
    }
    this.get = function () {
        return bTest;
    }
}

