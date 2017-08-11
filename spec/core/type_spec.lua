-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

local llvm = require "llvm"

describe("Type module", function ()
  describe("Integer type", function ()
    it("should have constant length", function ()
      local type = llvm.IntType.int1()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)

    it("should allow arbitrary percision", function ()
      local type = llvm.IntType.int(120)
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
      assert.are.equal(type:get_int_width(), 120)
    end)

    it("should be able to create in context", function ()
      local context = llvm.Context.global_context()
      local type = llvm.IntType.int(120, context)

      assert.is_not_nil(type)
      assert.is_not_nil(context)
      assert.are.equal(context, type:get_context())

      local type1 = llvm.IntType.int1(context)
      assert.is_not_nil(type1)
      assert.are.equal(context, type1:get_context())

    end)
  end)
  describe("Floating point type", function ()
    it("should have constant length", function ()
      local type = llvm.FloatType.half()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)

    it("should be able to create in context", function ()
      local context = llvm.Context.global_context()
      local type = llvm.FloatType.half(context)
      assert.is_not_nil(type)
      assert.is_not_nil(context)
      assert.are.equal(context, type:get_context())
    end)
  end)
  describe("Function type", function ()
    it("should have constant length", function ()
      local type = llvm.FloatType.half()
      assert.is_not_nil(type)
      assert.is.truthy(type:is_sized())
    end)
  end)
end)

describe("FunctionType module", function ()
  it("should construct correctly", function ()
    local r = llvm.IntType.int1()
    local v = {
      llvm.IntType.int8(),
      llvm.IntType.int16(),
    }
    local ftype = llvm.FunctionType.new(r, v, false)
    assert.is_false(ftype:is_vararg())
    assert.are_equal(ftype:count_param_types(), 2)
    assert.are.same(ftype:param_types(), v)

    -- TODO: Assert param_types doesen't own its data
  end)
end)
