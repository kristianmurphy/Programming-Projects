
function showstats() { // upon clicking the calculate button shows the stats
	let int1 = Number(document.getElementById("input1").value);
	let int2 = Number(document.getElementById("input2").value);
	let int3 = Number(document.getElementById("input3").value); // check if the the inputs are valid:
	if(int1==="" || int2==="" || int3==="" || isNaN(int1) || isNaN(int2) || isNaN(int3)) {
		//can put error code here
	} else {
		
		// allow the statistics to be visible if first calculation:
		document.getElementById("outputs").style.display = "block";
		
		// create array for the numbers and set list array:
		list = [int1, int2, int3];
		document.getElementById("ints").innerHTML=list;
		
		// for loop through list to find maximum and set span:
		var max = list[0]
		for(let i=0; i<list.length; i++){if(list[i]>max){max=list[i];}}
		document.getElementById("maximum").innerHTML=max;
		
		// for loop through list to find minimum and set span:
		var min = list[0]
		for(let i=0; i<list.length; i++){if(list[i]<min){min=list[i];}}
		document.getElementById("minimum").innerHTML=min;

		// for loop through list to find mean and set span:
		var mean = 0;
		for(let i=0; i<list.length; i++){mean+=list[i];}
		mean/=list.length;
		document.getElementById("mean").innerHTML=mean;

		// sort array and then return the middle value: (could be used for max/min)
		list.sort(function(a, b) {return a - b;});
		document.getElementById("median").innerHTML=list[1];

		// find range with subtraction of min and max:
		document.getElementById("range").innerHTML=max-min;

	}
	
}
