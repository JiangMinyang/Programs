

function getData(Table) {
	var matrix = [];
	for(var i = 1; i < Table.childNodes.length; i++) {
		var tr = Table.childNodes[i].childNodes;
		var row = [];
		for(var j = 0; j < tr.length; j++) {
			var td = tr[j];
			if (td.firstChild.value == 0) {
				td.firstChild.value = 0;
				row.push(0);
			}
			else
				row.push(parseInt(td.firstChild.value));
		}
		matrix.push(row);
	}
	return matrix;
}

Sudoku.prototype.setValue = function(x, y, n) {
	document.getElementById("dataTable").childNodes[x + 1].childNodes[y].firstChild.value = n;
}

Sudoku.prototype.isValid = function(x, y, xx) {
//	console.log(x + " " + y + " " + xx);
	for(var i = 0; i < 9; i++) {
		if (this.matrix[i][y] != 0 && i != x && this.matrix[i][y] == xx) return false;
		if (this.matrix[x][i] != 0 && i != y && this.matrix[x][i] == xx) return false;
	}
	for(var i = x - x % 3; i <= x - x % 3 + 2; i++)
		for(var j = y - y % 3; j <= y - y % 3 + 2; j++)
			if (x != i || y != j)
				if (this.matrix[i][j] != 0 && this.matrix[i][j] == xx) return false;
	return true;
}
Sudoku.prototype.solve = function(x, y) {
//	console.log(x + " " + y);
	if (x == 9) {
		this.check = false;
		for(var i = 0; i < 9; i++)
			for(var j = 0; j < 9; j++)
				this.setValue(i, j, this.matrix[i][j]);
		return;
	}
	if (this.matrix[x][y] == 0) {
		for(var i = 1; i <= 9; i++)
			if (this.isValid(x, y, i)) {
				if (!this.check) return;
				this.matrix[x][y] = i;
//				setValue(x, y, i);
				if (y == 8) this.solve(x + 1, 0);
				else this.solve(x, y + 1);
				if (!this.check) return;
				this.matrix[x][y] = 0;
//				setValue(x, y, 0);
			}
	}
	else {
		if (y == 8) this.solve(x + 1, 0);
		else this.solve(x, y + 1);
	}
}

function work() {
	var dataTable = document.getElementById("dataTable");
	var inputData = getData(dataTable);
	var sudoku = new Sudoku;
	sudoku.matrix = inputData;
	sudoku.check = true;
	for(var i = 0; i < 9; i++)
		for(var j = 0; j < 9; j++) {
			if (sudoku.matrix[i][j] != 0)
			if (!sudoku.isValid(i, j, sudoku.matrix[i][j])) {
				alert("input not valid");
				return;
			}
		}
//	dataTable.childNodes[5].childNodes[6].firstChild.value = "!";
	sudoku.solve(0, 0);
}

function Sudoku() {

}

function isNumberKey(evt) {
    var charCode = (evt.which) ? evt.which : event.keyCode
    if (charCode > 31 && (charCode < 48 || charCode > 57))
        return false;
	return true;
}

function init() {
	var dataTable = document.getElementById("dataTable");
	dataTable.style.align = "center";
	for(var i = 0; i < 9; i++) {
		var dataTableTr = document.createElement("tr");
		for(var j = 0; j < 9; j++) {
			var dataTableTd = document.createElement("td");
			if ((Math.floor(i / 3) + Math.floor(j / 3)) % 2 == 1) {
				dataTableTd.style.borderColor = "red";
				dataTableTd.style.backgroundColor = "red";
			}
			var input = document.createElement("input");
			input.type = "text";
			input.style.width = "20px";
			input.style.height = "20px";
			input.maxLength = 1;
			input.style.textAlign = "center";
			input.onkeypress = function(evt) {
				evt = (evt) ? evt : window.event
				var charCode = (evt.which) ? evt.which : evt.keyCode
				if (charCode > 31 && (charCode < 48 || charCode > 57)) {
					status = "This field accepts numbers only."
					return false;
			    }
			    status = ""
				return true;
					  
			};

			/*
			for(var k in input) {
				document.write(k + " " + input[k] + "</br>");
			}
			*/

			dataTableTd.appendChild(input);
			dataTableTr.appendChild(dataTableTd);
		}
		dataTable.appendChild(dataTableTr);
	}
}

init();

document.getElementById("run").onclick = function() {
	work();
}

document.getElementById("clear").onclick = function() {
	for(var i = 0; i < 9; i++)
		for(var j = 0; j < 9; j++)
			document.getElementById("dataTable").childNodes[i + 1].childNodes[j].firstChild.value = "";
}
