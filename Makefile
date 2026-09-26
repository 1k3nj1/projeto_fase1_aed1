# Compilador e flags
CXX      := g++
# O SFML 3 exige no mínimo o padrão C++17
CXXFLAGS := -std=c++17 -Wall -Wextra

# Bibliotecas do SFML 3
LIBS     := -lsfml-graphics -lsfml-window -lsfml-system

# Nome do executável
TARGET   := app

# Arquivos fonte
SRCS     := main.cpp \
            src/funcs_jogo.cpp \
            src/Fila.cpp \
            src/PokemonEntity.cpp

# Transforma a lista de .cpp em .o
OBJS     := $(SRCS:.cpp=.o)

# Regra padrão: compila e já executa o programa
all: $(TARGET)
	./$(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Compilação dos arquivos objetos (.o) a partir dos (.cpp)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra apenas para rodar (caso já esteja compilado)
run: $(TARGET)
	./$(TARGET)

# Limpeza dos binários gerados
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean