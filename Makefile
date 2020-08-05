AR     := ar
CC     := gcc

CPPFLAGS := -Wall -Werror -std=c99
CFLAGS   := -g -O0
LDFLAGS  :=
LIBS     :=

output := test.exe
src    := tree234.c test.c
objs   := $(patsubst %.c,%.o,$(src))
deps   := $(patsubst %.c,%.d,$(src))

$(output): $(objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

-include $(deps)
$(objs): %.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(deps)
	$(RM) $(objs)
	$(RM) $(output)
