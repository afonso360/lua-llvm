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
    assert.are.equal(module:get_identifier(), "mname")
    module:set_identifier("ident")
    assert.are.equal(module:get_identifier(), "ident")
    module.dispose()
  end)
end)

