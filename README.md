# vec2web - README

vec2web - Vector to web graphics convertor (C) 2000 Andrew Mustun

Version 0.1.1

vec2web is a program to convert DXF files to various formats.  This is a fork
of the code in order to fix a few issues for my own purposes and bring it up
to date to allow for compilation on semi-modern systems.  Hopefully eventually
it will involve updating to QT4 and overhauling much of it, but that is in the
distant future.

vec2web is a small tool to convert vector drawings (currently DXF) to graphics
which can be used on the web (currently PNG). However,  vec2web can also
convert DXF drawings to PS (post script) and WBMP (wireless bitmap) or display
them in an X11 or Windows window.

## Dependencies

As of right now vec2web itself depends only on qt3 and the libraries included
here and the scripts to convert to pdf also add a dependency of ps2pdf which
is installed on most unix systems I believe.

## Future Plans

I intend to update this to Qt4 ASAP. In fact, I am hoping it won't need much
work to do so, but I don't have time to do it right at this moment. Also, more
flexibility in the system is required, to allow for rendering in different
locations on the page, and to automatically scale down renders if needed.  And
of course fix some hardcoded assumptions like the location of fonts and
packages.


## License Information

This program is covered with GNU General Public License (GPL).


## CONTACT

You can contact the author by e-mail at [andrew@mustun.com][] or visit the vec2web home page on: [http://vec2web.sourceforge.net/][]
