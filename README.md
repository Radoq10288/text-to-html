# Make txt to html

## About
A program that accept a text (\*.txt) file and convert it to html (\*.html) file.
<br><br>

## How to use
To convert a text file to html file:

```
$>make-th <filename of text file> --title "My Webpage"
```

__Options:__<br>
* -t, \--title <title\> = set the title tag of the html file.<br>
* -h, \--help = show some text that tells how to use the program.<br>
* -v, \--version = show the current version of the program.<br>
<br>
__Note:__<br>
If '-t \\ \--title' option is omitted, it will take a default title of 'My Webpage'.
<br><br>

## Installation note
This program is build from source and installed using ```make && make install```. The installation
directory will be on ```/home/user/local``` directory of any linux distribution.<br>
<br>
To use the program installed in this directory, add the following to the ```.bashrc```
file.<br>
<br>
```
export PATH=$PATH;/home/<your-user-name>/local/bin
```

<br>

## About
This program is free and open-source with the license of GNU General Public
License Version 2. Please see [```COPYING```](COPYING) for details.
<br><br>


