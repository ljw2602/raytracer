CC=g++
CFLAGS=-I. -g -Wall
DEPS=vec3.h ray.h hitable.h hitable_list.h sphere.h material.h camera.h
OBJ=vec3.o ray.o hitable.o hitable_list.o sphere.o material.o camera.o raytracer.o

debug: CFLAGS += -g -Wall

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

raytracer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
