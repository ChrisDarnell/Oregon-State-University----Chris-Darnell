// Chris Darnell
// CS-290 Web Development
// 10/30/16
// DOM and Events Assignment - script.js

// A 4x4 table
function Create_Table(){
    var body1 = document.body,
    table1 = document.createElement('table');
    table1.setAttribute("id", "myTable");

// Border
    table1.style.width = '100px';
    table1.style.border = '1px solid black';


// Header
    var tr = table1.insertRow();
    for(var i = 0; i < 4; i++){


// The 4 header cells, from left to right should say "Header 1", "Header 2" ... "Header 4
        var headercell = document.createElement("TH");
        headercell.appendChild(document.createTextNode("Header " + (i + 1)))
        headercell.style.border = '1px solid black';
        tr.appendChild(headercell);
    }

// The non header cells should contain their position.
// The upper left cell should contain the text "1, 1", the cell to its right "2, 1", the cell below it "1, 2" and so on.
   for(var i = 0; i < 3; i++){

// Make rows
        var tr = table1.insertRow();
        for(var j = 0; j < 4; j++){

// Make/label cells.
            var td = tr.insertCell();
            td.appendChild(document.createTextNode((i + 1) +', '+ (j + 1)));
            td.style.border = '1px solid black';
        }
    }
    body1.appendChild(table1);


// Selecting cell 1,1 and thickening border of cell
    var table = document.getElementById("myTable");
    var rowIndex = 1;
    var cellIndex = 0;
    table.rows[rowIndex].cells[cellIndex].style.border='2px solid black';

 // 4 directional buttons (up, down, left right)
 // Up
    var element1 = document.createElement("input");
    element1.type = "button";
    element1.value = "Up";

// If you are already on the top row and hit 'up' nothing should happen (you should not be able to move into the header cells).
// Likewise if you are all the way right and hit right or all the way at the bottom.
   element1.onclick = function() {
        var current = table.rows[rowIndex].cells[cellIndex];

       if(rowIndex == 1){
           current = current;
       }

// When the page is loaded the upper left, non-header cell of the table should be 'selected'.
// This is denoted by it having a thicker border than the other cells.
       else{
            table.rows[rowIndex].cells[cellIndex].style.border = '1px solid black';
            rowIndex = rowIndex - 1;
            current = table.rows[rowIndex].cells[cellIndex];
            current.style.border = '2px solid black';
        }
    };
    body1.appendChild(element1);

// Down
    var element1 = document.createElement("input");
    element1.type = "button";
    element1.value = "Down";
    element1.name = "Down";
    element1.onclick = function() {
       var current = table.rows[rowIndex].cells[cellIndex];
       if(rowIndex == 3){
           current = current;
       }
       else{
            table.rows[rowIndex].cells[cellIndex].style.border = '1px solid black';
            rowIndex = rowIndex + 1;
            current = table.rows[rowIndex].cells[cellIndex];
            current.style.border = '2px solid black';
        }
    };
    body1.appendChild(element1);

// Left
    var element1 = document.createElement("input");
    element1.type = "button";
    element1.value = "Left";
    element1.name = "Left";
    element1.onclick = function() {
        var current = table.rows[rowIndex].cells[cellIndex];
        if(cellIndex == 0){
           current = current;
        }
        else{
            table.rows[rowIndex].cells[cellIndex].style.border = '1px solid black';
            cellIndex = cellIndex - 1;
           current = table.rows[rowIndex].cells[cellIndex];
           current.style.border= '2px solid black';
        }
    };
   body1.appendChild(element1);

// Right
   var element1 = document.createElement("input");
    element1.type = "button";
    element1.value = "Right";
    element1.name = "Right";

    element1.onclick = function() {
        var current = table.rows[rowIndex].cells[cellIndex];

       if(cellIndex == 3){
           current = current;
        }
        else {
            table.rows[rowIndex].cells[cellIndex].style.border = '1px solid black';
            cellIndex = cellIndex + 1;
            current = table.rows[rowIndex].cells[cellIndex];
            current.style.border = '2px solid black';
        }
    };
    body1.appendChild(element1);

//  A button labeled "Mark Cell"
    var element1 = document.createElement("input");
    element1.type = "button";
    element1.value = "Mark Cell";
    element1.name = "Mark Cell";

// Hitting the "Mark Cell" button should permanently change the background of the selected cell to yellow.
    element1.onclick = function() {
        table.rows[rowIndex].cells[cellIndex].style.backgroundColor = 'yellow';
   };
   body1.appendChild(element1);
}
// Call function CreateTable
window.onload = Create_Table();
