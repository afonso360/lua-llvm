local llvm = require "llvm"

describe("Context module", function ()
	it("should cleanly allocate and deallocate global context", function ()
    local context = llvm.Context.get_global_context()
    
		assert.truthy("ay")
	end)
end)
