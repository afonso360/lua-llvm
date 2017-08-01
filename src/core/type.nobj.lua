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
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMInt1Type();
      } else {
         ${this} = LLVMInt1TypeInContext(${ctx});
      }
    ]],
  },
  constructor "int_8" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMInt8Type();
      } else {
         ${this} = LLVMInt8TypeInContext(${ctx});
      }
    ]],
  },
  constructor "int_16" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMInt16Type();
      } else {
         ${this} = LLVMInt16TypeInContext(${ctx});
      }
    ]],
  },
  constructor "int_32" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMInt32Type();
      } else {
         ${this} = LLVMInt32TypeInContext(${ctx});
      }
    ]],
  },
  constructor "int_64" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMInt64Type();
      } else {
         ${this} = LLVMInt64TypeInContext(${ctx});
      }
    ]],
  },
  constructor "int_128" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMInt128Type();
      } else {
         ${this} = LLVMInt128TypeInContext(${ctx});
      }
    ]],
  },
  constructor "int" {
    doc [[ Context is optional ]],
    doc [[ Bits: Size of the integer ]],
    var_in { "unsigned", "bits" },
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMIntType(${bits});
      } else {
         ${this} = LLVMIntTypeInContext(${ctx}, ${bits});
      }
    ]],
  },

  method "get_int_width" {
    c_method_call "unsigned" "LLVMGetIntTypeWidth" {}
  },

  --                                          Floating Pointthis 
  constructor "half" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMHalfType();
      } else {
         ${this} = LLVMHalfTypeInContext(${ctx});
      }
    ]],
  },
  constructor "float" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMFloatType();
      } else {
         ${this} = LLVMFloatTypeInContext(${ctx});
      }
    ]],
  },
  constructor "double" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMDoubleType();
      } else {
         ${this} = LLVMDoubleTypeInContext(${ctx});
      }
    ]],
  },
  constructor "x86fp80" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMX86FP80Type();
      } else {
         ${this} = LLVMX86FP80TypeInContext(${ctx});
      }
    ]],
  },
  constructor "fp128" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMFP128Type();
      } else {
         ${this} = LLVMFP128TypeInContext(${ctx});
      }
    ]],
  },
  constructor "ppcfp128" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMPPCFP128Type();
      } else {
         ${this} = LLVMPPCFP128TypeInContext(${ctx});
      }
    ]],
  },

  --                                          Other types
  constructor "void" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMVoidType();
      } else {
         ${this} = LLVMVoidTypeInContext(${ctx});
      }
    ]],
  },
  constructor "label" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMLabelType();
      } else {
         ${this} = LLVMLabelTypeInContext(${ctx});
      }
    ]],
  },
  constructor "x86mmx" {
    doc [[ Context is optional ]],
    var_in { "Context *", "ctx?" },
    c_source [[
      if (${ctx} == NULL) {
         ${this} = LLVMX86MMXType();
      } else {
         ${this} = LLVMX86MMXTypeInContext(${ctx});
      }
    ]],
  },
  --                                          Function types
  constructor "func" {
    c_call "Type *" "LLVMFunctionType" {
      "Type *", "ret",
      "Type **", "param",
      "unsigned", "param_count",
      "bool", "var_arg"
    },
  },
}
