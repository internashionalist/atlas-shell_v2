Ariel:
* cd implementation
+ make strcspn
+ make strcmp
+ make strlen

Chepe:
* Which prototype
+ string prototypes


Nash:
* Implement the setenv and unsetenv builtin commands

+ setenv
+ Initialize a new environment variable, or modify an existing one
+ Command syntax: setenv VARIABLE VALUE
+ Should print something on stderr on failure
* unsetenv
+ Remove a environment variable
+ Command syntax: unsetenv VARIABLE
+ Should print something on stderr on failure