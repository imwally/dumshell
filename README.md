# dumshell
The dumb shell that dumps information about the current UNIX process. Seriously, this is a dumb shell. Don't use it.

```
wally@io (~/Code/dumshell) ./dumshell
Hello wally,

Welcome to the dumshell -- a dumb shell that dumps UNIX process information to STDOUT.

Use the command 'exit' to leave the shell at anytime.

Here is some information about this current process:
----
Current working directory (CWD): /Users/wally/Code/dumshell
User running this process (UID): 501
Parent Process (PPID): 1155
Current Process (PID): 1974
----
% ./dumshell
>>>> Process 1975 forked from 1974 <<<<
Hello wally,

Welcome to the dumshell -- a dumb shell that dumps UNIX process information to STDOUT.

Use the command 'exit' to leave the shell at anytime.

Here is some information about this current process:
----
Current working directory (CWD): /Users/wally/Code/dumshell
User running this process (UID): 501
Parent Process (PPID): 1974
Current Process (PID): 1975
----
% date
>>>> Process 1976 forked from 1975 <<<<
Wed Sep 21 23:11:06 EDT 2016
>>>> Returning to parent process 1975 <<<<
% whoami     
>>>> Process 1977 forked from 1975 <<<<
wally
>>>> Returning to parent process 1975 <<<<
% exit
>>>> Returning to parent process 1974 <<<<
% exit
wally@io (~/Code/dumshell) 
```

### But, why?

I started reading [APUE](http://www.apuebook.com/) and wanted to get a feel for how UNIX processes fork and exec from another parent process. The code is mostly identical to the example taken from Figure 1.10 of Chapter 1.
