-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Type" {
  c_source [[
      typedef struct LLVMOpaqueType Type;
  ]],

  method "get_context" {
    c_method_call "Context *" "LLVMGetTypeContext" {},
  },

  method "is_sized" {
    c_method_call "bool" "LLVMTypeIsSized" {},
  },

  --                                          Integer types
  c_function "int_1_type" {
    c_call "Type *" "LLVMInt1Type" { }
  },
  c_function "int_8_type" {
    c_call "Type *" "LLVMInt8Type" { }
  },
  c_function "int_16_type" {
    c_call "Type *" "LLVMInt16Type" { }
  },
  c_function "int_32_type" {
    c_call "Type *" "LLVMInt32Type" { }
  },
  c_function "int_64_type" {
    c_call "Type *" "LLVMInt64Type" { }
  },
  c_function "int_128_type" {
    c_call "Type *" "LLVMInt128Type" { }
  },
  c_function "int_type" {
    c_call "Type *" "LLVMIntType" { "unsigned", "bits" }
  },
  c_function "int_1_type_in_context" {
    c_call "Type *" "LLVMInt1TypeInContext" { "Context *", "ctx" }
  },
  c_function "int_8_type_in_context" {
    c_call "Type *" "LLVMInt8TypeInContext" { "Context *", "ctx" }
  },
  c_function "int_16_type_in_context" {
    c_call "Type *" "LLVMInt16TypeInContext" { "Context *", "ctx" }
  },
  c_function "int_32_type_in_context" {
    c_call "Type *" "LLVMInt32TypeInContext" { "Context *", "ctx" }
  },
  c_function "int_64_type_in_context" {
    c_call "Type *" "LLVMInt64TypeInContext" { "Context *", "ctx" }
  },
  c_function "int_128_type_in_context" {
    c_call "Type *" "LLVMInt128TypeInContext" { "Context *", "ctx" }
  },
  c_function "int_type_in_context" {
    c_call "Type *" "LLVMIntTypeInContext" { "Context *", "ctx", "unsigned", "bits" }
  },

  method "get_int_type_width" {
    c_method_call "unsigned" "LLVMGetIntTypeWidth" {}
  },
}

