local llvm = require "llvm"

describe("Builder module", function ()
  it("should cleanly allocate and deallocate", function ()
    local builder = llvm.Builder.create()
    assert.is_not_nil(builder)
    builder.dispose()
  end)

  it("should have a destructor", function ()
    local builder = llvm.Builder.create()
    assert.is.truthy(getmetatable(builder).__gc)
    assert.is.truthy(builder.dispose)
    builder.dispose()
  end)

  it("should provide access to constructors", function ()
    assert.is.truthy(llvm.Builder.create)
    assert.is.truthy(llvm.Builder.create_in_context)
  end)
end)
