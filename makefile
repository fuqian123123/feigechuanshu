myclient:
	$(CC) ./my_tcp/tcp_op.c ./my_udp/udp_op.c ./util/util.c main.c -o myclient -lpthread
clean:
	rm -rf ./myclient
