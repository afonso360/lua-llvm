local llvm = require "llvm"

describe("Context module", function ()
	it("should cleanly allocate and deallocate global context", function ()
    local context = llvm.Context.global_context()
		assert.is_not_nil(context)
	end)

	it("should provide access to constructors", function ()
    assert.is_truthy(llvm.Context.global_context)
    assert.is_truthy(llvm.Context.create)
	end)

	it("should have a destructor", function ()
    assert.is_truthy(getmetatable(llvm.Context.global_context()).__gc)
	end)
end)
