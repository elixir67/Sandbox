var CANVAS_WIDTH = 500;
var CANVAS_HEIGHT = 500;
//<![CDATA[
$(document).ready(function () {
    var paper = Raphael("canvas", CANVAS_WIDTH, CANVAS_HEIGHT);
    var lineString;
    var bEditable = false;

    $("#drawLineBtn").click(function (e) {
        // TODO current it only support load/save one line
        // so we just draw one line, let's enhance it later.
        paper.clear();
        $("#canvas").bind("mouseup", function (e) {
            if (e.which !== 1)
                return;

            // left mouse up
            if (!bEditable) {
                // Begin to draw linestring
                bEditable = true;
                x = e.offsetX;
                y = e.offsetY;
                lineString = new LineString(x, y, paper);
                lineString.initVertices();

                $("#canvas").bind("mousemove", function (e) {
                    x = e.offsetX;
                    y = e.offsetY;
                    lineString.sketchNext(x, y);
                });

            } else {
                // Add one more vertex
                x = e.offsetX;
                y = e.offsetY;
                if (lineString)
                    lineString.addVertex(x, y);
            }
        });
    });

    // Right click to finish sketch.
    $('#canvas').bind('contextmenu', function (e) {
        e.preventDefault();

        if (e.which === 3 && bEditable) {
            $("#canvas").unbind("mouseup");
            $("#canvas").unbind("mousemove");
            bEditable = false;
            lineString.sketchFinish();
        }
        return false;
    });

    // Esc key to cancel the sketch.
    $(document).keyup(function (e) {
        if (e.which === ESC_KEYCODE) {
            alert("ESC!");
        }
    });

    $("#clearBtn").click(function () {
        paper.clear();
    });

    $("#saveBtn").click(function () {
        if (lineString)
            lineString.save();
    });

    $("#loadBtn").click(function () {
        paper.clear();
        lineString = new LineString(0, 0, paper);
        lineString.load();
    });
});