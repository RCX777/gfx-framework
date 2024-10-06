BUILD_DIR = build

.PHONY: all run clean

all: | $(BUILD_DIR)
	@make -C $(BUILD_DIR)

run: all
	@./$(BUILD_DIR)/bin/Debug/GFXFramework

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@
	@cd $@ && cmake .. && cd ..

