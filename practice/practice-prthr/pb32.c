// 32. Write a C program that creates N threads (N given as a command
// line argument). The main process opens a file F, provided as a command
// line argument (the file's contents are words of a maximum of 20
// characters each separated by spaces). Each thread will take turns
// reading between 1 and 3 words from the file and concatenating them to
// a thread-local buffer until all the content of the file is read. Once
// the whole file is completely read, the threads return their local
// buffer and the main process will print the result from each thread.
// After it does one reading pass, ensure that each thread waits for the
// other threads to complete their reading attempt before starting a new
// reading pass.

