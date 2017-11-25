# primes

	//Create a set of numerical data FROM 2 TO the given number
	num_set(int tail); 
  
  //Create a set of numerical data BETWEEN 2 given numbers* 
  num_set(int head, int tail); 
  
  //Create a set of numerical data BETWEEN 2 given 
    numbers but only store before/after/on each 
    multiple of the given divisor*
  num_set(int head, int tail, int divisor); 
  
  //Create a set of numerical data BETWEEN 2 given 
    numbers and provide the location 
    of the "prime_list.txt"
	num_set(int head, int tail, string primeFile);
  
  *requires "prime_list.txt" to have been made
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - -//
  
  //Writes the entire set of numbers into files within 
    these folders {..\composites} and {..\primes}
  num_set::writeAll()
