function LineString(startX, startY, paper) {
    Geometry.apply(this, arguments);
    this.geoType = GeometryType.LineString;
};

LineString.prototype = new Geometry();
LineString.prototype.constructor = LineString;

LineString.prototype.sketchNext = function (x, y) {
    var lastX = this.vertices[this.verticesCount() - 1].x;
    var lastY = this.vertices[this.verticesCount() - 1].y;
    var path = "M" + lastX + " " + lastY + " L" + x + " " + y;
    if (!this.sketchGizmo) {
        this.sketchGizmo = this.paper.path(path);
        this.sketchGizmo.attr("stroke", "red");
        this.sketchGizmo.attr("stroke-width", LINE_WIDTH);
        this.sketchGizmo.attr("stroke-dasharray", ".");
    }
    else
        this.sketchGizmo.attr("path", path);
}

