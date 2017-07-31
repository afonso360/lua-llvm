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
