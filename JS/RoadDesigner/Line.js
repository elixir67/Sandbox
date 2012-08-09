var CANVAS_WIDTH = 500;
var CANVAS_HEIGHT = 500;
var LINE_WIDTH = 5;
var CONTROL_POINT_RADIOUS = 4;

function Vertex(x, y) {
    this.x = x;
    this.y = y;
};

function Line(startX, startY, endX, endY, paper) {
    this.start = new Vertex(startX, startY);
    this.end = new Vertex(endX, endY)
    this.paper = paper;
    this.gizmo = paper.path("M" + this.start.x + " " + this.start.y + " L" + this.end.x + " " + this.end.y);
    this.gizmo.attr("stroke", "red");
    this.gizmo.attr("stroke-width", LINE_WIDTH);

    this.endGizmo;
    this.startGizmo;
    this.moveGizmo;
    this.bEditable = false;
};

Line.prototype.updateStart = function (x, y) {
    this.start.x = x;
    this.start.y = y;
    this.redraw();
    return this;
};

Line.prototype.updateEnd = function (x, y) {
    this.end.x = x;
    this.end.y = y;
    this.redraw();
    return this;
};

Line.prototype.print = function () {
    console.log(this.start.x + ";" + this.start.y + ";" + this.end.x + ";" + this.end.y);
};

Line.prototype.startEdit = function () {
    var me = this;

    // Avoid triggering multi-times
    if (me.bEditable)
        return;
    me.bEditable = true;

    // Change the line attributes
    me.gizmo.attr("stroke", "blue");
    me.gizmo.attr("stroke-dasharray", ".");
    // Show the end control point
    me.endGizmo = this.paper.circle(this.end.x, this.end.y, CONTROL_POINT_RADIOUS);
    me.endGizmo.attr("fill", "yellow");

    me.endGizmo.drag(function (dx, dy) {
        // move
        me.end.x += dx;
        me.end.y += dy;
        me.redraw();
        me.endGizmo.attr({ cx: me.end.x, cy: me.end.y });
        me.moveGizmo.attr({ cx: (me.start.x + me.end.x) / 2, cy: (me.start.y + me.end.y) / 2 });
        me.end.x -= dx;
        me.end.y -= dy;
    },
    function () {
        // drag start 
    },
    function () {
        // drag end
        me.end.x = me.endGizmo.attr("cx");
        me.end.y = me.endGizmo.attr("cy");
    });

    // Show the start control point
    me.startGizmo = this.paper.circle(this.start.x, this.start.y, CONTROL_POINT_RADIOUS);
    me.startGizmo.attr("fill", "yellow");

    me.startGizmo.drag(function (dx, dy) {
        // move
        me.start.x += dx;
        me.start.y += dy;
        me.redraw();
        me.startGizmo.attr({ cx: me.start.x, cy: me.start.y });
        me.moveGizmo.attr({ cx: (me.start.x + me.end.x) / 2, cy: (me.start.y + me.end.y) / 2 });
        me.start.x -= dx;
        me.start.y -= dy;
    },
    function () {
        // drag start 
    },
    function () {
        // drag end
        me.start.x = me.startGizmo.attr("cx");
        me.start.y = me.startGizmo.attr("cy");
    });

    // Show the move control point
    me.moveGizmo = me.paper.circle((me.start.x + me.end.x) / 2, (me.start.y + me.end.y) / 2, CONTROL_POINT_RADIOUS);
    me.moveGizmo.attr("fill", "yellow");
    me.moveGizmo.drag(function (dx, dy) {
        // move
        me.start.x += dx;
        me.start.y += dy;
        me.end.x += dx;
        me.end.y += dy;
        me.redraw();
        me.startGizmo.attr({ cx: me.start.x, cy: me.start.y });
        me.endGizmo.attr({ cx: me.end.x, cy: me.end.y });
        me.moveGizmo.attr({ cx: (me.start.x + me.end.x) / 2, cy: (me.start.y + me.end.y) / 2 });
        me.start.x -= dx;
        me.start.y -= dy;
        me.end.x -= dx;
        me.end.y -= dy;
    },
    function () {
        // drag start 
    },
    function () {
        // drag end
        me.start.x = me.startGizmo.attr("cx");
        me.start.y = me.startGizmo.attr("cy");
        me.end.x = me.endGizmo.attr("cx");
        me.end.y = me.endGizmo.attr("cy");
    });
};

Line.prototype.endEdit = function () {
    // Recover the line
    this.gizmo.attr("stroke", "red");
    this.gizmo.attr("stroke-dasharray", "");

    // Clear the control points
    this.startGizmo.remove();
    this.endGizmo.remove();
    this.moveGizmo.remove();
    this.bEditable = false;
};

Line.prototype.getPath = function () {
    return "M" + this.start.x + " " + this.start.y + " L" + this.end.x + " " + this.end.y;
};

Line.prototype.redraw = function () {
    this.gizmo.attr("path", this.getPath());
};

