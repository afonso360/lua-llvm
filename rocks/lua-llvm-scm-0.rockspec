#!/usr/bin/env lua

package	= "lua-llvm"
version	= "scm-0"
source	= {
	url	= "https://github.com/afonso360/lua-llvm.git"
}
description	= {
	summary	= "LLVM-C API Bindings for lua",
	detailed	= "",
	homepage	= "https://github.com/afonso360/lua-llvm",
	license	= "MIT",
	maintainer = "Afonso Bordado",
}
dependencies = {
	"lua >= 5.1",
}
external_dependencies = {
	LLVM = {
		header = "llvm-c/Core.h",
		library = "LLVM",
	}
}
build	= {
	type = "builtin",
	modules = {
		llvm = {
			sources = { "src/pre_generated-llvm.nobj.c" },
			libraries = { "llvm" },
			incdirs = { "$(LLVM_INCDIR)" },
			libdirs = { "$(LLVM_LIBDIR)" },
		}
	}
}
