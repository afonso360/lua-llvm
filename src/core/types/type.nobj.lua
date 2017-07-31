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
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMInt1Type();
      } else {
         ${type} = LLVMInt1TypeInContext(${ctx});
      }
    ]],
  },
  c_function "int_8_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMInt8Type();
      } else {
         ${type} = LLVMInt8TypeInContext(${ctx});
      }
    ]],
  },
  c_function "int_16_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMInt16Type();
      } else {
         ${type} = LLVMInt16TypeInContext(${ctx});
      }
    ]],
  },
  c_function "int_32_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMInt32Type();
      } else {
         ${type} = LLVMInt32TypeInContext(${ctx});
      }
    ]],
  },
  c_function "int_64_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMInt64Type();
      } else {
         ${type} = LLVMInt64TypeInContext(${ctx});
      }
    ]],
  },
  c_function "int_128_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMInt128Type();
      } else {
         ${type} = LLVMInt128TypeInContext(${ctx});
      }
    ]],
  },
  c_function "int_type" {
    doc [[ Context is optional ]],
    var_in { "unsigned", "bits" },
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMIntType(${bits});
      } else {
         ${type} = LLVMIntTypeInContext(${ctx}, ${bits});
      }
    ]],
  },

  method "get_int_type_width" {
    c_method_call "unsigned" "LLVMGetIntTypeWidth" {}
  },

  --                                          Floating Point types
  c_function "half_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMHalfType();
      } else {
         ${type} = LLVMHalfTypeInContext(${ctx});
      }
    ]],
  },
  c_function "float_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMFloatType();
      } else {
         ${type} = LLVMFloatTypeInContext(${ctx});
      }
    ]],
  },
  c_function "double_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMDoubleType();
      } else {
         ${type} = LLVMDoubleTypeInContext(${ctx});
      }
    ]],
  },
  c_function "x86fp80_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMX86FP80Type();
      } else {
         ${type} = LLVMX86FP80TypeInContext(${ctx});
      }
    ]],
  },
  c_function "fp128_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMFP128Type();
      } else {
         ${type} = LLVMFP128TypeInContext(${ctx});
      }
    ]],
  },
  c_function "ppcfp128_type" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMPPCFP128Type();
      } else {
         ${type} = LLVMPPCFP128TypeInContext(${ctx});
      }
    ]],
  },
}

