-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.


object "BasicBlock" {
  c_source [[
      typedef struct LLVMOpaqueBasicBlock BasicBlock;
  ]],

  constructor "append" {
    doc [[ Context is optional ]],
    var_in { "Value *", "fn" }, -- TODO: Change to FunctionValue
    var_in { "const char *", "name" },
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMAppendBasicBlock(${fn}, ${name});
      } else {
         ${this} = LLVMAppendBasicBlockInContext(${ctx}, ${fn}, ${name});
      }
    ]],
  },

  method "name" {
    c_method_call "const char *" "LLVMGetBasicBlockName" { }
  }

}
