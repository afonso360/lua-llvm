-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Builder module", function ()
  it("should cleanly allocate and deallocate", function ()
    local builder = llvm.Builder.new()
    assert.is_not_nil(builder)
    builder.dispose()
  end)

  it("should have a destructor", function ()
    local builder = llvm.Builder.new()
    assert.is.truthy(getmetatable(builder).__gc)
    assert.is.truthy(builder.dispose)
    builder.dispose()
  end)
end)
