-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

-- Missing
-- Sequential types
-- Structure types
-- Function  types
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
  constructor "int_1" {
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
  constructor "int_8" {
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
  constructor "int_16" {
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
  constructor "int_32" {
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
  constructor "int_64" {
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
  constructor "int_128" {
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
  constructor "int" {
    doc [[ Context is optional ]],
    doc [[ Bits: Size of the integer ]],
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

  method "get_int_width" {
    c_method_call "unsigned" "LLVMGetIntTypeWidth" {}
  },

  --                                          Floating Point types
  constructor "half" {
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
  constructor "float" {
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
  constructor "double" {
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
  constructor "x86fp80" {
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
  constructor "fp128" {
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
  constructor "ppcfp128" {
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

  --                                          Other types
  constructor "void" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMVoidType();
      } else {
         ${type} = LLVMVoidTypeInContext(${ctx});
      }
    ]],
  },
  constructor "label" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMLabelType();
      } else {
         ${type} = LLVMLabelTypeInContext(${ctx});
      }
    ]],
  },
  constructor "x86mmx" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    var_out { "Type *", "type" },
    c_source [[
      if (${ctx} == NULL) {
         ${type} = LLVMX86MMXType();
      } else {
         ${type} = LLVMX86MMXTypeInContext(${ctx});
      }
    ]],
  },
}
