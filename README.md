# busybox-w32-shim

BusyBox for Windows, application shims, providing an alternative installation method to _busybox --install_.

Providing an installation for environments where links can not be created or are suitable.

Simply unzip the application shims into a target directory along-side a current busybox for windows binary.

## Example Installation:

 * Download _package-x86.zip_ or _package-x64.zip_, dependent on your requirements.

 * Download the current busybox from https://frippery.org/busybox.

 * Local installation
    
        mkdir c:\busybox
        unzip C:\Users\%USERNAME%\Downloads\package-x86.zip c:\busybox
        copy  C:\Users\%USERNAME%\Downloads\busybox.exe c:\busybox

 * Add the installation directory to your PATH.   

## Usage

Once installed, busybox commands can be executing using their _applet_ name, for example:
       
        $ ./grep
        
        BusyBox v1.37.0-FRP-5007-g82accfc19 (2023-05-28 10:59:20 BST)
   
        Usage: grep [-HhnlLoqvsrRiwFE] [-m N] [-A|B|C N] { PATTERN | -e PATTERN... | -f FILE... } [FILE]...
   
        Search for PATTERN in FILEs (or stdin)

	        -H	Add 'filename:' prefix
	        -h	Do not add 'filename:' prefix
	        -n	Add 'line_no:' prefix
	        -l	Show only names of files that match
	        -L	Show only names of files that don't match
	        -c	Show only count of matching lines
	        -o	Show only the matching part of line
	        -q	Quiet. Return 0 if PATTERN is found, 1 otherwise
	        -v	Select non-matching lines
	        -s	Suppress open and read errors
	        -r	Recurse
	        -R	Recurse and dereference symlinks
	        -i	Ignore case
	        -w	Match whole words only
	        -x	Match whole lines only
	        -F	PATTERN is a literal (not regexp)
	        -E	PATTERN is an extended regexp
	        -m N	Match up to N times per file
	        -A N	Print N lines of trailing context
	        -B N	Print N lines of leading context
	        -C N	Same as '-A N -B N'
	        -e PTRN	Pattern to match
	        -f FILE	Read pattern from file
        
