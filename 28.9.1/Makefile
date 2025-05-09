CXX        := g++
CXXFLAGS   := -std=c++20 -Wall -Wextra -pthread
INCFLAGS   := -Iinclude
LDFLAGS    := -pthread
SRCDIR_APP := app
SRCDIR_LIB := lib
BUILDDIR   := build
TARGET     := parallel_merge_sort_app
APP_SRCS   := $(wildcard $(SRCDIR_APP)/*.cpp)
LIB_SRCS   := $(wildcard $(SRCDIR_LIB)/*.cpp)
SRCS       := $(APP_SRCS) $(LIB_SRCS)
OBJS       := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(notdir $(SRCS)))
.PHONY: all
all: $(TARGET)
.PHONY: run
run: $(TARGET)
	@echo "Запуск $(TARGET)..."
	./$(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILDDIR)/main.o: $(SRCDIR_APP)/main.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
$(BUILDDIR)/merge_sort.o: $(SRCDIR_LIB)/merge_sort.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)
.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGET)
	@echo "Сборка очищена."
