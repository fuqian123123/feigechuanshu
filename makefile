CFLAGS=-Wall -g
#main:
#	$(CC) ./util/util.c ./my-tcp/tcp-op.c ./my-udp/udp-op.c ./user/user-op.c ./my-ds/ds-op.c ./file/file-op.c  main.c -o main -lpthread
tcp-op.o:./my-tcp/tcp-op.c ./my-tcp/tcp-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
file-op.o:./file/file-op.c ./file/file-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
util.o:./util/util.c ./util/util.h
	$(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm -rf ./main *.o
