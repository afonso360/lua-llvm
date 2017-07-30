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

  include "llvm-c/Core.h",
  include "llvm-c/Types.h",

  c_source "typedefs" [[
    typedef struct LLVMOpaqueType *  LLVMTypeRef;
  ]],

  subfiles {
    --"src/core/core.nobj.lua",
    "src/core/context.nobj.lua",
    ---- Missing modules
    -- Threading
    -- Bit Reader
    -- Analysis
    -- Bit Writer
    -- Target Information
    -- LTO
    -- Instruction Builders
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
  },
}
