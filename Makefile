# === Config ===
KEYBOARD := planck/rev7
KEYMAP   := stphn
QMK_HOME := $(PWD)/qmk
BUILD_DIR := $(QMK_HOME)/.build
FIRMWARE_DIR := $(PWD)/firmware
KEYMAP_LINK := $(QMK_HOME)/keyboards/planck/keymaps/$(KEYMAP)

# === Targets ===
.PHONY: build flash save clean

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
