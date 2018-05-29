myclient:
	$(CC) ./my-tcp/tcp-op.c ./my-udp/udp-op.c ./util/util.c ./user/user.c ./file/file.c ./my-ds/ds-op.c main.c -o myclient -lpthread
clean:
	rm -rf ./myclient
