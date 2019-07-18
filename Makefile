CFLAGS   = -Wall -Wextra -mtune=native -no-pie `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = 0 0a 1 2 3 3a 3a1 4 4a 4b 4c main 5 5a 5b 5c 5d 6

.PHONY: all
all: $(TARGETS)

0: $(srcdir)helper.c $(srcdir)0.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

0a: $(srcdir)helper.c $(srcdir)0a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

1: $(srcdir)helper.c $(srcdir)1.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

2: $(srcdir)helper.c $(srcdir)2.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

3: $(srcdir)helper.c $(srcdir)3.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

3a: $(srcdir)helper.c $(srcdir)3a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

3a1: $(srcdir)helper.c $(srcdir)3a1.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

4: $(srcdir)helper.c $(srcdir)4.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

4a: $(srcdir)helper.c $(srcdir)4a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

main: $(srcdir)helper.c $(srcdir)main.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

4b: $(srcdir)helper.c $(srcdir)4b.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

4c: $(srcdir)helper.c $(srcdir)4c.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5: $(srcdir)helper.c $(srcdir)5.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5a: $(srcdir)helper.c $(srcdir)5a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5b: $(srcdir)helper.c $(srcdir)5b.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5c: $(srcdir)helper.c $(srcdir)5c.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5d: $(srcdir)helper.c $(srcdir)5d.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

6: $(srcdir)helper.c $(srcdir)6.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

# ----------------------------------------------------------------------------------

# $<	die erste Abhängigkeit
# $@	Name des targets
# $+	eine Liste aller Abhängigkeiten
# $^	eine Liste aller Abhängigkeiten,
# 	wobei allerdings doppelt vorkommende Abhängigkeiten eliminiert wurden.

# while inotifywait -e close_write ./src/4c.c; do sleep 0.02; make; done

# while inotifywait -e close_write ./anim.c; do date +%X; make > /dev/null; done

