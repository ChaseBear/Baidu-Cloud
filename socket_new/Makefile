all: fdata   ffile
ffile: file_server.o   dofile.o
		gcc $^ -o $@ 
file_server.o: file_server.c 
		gcc $^ -o $@ -c
dofile.o: dofile.c  
	 	gcc $^ -o $@ -c
fdata: linklist.o tcp_server.o
			gcc $^ -o $@ 
linklist.o: linklist.c
	 		gcc $^ -o $@ -c
tcp_server.o: tcp_server.c
	        gcc $^ -o $@ -c
clean:
	         rm *o
	
install:
	 	   mv fdata /usr/bin
	 	   mv ffile /usr/bin
uninstall:
	 	   mv /usr/bin/ffile /usr/bin/fdata
