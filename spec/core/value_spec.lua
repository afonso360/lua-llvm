-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Value module", function ()
  describe("IntValue type", function ()
    it("should construct correctly", function ()
      local value = llvm.IntValue.const_int(llvm.IntType.int8(), 10, false)
      assert.is.truthy(value:is_constant())
      assert.is.falsy(value:is_undef())
    end)
  end)
end)
