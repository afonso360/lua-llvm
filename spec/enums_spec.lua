-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Enum exports", function ()
  it("RealPredicate", function ()
    local inspect = require("inspect")
    print(inspect(llvm))
    assert.is.not_nil(llvm.RealPredicate.OEQ)
  end)
end)
