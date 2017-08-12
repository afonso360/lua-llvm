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
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMCreateBuilder();
      } else {
         ${this} = LLVMCreateBuilderInContext(${ctx});
      }
    ]],
  },

  destructor "dispose" {
    c_method_call "void" "LLVMDisposeBuilder" {},
  },

  method "position_at_end" {
    c_method_call "void" "LLVMPositionBuilderAtEnd" { "BasicBlock *", "bb" }
  },

  method "build_add" {
    c_method_call "Value *" "LLVMBuildAdd" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_sub" {
    c_method_call "Value *" "LLVMBuildSub" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_ret" {
    c_method_call "Value *" "LLVMBuildRet" { "Value *", "lhs" }
  }

}
