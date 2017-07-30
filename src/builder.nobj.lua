-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.


object "Builder" {
  c_source [[
      typedef struct LLVMOpaqueBuilder Builder;
  ]],

  constructor "create" {
    c_call "Builder *" "LLVMCreateBuilder" { },
  },

  constructor "create_in_context" {
    c_call "Builder *" "LLVMCreateBuilderInContext" { "Context *", "ctx" },
  },

  destructor "dispose" {
    c_method_call "void" "LLVMDisposeBuilder" {},
  },
}
