# Core_Parser: Jiyong Kwag

### Submitting files
<ol>
  <li><b>main.c:</b> Recieving the file name as argument and pass the file name to the parser to parse the program into the parseTree</li>
  <li><b>parser.c:</b> Recieving the file name from the main and processing the parsing</li>
  <li><b>parser.h:</b> header file for parser.c</li>
  <li><b>printer.c:</b> print the all the nodes of tree appropriaty like original program</li>
  <li><b>printer.h:</b> header file for printer</li>
  <li><b>core.h:</b> storing enums for keywords, symbols, and others</li>
  <li><b>tree.h:</b> storing structure of struct for parseTree</li>
  <li><b>tester.sh:</b> testing the parser</li>
</ol>

### Special Feature
When checking the parsing error and sematic error, rather than check the error after build the parseTree, I implmented in way that progarm checks the error as build the tree. As a result, it could reduce some running time of the program. <br>

Moreover, when priting the parseTree back to original program, I implemented the program in a way that it frees the node that is printed. Because, after print, we no longer need parseTree.

### Description 
In this project, we are asked to build the parseTree based on the given regular grammar. Overall, the program recursivly check the currentToken to see appropriate node to intialize the token. At first, I implement the struct and parse function for each of the non-terminals to store appropriate information about program. Then, using the struct, I loop through the progarm using the nextToken. <br>

For exmaple, when program encounters the ID token, it starts from parseProcedure function. Then, following the given regular grammar, it goes down to the parseFactor and stores the ID into the factor struct. This is simple example of how I store the program into parseTree. To have more detail about the handling the parseTree, one should look into regular grammar.

### Handling the test case
Handling the test case was the most difficult part of this project because of various number of cases. For instance, "id<index>:=<expr>" can be "x:=0;" or "x[3]:=y."Thus, for each of non-terminals, I have to make all the possible cases that might regular grammar leads. <br>

In the project, I have not found any futher bugs about structure of regular grammar and structure of parseTree.
