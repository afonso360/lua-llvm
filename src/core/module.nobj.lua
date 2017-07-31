-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.


object "Module" {
  c_source [[
      typedef struct LLVMOpaqueModule Module;
  ]],

  constructor "create_with_name" {
    c_call "Module *" "LLVMModuleCreateWithName" { "const char *", "ModuleId" },
  },

  constructor "create_with_name_in_context" {
    c_call "Module *" "LLVMModuleCreateWithNameInContext" { "const char *", "mid", "Context *", "ctx" },
  },

  method "clone" {
    c_call "Module *" "LLVMCloneModule" { "Module *", "this" },
  },

  method "get_identifier" {
    var_out { "const char *", "str" },
    c_source [[
      size_t sz;
      ${str} = LLVMGetModuleIdentifier(${this}, &sz);
    ]],
  },

  method "set_identifier" {
    var_in { "const char *", "str" },
    c_source [[
      LLVMSetModuleIdentifier(${this}, ${str}, ${str_len});
    ]],
  },

  destructor "dispose" {
    c_method_call "void" "LLVMDisposeModule" {},
  },
}
