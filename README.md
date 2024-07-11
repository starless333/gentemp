# gentemp
This is just a simple program that will generate some basic boiler plate Java Code. Think of Templates/Snippets but for basic Algorithm targeted problems!

## Why Make This? 
To me this program primarily serves to simply help create boilerplate code for things like Competitive Programming or more Specifically UIL CS. <br />
This project at no point will aim to implement things like Templates for Data Structures and or Algorithms.  <br />

## Available Commands
There is currently support for the Following Commands: <br /> <br />
-i: This will add as many imports as you want on top of the basic util/io. <br /> <br />
-c: This will add a basic empty class that you may need. add as many as you want. <br /> <br />
-nm: This will create a file without a main entry point <br /> <br />
-S {Implements}: Creates Sort Class that can help generating a sort method for Collections. <br /> <br />
-CArr {Name:Required} {Type:Optional}: Creates an ArrayList of type Type with name Name while putting data into it.  <br /> <br />
Note: This list is growing. <br />
## Running
```
$ g++ gen.cpp -o "gen" 
```
NOTE: if you do not use nvim simply change the last few lines of the program to whatever text editor you do use. IE. vim, emacs, code. <br/>
not that bad.  <br />
## Example
```
$ .\gen Test.java -i java.awt.* java.lang.System.* -c Clown Person Alien -S Comparator -CArr list Integer 
```
This command is to show just what most of the features can do.  <br />
The following code is the output of this command:  <br />

``` java
import java.util.*;
import java.io.*;
import java.awt.*;
import java.lang.System.*;


class Sort implements Comparator<> {
	public static int compare(Object o, Object k) {

	}
}


class Clown {

}

class Person {

}

class Alien {

}

public class Test {
	public static void main(String[] args) throws IOException {

		Scanner s = new Scanner(new File("Test.dat"));

		int T = s.nextInt();

		while(T-- > 0) {
			int n = s.nextInt();
			ArrayList<Integer> list = new ArrayList<Integer> ();
			for(int i = 0; i < n; i++) {
				list.add(s.next());
			}
		}

		s.close();
	}

}
```

