DOCS_DIR ?= $(abspath docs/)
ROCKS_DIR ?= $(abspath rockspecs/)
PACKAGE_DIR ?= $(abspath package/)
BUILD_DIR ?= $(abspath build/)

BUSTED_FLAGS := --shuffle --cpath=./build/?.so

all: build

build:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)
	(cd $(BUILD_DIR) && cmake ..)
	(cd $(BUILD_DIR) && make)

test:
	busted $(BUSTED_FLAGS)

ci-test:
	busted -c -Xhelper travis,env=full --verbose $(BUSTED_FLAGS)


doc:
	(cd $(BUILD_DIR) && cmake -D USE_PRE_GENERATED_BINDINGS=FALSE -D GENERATE_LUADOCS=TRUE .. && make llvm.luadoc)

clean:
	rm -rf $(BUILD_DIR)

deterministic: build
	while [ $$? -eq 0 ]; do make test; done

package: build test doc
	mkdir -p $(PACKAGE_DIR)
	cp -r $(BUILD_DIR)/llvm.nobj.c \
		$(ROCKS_DIR)/llvm-scm-0.rockspec \
		LICENSE \
		README.md \
		$(DOCS_DIR) \
		$(PACKAGE_DIR)/

.PHONY: test clean build
