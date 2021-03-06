m4_include(`header.h')m4_dnl

WBigTitle(Basics)
WTitle((1/5)Simple hello world program)
Let show now a simple hello world program:
OCode 
{reuse L42.is/AdamTowel
Main:{
  Debug(S"Hello world")
  return ExitCode.success()
  }
}
CCode
At the right of Wcode(Main:) we write the expression/statements that
we wish to execute. Wcode(Main) is not a method, and Wcode(Main) is not special name either. In 42 there is no concept of main method as in
Java or C. For now you can think of Wcode(Main:) as a top level command, we will understand later how this fits with the general language design.

When we write Wcode(reuse L42.is/AdamTowel) we are asking 42 to
reuse the code offered by the library offered in the internet address 
Wcode(L42.is/AdamTowel).
AdamTowel is our Towel, that is the set of classes and interfaces that we wish to start from (Wlink(towel,see more on towels)).
Wcode(L42.is) is the main website of 42, where most commonly used libraries are hosted. To reuse code you need internet connection; but this also means that you will never have to manually import any code. Required code will be transitivelly downloaded and cached on your machine, you need not to be aware of the existence of this mechanism.
WP
We are not supposed to always start from AdamTowel, there are many interesting towels out there, and you may also become skilled in the 
advance technique of towel embroidery.
WP

WTitle((2/5)Method declaration and call)
Lets now declare a method and call it.
OCode
{reuse L42.is/AdamTowel
MyCode:{
  class method
  S hello(S name){
    return S"hello "++name
    } 
  }
Main:{
  Debug(MyCode.hello(name=S"world"))
  return ExitCode.success()
  }
}
CCode
Here we declare a class to host our Wcode(hello(name)) method.
We write Wcode(class method) to declare a method that can be called on the class object, as in Wcode(MyCode.hello(name=S"world")). This is equivalent to a static method in languages like Java or C++.

WP
Note how the method is called using the parameter name explicitly.
We believe this increase readability.
WP
You can also notice how there are two different usages for curly brackets: if there is at least a return keyword it is a set of statements,
otherwise is a library literal, and can contains methods and nesteds.
A nested (class or interface) is denoted by an upper-case name, and can be obtained by a library literal or an expression producing a library literal.
A library can be a class (default case) or an interface (starts with the Wcode(interface) keyword).
A nested in 42 is similar to a static inner class in Java, or a nested class in C++. It is just a convenient way to divide in a tree shape the various components of our program.
WP
The class Wcode(MyCode) of before offers a single class method, have no fields and you can not create instances of Wcode(MyCode), since no factory is present; you can think about it as a module.
In 42 we do not have constructors. Objects are created by factory methods. We believe this is a much simpler and consistent approach to object initialization.

WTitle((3/5)Simple class with internal state)
Let create now a class with state and factory:
OCode
Point:Data<<{
  Int x
  Int y
  method
  Point add(Int x)
    Point(x=x+this.x(), y=this.y())
  Point add(Int y)
    this.with(y=y+this.y())
  }
CCode
Here you can see we declare a Wcode(Point) class with Wcode(x) and Wcode(y) Wcode(Int) coordinates.
Wcode(Data) is a decorator. Decorators are classes/objects that offers an operator Wcode(<<), called the babel fish operator,
whose goal is to translate a library into a "better" library.
In this case, Wcode(Data) is translating the class Wcode(`{Int x, Int y}') into a much longer class, with
a factory method taking in input the fields and initializing them, but also containing
 boring but useful definitions for
equality, inequality, conversions from and into human readable strings, xml and binary representations for (de)serialization.
WP
Finally, we declare methods to add to a single coordinate.
For very short methods we can omit the curly brackets and return.
Indeed method bodies are just expressions, and the curly brackets turn statements into expressions. 

In the method Wcode(add(x)) we show a constructor call and getters.
In the method Wcode(add(y)) we show an improved version, using the Wcode(with) method, another gift of Data, that allows us to easily create a clone with a
single field updated.
We can declare two methods, Wcode(add(x)) and Wcode(add(y)) with the same name, if parameter names are different.
WP
Note how we use always getters and we never access fields directly.
In many other languages we can use write Wcode(a.fieldName) and Wcode(a.fieldName=newValue). Such syntax do not exists in 42. Same goes for object instantiation; in many languages there is a special Wcode(new ClassName(..)) dedicated syntax, while in 42 it is just a method call.
WP
Also, similarly to what happens in python, we need to use Wcode(this.methodName()) to call methods when the receiver is Wcode(this).
While this makes some code more verbose, save us from the burden of  method hiding.   



WTitle((4/5)Decorators)
Decorators are one of the main concepts used by 42 programmers. We will encounter many decorators in this tutorial.
For now, just get used to the pattern of writing
Wcode(<<) to go from a minimal chunk of code, with method declarations for the important bits, to a fully fledged usable class.
Wlink(Decorators, More on decorators)

WTitle(`(5/5)Object creation, recall')
42 supports many different syntactic forms that are convenient to create objects:
<ul><li>
12Int: from a numeric representation
</li><li>
S"foo": from a string representation
</li><li>
Point(x=_,y=_): from the parameter values
</li><li>
Points[_;_;_]: from a variable length sequence of values; for example Wcode(Points) can be a list of Wcode(Point). We can instantiate Wcode(Points) by using the square brakets as shown later. 
</li></ul>

Note that in 42 those are all just expressions, and represents methods in the named class.
Sometime is convenient to reuse this kind of syntax to get better syntactic support for certain operations; for example the string class use square brakets to support string formatting.
Wlink(S, To understand it better: a guide to the S class)

WBigTitle(`Keep control: Modifiers, kinds of classes/references/objects')

WTitle(`(1/5)Kinds of classes')
Wcode(Point) is a WEmph(Immutable class): none of its field can be updated or mutated.
Immutable classes are very easy to use but may be inadequate when representing real objects, whose state can mutate across time.
A WEmph(Mutable class) is a class where the state of (some of) its instances may be mutated.

Lets now declare a Wcode(Animal) mutable class, whose location can be updated.
OCode
Animal:Data<<{
  var Point location
  mut method
  Void run() 
    this.location(this.location().add(x=20Int))
  }
CCode
There are two new keywords used here:
<ul><li>
the Wcode(location) field is declared Wcode(var).
  This is called a variable field, and can be updated by calling a setter.
  Non variable fields can not be updated
</li><li>
  the modifier "mut" in front of the method. 
  We have seen "class" already, an we have seen methods with the default modifier ( add(x) and add(y) ).
  mut methods can mutate the "this" object. If you have experience with C++ you can see the similarity with Wcode(const) methods.
  immutable (default) methods works only on immutable "this" objects. We will see later much more about modifiers
</li></ul>

WP
As you see, we are using the Wcode(add) method from before.
Also notice that we are using a setter here, where we are providing the first parameter without the argument name.
While usual in other languages, in 42 parameters are passed
by name.
However, for some methods with a single parameter writing down the parameter name would not improve the readability and just add noise.
In those cases the first parameter is conventionally called Wcode(that), 
and writing Wcode(a.b(that=c))
is equivalent to writing Wcode(a.b(c)).
This works also for methods with multiple parameters, if the first one is called Wcode(that).
We can use an animal by writing, for example:

OCode
  dog=Animal(location=Point(x=0Int, y=0Int))//type of the reference inferred
  mut Animal dogAlias=dog //this is the exact type 
  dog.run()
CCode

WTitle(`(2/5)Interaction between mutable and immutable')

We now explore some interaction between mutable and immutable objects.
OCode
Animal:Data<<{
  var Point location
  mut Points path
  mut method
  Void move() 
    this.location(path.first()))
    this.path().removeFirst()
  }
CCode


Here we use Wcode(mut Points path) to denote a mutable list of points. Note the absence of Wcode(var); this is conceptually similar to a Wcode(Points * const path;) in C++ or Wcode(final Points path;) in Java.
To contrast, the declaration Wcode(var Point location) is similar to
Wcode(Point const * location;) in C++ or Wcode(ImmPoint location;) in Java (for an opportune Wcode(ImmPoint) class).
That is, 
mutable objects can be referred using mutable references,
Immutable objects can be referred using immutable references.

This code models an animal following a path. It can be used like this.
OCode
  zero=Point(x=0Int, y=0Int)
  ps1=Points[ Point(x=12Int, y=20Int);Point(x=1Int, y=2Int)]
  ps2=Points[ zero;Point(x=1Int, y=2Int)]
  dog1=Animal(location=zero, path=ps1)
  dog2=Animal(location=zero, path=ps2)
  dog1.move()
  dog2.move()
CCode

In this code the first dog goes to 12:20.
The secon dog goes to 0:0. 

This code involve a mutable animal with a mutable field. This is often
a terrible idea, since its behaviour may depend on aliasing: what happens if two dogs follow the same paths?
OCode
  zero=Point(x=0Int, y=0Int)
  ps=Points[ Point(x=12Int, y=20Int);Point(x=1Int, y=2Int)]
  dog1=Animal(location=zero, path=ps)
  dog2=Animal(location=zero, path=ps)
  dog1.move()
  dog2.move()
CCode
The first dog moves and consumes the path also for the second one.
That is, the first goes to 12:20 and the second goes to 1:2.

This is because Wcode(Animal) is now a WEmph(Deeply mutable class): a mutable class with mutable fields. 
An amazing amount of bugs is caused by the usage of deeply mutable classes.

WTitle(`(3/5)Capsules: Keep aliasing graphs untangled')

This triky behaviour is correct for a 
deeply mutable class. 
In 42 we can change Wcode(Animal) to prevent this aliasing issue.
OCode
Animal:Data<<{
  var Point location
  capsule Points path
  mut method
  Void move() 
    this.location(path.first()))
    this.path().removeFirst()
  }
CCode
Now we use the modifier "capsule", this requires the field to be encapsulated with respect to aliasing.
Immutable objects do not influence aliasing, so they are free from aliasing limitations.

WP
The "capsule" modifier WEmph(enforce) the users to provide well encapsulated values, and WEmph(ensure) the Wcode(Animal) data is well encapsulated.
WP

Now the code of before would not compile. However we can still write the following variant
OCode
  zero=Point(x=0Int, y=0Int)
  capsule Points ps=Points[ Point(x=12Int, y=20Int);Point(x=1Int, y=2Int)]
  dog1=Animal(location=zero, path=ps)
  dog2=Animal(location=zero, path=Points[ Point(x=12Int, y=20Int);Point(x=1Int, y=2Int)])
  dog1.move()
  dog2.move()
CCode
Where the Wcode(ps) local binding is declared capsule, thus it can satisfy the Animal.path requirement, but it can be used only once.
dog2 have to use another capsule. It is ok to just write the object creation in place as is done.
Alternativelly, most classes offers a Wcode(clone()) method,
in this case we could write

Wcode(dog2=Animal(location=zero, path=dog1.ps().clone()))



WTitle(`(4/5)Immutable objects of Mutable classes')

How can we get an immutable Wcode(Animal)?
When an Wcode(Animal) is created using Wcode(Animal(location=__,path=__)) we create a Wcode(mut Animal).

In most cases you can promote such reference to immutable/capsule; just make the type of the local binding explicit.
 The type system will take care of the rest.
If a reference can not be safely promoted to immutable/capsule, you may have to use the Wcode(.clone()) method or to refactor your code.
OCode
  mut Animal dog1=Animal(__)//no promotion here
  Animal dog2=Animal(__)//promotion mutable->immutable
  dog1.move()
  //dog2.move() //ill-typed, requires a mut Animal
CCode

We will explain later the exact rules for promotion,
the main idea is that if the initialization expression uses local bindings in a controlled way, then promotion can be applied.
For example, a mutable expression using only capsule or immutable references can be promoted to capsule/immutable.

WTitle(read)

Use "read" when you do not care what is the mutability of an object.
For example, we could add to Wcode(Animal)

OCode
read method
Bool isArrived()
  this.path().isEmpty()
CCode
This method can be called to mutable and immutable animals:

OCode
Debug(dog1.isArrived())
Debug(dog2.isArrived())
CCode

WTitle(`(5/5) Recall')
  
WTitle(`Kinds of classes, recall')
  
<ul>
<li>
immutable classes: have only immutable fields.
It is usefull to model mathematical concepts.
It is easy to reason about code using immutable classes,
but some properties of real objects can be better modelled with state mutation.
</li><li>
shallow mutable classes: have only (variable) fields of immutable or capsule type (or class, as we will see later). 
Reasoning with shallow mutable classes is near as easy as reasoning with immutable ones, and often more natural.
</li><li>
deep mutable classes: have mutable fields.
Reasoning with deep mutable classes can be very hard.
</li></ul>
  
WTitle(`Modifiers up to now, recall')

<ul>
<li>
immutable: the default, when you omit the modifier,
 you mean immutable. 
An immutable reference points to an object that is never changing. Its whole reachable object graph never change and is immutable as well.

</li><li>
mutable: A mutable reference behave like normal reference in Java, C#,C++, Python and many other languages.
Mutable references allows to mutate the referred object.
</li><li>
capsule: local capsule references are used only once and they guaranteed that the whole reachable object graph is reachable only thought that
capsule reference. 
Local Capsule references provide a structured way to reason over deep mutable objects.

Fields can be annotate capsule, the meaning is that they need to be initialized/updated with capsule variables.
We will discuss more about capsule fields and how they differs from capsule local binding later.
 
</li><li>
read: A readable reference can not be used to mutate the referred object; but other mutable references pointing to the same object can mutate it.
Read references can point to both mutable and immutable objects.
It is easy to confound between read and immutable references.
As a rule of thumb, if you are in doubt if you should use an immutable or a readable, you probably want an immutable reference.

</li><li>

class: class references denote the class object,
  on methods the meaning is the same of static methods in many languages, but it can consistently be used on parameters/local variables/fields
to encode behaviours similar to dependency injection.


</li><li>
lent: we still need to see the lent modifier; a hygienic mutable reference allowing mutation but not storage (more on lent later).
</li></ul>



WTitle(`Kinds of objects, recall')

<ul>
<li>
immutable: objects 
 can be instances of immutable classes, or promoted instances of mutable classes.
 They
can be referred only by immutable and read references.
</li><li>
mutable: objects are instances of mutable classes.
They can be referred by capsule, mutable, lent and read references.
</li><li>
class: objects are instances of themselves.
They can be referred only by class references, either of their class or of one transitivelly implemented interface.
</li></ul>




WBigTitle(not ready to read yet Libraries)

WTitle(Libraries)
42 stands for the primate of libraries, so let see some libraries in action.
We have already see how to chose a towel, and many classes that are likely to be present in such towel, like
Int and Data.
Let see now how to load a library from its url:
OCode
{reuse L42.is/AdamTowel
Gui: Load<<{reuse L42.is/Gui}
Main:{
  Gui.alert(S"hi!")
  return ExitCode.success()
  }
}
CCode
Load is another decorator, here it modifies the library found in L42.is/Gui so that it can be used easly from AdamTowel.
OCode
{reuse L42.is/AdamTowel
Collections: Load<<{reuse L42.is/Collections}
Point:Data<<{Int x, Int y}
Points:Collections.vector(of:Point)
Main:{
  ps=Points[ Point(x=12Int, y=20Int);Point(x=1Int, y=2Int);]
  var tot=0
  with p in ps (tot+=p.x()+p.y())
  return ExitCode.success()
  }
}
CCode
A very large class of practically useful programs can be obtained by just declaring smart structs using Data and Collections.




WTitle(Collections)
Declaring and using collections is simple and easy in 42.
For example, we can declare and use a list of  Wcode(Point) by writing
OCode
Points:Collections.mutList(Point)

...

zero=Point(x=0Int, y=0Int)
one=Point(x=1Int, y=1Int)
ps0=Points[]//the empty list
ps1=Points[zero;one]//contains zero, one
ps2=Points[zero;one]//contains zero, one

CCode



<!--OCode Library myCode={ method Int foo()} CCode
A local binding of type Library initialized with a class with a single Wcode(foo()) method. Since there is no body, it is an abstract method.
 -->	 

 <!--WTitle(Simpler complete program)

Let now starts showing the simplest 42 program: an empty library.

OCode {} CCode

If we save this valid program in a file Wcode(Test.L42) and we run Wcode(L42 Test), we get an error.
WP
As you see 42 is very intuitive, as you would expect from your former life experiences, most simple things just does not work.
Note how valid programs can produce errors.
We will soon learn how to produce errors in controlled and elegant ways.
-->
<!--A 42 program execution WEmph(is) the generation of all its nested classes/interface.
, code is simply executed from top to bottom as in 
Python, Javascript or Php. However, the
top level expression is a Library, and code can go in libraries 
as an initializer for you need to put the code into an expression
-->

<!-- LATER?
Wcode(MyCode.hello(..)) use directly the Wcode(MyCode) class instance as receiver. We can also give it a name 
e se vuoi puoi anche salvarlo su un binding locale, tipo x=MyCode  x.hello(...)
-->
 
m4_include(`footer.h')m4_dnl
