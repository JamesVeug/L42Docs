m4_include(`header.h')m4_dnl

WTitle(`First, read in any order those introductions')
<Button class='button' type='button' onclick='selectDiv("a");'>
Why 42
</Button>
<Button class='button' type='button' onclick='selectDiv("b");'>
Learn by examples
</Button>

<Button class='button' type='button' onclick='selectDiv("c");'>
Pure OO
</Button>

<Button class='button' type='button' onclick='showAll(allDivs);'>
Show all content
</Button>


<Div id="a"><p>
WTitle(Why 42)
42 is a new programming language,
the name is inspired by The Hitchhiker's Guide to the Galaxy.
The language goal is to allow the transparent cooperation and composition of millions of libraries at the same time.
WP
In 42 you will be able to import libraries just by naming them and to
compose them in your code without worrying of their dependencies.
Normally libraries are big monolitic things, coming from outside and manually imported/installed. The user have little control on
the library code, and the library have no influence on the importing context.
WP
In 42 Libraries are usually much smaller and are first class entities, that can be manipulated as values,loaded, stored, modified, adapted, saved or simply used. You will write code that manipulate libraries, but more importantly you will use libraries that manipulate libraries in non trivial ways.
Indeed in 42 manipulating libraries is so natural that is convenient to think of your own code as a library that you offer to yourself only.
WP
42 enforce a high level of abstraction, thus there is no access to primitive
structures like arrays (just use collections), and there is no concept of null or default initialization.
While is possible to write in a fully functional style in 42, usually 42 programs mix
WEmph(`mutable datastructure with aliasing')
and
WEmph(`deeply immutable data').
Indeed 42 offers powerful support for aliasing control and immutability, helping in mixing the two stiles in an easy and natural way.

WP
42 offers (well, will offer) automatic parallelism: thanks to immutability and aliasing control, many patterns of normal sequential code will be safely be executed in parallel.

</p></Div>

m4_include(`syntaxCompare.h')m4_dnl


<Div id="c"><p>
WTitle(Pure and fair Object Oriented language)
42 is a pure object oriented language,
where every value is an object. This means that:
<ul>
<li>
Numbers are objects, 
so thay can have methods like Wcode(.sqrt()) or Wcode(.abs()). 
</li><li>
All operators are just method calls, thus Wcode(a + b) is sugar for Wcode(a.operator+(b)), and so on. Note how Wcode(operator+) is a valid method name.
Any class that offers that method supports the operator.

</li><li>
Classes are objects, when you write Wcode(Foo.bar()) you refer to the method Wcode(.bar()) offered by the object denoted by Wcode(Foo).
class objects are just objects, and you can also store them in local bindings if you wish, as in Wcode(x=Foo)
</li><li>
The code is an object, but only at the granularity of 
Libraries, that is, balanced pairs of curly brackets representing classes (or interfaces) with methods and nesteds.
This is usefull for meta-programming, as we will see later this is the most important feature of 42.


</li><li>
Differently from other pure object oriented languages, in 42
all objects have the same treatment, both syntactically and semantically.
For example Wcode(x = S"Hello " ++ S"World")
This is a declaration for a local binding Wcode(x), using the string class Wcode(S) and the operator Wcode(++),
used as string (or in general sequence/collection) concatenation.

Coming from another programming language, you many be surprised that we have to write Wcode(S) before Wcode("Hello ") and Wcode("World").
This extra verbosity is need to provide fair treatment to all classes. (Wlink(note1,see more))
In 42 we do not give preferential treatment
to special object/classes. In this sense, we consider
most other languages to be racist.
They give priority to their "preferred" version of numbers and strings, and this puts into a position of unfair disadvantage library code trying to define its own numbers kinds.
Instead in 42 you may encounter strings like Wcode(URL"www.google.com") or
 Wcode(EMAIL"Artur.Dent@gmail.com").
The same for numeric classes: to talk about a street, 20 meters long, you would write
Wcode(streetLenght=20Meter).
Note that we write the class name after the number,
while usually the class name is before.
42 is a little incoherent in this point, both for better readability and because Wcode(Meter20) would be consider an identifier by the parser.
You may encounter Wcode(Int), Wcode(UInt), Wcode(Float),Wcode(Size), Wcode(Meter), Wcode(Kg), Wcode(Second), Wcode(Year), Wcode(PhoneNumber) and many other numeric classes.
</li></ul>

WTitle(A simple language)
We believe 42 is a simple language,
where all classes are final and interfaces are the only instrument to obtain subtyping.
Moreover, 42 do not offers many controversial features usually found in other programming
languages, including:
(method) overloading, threading, numeric conversions and cohercions,
casts, var-args, primitive types and automatic (un-)boxing,
inner classes, arrays, generics, methods fields and local variable hiding,
closures/lambdas and null.


</p></Div>

WTitle(`Now, dig into the tutorial!')

Wlink(tutorial,`Lets board the Vogon ship')


m4_include(`footer.h')m4_dnl
