CXX       := g++
CXXFLAGS  := -std=c++17 -pthread -Iinclude -O2
SRCDIR    := src
BUILDDIR  := build
BINDIR    := bin
TARGET    := chat_sim
BINARY    := $(BINDIR)/$(TARGET)
APP_SRCS      := $(wildcard $(SRCDIR)/app/*.cpp)
DOMAIN_SRCS   := $(wildcard $(SRCDIR)/domain/*.cpp)
INFRA_SRCS    := $(wildcard $(SRCDIR)/infrastructure/*.cpp)
SOURCES       := $(APP_SRCS) $(DOMAIN_SRCS) $(INFRA_SRCS)
OBJECTS       := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
.PHONY: all run clean
all: $(BINARY)
$(BINARY): $(OBJECTS) | $(BINDIR)
	@echo "[LD] $@"
	$(CXX) $(CXXFLAGS) $^ -o $@
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@echo "[CC] $<"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(BUILDDIR):
	mkdir -p $(BUILDDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
run: all
	@echo "[RUN] ./$(BINARY)"
	@./$(BINARY)
clean:
	@echo "Чисто"
	@rm -rf $(BUILDDIR) $(BINDIR) log.txt
