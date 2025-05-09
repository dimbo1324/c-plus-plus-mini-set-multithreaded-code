CXX        := g++
CXXFLAGS   := -std=c++20 -Wall -Wextra -pthread
INCFLAGS   := -Iinclude
LDFLAGS    := -pthread
SRCDIR_APP := app
SRCDIR_LIB := lib
BUILDDIR   := build
TARGET     := fine_grained_queue_app
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
$(BUILDDIR)/%.o: $(SRCDIR_APP)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
$(BUILDDIR)/%.o: $(SRCDIR_LIB)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)
.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGET)
	@echo "Сборка очищена."
