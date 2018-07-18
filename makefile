CFLAGS=-Wall -g -lpthread
target=main
obj=main.o udp-op.o tcp-op.o file-op.o user-op.o ds-op.o util.o

$(target):$(obj)
	$(CC) $^ -o $@ $(CFLAGS)
main.o:main.c
	$(CC) -c $< -o $@ $(CFLAGS)
udp-op.o:./my-udp/udp-op.c ./my-udp/udp-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
tcp-op.o:./my-tcp/tcp-op.c ./my-tcp/tcp-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
ds-op.o:./my-ds/ds-op.c ./my-ds/ds-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
file-op.o:./file/file-op.c ./file/file-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
user-op.o:./user/user-op.c ./user/user-op.h
	$(CC) -c $< -o $@ $(CFLAGS)
util.o:./util/util.c ./util/util.h
	$(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm -rf $(obj) $(target)
