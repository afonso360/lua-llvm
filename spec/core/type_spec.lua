local llvm = require "llvm"

describe("Type module", function ()
  describe("Integer type", function ()
    it("should have constant length", function ()
      local type = llvm.Type.int_1_type()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)

    it("should allow arbitrary percision", function ()
      local type = llvm.Type.int_type(120)
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
      assert.are.equal(type:get_int_type_width(), 120)
    end)

    it("should be able to create in context", function ()
      local context = llvm.Context.global_context()
      local type = llvm.Type.int_type(120)
      assert.is_not_nil(type)
      assert.is_not_nil(context)
      assert.are.equal(context, type:get_context())
    end)
  end)
end)
