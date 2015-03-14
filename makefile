#defines
COMPILE    = g++ -c
LINK       = g++
WITH_GL    = -lGL -lGLU -lglut
OBJECTS    = main.o Game.o Level.o camera.o obstacle.o Plano.o player.o ray.o Stage.o timer.o vector.o glm.o loadFile.o parallelepiped.o
BIN        = a.exe


#Universal "make" commands
.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	rm -f $(OBJECTS) "$(BIN)"

#rules for "make"
$(BIN): $(OBJECTS)
	$(LINK) $(OBJECTS) $(WITH_GL) -o $(BIN)

main.o: main.cpp MATH.h camera.h Stage.h Plano.h player.h ray.h vector.h representation.h parallelepiped.h
	$(COMPILE) main.cpp $(WITH_GL) -o main.o

loadFile.o: $(GLOBALDEPS) loadFile.cpp vector.h representation.h parallelepiped.h Plano.h obstacle.h timer.h ray.h onStageElement.h MATH.h player.h heightMap.h Level.h Stage.h Game.h
	$(COMPILE) loadFile.cpp $(WITH_GL) -o loadFile.o

Game.o: Game.cpp Game.h Level.h onStageElement.h Stage.h Plano.h vector.h parallelepiped.h representation.h heightMap.h obstacle.h timer.h ray.h player.h MATH.h
	$(COMPILE) Game.cpp $(WITH_GL) -o Game.o

Level.o: $(GLOBALDEPS) Level.cpp Level.h Stage.h Plano.h vector.h parallelepiped.h representation.h heightMap.h obstacle.h onStageElement.h timer.h ray.h player.h
	$(COMPILE) Level.cpp $(WITH_GL) -o Level.o

player.o: $(GLOBALDEPS) player.cpp timer.h MATH.h player.h ray.h vector.h representation.h Plano.h parallelepiped.h onStageElement.h MATH.h
	$(COMPILE) player.cpp $(WITH_GL) -o player.o

obstacle.o: $(GLOBALDEPS) obstacle.cpp timer.h MATH.h obstacle.h ray.h vector.h onStageElement.h representation.h
	$(COMPILE) obstacle.cpp $(WITH_GL) -o obstacle.o

parallelepiped.o: $(GLOBALDEPS) parallelepiped.cpp parallelepiped.h representation.h vector.h Stage.h Plano.h
	$(COMPILE) parallelepiped.cpp $(WITH_GL) -o parallelepiped.o

ray.o: ray.cpp ray.h vector.h MATH.h
	$(COMPILE) ray.cpp -o ray.o

vector.o: vector.cpp vector.h MATH.h
	$(COMPILE) vector.cpp -o vector.o

Stage.o: Stage.cpp Stage.h Plano.h
	$(COMPILE) Stage.cpp $(WITH_GL) -o Stage.o

Plano.o: Plano.cpp Plano.h
	$(COMPILE) Plano.cpp $(WITH_GL) -o Plano.o

camera.o: camera.cpp camera.h vector.h MATH.h
	$(COMPILE) camera.cpp $(WITH_GL) -o camera.o

glm.o: glm.cpp glm.h MATH.h
	$(COMPILE) glm.cpp $(WITH_GL) -o glm.o

timer.o: timer.cpp timer.h
	$(COMPILE) timer.cpp -o timer.o
