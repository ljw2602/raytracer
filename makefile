CC=g++
CFLAGS=-I.
DEPS=vec3.h ray.h hitable.h hitable_list.h sphere.h camera.h material.h
OBJ=raytracer.o vec3.o ray.o hitable.o hitable_list.o sphere.o camera.o material.o

%.o: &.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

raytracer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
