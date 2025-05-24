# busybox-w32-shim

BusyBox for Windows, application shims, providing an alternative installation method to _busybox --install_.
Providing an installation with a smaller storage foot print.

Simply unzip the application shims into a target directory along-side a current busybox for windows binary.

Example Installation:

 * Download _package-x86.zip_ or _package-x64.zip_, dependent on your requirements.

 * Download the current busybox from https://frippery.org/busybox.

 * Local installation
    
        mkdir c:\busybox
        unzip C:\Users\%USERNAME%\Downloads\package-x86.zip c:\busybox
        copy  C:\Users\%USERNAME%\Downloads\busybox.exe c:\busybox

 * Add the installation directory to your PATH.   
