package = "llvm"
version = "scm-1"
source = {
  url = "https://github.com/afonso360/llang.git"
}
description = {
  homepage = "https://github.com/afonso360/llang",
  license = "GPL-2.0",
  summary = "LLVM-C API Bindings for lua",
  license = "MIT",
  maintainer = "Afonso Bordado <afonsobordado@az8.co>"
}
dependencies = {
   "lua >= 5.1"
}
external_dependencies = {
   LIBLLVM = {
      header = "llvm-c/Core.h"
   }
}
build = {
   type = "builtin",
   modules = {
     ["llvm"] = "src/llvm.lua"
   }
}
