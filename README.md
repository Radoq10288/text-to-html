# Make txt to html

## About
A program that accept a text (\*.txt) file and convert it to html (\*.html) file.
<br><br>

## Requirement
An installation of MinGW is required to build, compile, and install this program in windows.<br>
<br>
__Note:__<br>
For those who are new to using MinGW, after installing it, please
read <a target="_blank" href="https://opensource.com/article/20/8/gnu-windows-mingw" title="Use GNU on Windows with MinGW">this</a> to set it properly.
<br><br>

## How to build, compile, and install
To build and compile *cpps*, just run the following command:<br>

```
$>make
...
$>make install
```

Then manually add ```~/local/bin``` to the environment variable *Path*.<br>
<br>
__Installation note:__<br>
In linux, to use the program installed in this directory, add the following to the ```.bashrc```
file.<br>
<br>
```
export PATH=$PATH;~/local/bin
```

<br>

## How to use
To convert a text file to html file:

```
$>make-t2h <filename of text file> --title "My Webpage"
```

__Options:__<br>
* -t, \--title <title\> = set the title tag of the html file.<br>
* -h, \--help = show some text that tells how to use the program.<br>
* -v, \--version = show the current version of the program.<br>
<br>
__Note:__<br>
If '-t\--title' option is omitted, it will take a default title of 'My Webpage'.
<br><br>

## About
This program is free and open-source with the license of GNU General Public
License Version 2. Please see [```COPYING```](COPYING) for details.
<br><br>


