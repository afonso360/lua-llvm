-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.


object "BasicBlock" {
  c_source [[
      typedef struct LLVMOpaqueBasicBlock BasicBlock;
  ]],

  constructor "create" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMCreateBasicBlock();
      } else {
         ${this} = LLVMCreateBasicBlockInContext(${ctx});
      }
    ]],
  },

  method "name" {
    c_method_call "const char *" "LLVMGetBasicBlockName" { }
  }


}
