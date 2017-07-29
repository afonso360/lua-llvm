-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Context" {
  -- For some reason using LLVMContextRef isn't really working
  -- so for now we can use LLVMOpaqueContext
  c_source [[
      typedef struct LLVMOpaqueContext Context;
  ]],

  constructor "create" {
    c_call "!Context *" "LLVMContextCreate" { },
  },

  constructor "global_context" {
    c_call "Context *" "LLVMGetGlobalContext" { },
  },

  destructor "dispose" {
    c_method_call "void" "LLVMContextDispose" {},
  },
}
