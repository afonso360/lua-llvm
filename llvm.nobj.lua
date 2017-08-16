-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

-- make generated variable nicer.
set_variable_format "%s%d"

c_module "llvm" {
  luajit_ffi = false,
  luajit_ffi_load_cmodule = false,

  use_globals = false,
  hide_meta_info = false, --true,

  include "llvm-c/Analysis.h",
  include "llvm-c/BitReader.h",
  include "llvm-c/BitWriter.h",
  include "llvm-c/Core.h",
  include "llvm-c/Disassembler.h",
  include "llvm-c/ErrorHandling.h",
  include "llvm-c/ExecutionEngine.h",
  include "llvm-c/Initialization.h",
  include "llvm-c/IRReader.h",
  include "llvm-c/Linker.h",
  include "llvm-c/LinkTimeOptimizer.h",
  include "llvm-c/lto.h",
  include "llvm-c/Object.h",
  include "llvm-c/OrcBindings.h",
  include "llvm-c/Support.h",
  include "llvm-c/Target.h",
  include "llvm-c/TargetMachine.h",
  include "llvm-c/Types.h",

  subfiles {
    "src/core/type.nobj.lua",
    "src/core/module.nobj.lua",
    "src/core/context.nobj.lua",
    "src/core/value.nobj.lua",
    "src/core/basic_block.nobj.lua",
    -- Threading
    -- Bit Reader
    -- Analysis
    -- Bit Writer
    -- Target Information
    -- LTO
    "src/builder.nobj.lua",
    -- Disassembler
    -- Transforms
    -- Link Time Optimization
    -- Memory Buffers
    -- Pass Registry
    -- Module Providers
    -- Object file reading and writing
    -- Pass Managers
    -- Execution Engine
    -- ThinLTO
    -- Initialization Routines
    "src/enums.nobj.lua",
  },
}
