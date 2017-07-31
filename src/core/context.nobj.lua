-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Context" {
  c_source [[
      typedef struct LLVMOpaqueContext Context;
  ]],

  constructor "create" {
    c_call "Context *" "LLVMContextCreate" { },
  },

  constructor "global_context" {
    c_source [[
      ${this} = LLVMGetGlobalContext();
      ${this_flags} = 0;
    ]],
  },

  destructor "dispose" {
    c_method_call "void" "LLVMContextDispose" {},
  },
}
