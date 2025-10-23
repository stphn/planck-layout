# === Config ===
KEYBOARD := planck/rev7
KEYMAP   := stphn
QMK_HOME := $(PWD)/qmk
BUILD_DIR := $(QMK_HOME)/.build
FIRMWARE_DIR := $(PWD)/firmware
KEYMAP_LINK := $(QMK_HOME)/keyboards/planck/keymaps/$(KEYMAP)

# === Targets ===
.PHONY: all test build flash save clean init-qmk qmk-status update-qmk layout draw

# Default target
all: build

# Run QMK tests
test:
	@echo "🧪 Running QMK tests..."
	@cd qmk && make test:basic

# Ensure symlink exists before building
$(KEYMAP_LINK):
	@echo "🔗 Linking keymap $(KEYMAP) into QMK..."
	@mkdir -p $(QMK_HOME)/keyboards/planck/keymaps
	@ln -sfn "$(PWD)/keymap" "$(KEYMAP_LINK)"

build: $(KEYMAP_LINK)
	@echo "⚙️  Building $(KEYBOARD) with keymap $(KEYMAP)..."
	QMK_HOME="$(QMK_HOME)" qmk compile -kb $(KEYBOARD) -km $(KEYMAP)

flash: $(KEYMAP_LINK)
	@echo "⚡ Flashing $(KEYBOARD) with keymap $(KEYMAP)..."
	QMK_HOME="$(QMK_HOME)" qmk flash -kb $(KEYBOARD) -km $(KEYMAP)

save: build
	@mkdir -p $(FIRMWARE_DIR)
	@cp -f $(BUILD_DIR)/planck_rev7_$(KEYMAP).bin \
		$(FIRMWARE_DIR)/planck_rev7_$(KEYMAP)-$$(date +%Y%m%d-%H%M%S).bin
	@echo "✅ Firmware copied into $(FIRMWARE_DIR)/"

clean:
	QMK_HOME="$(QMK_HOME)" qmk clean

# Visualize keyboard layouts (quick ASCII in terminal)
layout:
	@python3 draw_layout.py $(filter-out $@,$(MAKECMDGOALS))

# Generate professional layout diagrams (SVG/PNG)
draw:
	@./draw/generate.sh

# Allow passing layer names as targets
%:
	@:

# === QMK submodule helpers ===

# Initialize submodule (first time only)
init-qmk:
	@git submodule update --init --recursive qmk
	@echo "✅ QMK submodule initialized."

# Show current QMK submodule commit + status
qmk-status:
	@echo "📦 QMK @ $$(git -C qmk rev-parse --short HEAD) ($$(git -C qmk rev-parse --abbrev-ref HEAD))"
	@git -C qmk status --short || true

# Update submodule to latest upstream master/main and commit pointer
update-qmk:
	@set -e; \
	if [ ! -d qmk/.git ] && [ ! -f qmk/.git ]; then \
	  echo "❌ qmk submodule not initialized. Run: make init-qmk"; exit 1; \
	fi; \
	echo "⏩ Fetching upstream in submodule…"; \
	git -C qmk fetch --all --tags; \
	if git -C qmk show-ref --verify --quiet refs/remotes/origin/master; then \
	  TARGET_BRANCH=master; \
	elif git -C qmk show-ref --verify --quiet refs/remotes/origin/main; then \
	  TARGET_BRANCH=main; \
	else \
	  echo "❌ Neither origin/master nor origin/main found."; exit 1; \
	fi; \
	git -C qmk checkout $$TARGET_BRANCH; \
	git -C qmk pull --ff-only origin $$TARGET_BRANCH; \
	NEW=$$(git -C qmk rev-parse --short HEAD); \
	echo "✅ QMK now at $$NEW on $$TARGET_BRANCH"; \
	echo "📝 Staging submodule pointer…"; \
	git add qmk; \
	git commit -m "chore: update QMK submodule to $$(git -C qmk rev-parse --short HEAD)" 2>/dev/null || echo "ℹ️ No changes to commit."
