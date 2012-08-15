var LINE_WIDTH = 5;
var CONTROL_POINT_RADIOUS = 4;
var ESC_KEYCODE = 27;
var TOLERANCE = 2;  // TODO normalize it later.
var OFFSET = 10;

function Vertex(x, y) {
    this.x = x;
    this.y = y;
};

Vertex.prototype.toJson = function() {
    var object = {
        x: this.x,
        y: this.y
    }
    return object;
};

function LineString(startX, startY, paper) {
    this.paper = paper;

    this.gizmo = paper.path("M" + startX + " " + startY);
    this.gizmo.attr("stroke", "red");
    this.gizmo.attr("stroke-width", LINE_WIDTH);

    this.vertices = [];
    this.vertices.push(new Vertex(startX, startY));

    this.vertexGizmos = [];
    this.sketchGizmo = null;    // Help to draw the next vertex.

    this.bEditable = false;
};

LineString.prototype.initVertices = function () {
    // clear first
    for (var i = 0, len = this.vertexGizmos.length; i < len; ++i) {
        this.vertexGizmos[i][0].remove();
        this.vertexGizmos[i][1].remove();
    }

    this.vertexGizmos = [];

    // setup control points
    for (var i = 0, len = this.vertices.length; i < len; ++i)
        this.vertexGizmos.push(this.createControlPoint(i));
}


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

LineString.prototype.isOnLine = function (x, y, startPos, endPos) {
    // are they on this segment
    if (x < startPos.x || x > endPos.x)
        return false;
    var f = function (somex) { return (endPos.y - startPos.y) / (endPos.x - startPos.x) * (somex - startPos.x) + startPos.y; };
    var fx = f(x);
    var fy = Math.abs(f(x) - y);
    // return Math.abs(f(x) - y) < TOLERANCE // tolerance, rounding errors
    return fy < TOLERANCE;
}

LineString.prototype.getNearestIndex = function (x, y) {
    for (var i = 1, len = this.vertices.length; i < len; ++i)
        if (this.isOnLine(x, y, this.vertices[i - 1], this.vertices[i]))
            return i;
    return -1;
}

LineString.prototype.sketchFinish = function () {
    if (this.sketchGizmo) {
        this.sketchGizmo.remove();
    }

    this.bEditable = true;
    var me = this;
    var newVertexGizmo;
    this.gizmo.mouseover(function (e) {
        var x = e.offsetX;
        var y = e.offsetY;
        if (!newVertexGizmo)
            newVertexGizmo = me.paper.circle(x, y, CONTROL_POINT_RADIOUS);
        else
            newVertexGizmo.attr({ cx: x, cy: y });
    });
    this.gizmo.mouseup(function (e) {
        // Add a new vertex now
        var x = e.offsetX;
        var y = e.offsetY;
        // Ccompute the nearest index
        var index = me.getNearestIndex(x, y);
        if (-1 == index) {
            alert("index is  -1");
            return;
        }
        me.vertices.splice(index, 0, new Vertex(x, y));
        // Rest control points
        me.initVertices();
        me.redraw();
    });
    this.gizmo.mouseout(function () {
        if (newVertexGizmo) {
            newVertexGizmo.remove();
            newVertexGizmo = null;
        }
    })
}

LineString.prototype.addVertex = function (x, y) {
    this.vertices.push(new Vertex(x, y));
    var c = this.createControlPoint(this.vertices.length - 1);
    this.vertexGizmos.push(c);
    this.redraw();
};

LineString.prototype.updateVertex = function (x, y, index) {
    this.vertices[index].x = x;
    this.vertices[index].y = y;
    this.redraw();
    this.vertexGizmos[index][0].attr({ cx: x, cy: y }); // controlGizmo
    this.vertexGizmos[index][1].attr({ x: x + OFFSET, y: y }); // removeGizmo
};

LineString.prototype.verticesCount = function () {
    return this.vertices.length;
}

LineString.prototype.toString = function () {
    var path = ""
    for (var i = 0, len = this.vertices.length; i < len; ++i)
        path += i.toString() + "." + this.vertices[i].x + "," + this.vertices[i].y; + "\n"
    return path;
};

LineString.prototype.createControlPoint = function (index) {
    var me = this;  // avoid conflict in drag
    var x = me.vertices[index].x;
    var y = me.vertices[index].y;
    var controlGizmo = this.paper.circle(x, y, CONTROL_POINT_RADIOUS);
    controlGizmo.attr("fill", "yellow");
    controlGizmo.data("index", index);   // save index as customized data

    controlGizmo.drag(function (dx, dy, x, y, event) {
        // move
        if (me.bEditable && event.which == 1) {
            var index = this.data("index");

            // update the display in screen
            var x = me.vertices[index].x + dx;
            var y = me.vertices[index].y + dy;
            me.updateVertex(x, y, index);

            // recover the value back for next move
            me.vertices[index].x -= dx;
            me.vertices[index].y -= dy;
        }

    },
        function () {
            // drag start 
        },
        function () {
            if (me.bEditable) {
                var index = this.data("index");
                // drag end
                me.vertices[index].x = this.attr("cx");
                me.vertices[index].y = this.attr("cy");
            }
        });

        controlGizmo.hover(function () {
            if (me.bEditable) {
                this.attr("cursor", "move");
            }
        }, function () {
            if (me.bEditable) {
                this.attr("cursor", "default");
            }
        });

    var removeGizmo = me.paper.text(x + OFFSET, y, "X");
    removeGizmo.data("index", index);
    removeGizmo.click(function () {
        if (me.bEditable) {
            var index = this.data("index");
            // Remove the vertex at index
            me.vertices.splice(index, 1);
            // Rest control points
            me.initVertices();
            me.redraw();
        }
    });
    removeGizmo.hover(function () {
        if (me.bEditable) {
            this.attr("cursor", "pointer");
        }
    }, function () {
        if (me.bEditable) {
            this.attr("cursor", "default");
        }
    });

    return [controlGizmo, removeGizmo];
}

LineString.prototype.getPath = function () {
    if (this.vertices.length <= 0)
        alert("this.vertices.length <= 0");
    var path = "M" + this.vertices[0].x + " " + this.vertices[0].y;
    for (var i = 1, len = this.vertices.length; i < len; ++i)
        path += " L" + this.vertices[i].x + " " + this.vertices[i].y;
    return path;
};

LineString.prototype.redraw = function () {
    this.gizmo.attr("path", this.getPath());
};

LineString.prototype.save = function () {
    // save vertices values            
    if (typeof (Storage) !== "undefined") {
        var jsonVertices = [];
        for (var i = 0, len = this.vertices.length; i < len; ++i)
            jsonVertices.push(this.vertices[i].toJson());
        localStorage.raphael = JSON.stringify(jsonVertices);
    }
    else {
        alert("HTML5 Web Storage isn't supported.");
    }
};

LineString.prototype.load = function () {
    // load vertices values
    if (typeof (Storage) !== "undefined") {
        var json = localStorage.raphael;
        this.vertices = [];
        if (typeof (json) == "string") {
            var jsonVertices = JSON.parse(json); // load it back
            for (var i = 0, len = jsonVertices.length; i < len; ++i)
                this.vertices.push(new Vertex(jsonVertices[i].x, jsonVertices[i].y));
            this.redraw();
            this.initVertices();
            this.sketchFinish();
        }
    }
    else {
        alert("HTML5 Web Storage isn't supported.");
    }
};
