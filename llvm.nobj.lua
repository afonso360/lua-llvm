
c_module "llvm" {

-- enable FFI bindings support.
luajit_ffi = true,

-- load LLVM shared library.
ffi_load"llvm",

include "llvm.h",

subfiles {
"src/object.nobj.lua",
},
}

