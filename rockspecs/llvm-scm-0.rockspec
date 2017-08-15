#!/usr/bin/env lua

package	= "llvm"
version	= "scm-0"
source	= {
	url	= "git://github.com/afonso360/lua-llvm",
  branch = "built"
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
			sources = { "llvm.nobj.c" },
			libraries = { "LLVM" },
			incdirs = { "$(LLVM_INCDIR)" },
			libdirs = { "$(LLVM_LIBDIR)" },
		}
	},
  copy_directories = { "docs" }
}
