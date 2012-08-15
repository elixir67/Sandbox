function Polygon(startX, startY, paper) {
    Geometry.apply(this, arguments);
    this.geoType = GeometryType.Polygon;
};

Polygon.prototype = new Geometry();
Polygon.prototype.constructor = Polygon;

Polygon.prototype.sketchNext = function (x, y) {
    var lastX = this.vertices[this.verticesCount() - 1].x;
    var lastY = this.vertices[this.verticesCount() - 1].y;
    var startX = this.vertices[0].x;
    var startY = this.vertices[0].y;
    var path = "M" + lastX + " " + lastY + " L" + x + " " + y + " L" + startX + " " + startY;
    if (!this.sketchGizmo) {
        this.sketchGizmo = this.paper.path(path);
        this.sketchGizmo.attr("stroke", "red");
        this.sketchGizmo.attr("stroke-width", LINE_WIDTH);
        this.sketchGizmo.attr("stroke-dasharray", ".");
    }
    else
        this.sketchGizmo.attr("path", path);
}

Polygon.prototype.sketchFinish = function () {
    Geometry.prototype.sketchFinish.apply(this, arguments);
    Geometry.prototype.redraw.apply(this, arguments);
}

Polygon.prototype.getPath = function () {
    if (this.vertices.length <= 0)
        alert("this.vertices.length <= 0");

    var path = "M" + this.vertices[0].x + " " + this.vertices[0].y;
    for (var i = 1, len = this.vertices.length; i < len; ++i)
        path += " L" + this.vertices[i].x + " " + this.vertices[i].y;

    if (this.bEditable)
        path += " Z";
    return path;
};

Polygon.prototype.getNearestIndex = function (x, y) {
    for (var i = 1, len = this.vertices.length; i < len; ++i)
        if (Geometry.isOnLine(x, y, this.vertices[i - 1], this.vertices[i]))
            return i;
    if(Geometry.isOnLine(x, y, this.vertices[len - 1], this.vertices[0]))
        return len;
    return -1;
}
