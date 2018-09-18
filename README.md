# oslab
Operating System-based projects explored and implemented chapter-wise. 
The programs are inspired from end-of-chapter projects in Silberchatz's _Operating System Concepts_.

## List of projects fully implemented

### Projects concurrent with chapters from Silberchatz's _Operating System Concepts_, 9th edition.
<ul>
	<li> Linux Kernel Modules (Chapter #2)
	<li> Simple UNIX Shell (Chapter #3)
	<li> Sudoku Solution Validator (Chapter #4)
	<li> Multithreaded Sorting Application (Chapter #4)
</ul>
  
### Projects indepentdent of chapters from any book
<ul>
	<li> Producer-Consumer problem
	<li> PING-PONG problem
</ul>

## Running a multhreaded program

### Prerequisites
1. These programs are tested in Linux Ubuntu, Fedora and Debain. They do not run in Windows; you will need a **Linux OS** to run them.
2. You will need a **Terminal** to execute commands.
3. You will require a **C-compiler**, preferably `gcc`.

### Procedure
At first, open a Terminal and `cd` your way through the directory whose program you want to run. Then, run the commands required to execute a multithreaded program.

For example, in order to run `shell.c` inside of Simple-UNIX-shell directory,
<ul>
	<li> Open a Terminal
	<li> Reach the folder.
	<li> Compile the program (ignore warnings generated, if any).
	<li> Run the executable
</ul>
Like this:

	# move to the desired directory
	cd Simple-UNIX-shell

	# link pthreads library and compile; ignore warnings, if any
	gcc shell.c -pthread -o myShell 

	# run the executable
	./myShell

## Testing environment
All programs were created and executed on a **Linux Debian** virtual OS running atop my Windows 8.1 native OS via VMware Workstation.

The Debian virtual OS I used was the official virtual OS provided as a student resource here: http://www.os-book.com/ 

### Disclaimer
<li> All the starter code for each project was readily available in the virtual OS. I only had to add upon them as per the instructions given in the book. I did not create the programs from scratch.
<li> I have not copied the code from elsewhere, nor do I claim the code to be error free or the official solutions. 
Please <em>do not</em> copy-paste my code as homework solutions.
<li> In case of any error, feel free to create an Issue, or email me: <a href="mailto:alimdrafi@gmail.com" target="_blank"> alimdrafi@gmail.com </a>
