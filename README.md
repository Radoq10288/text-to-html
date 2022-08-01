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
To build, compile, and install *make-t2h* in debug build, just run the following command:<br>

```
$> make

$> make install
```
<br>

To build, compile, and install in release build, run the following command:<br>
```
$> make release

$> make install
```

Then manually add ```~/local/bin``` to the environment variable *Path*.<br>
<br>
__Installation note:__<br>
In linux, to use the program installed in this directory, add the following to the ```.bashrc```
file.<br>
<br>
```
export PATH=$PATH:~/local/bin
```


In windows, to use this program installed in the same directory (expecting that you installed the required MinGW), add the following to the ```Path``` environment variable.<br>
<br>
```
C:\MinGW\msys\1.0\home\<your-user-name>\local\bin
```

<br>

## How to use
To convert a text file to html file:

```
$> make-t2h <filename of text file> --title "My Webpage"
```


__Options:__<br>
* -t, \--title <title\> = set the title tag of the html file.<br>
* -h, \--help = show some text that tells how to use the program.<br>
* -v, \--version = show the current version of the program.<br>
<br>

__Note:__<br>
If '-t\--title' option is omitted, it will take a default title of 'My Webpage'.
<br><br>

## Simple pattern to follow
To properly convert a text file to html, strictly follow this one very simple
rule:<br>
<br>
```
"Provide a single empty line between paragraph"
```

For a sample, copy & paste this three paragraph ramdom text I get somewhere out
there, to any text editor and save it. And try to convert this to an html file.<br>
```
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Velit scelerisque in dictum non consectetur a erat. Sit amet justo donec enim diam vulputate. Id aliquet lectus proin nibh nisl condimentum id venenatis a. Eget gravida cum sociis natoque penatibus et magnis dis. Habitant morbi tristique senectus et netus et. Interdum consectetur libero id faucibus nisl tincidunt eget nullam. Aliquam purus sit amet luctus. Fringilla ut morbi tincidunt augue interdum velit. Neque sodales ut etiam sit. Quam viverra orci sagittis eu volutpat odio facilisis mauris. Ornare suspendisse sed nisi lacus sed. Iaculis at erat pellentesque adipiscing commodo elit at imperdiet dui. Quam nulla porttitor massa id neque aliquam vestibulum morbi. Dignissim diam quis enim lobortis scelerisque fermentum dui faucibus. Turpis egestas integer eget aliquet.

In nisl nisi scelerisque eu ultrices vitae auctor eu. Dolor sit amet consectetur adipiscing elit duis. Tortor dignissim convallis aenean et tortor at. Iaculis at erat pellentesque adipiscing commodo. Viverra suspendisse potenti nullam ac tortor. Elementum nibh tellus molestie nunc non blandit massa enim. Ultricies integer quis auctor elit sed. Varius vel pharetra vel turpis nunc eget lorem dolor. Sit amet massa vitae tortor condimentum. Adipiscing elit ut aliquam purus sit amet luctus venenatis lectus. Nascetur ridiculus mus mauris vitae ultricies leo integer.

Urna nunc id cursus metus. Id leo in vitae turpis massa. Blandit turpis cursus in hac habitasse platea. Feugiat sed lectus vestibulum mattis ullamcorper. Diam sit amet nisl suscipit adipiscing bibendum est. Enim nunc faucibus a pellentesque sit amet porttitor eget dolor. Enim eu turpis egestas pretium aenean pharetra. Amet mattis vulputate enim nulla aliquet. Tristique et egestas quis ipsum suspendisse ultrices gravida dictum fusce. Risus commodo viverra maecenas accumsan lacus vel. Eu mi bibendum neque egestas congue quisque egestas diam in. Fermentum odio eu feugiat pretium nibh ipsum consequat.

```

Observe properly the empty lines between paragraphs. This will be used by the program to identify where the opening \<p\> tag and closing \</p\> tag will be placed.<br>
<br><br>

## About
This program is free and open-source with the license of GNU General Public
License Version 2. Please see [```COPYING```](COPYING) for details.
<br><br>


