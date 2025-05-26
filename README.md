# busybox-w32-shims

BusyBox for Windows, application shims, providing an alternative installation method to _busybox --install_.

Providing an installation for environments where links can not be created or are unsuitable.

Simply unzip the application shims into a target directory along-side a current busybox for windows binary.

## Example Installation:

 * Download _busybox-shims-x86.zip_ or _busybox-shims-x64.zip_, dependent on your requirements.

 * Download the current busybox from https://frippery.org/busybox.

 * Local installation

        mkdir c:\busybox
        unzip C:\Users\%USERNAME%\Downloads\busybox-shims-x86.zip c:\busybox
        copy  C:\Users\%USERNAME%\Downloads\busybox.exe c:\busybox

 * Add the installation directory to your PATH.

## Usage

Once installed, busybox commands can be executing using their _applet_ name, for example:

        $ ./grep

        BusyBox v1.37.0-FRP-5007-g82accfc19 (2023-05-28 10:59:20 BST)

        Usage: grep [-HhnlLoqvsrRiwFE] [-m N] [-A|B|C N] {PATTERN|-e PATTERN...| -f FILE...} [FILE]...

        Search for PATTERN in FILEs (or stdin)

                -H      Add 'filename:' prefix
                -h      Do not add 'filename:' prefix
                -n      Add 'line_no:' prefix
                -l      Show only names of files that match
                -L      Show only names of files that don't match
                -c      Show only count of matching lines
                -o      Show only the matching part of line
                -q      Quiet. Return 0 if PATTERN is found, 1 otherwise
                -v      Select non-matching lines
                -s      Suppress open and read errors
                -r      Recurse
                -R      Recurse and dereference symlinks
                -i      Ignore case
                -w      Match whole words only
                -x      Match whole lines only
                -F      PATTERN is a literal (not regexp)
                -E      PATTERN is an extended regexp
                -m N    Match up to N times per file
                -A N    Print N lines of trailing context
                -B N    Print N lines of leading context
                -C N    Same as '-A N -B N'
                -e PTRN Pattern to match
                -f FILE Read pattern from file

## Applets

List of current applets.

  * ar
  * arch
  * ascii
  * ash
  * awk
  * base32
  * base64
  * basename
  * bash
  * bc
  * bunzip2
  * busybox
  * bzcat
  * bzip2
  * cal
  * cat
  * cdrop
  * chattr
  * chmod
  * cksum
  * clear
  * cmp
  * comm
  * cp
  * cpio
  * crc32
  * cut
  * date
  * dc
  * dd
  * df
  * diff
  * dirname
  * dos2unix
  * dpkg-deb
  * dpkg
  * drop
  * du
  * echo
  * ed
  * egrep
  * env
  * expand
  * expr
  * factor
  * false
  * fgrep
  * find
  * fold
  * free
  * fsync
  * ftpget
  * ftpput
  * getopt
  * grep
  * groups
  * gunzip
  * gzip
  * hd
  * head
  * hexdump
  * httpd
  * iconv
  * id
  * inotifyd
  * ipcalc
  * jn
  * kill
  * killall
  * less
  * ln
  * logname
  * ls
  * lsattr
  * lzcat
  * lzma
  * lzop
  * lzopcat
  * man
  * md5sum
  * mkdir
  * mktemp
  * mv
  * nc
  * nl
  * nproc
  * od
  * paste
  * patch
  * pdpmake
  * pdrop
  * pgrep
  * pidof
  * pipe_progress
  * pkill
  * printenv
  * printf
  * ps
  * pwd
  * readlink
  * realpath
  * reset
  * rev
  * rm
  * rmdir
  * rpm
  * rpm2cpio
  * sed
  * seq
  * sh
  * sha1sum
  * sha256sum
  * sha3sum
  * sha512sum
  * shred
  * shuf
  * sleep
  * sort
  * split
  * ssl_client
  * stat
  * strings
  * su
  * sum
  * sync
  * tac
  * tail
  * tar
  * tee
  * test
  * time
  * timeout
  * touch
  * tr
  * true
  * truncate
  * ts
  * tsort
  * ttysize
  * uname
  * uncompress
  * unexpand
  * uniq
  * unix2dos
  * unlink
  * unlzma
  * unlzop
  * unxz
  * unzip
  * uptime
  * usleep
  * uudecode
  * uuencode
  * vi
  * watch
  * wc
  * wget
  * which
  * whoami
  * whois
  * xargs
  * xxd
  * xz
  * xzcat
  * yes
  * zcat

Note the following are explicity prefixed with "busybox-", as they generally clash with local development tools:

  * install
  * link
  * make
  
If further local conflicts arise, the straightforward solution is to rename the shim in a similar manner, 
for instance:

    $ .\busybox date -u
    Sun May 25 12:59:01 UTC 2025

    $ .\date -u
    Sun May 25 12:59:04 UTC 2025   

    $ mv date.exe busybox-date.exe

    $ .\busybox-date -u
    Sun May 25 12:59:36 UTC 2025
