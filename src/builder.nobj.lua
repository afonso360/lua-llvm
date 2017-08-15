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
      "FloatValue *", "lhs",
      "FloatValue *", "rhs",
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
      "FloatValue *", "lhs",
      "FloatValue *", "rhs",
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
      "FloatValue *", "lhs",
      "FloatValue *", "rhs",
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
      "FloatValue *", "lhs",
      "FloatValue *", "rhs",
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
      "FloatValue *", "lhs",
      "FloatValue *", "rhs",
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
      "FloatValue *", "v",
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

  method "build_free" {
    c_method_call "Value *" "LLVMBuildFree" {
      "Value *", "ptr"
    }
  },

  method "build_load" {
    c_method_call "Value *" "LLVMBuildLoad" {
      -- TODO: Replace with PtrValue
      "Value *", "ptr",
      "const char *", "name"
    }
  },

  method "build_store" {
    c_method_call "Value *" "LLVMBuildStore" {
      "Value *", "val",
      -- TODO: Replace with PtrValue
      "Value *", "ptr"
    }
  },

  --method "build_gep" {
  --  c_method_call "LLVMValueRef" "LLVMBuildGEP" {
  --    "LLVMValueRef", "ptr",
  --    "LLVMValueRef *", "Indices",
  --    "unsigned", "NumIndices",
  --    "const char *", "name"
  --  }
  --},

  --method "build_in_bounds_gep" {
  --  c_method_call "LLVMValueRef" "LLVMBuildInBoundsGEP" {
  --    "LLVMValueRef", "ptr",
  --    "LLVMValueRef *", "Indices",
  --    "unsigned", "NumIndices",
  --    "const char *", "name"
  --  }
  --},

  method "build_Struct_GEP" {
    c_method_call "Value *" "LLVMBuildStructGEP" {
      "Value *", "ptr",
      "unsigned", "Idx",
      "const char *", "name"
    }
  },

  method "build_global_string" {
    c_method_call "Value *" "LLVMBuildGlobalString" {
      "const char *", "Str",
      "const char *", "name"
    }
  },

  method "build_global_string_ptr" {
    c_method_call "Value *" "LLVMBuildGlobalStringPtr" {
      "const char *", "Str",
      "const char *", "name"
    }
  },

  --[[
  method "LLVMGetVolatile" {
    c_method_call "LLVMBool" "LLVMGetVolatile" {
      "Value *", "MemoryAccessInst"
    }
  },

  method "LLVMSetVolatile" {
    c_method_call "void" "LLVMSetVolatile" {
      "Value *", "MemoryAccessInst",
      "bool", "IsVolatile"
    }
  },

  method "LLVMGetOrdering" {
    c_method_call "LLVMAtomicOrdering" "LLVMGetOrdering" {
      "Value *", "MemoryAccessInst"
    }
  },

  method "LLVMSetOrdering" {
    c_method_call "void" "LLVMSetOrdering" {
      "Value *", "MemoryAccessInst",
      "LLVMAtomicOrdering", "Ordering"
    }
  },
  ]]--
  method "build_trunc" {
    c_method_call "IntValue *" "LLVMBuildTrunc" {
      "IntValue *", "Val",
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_zext" {
    c_method_call "IntValue *" "LLVMBuildZExt" {
      "IntValue *", "Val",
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_sext" {
    c_method_call "IntValue *" "LLVMBuildSExt" {
      "IntValue *", "Val",
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_fp_to_ui" {
    c_method_call "IntValue *" "LLVMBuildFPToUI" {
      "FloatValue *", "Val",
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_fp_to_si" {
    c_method_call "IntValue *" "LLVMBuildFPToSI" {
      "FloatValue *", "Val",
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_ui_to_fp" {
    c_method_call "FloatValue *" "LLVMBuildUIToFP" {
      "FloatValue *", "Val",
      "FloatType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_si_to_fp" {
    c_method_call "FloatValue *" "LLVMBuildSIToFP" {
      "IntValue *", "Val",
      "FloatType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_fptrunc" {
    c_method_call "FloatValue *" "LLVMBuildFPTrunc" {
      "FloatValue *", "Val",
      "FloatType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_fpext" {
    c_method_call "FloatValue *" "LLVMBuildFPExt" {
      "FloatValue *", "Val",
      "FloatType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_ptr_to_int" {
    c_method_call "IntValue *" "LLVMBuildPtrToInt" {
      "Value *", "Val", -- TODO: PtrValue
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_int_to_ptr" {
    c_method_call "Value *" "LLVMBuildIntToPtr" { --TODO PtrValue
      "IntValue *", "Val",
      "Type *", "DestTy", -- TODO: PTRType
      "const char *", "name"
    }
  },

  method "build_bit_cast" {
    c_method_call "Value *" "LLVMBuildBitCast" {
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_addr_space_cast" {
    c_method_call "Value *" "LLVMBuildAddrSpaceCast" {
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_zext_or_bit_cast" {
    c_method_call "Value *" "LLVMBuildZExtOrBitCast" {
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_sext_or_bit_cast" {
    c_method_call "Value *" "LLVMBuildSExtOrBitCast" {
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_trunc_or_bit_cast" {
    c_method_call "Value *" "LLVMBuildTruncOrBitCast" {
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },

  --[[
  method "build_cast" {
    c_method_call "Value *" "LLVMBuildCast" {
      "LLVMOpcode", "Op",
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },
  ]]--

	-- TODO: PtrValues
  method "build_ptr_cast" {
    c_method_call "Value *" "LLVMBuildPointerCast" {
      "Value *", "Val",
      "Type *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_int_cast" {
    c_method_call "IntValue *" "LLVMBuildIntCast" {
      "IntValue *", "Val",
      "IntType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_fpcast" {
    c_method_call "FloatValue *" "LLVMBuildFPCast" {
      "FloatValue *", "Val",
      "FloatType *", "DestTy",
      "const char *", "name"
    }
  },

  method "build_icmp" {
    c_method_call "Value *" "LLVMBuildICmp" {
      "IntPredicate *", "*Op",
      "IntValue *", "lhs",
      "IntValue *", "rhs",
      "const char *", "name"
    }
  },

  method "build_fcmp" {
    c_method_call "Value *" "LLVMBuildFCmp" {
      "RealPredicate *", "*Op",
      "FloatValue *", "lhs",
      "FloatValue *", "rhs",
      "const char *", "name"
    }
  },

  method "build_phi" {
    c_method_call "Value *" "LLVMBuildPhi" {
      "Type *", "Ty",
      "const char *", "name"
    }
  },

  --method "build_call" {
  --  c_method_call "Value *" "LLVMBuildCall" {
  --    "Value *", "Fn",
  --    "Value **", "Args",
  --    "unsigned", "NumArgs",
  --    "const char *", "name"
  --  }
  --},

  method "build_select" {
    c_method_call "Value *" "LLVMBuildSelect" {
      "Value *", "If",
      "Value *", "Then",
      "Value *", "Else",
      "const char *", "name"
    }
  },

  method "build_vaarg" {
    c_method_call "Value *" "LLVMBuildVAArg" {
      "Value *", "list",
      "Type *", "ty",
      "const char *", "name"
    }
  },

  method "build_extract_element" {
    c_method_call "Value *" "LLVMBuildExtractElement" {
      "Value *", "vecval",
      "Value *", "index",
      "const char *", "name"
    }
  },

  method "build_insert_element" {
    c_method_call "Value *" "LLVMBuildInsertElement" {
      "Value *", "vecval",
      "Value *", "eltval",
      "Value *", "index",
      "const char *", "name"
    }
  },

  method "build_shuffle_vector" {
    c_method_call "Value *" "LLVMBuildShuffleVector" {
      "Value *", "v1",
      "Value *", "v2",
      "Value *", "mask",
      "const char *", "name"
    }
  },

  method "build_extract_value" {
    c_method_call "Value *" "LLVMBuildExtractValue" {
      "Value *", "aggval",
      "unsigned", "index",
      "const char *", "name"
    }
  },

  method "build_insert_value" {
    c_method_call "Value *" "LLVMBuildInsertValue" {
      "Value *", "agg_val",
      "Value *", "elt_val",
      "unsigned", "index",
      "const char *", "name"
    }
  },

  method "build_is_null" {
    c_method_call "Value *" "LLVMBuildIsNull" {
      "Value *", "val",
      "const char *", "name"
    }
  },

  method "build_is_not_null" {
    c_method_call "Value *" "LLVMBuildIsNotNull" {
      "Value *", "val",
      "const char *", "name"
    }
  },

  --[[
  method "build_ptr_diff" {
    c_method_call "Value *" "LLVMBuildPtrDiff" {
      "Value *", "lhs",
      "Value *", "rhs",
      "const char *", "name"
    }
  },

  method "build_fence" {
    c_method_call "Value *" "LLVMBuildFence" {
      "LLVMAtomicOrdering", "ordering",
      "LLVMBool", "singleThread",
      "const char *", "name"
    }
  },

  method "build_atomic_rmw" {
    c_method_call "Value *" "LLVMBuildAtomicRMW" {
      "LLVMAtomicRMWBinOp", "op",
      "Value *", "PTR",
      "Value *", "Val",
      "LLVMAtomicOrdering", "ordering",
      "LLVMBool", "singleThread"
    }
  },

  method "build_Atomic_Cmp_Xchg" {
    c_method_call "Value *" "LLVMBuildAtomicCmpXchg" {
      "Value *", "Ptr",
      "Value *", "Cmp",
      "Value *", "New",
      "LLVMAtomicOrdering", "SuccessOrdering",
      "LLVMAtomicOrdering", "FailureOrdering",
      "LLVMBool", "SingleThread"
    }
  },

  method "build_is_atomic_single_thread" {
    c_method_call "LLVMBool" "LLVMIsAtomicSingleThread" {
      "Value *", "AtomicInst"
    }
  },

  method "LLVMSetAtomicSingleThread" {
    c_method_call "void" "LLVMSetAtomicSingleThread" {
      "Value *", "AtomicInst",
      "LLVMBool", "SingleThread"
    }
  },

  method "LLVMGetCmpXchgSuccessOrdering" {
    c_method_call "LLVMAtomicOrdering" "LLVMGetCmpXchgSuccessOrdering" {
      "Value *", "CmpXchgInst"
    }
  },

  method "LLVMSetCmpXchgSuccessOrdering" {
    c_method_call "void" "LLVMSetCmpXchgSuccessOrdering" {
      "Value *", "CmpXchgInst",
      "LLVMAtomicOrdering", "Ordering"
    }
  },

  method "LLVMGetCmpXchgFailureOrdering" {
    c_method_call "LLVMAtomicOrdering" "LLVMGetCmpXchgFailureOrdering" {
      "Value *", "CmpXchgInst"
    }
  },

  method "LLVMSetCmpXchgFailureOrdering" {
    c_method_call "void" "LLVMSetCmpXchgFailureOrdering" {
      "Value *", "CmpXchgInst",
      "LLVMAtomicOrdering", "Ordering"
    }
  },
  ]]--
}
