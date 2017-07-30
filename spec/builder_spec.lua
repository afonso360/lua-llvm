local llvm = require "llvm"

describe("Builder module", function ()
  it("should cleanly allocate and deallocate", function ()
    local builder = llvm.Builder.create()
    assert.is_not_nil(builder)
  end)

  it("should have a destructor", function ()
    assert.is.truthy(getmetatable(llvm.Builder.create()).__gc)
  end)

  it("should provide access to constructors", function ()
    assert.is.truthy(llvm.Builder.create)
    assert.is.truthy(llvm.Builder.create_in_context)
  end)
end)
