-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Module module", function ()
  local function_type_helper = function ()
    local r = llvm.IntType.int1()
    local v = {
      llvm.IntType.int8(),
      llvm.IntType.int16(),
    }
    return llvm.FunctionType.new(r, v, false)
  end

  it("should cleanly allocate and deallocate", function ()
    local module = llvm.Module.create("mname")
    assert.is_not_nil(module)
    module.dispose()
  end)

  it("Can set and get identifier", function ()
    local module = llvm.Module.create("mname")
    assert.is_not_nil(module)
    assert.are.equal(module:identifier(), "mname")
    module:set_identifier("ident")
    assert.are.equal(module:identifier(), "ident")
    module.dispose()
  end)

  it("Can set and get target triplet", function ()
    local module = llvm.Module.create("mname")
    assert.is_not_nil(module)
    module:set_target("i386-ibm-none-android")
    assert.are.equal(module:target(), "i386-ibm-none-android")
  end)

  it("Can add and retrieve functions", function ()
    local module = llvm.Module.create("mname")
    local functy = function_type_helper()
    module:add_function("fname", functy)
    local retf = module:get_function("fname")
    assert.is_not_nil(retf)
  end)
end)

