# busybox-w32-shim

BusyBox for Windows, application shims, providing an alternative installation method to ```busybox --install <target>```.
Providing an installation with a small smaller storage foot print.

Simply unzip the application shims into a target directory along-side a current busybox for windows binary.

Example Installation:

    o Download _package-x86.zip_ or _package-x64.zip_, dependent on your requirements.

    o Download the current busybox from https://frippery.org/busybox.

    o Local installation
    
        mkdir c:\busybox
        unzip C:\Users\%USERNAME%\Downloads\package-x86.zip c:\busybox
        copy  C:\Users\%USERNAME%\Downloads\busybox.exe c:\busybox

    o Add the installation directory to your PATH.   
