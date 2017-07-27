-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Context" {
  c_source [[
    typedef LLVMContextRef Context;
  ]],

  constructor "get_global_context" {
    c_call "Context" "LLVMGetGlobalContext" { },
  },

  destructor "dispose" {
    c_call "void" "LLVMContextDispose" { "Context", "*this" },
  },
}
