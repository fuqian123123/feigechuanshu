myclient:
	$(CC) ./util/util.c ./my-tcp/tcp-op.c ./my-udp/udp-op.c ./user/user-op.c ./my-ds/ds-op.c ./file/file-op.c  main.c -o myclient -lpthread
clean:
	rm -rf ./myclient
