# gentemp
This is just a simple program that will generate some basic boiler plate Java Code. Think of Templates/Snippets.

## Why Make This? 
To me this program primarily serves to simply help create boilerplate code for things like Competitive Programming or more Specifically UIL CS.

## Running
Just compile the gen.cpp file with any of your favorite compilers and run the program.<br />
If you want the default output simple run ./gen [file]. <br />
If you want to add separate classes run ./gen [class1] [class2] etc.<br />
Same thing goes with imports, and the command -nm will not create a main entry point<br />

## Example
```
$ ./gen Test.java -nm -i java.awt.* -c Person Clown
```
That Command will have this output<br />

```
import java.util.*;
import java.io.*;
import java.awt.*;

class Person {

}

class Clown {

}
```

