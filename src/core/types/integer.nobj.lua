-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

-- Functions Missing
--LLVMInt1TypeInContext
--LLVMInt8TypeInContext
--LLVMInt16TypeInContext
--LLVMInt32TypeInContext
--LLVMInt64TypeInContext
--LLVMInt128TypeInContext
--LLVMIntTypeInContext
--LLVMInt1Type
--LLVMInt8Type
--LLVMInt16Type
--LLVMInt32Type
--LLVMInt64Type
--LLVMInt128Type
--LLVMIntType
--LLVMGetIntTypeWidth

object "integer" {
  method "int1type" {
    c_call "void *" "LLVMInt1Type" { }
    --c_call "LLVMTypeRef" "LLVMInt1Type" { }
  }
}
