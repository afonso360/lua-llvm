-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Module module", function ()
  it("should cleanly allocate and deallocate", function ()
    local module = llvm.Module.create_with_name("mname")
    assert.is_not_nil(module)
    module.dispose()
  end)

  it("Can set and get identifier", function ()
    local module = llvm.Module.create_with_name("mname")
    assert.is_not_nil(module)
    assert.are.equal(module:identifier(), "mname")
    module:set_identifier("ident")
    assert.are.equal(module:identifier(), "ident")
    module.dispose()
  end)
end)

