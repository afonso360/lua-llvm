-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

-- TODO: Make a ownership function and test for it
describe("Context module", function ()
  it("should cleanly get global context", function ()
    local context = llvm.Context.global_context()
    assert.is_not_nil(context)
  end)

  it("should have a destructor", function ()
    local context = llvm.Context.global_context()
    assert.is.truthy(getmetatable(context).__gc)
    assert.is.truthy(context.dispose)
  end)

  it("should provide access to constructors", function ()
    assert.is.truthy(llvm.Context.global_context)
    assert.is.truthy(llvm.Context.create)
  end)
end)
