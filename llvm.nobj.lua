-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

c_module "llvm" {

  -- enable FFI bindings support.
  luajit_ffi = true,

  -- load LLVM shared library.
  ffi_load "llvm",

  include "llvm-c/Core.h",

  subfiles {
    "src/core/core.nobj.lua",
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
