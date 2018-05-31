main:
	$(CC) ./util/util.c ./my-tcp/tcp-op.c ./my-udp/udp-op.c ./user/user-op.c ./my-ds/ds-op.c ./file/file-op.c  main.c -o main -lpthread
clean:
	rm -rf ./main