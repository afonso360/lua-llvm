-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Type module", function ()
  describe("Integer type", function ()
    it("should have constant length", function ()
      local type = llvm.Type.int1()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)

    it("should allow arbitrary percision", function ()
      local type = llvm.Type.int(120)
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
      assert.are.equal(type:get_int_width(), 120)
    end)

    it("should be able to create in context", function ()
      local context = llvm.Context.global_context()
      local type = llvm.Type.int(120, context)

      assert.is_not_nil(type)
      assert.is_not_nil(context)
      assert.are.equal(context, type:get_context())

      local type1 = llvm.Type.int1(context)
      assert.is_not_nil(type1)
      assert.are.equal(context, type1:get_context())

    end)
  end)
  describe("Floating point type", function ()
    it("should have constant length", function ()
      local type = llvm.Type.half()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)

    it("should be able to create in context", function ()
      local context = llvm.Context.global_context()
      local type = llvm.Type.half(context)
      assert.is_not_nil(type)
      assert.is_not_nil(context)
      assert.are.equal(context, type:get_context())
    end)
  end)
  describe("Function type", function ()
    it("should have constant length", function ()
      local type = llvm.Type.half()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)
  end)
end)
