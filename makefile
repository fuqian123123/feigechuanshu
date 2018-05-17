myclient:
	$(CC) ./my-tcp/tcp-op.c ./my-udp/udp-op.c ./util/util.c main.c -o myclient -lpthread
clean:
	rm -rf ./myclient
