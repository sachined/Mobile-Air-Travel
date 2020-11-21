# Mobile-Air-Travel
 A game in which goods and people travel. You will make money and eventually buy more planes to make even more!

Language used: C++

November 18, 2020 : Base class (airPort) uploaded with functional class (mapQueue). Defined w/ cpp & hpp for readability and ease of debugging.
                    Currently creating sort functions for airPort pointers. There is a bug with the remove function (mapQueue), in which the location 
                    of prev. occupied airport is still occupied by prev. in the mapQueue object. 
                    
            Plans - Finish making the sort functions, create few additional classes, such as Plane, Person, & Goods.
                    Start on an outline for integration of graph, to connect the airPorts. Distance is the important factor.

November 21, 2020 : Created a Building base class (for airPort and more) along with additional functions (sort, display) for both airPort and maqQueue classes.
                    Cleaned up the comments and tried to be more concise in explanations. Added a string member for airPort class (serves as name of airport).
		    Fixed the remove function, but there are issues regarding the airPort pointers when regarding move and copy (outside of mapQueue object).
																				
	    Plans - Create the additional classes, such as Plane, Person & Goods.
		    Once the above classes are made, integrate with airPort
		    * Start on an outline for integration of graph, to connect the airPorts. Distance is the importan factor. *
                  		
