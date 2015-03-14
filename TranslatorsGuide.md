# Introduction #

This guide should give some lights on how to translate `400plus` project to your language.

# Details #

With the Easter (2012) release it is now very easy to translate `400plus` to any language. (this includes the languages not supported by the camera).

First, you need to download the latest version of  [new\_lang.ini](http://400plus.googlecode.com/svn/trunk/languages/new_lang.ini) file. This is the base template (written in English) which you will translate.

Translating the file should be pretty straightforward, but you will have to obey one rule: _DO NOT USE MS-Windows's Notepad_. It does not support UTF-8 and will brake the translations. Use UTF-8 capable editor as [Notepad++](http://notepad-plus-plus.org/) (free).

After you translate the file, save it as "languages.ini", and put it on the camera, replacing the original one. (and use the latest [source release](https://googledrive.com/host/0B66DLxueQUdxRDVsYTQtR2VSNFU) if possible)

Test what you have done.

If you are satisfied, open a new [issue](http://code.google.com/p/400plus/issues/entry?template=Feature%20request) and put into the summary line something like: 'My Language translations'.
_Do not forget to attach the file_.

That's all, Enjoy.