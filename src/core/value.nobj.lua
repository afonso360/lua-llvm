-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Value" {
  c_source [[
      typedef struct LLVMOpaqueValue Value;
  ]],

  method "name" {
    c_method_call "const char *" "LLVMGetValueName" {},
  },

  method "set_name" {
    var_in { "const char *", "str" },
    c_source [[
      LLVMSetValueName(${this}, ${str});
    ]],
  },

  method "dump" {
    doc [[ Dumps the value to stderr ]],
    c_method_call "void" "LLVMDumpValue" {},
  },

  method "is_constant" {
    c_method_call "bool" "LLVMIsConstant" {},
  },

  method "is_undef" {
    c_method_call "bool" "LLVMIsUndef" {},
  },

  method "is_null" {
    c_method_call "bool" "LLVMIsNull" {},
  },

}

object "IntValue" {
  extends "Value",
  c_source [[
      typedef Value IntValue;
  ]],

  -- TODO: Rename to const
  constructor "const" {
    c_call "IntValue *" "LLVMConstInt" {
      "IntType *", "ty",
      "uint64_t", "n", -- The original type is unsigned long long, but LNO is not liking that
      "bool", "sign_extend",
    },
  },

  constructor "const_of_string" {
    c_call "IntValue *" "LLVMConstIntOfStringAndSize" {
      "IntType *", "ty",
      "const char *", "str",
      "unsigned", "#str",
      "uint8_t", "radix",
    },
  },

  method "zext" {
    -- The original type is unsigned long long, but LNO is not liking that
    c_method_call "uint64_t" "LLVMConstIntGetZExtValue" { }
  },

  method "sext" {
    -- The original type is long long, but LNO is not liking that
    c_method_call "int64_t" "LLVMConstIntGetSExtValue" { }
  }
}

object "FloatValue" {
  extends "Value",
  c_source [[
      typedef Value FloatValue;
  ]],

  -- TODO: Rename to const
  constructor "const" {
    c_call "FloatValue *" "LLVMConstReal" {
      "FloatType *", "ty",
      "double", "n",
    },
  },

  constructor "const_of_string" {
    c_call "IntValue *" "LLVMConstRealOfStringAndSize" {
      "FloatType *", "ty",
      "const char *", "str",
      "unsigned", "#str",
    },
  },

  method "value" {
    -- TODO: double 	LLVMConstRealGetDouble (LLVMValueRef ConstantVal, LLVMBool *losesInfo)
-- 	Obtain the double value for an floating point constant value.
  }
}


object "FunctionValue" {
  extends "Value",
  c_source [[
      typedef Value FunctionValue;
  ]],

}
