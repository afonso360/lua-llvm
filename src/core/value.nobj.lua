-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Value" {
  c_source [[
      typedef struct LLVMOpaqueValue Value;
  ]],

  method "value_name" {
    c_method_call "const char *" "LLVMGetValueName" {},
  },

  method "set_value_name" {
    var_in { "const char *", "str" },
    c_source [[
      LLVMSetValueName(${this}, ${str});
    ]],
  },

  method "is_constant" {
    c_method_call "bool" "LLVMIsConstant" {},
  },

  method "is_undef" {
    c_method_call "bool" "LLVMIsUndef" {},
  },

}

object "IntValue" {
  extends "Value",

  c_function "const_int" {
    c_call "Value *" "LLVMConstInt" {
      "Type *", "int_ty",
      "uint64_t", "n", -- The original type is unsigned long long, but LNO is not liking that
      "bool", "sign_extend",
    },
  },

  c_function "const_int_of_string" {
    c_call "Value *" "LLVMConstIntOfStringAndSize" {
      "Type *", "int_ty",
      "const char *", "str",
      "unsigned", "#str",
      "uint8_t", "radix",
    },
  },
}
