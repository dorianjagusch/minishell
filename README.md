# minishell
As beautiful as a shell

In this group project with Dorian Jagusch we wrote our very own shell. Using readline we take the passed line and after lexing, retokenizing and parsing the line we will either execute it finding it's binary in the PATH or execute it using our own builtin functions if the command is echo, cd, export, env, unset, or pwd.

To use the shell just git clone and make. We tried to mimic the behavior of bash and so the program will have matching output as bash.