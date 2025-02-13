/*
handling >, >>, <, <<, etc:
- parse input tokens, looking for redirects
- get following file name
- remove the tokens from that array
- in child process
  - open the file witih whatever flags
  - redirect the I/O (dup2???)
  - close up file descriptors
  - unless I missed something, execve
- probably need _strcmp for this
- cases could include multiple redirects, no file name, invalid file name, whatever
*/
