-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Value" {
  c_source [[
      typedef struct LLVMOpaqueValue Value;
  ]],

  method "get_value_name" {
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
