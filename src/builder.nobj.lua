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


  method "build_ret" {
    c_method_call "Value *" "LLVMBuildRet" { "Value *", "lhs" }
  },
  method "build_ret_void" {
    c_method_call "Value *" "LLVMBuildRetVoid" { }
  },

  method "build_add" {
    c_method_call "Value *" "LLVMBuildAdd" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_nswadd" {
    c_method_call "Value *" "LLVMBuildNSWAdd" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_nuwadd" {
    c_method_call "Value *" "LLVMBuildNUWAdd" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_fadd" {
    c_method_call "Value *" "LLVMBuildFAdd" {
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

  method "build_nswsub" {
    c_method_call "Value *" "LLVMBuildNSWSub" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_nuwsub" {
    c_method_call "Value *" "LLVMBuildNUWSub" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_fsub" {
    c_method_call "Value *" "LLVMBuildFSub" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_mul" {
    c_method_call "Value *" "LLVMBuildMul" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_nswmul" {
    c_method_call "Value *" "LLVMBuildNSWMul" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_nuwmul" {
    c_method_call "Value *" "LLVMBuildNUWMul" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_fmul" {
    c_method_call "Value *" "LLVMBuildFMul" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_udiv" {
    c_method_call "Value *" "LLVMBuildUDiv" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_exact_udiv" {
    c_method_call "Value *" "LLVMBuildExactUDiv" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_sdiv" {
    c_method_call "Value *" "LLVMBuildSDiv" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_exact_sdiv" {
    c_method_call "Value *" "LLVMBuildExactSDiv" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_fdiv" {
    c_method_call "Value *" "LLVMBuildFDiv" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_urem" {
    c_method_call "Value *" "LLVMBuildURem" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_srem" {
    c_method_call "Value *" "LLVMBuildSRem" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_frem" {
    c_method_call "Value *" "LLVMBuildFRem" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_shl" {
    c_method_call "Value *" "LLVMBuildShl" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_lshr" {
    c_method_call "Value *" "LLVMBuildLShr" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_ashr" {
    c_method_call "Value *" "LLVMBuildAShr" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_and" {
    c_method_call "Value *" "LLVMBuildAnd" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_or" {
    c_method_call "Value *" "LLVMBuildOr" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_xor" {
    c_method_call "Value *" "LLVMBuildXor" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  --method "build_binop" {
  --  c_method_call "LVMValueRef" "LLVMBuildBinOp" {
  --    -- TODO: Impl Opcode
  --    "LLVMOpcode", "op",
  --    "Value *", "lhs",
  --    "Value *", "rhs",
  --    "const char *", "name"
  --  }
  --},

  method "build_neg" {
    c_method_call "Value *" "LLVMBuildNeg" {
      "Value *", "v",
      "const char *", "name"
    }
  },

  method "build_nswneg" {
    c_method_call "Value *" "LLVMBuildNSWNeg" {
      "Value *", "v",
      "const char *", "name"
    }
  },

  method "build_nuwneg" {
    c_method_call "Value *" "LLVMBuildNUWNeg" {
      "Value *", "v",
      "const char *", "name"
    }
  },

  method "build_fneg" {
    c_method_call "Value *" "LLVMBuildFNeg" {
      "Value *", "v",
      "const char *", "name"
    }
  },

  method "build_not" {
    c_method_call "Value *" "LLVMBuildNot" {
      "Value *", "v",
      "const char *", "name"
    }
  },

  method "build_malloc" {
    c_method_call "Value *" "LLVMBuildMalloc" {
      "Type *", "Tv",
      "const char *", "name"
    }
  },

  method "build_array_malloc" {
    c_method_call "Value *" "LLVMBuildArrayMalloc" {
      "Type *", "ty",
      "Value *", "val",
      "const char *", "name"
    }
  },

  method "build_alloca" {
    c_method_call "Value *" "LLVMBuildAlloca" {
      "Type *", "ty",
      "const char *", "name"
    }
  },

  method "build_array_alloca" {
    c_method_call "Value *" "LLVMBuildArrayAlloca" {
      "Type *", "ty",
      "Value *", "val",
      "const char *", "name"
    }
  },

  method "LLVMBuildFree" {
    c_method_call "Value *" "LLVMBuildFree" {
      "Value *", "ptr"
    }
  },

  method "LLVMBuildLoad" {
    c_method_call "Value *" "LLVMBuildLoad" {
      -- TODO: Replace with PtrValue
      "Value *", "ptr",
      "const char *", "name"
    }
  },

  method "LLVMBuildStore" {
    c_method_call "Value *" "LLVMBuildStore" {
      "Value *", "val",
      -- TODO: Replace with PtrValue
      "Value *", "ptr"
    }
  },

}
