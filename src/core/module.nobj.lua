-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.


object "Module" {
  c_source [[
      typedef struct LLVMOpaqueModule Module;
  ]],

  constructor "create" {
    doc [[ Context is optional ]],
    var_in { "const char *", "identifier" },
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMModuleCreateWithName(${identifier});
      } else {
         ${this} = LLVMModuleCreateWithNameInContext(${identifier}, ${ctx});
      }
    ]],
  },

  method "clone" {
    c_method_call "Module *" "LLVMCloneModule" { },
  },

  method "identifier" {
    var_out { "const char *", "str" },
    c_source [[
      size_t sz;
      ${str} = LLVMGetModuleIdentifier(${this}, &sz);
    ]],
  },

  method "set_identifier" {
    c_method_call "void" "LLVMSetModuleIdentifier" { "const char *", "str", "size_t", "#str" }
  },

  method "dump" {
    c_method_call "void" "LLVMDumpModule" { }
  },

  method "target" {
    c_method_call "const char *" "LLVMGetTarget" { }
  },
  method "set_target" {
    c_method_call "void" "LLVMSetTarget" { "const char *", "target_triplet" }
  },

  method "add_function" {
    -- TODO: should this be a FunctionType, instead of a valueType?
    c_method_call "Value *" "LLVMAddFunction" { "const char *", "name", "FunctionType *", "function_type" }
  },
  method "get_function" {
    c_method_call "Value *" "LLVMGetNamedFunction" { "const char *", "name" }
  },

  destructor "dispose" {
    c_method_call "void" "LLVMDisposeModule" {},
  },
}
