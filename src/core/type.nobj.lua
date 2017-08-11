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

  method "dump" {
    doc [[ Dumps a type to stderr ]],
    c_method_call "void" "LLVMDumpType" {},
  },

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
}

object "FunctionType" {
  extends "Type",
  c_source [[
      typedef Type FunctionType;
  ]],

  constructor "new" {
    var_in { "Type *", "return_type" },
    var_in { "<any>", "parameters" },
    var_in { "bool", "var_arg" },
    c_source [[
      size_t n;
      Type ** arr;

      n = lua_rawlen(L, 2);
      arr = calloc(n, sizeof(Type *));

      for (int i=1; i<=n; i++) {
        lua_rawgeti(L, 2, i);
        arr[i-1] = obj_type_Type_check(L, -1);
        lua_pop(L, 1);
      }

      ${this} = LLVMFunctionType(${return_type}, arr, n, ${var_arg});

      free(arr);
    ]],
  },

  method "is_vararg" {
    c_method_call "bool" "LLVMIsFunctionVarArg" {}
  },

  method "return_type" {
    c_method_call "Type *" "LLVMGetReturnType" {}
  },

  method "count_param_types" {
    c_method_call "unsigned" "LLVMCountParamTypes" {}
  },
  method "param_types" {
    var_out { "<any>", "parameters" },

    c_source [[
      size_t n = LLVMCountParamTypes(${this});
      Type ** arr = calloc(n, sizeof(Type *));

      lua_createtable(L, n, 0);

      LLVMGetParamTypes(${this}, arr);

      for (int i=0; i<n; i++) {
        Type * ty = arr[i];
        obj_type_FunctionType_push(L, ty, 0);
        lua_rawseti(L, -2, i+1);
      }

      free(arr);
    ]],
  }
}

object "IntType" {
  extends "Type",
  c_source [[
      typedef Type IntType;
  ]],

  constructor "int1" {
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
  constructor "int8" {
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
  constructor "int16" {
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
  constructor "int32" {
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
  constructor "int64" {
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
  constructor "int128" {
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
}

object "FloatType" {
  extends "Type",
  c_source [[
      typedef Type FloatType;
  ]],
  --                                          Floating Point
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
}
