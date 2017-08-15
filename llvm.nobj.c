/***********************************************************************************************
************************************************************************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!! Warning this file was generated from a set of *.nobj.lua definition files !!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
************************************************************************************************
***********************************************************************************************/

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

/* some Lua 5.0 compatibility support. */
#if !defined(lua_pushliteral)
#define lua_pushliteral(L, s) lua_pushstring(L, "" s, (sizeof(s)/sizeof(char))-1)
#endif

#if !defined(LUA_VERSION_NUM)
#define lua_pushinteger(L, n) lua_pushnumber(L, (lua_Number)n)
#define luaL_Reg luaL_reg
#endif

/* some Lua 5.1 compatibility support. */
#if !defined(LUA_VERSION_NUM) || (LUA_VERSION_NUM == 501)
/*
** Adapted from Lua 5.2.0
*/
static void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
  luaL_checkstack(L, nup, "too many upvalues");
  for (; l->name != NULL; l++) {  /* fill the table with given functions */
    int i;
    for (i = 0; i < nup; i++)  /* copy upvalues to the top */
      lua_pushvalue(L, -nup);
    lua_pushstring(L, l->name);
    lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
    lua_settable(L, -(nup + 3));
  }
  lua_pop(L, nup);  /* remove upvalues */
}

#define lua_load_no_mode(L, reader, data, source) \
	lua_load(L, reader, data, source)

#define lua_rawlen(L, idx) lua_objlen(L, idx)

#endif

#if LUA_VERSION_NUM >= 502

#define lua_load_no_mode(L, reader, data, source) \
	lua_load(L, reader, data, source, NULL)

static int luaL_typerror (lua_State *L, int narg, const char *tname) {
  const char *msg = lua_pushfstring(L, "%s expected, got %s",
                                    tname, luaL_typename(L, narg));
  return luaL_argerror(L, narg, msg);
}

#endif

#define REG_PACKAGE_IS_CONSTRUCTOR 0
#define REG_MODULES_AS_GLOBALS 0
#define REG_OBJECTS_AS_GLOBALS 0
#define OBJ_DATA_HIDDEN_METATABLE 0
#define USE_FIELD_GET_SET_METHODS 0
#define LUAJIT_FFI 0


#include "llvm-c/Core.h"
#include "llvm-c/Types.h"



#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#ifdef _MSC_VER
#define __WINDOWS__
#else
#if defined(_WIN32)
#define __WINDOWS__
#endif
#endif

#ifdef __WINDOWS__

/* for MinGW32 compiler need to include <stdint.h> */
#ifdef __GNUC__
#include <stdint.h>
#include <stdbool.h>
#else

/* define some standard types missing on Windows. */
#ifndef __INT32_MAX__
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
#ifndef __INT64_MAX__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef int bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#endif

/* wrap strerror_s(). */
#ifdef __GNUC__
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) do { \
	strncpy((buf), strerror(errno), (buflen)-1); \
	(buf)[(buflen)-1] = '\0'; \
} while(0)
#endif
#else
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) strerror_s((buf), (buflen), (errno))
#endif
#endif

#define FUNC_UNUSED

#define LUA_NOBJ_API __declspec(dllexport)

#else

#define LUA_NOBJ_API LUALIB_API

#include <stdint.h>
#include <stdbool.h>

#define FUNC_UNUSED __attribute__((unused))

#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define assert_obj_type(type, obj) \
	assert(__builtin_types_compatible_p(typeof(obj), type *))
#else
#define assert_obj_type(type, obj)
#endif

void *nobj_realloc(void *ptr, size_t osize, size_t nsize);

void *nobj_realloc(void *ptr, size_t osize, size_t nsize) {
	(void)osize;
	if(0 == nsize) {
		free(ptr);
		return NULL;
	}
	return realloc(ptr, nsize);
}

#define obj_type_free(type, obj) do { \
	assert_obj_type(type, obj); \
	nobj_realloc((obj), sizeof(type), 0); \
} while(0)

#define obj_type_new(type, obj) do { \
	assert_obj_type(type, obj); \
	(obj) = nobj_realloc(NULL, 0, sizeof(type)); \
} while(0)

typedef struct obj_type obj_type;

typedef void (*base_caster_t)(void **obj);

typedef void (*dyn_caster_t)(void **obj, obj_type **type);

#define OBJ_TYPE_FLAG_WEAK_REF (1<<0)
#define OBJ_TYPE_SIMPLE (1<<1)
#define OBJ_TYPE_IMPORT (1<<2)
struct obj_type {
	dyn_caster_t    dcaster;  /**< caster to support casting to sub-objects. */
	int32_t         id;       /**< type's id. */
	uint32_t        flags;    /**< type's flags (weak refs) */
	const char      *name;    /**< type's object name. */
};

typedef struct obj_base {
	int32_t        id;
	base_caster_t  bcaster;
} obj_base;

typedef enum obj_const_type {
	CONST_UNKOWN    = 0,
	CONST_BOOLEAN   = 1,
	CONST_NUMBER    = 2,
	CONST_STRING    = 3
} obj_const_type;

typedef struct obj_const {
	const char      *name;    /**< constant's name. */
	const char      *str;
	double          num;
	obj_const_type  type;
} obj_const;

typedef enum obj_field_type {
	TYPE_UNKOWN    = 0,
	TYPE_UINT8     = 1,
	TYPE_UINT16    = 2,
	TYPE_UINT32    = 3,
	TYPE_UINT64    = 4,
	TYPE_INT8      = 5,
	TYPE_INT16     = 6,
	TYPE_INT32     = 7,
	TYPE_INT64     = 8,
	TYPE_DOUBLE    = 9,
	TYPE_FLOAT     = 10,
	TYPE_STRING    = 11
} obj_field_type;

typedef struct obj_field {
	const char      *name;  /**< field's name. */
	uint32_t        offset; /**< offset to field's data. */
	obj_field_type  type;   /**< field's data type. */
	uint32_t        flags;  /**< is_writable:1bit */
} obj_field;

typedef enum {
	REG_OBJECT,
	REG_PACKAGE,
	REG_META,
} module_reg_type;

typedef struct reg_impl {
	const char *if_name;
	const void *impl;
} reg_impl;

typedef struct reg_sub_module {
	obj_type        *type;
	module_reg_type req_type;
	const luaL_Reg  *pub_funcs;
	const luaL_Reg  *methods;
	const luaL_Reg  *metas;
	const obj_base  *bases;
	const obj_field *fields;
	const obj_const *constants;
	const reg_impl  *implements;
	int             bidirectional_consts;
} reg_sub_module;

#define OBJ_UDATA_FLAG_OWN (1<<0)
#define OBJ_UDATA_FLAG_LOOKUP (1<<1)
#define OBJ_UDATA_LAST_FLAG (OBJ_UDATA_FLAG_LOOKUP)
typedef struct obj_udata {
	void     *obj;
	uint32_t flags;  /**< lua_own:1bit */
} obj_udata;

/* use static pointer as key to weak userdata table. */
static char obj_udata_weak_ref_key[] = "obj_udata_weak_ref_key";

/* use static pointer as key to module's private table. */
static char obj_udata_private_key[] = "obj_udata_private_key";

#if LUAJIT_FFI
typedef int (*ffi_export_func_t)(void);
typedef struct ffi_export_symbol {
	const char *name;
	union {
	void               *data;
	ffi_export_func_t  func;
	} sym;
} ffi_export_symbol;
#endif





static obj_type obj_types[] = {
#define obj_type_id_Type 0
#define obj_type_Type (obj_types[obj_type_id_Type])
  { NULL, 0, OBJ_TYPE_FLAG_WEAK_REF, "Type" },
#define obj_type_id_FunctionType 1
#define obj_type_FunctionType (obj_types[obj_type_id_FunctionType])
  { NULL, 1, OBJ_TYPE_FLAG_WEAK_REF, "FunctionType" },
#define obj_type_id_IntType 2
#define obj_type_IntType (obj_types[obj_type_id_IntType])
  { NULL, 2, OBJ_TYPE_FLAG_WEAK_REF, "IntType" },
#define obj_type_id_FloatType 3
#define obj_type_FloatType (obj_types[obj_type_id_FloatType])
  { NULL, 3, OBJ_TYPE_FLAG_WEAK_REF, "FloatType" },
#define obj_type_id_Module 4
#define obj_type_Module (obj_types[obj_type_id_Module])
  { NULL, 4, OBJ_TYPE_FLAG_WEAK_REF, "Module" },
#define obj_type_id_Context 5
#define obj_type_Context (obj_types[obj_type_id_Context])
  { NULL, 5, OBJ_TYPE_FLAG_WEAK_REF, "Context" },
#define obj_type_id_Value 6
#define obj_type_Value (obj_types[obj_type_id_Value])
  { NULL, 6, OBJ_TYPE_FLAG_WEAK_REF, "Value" },
#define obj_type_id_IntValue 7
#define obj_type_IntValue (obj_types[obj_type_id_IntValue])
  { NULL, 7, OBJ_TYPE_FLAG_WEAK_REF, "IntValue" },
#define obj_type_id_FloatValue 8
#define obj_type_FloatValue (obj_types[obj_type_id_FloatValue])
  { NULL, 8, OBJ_TYPE_FLAG_WEAK_REF, "FloatValue" },
#define obj_type_id_FunctionValue 9
#define obj_type_FunctionValue (obj_types[obj_type_id_FunctionValue])
  { NULL, 9, OBJ_TYPE_FLAG_WEAK_REF, "FunctionValue" },
#define obj_type_id_BasicBlock 10
#define obj_type_BasicBlock (obj_types[obj_type_id_BasicBlock])
  { NULL, 10, OBJ_TYPE_FLAG_WEAK_REF, "BasicBlock" },
#define obj_type_id_Builder 11
#define obj_type_Builder (obj_types[obj_type_id_Builder])
  { NULL, 11, OBJ_TYPE_FLAG_WEAK_REF, "Builder" },
#define obj_type_id_Opcode 12
#define obj_type_Opcode (obj_types[obj_type_id_Opcode])
  { NULL, 12, OBJ_TYPE_FLAG_WEAK_REF, "Opcode" },
#define obj_type_id_TypeKind 13
#define obj_type_TypeKind (obj_types[obj_type_id_TypeKind])
  { NULL, 13, OBJ_TYPE_FLAG_WEAK_REF, "TypeKind" },
#define obj_type_id_Linkage 14
#define obj_type_Linkage (obj_types[obj_type_id_Linkage])
  { NULL, 14, OBJ_TYPE_FLAG_WEAK_REF, "Linkage" },
#define obj_type_id_Visibility 15
#define obj_type_Visibility (obj_types[obj_type_id_Visibility])
  { NULL, 15, OBJ_TYPE_FLAG_WEAK_REF, "Visibility" },
#define obj_type_id_DLLStorageClass 16
#define obj_type_DLLStorageClass (obj_types[obj_type_id_DLLStorageClass])
  { NULL, 16, OBJ_TYPE_FLAG_WEAK_REF, "DLLStorageClass" },
#define obj_type_id_CallConv 17
#define obj_type_CallConv (obj_types[obj_type_id_CallConv])
  { NULL, 17, OBJ_TYPE_FLAG_WEAK_REF, "CallConv" },
#define obj_type_id_ValueKind 18
#define obj_type_ValueKind (obj_types[obj_type_id_ValueKind])
  { NULL, 18, OBJ_TYPE_FLAG_WEAK_REF, "ValueKind" },
#define obj_type_id_IntPredicate 19
#define obj_type_IntPredicate (obj_types[obj_type_id_IntPredicate])
  { NULL, 19, OBJ_TYPE_FLAG_WEAK_REF, "IntPredicate" },
#define obj_type_id_RealPredicate 20
#define obj_type_RealPredicate (obj_types[obj_type_id_RealPredicate])
  { NULL, 20, OBJ_TYPE_FLAG_WEAK_REF, "RealPredicate" },
#define obj_type_id_LandingPadClauseTy 21
#define obj_type_LandingPadClauseTy (obj_types[obj_type_id_LandingPadClauseTy])
  { NULL, 21, OBJ_TYPE_FLAG_WEAK_REF, "LandingPadClauseTy" },
#define obj_type_id_ThreadLocalMode 22
#define obj_type_ThreadLocalMode (obj_types[obj_type_id_ThreadLocalMode])
  { NULL, 22, OBJ_TYPE_FLAG_WEAK_REF, "ThreadLocalMode" },
#define obj_type_id_AtomicOrdering 23
#define obj_type_AtomicOrdering (obj_types[obj_type_id_AtomicOrdering])
  { NULL, 23, OBJ_TYPE_FLAG_WEAK_REF, "AtomicOrdering" },
#define obj_type_id_AtomicRMWBinOp 24
#define obj_type_AtomicRMWBinOp (obj_types[obj_type_id_AtomicRMWBinOp])
  { NULL, 24, OBJ_TYPE_FLAG_WEAK_REF, "AtomicRMWBinOp" },
#define obj_type_id_DiagnosticSeverity 25
#define obj_type_DiagnosticSeverity (obj_types[obj_type_id_DiagnosticSeverity])
  { NULL, 25, OBJ_TYPE_FLAG_WEAK_REF, "DiagnosticSeverity" },
#define obj_type_id_AttributeIndex 26
#define obj_type_AttributeIndex (obj_types[obj_type_id_AttributeIndex])
  { NULL, 26, OBJ_TYPE_FLAG_WEAK_REF, "AttributeIndex" },
  {NULL, -1, 0, NULL},
};


#if LUAJIT_FFI

/* nobj_ffi_support_enabled_hint should be set to 1 when FFI support is enabled in at-least one
 * instance of a LuaJIT state.  It should never be set back to 0. */
static int nobj_ffi_support_enabled_hint = 0;
static const char nobj_ffi_support_key[] = "LuaNativeObject_FFI_SUPPORT";
static const char nobj_check_ffi_support_code[] =
"local stat, ffi=pcall(require,\"ffi\")\n" /* try loading LuaJIT`s FFI module. */
"if not stat then return false end\n"
"return true\n";

static int nobj_check_ffi_support(lua_State *L) {
	int rc;
	int err;

	/* check if ffi test has already been done. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_rawget(L, LUA_REGISTRYINDEX);
	if(!lua_isnil(L, -1)) {
		rc = lua_toboolean(L, -1);
		lua_pop(L, 1);
		/* use results of previous check. */
		goto finished;
	}
	lua_pop(L, 1); /* pop nil. */

	err = luaL_loadbuffer(L, nobj_check_ffi_support_code,
		sizeof(nobj_check_ffi_support_code) - 1, nobj_ffi_support_key);
	if(0 == err) {
		err = lua_pcall(L, 0, 1, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Error when checking for FFI-support: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
		return 0;
	}
	/* check results of test. */
	rc = lua_toboolean(L, -1);
	lua_pop(L, 1); /* pop results. */
		/* cache results. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_pushboolean(L, rc);
	lua_rawset(L, LUA_REGISTRYINDEX);

finished:
	/* turn-on hint that there is FFI code enabled. */
	if(rc) {
		nobj_ffi_support_enabled_hint = 1;
	}

	return rc;
}

typedef struct {
	const char **ffi_init_code;
	int offset;
} nobj_reader_state;

static const char *nobj_lua_Reader(lua_State *L, void *data, size_t *size) {
	nobj_reader_state *state = (nobj_reader_state *)data;
	const char *ptr;

	(void)L;
	ptr = state->ffi_init_code[state->offset];
	if(ptr != NULL) {
		*size = strlen(ptr);
		state->offset++;
	} else {
		*size = 0;
	}
	return ptr;
}

static int nobj_try_loading_ffi(lua_State *L, const char *ffi_mod_name,
		const char *ffi_init_code[], const ffi_export_symbol *ffi_exports, int priv_table)
{
	nobj_reader_state state = { ffi_init_code, 0 };
	int err;

	/* export symbols to priv_table. */
	while(ffi_exports->name != NULL) {
		lua_pushstring(L, ffi_exports->name);
		lua_pushlightuserdata(L, ffi_exports->sym.data);
		lua_settable(L, priv_table);
		ffi_exports++;
	}
	err = lua_load_no_mode(L, nobj_lua_Reader, &state, ffi_mod_name);
	if(0 == err) {
		lua_pushvalue(L, -2); /* dup C module's table. */
		lua_pushvalue(L, priv_table); /* move priv_table to top of stack. */
		lua_remove(L, priv_table);
		lua_pushvalue(L, LUA_REGISTRYINDEX);
		err = lua_pcall(L, 3, 0, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Failed to install FFI-based bindings: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
	}
	return err;
}
#endif


typedef struct {
	void *impl;
	void *obj;
} obj_implement;

static FUNC_UNUSED void *obj_implement_luaoptional(lua_State *L, int _index, void **impl, char *if_name) {
	void *ud;
	if(lua_isnoneornil(L, _index)) {
		return NULL;
	}
	/* get the implements table for this interface. */
	lua_pushlightuserdata(L, if_name);
	lua_rawget(L, LUA_REGISTRYINDEX);

	/* get pointer to userdata value & check if it is a userdata value. */
	ud = (obj_implement *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* get the userdata's metatable */
		if(lua_getmetatable(L, _index)) {
			/* lookup metatable in interface table for this object's implementation of the interface. */
			lua_gettable(L, -2);
		} else {
			/* no metatable. */
			goto no_interface;
		}
#if LUAJIT_FFI
	} else if(nobj_ffi_support_enabled_hint) { /* handle cdata. */
		/* get cdata interface check function from interface table. */
		lua_getfield(L, -1, "cdata");
		if(lua_isfunction(L, -1)) {
			/* pass cdata to function, return value should be an implmentation. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			/* get pointer to cdata. */
			ud = (void *)lua_topointer(L, _index);
		} else {
			lua_pop(L, 1); /* pop non-function. */
			goto no_interface;
		}
#endif
	} else {
		goto no_interface;
	}

	if(!lua_isnil(L, -1)) {
		*impl = lua_touserdata(L, -1);
		lua_pop(L, 2); /* pop interface table & implementation. */
		/* object implements interface. */
		return ud;
	} else {
		lua_pop(L, 1); /* pop nil. */
	}
no_interface:
	lua_pop(L, 1); /* pop interface table. */
	return NULL;
}

static FUNC_UNUSED void *obj_implement_luacheck(lua_State *L, int _index, void **impl, char *type) {
	void *ud = obj_implement_luaoptional(L, _index, impl, type);
	if(ud == NULL) {
#define ERROR_BUFFER_SIZE 256
		char buf[ERROR_BUFFER_SIZE];
		snprintf(buf, ERROR_BUFFER_SIZE-1,"Expected object with %s interface", type);
		/* value doesn't implement this interface. */
		luaL_argerror(L, _index, buf);
	}
	return ud;
}

/* use static pointer as key to interfaces table. (version 1.0) */
static char obj_interfaces_table_key[] = "obj_interfaces<1.0>_table_key";

static void obj_get_global_interfaces_table(lua_State *L) {
	/* get global interfaces table. */
	lua_getfield(L, LUA_REGISTRYINDEX, obj_interfaces_table_key);
	if(lua_isnil(L, -1)) {
		/* Need to create global interfaces table. */
		lua_pop(L, 1); /* pop nil */
		lua_createtable(L, 0, 4); /* 0 size array part, small hash part. */
		lua_pushvalue(L, -1); /* dup table. */
		/* store interfaces table in Lua registery. */
		lua_setfield(L, LUA_REGISTRYINDEX, obj_interfaces_table_key);
	}
}

static void obj_get_interface(lua_State *L, const char *name, int global_if_tab) {
	/* get a interface's implementation table */
	lua_getfield(L, global_if_tab, name);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil */
		/* new interface. (i.e. no object implement it yet.)
		 *
		 * create an empty table for this interface that will be used when an
		 * implementation is registered for this interface.
		 */
		lua_createtable(L, 0, 2); /* 0 size array part, small hash part. */
		lua_pushvalue(L, -1); /* dup table. */
		lua_setfield(L, global_if_tab, name); /* store interface in global interfaces table. */
	}
}

static int obj_get_userdata_interface(lua_State *L) {
	/* get the userdata's metatable */
	if(lua_getmetatable(L, 2)) {
		/* lookup metatable in interface table for the userdata's implementation of the interface. */
		lua_gettable(L, 1);
		if(!lua_isnil(L, -1)) {
			/* return the implementation. */
			return 1;
		}
	}
	/* no metatable or no implementation. */
	return 0;
}

static void obj_interface_register(lua_State *L, char *name, int global_if_tab) {
	/* get the table of implementations for this interface. */
	obj_get_interface(L, name, global_if_tab);

	/* check for 'userdata' function. */
	lua_getfield(L, -1, "userdata");
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		/* add C function for getting a userdata's implementation. */
		lua_pushcfunction(L, obj_get_userdata_interface);
		lua_setfield(L, -2, "userdata");
	} else {
		/* already have function. */
		lua_pop(L, 1); /* pop C function. */
	}
	/* we are going to use a lightuserdata pointer for fast lookup of the interface's impl. table. */
	lua_pushlightuserdata(L, name);
	lua_insert(L, -2);
	lua_settable(L, LUA_REGISTRYINDEX);
}

static void obj_register_interfaces(lua_State *L, char *interfaces[]) {
	int i;
	int if_tab;
	/* get global interfaces table. */
	obj_get_global_interfaces_table(L);
	if_tab = lua_gettop(L);

	for(i = 0; interfaces[i] != NULL ; i++) {
		obj_interface_register(L, interfaces[i], if_tab);
	}
	lua_pop(L, 1); /* pop global interfaces table. */
}

static void obj_type_register_implement(lua_State *L, const reg_impl *impl, int global_if_tab, int mt_tab) {
	/* get the table of implementations for this interface. */
	obj_get_interface(L, impl->if_name, global_if_tab);

	/* register object's implement in the interface table. */
	lua_pushvalue(L, mt_tab);
	lua_pushlightuserdata(L, (void *)impl->impl);
	lua_settable(L, -3);

	lua_pop(L, 1); /* pop inteface table. */
}

static void obj_type_register_implements(lua_State *L, const reg_impl *impls) {
	int if_tab;
	int mt_tab;
	/* get absolute position of object's metatable. */
	mt_tab = lua_gettop(L);
	/* get global interfaces table. */
	obj_get_global_interfaces_table(L);
	if_tab = lua_gettop(L);

	for(; impls->if_name != NULL ; impls++) {
		obj_type_register_implement(L, impls, if_tab, mt_tab);
	}
	lua_pop(L, 1); /* pop global interfaces table. */
}

#ifndef REG_PACKAGE_IS_CONSTRUCTOR
#define REG_PACKAGE_IS_CONSTRUCTOR 1
#endif

#ifndef REG_MODULES_AS_GLOBALS
#define REG_MODULES_AS_GLOBALS 0
#endif

/* For Lua 5.2 don't register modules as globals. */
#if LUA_VERSION_NUM == 502
#undef REG_MODULES_AS_GLOBALS
#define REG_MODULES_AS_GLOBALS 0
#endif

#ifndef REG_OBJECTS_AS_GLOBALS
#define REG_OBJECTS_AS_GLOBALS 0
#endif

#ifndef OBJ_DATA_HIDDEN_METATABLE
#define OBJ_DATA_HIDDEN_METATABLE 1
#endif

static FUNC_UNUSED int obj_import_external_type(lua_State *L, obj_type *type) {
	/* find the external type's metatable using it's name. */
	lua_pushstring(L, type->name);
	lua_rawget(L, LUA_REGISTRYINDEX); /* external type's metatable. */
	if(!lua_isnil(L, -1)) {
		/* found it.  Now we will map our 'type' pointer to the metatable. */
		/* REGISTERY[lightuserdata<type>] = REGISTERY[type->name] */
		lua_pushlightuserdata(L, type); /* use our 'type' pointer as lookup key. */
		lua_pushvalue(L, -2); /* dup. type's metatable. */
		lua_rawset(L, LUA_REGISTRYINDEX); /* save external type's metatable. */
		/* NOTE: top of Lua stack still has the type's metatable. */
		return 1;
	} else {
		lua_pop(L, 1); /* pop nil. */
	}
	return 0;
}

static FUNC_UNUSED int obj_import_external_ffi_type(lua_State *L, obj_type *type) {
	/* find the external type's metatable using it's name. */
	lua_pushstring(L, type->name);
	lua_rawget(L, LUA_REGISTRYINDEX); /* external type's metatable. */
	if(!lua_isnil(L, -1)) {
		/* found it.  Now we will map our 'type' pointer to the C check function. */
		/* _priv_table[lightuserdata<type>] = REGISTERY[type->name].c_check */
		lua_getfield(L, -1, "c_check");
		lua_remove(L, -2); /* remove metatable. */
		if(lua_isfunction(L, -1)) {
			lua_pushlightuserdata(L, type); /* use our 'type' pointer as lookup key. */
			lua_pushvalue(L, -2); /* dup. check function */
			lua_rawset(L, -4); /* save check function to module's private table. */
			/* NOTE: top of Lua stack still has the type's C check function. */
			return 1;
		} else {
			lua_pop(L, 1); /* pop non function value. */
		}
	} else {
		lua_pop(L, 1); /* pop nil. */
	}
	return 0;
}

static FUNC_UNUSED obj_udata *obj_udata_toobj(lua_State *L, int _index) {
	obj_udata *ud;
	size_t len;

	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	/* verify userdata size. */
	len = lua_rawlen(L, _index);
	if(len != sizeof(obj_udata)) {
		/* This shouldn't be possible */
		luaL_error(L, "invalid userdata size: size=%d, expected=%d", len, sizeof(obj_udata));
	}
	return ud;
}

static FUNC_UNUSED int obj_udata_is_compatible(lua_State *L, obj_udata *ud, void **obj, base_caster_t *caster, obj_type *type) {
	obj_base *base;
	obj_type *ud_type;
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
recheck_metatable:
	if(lua_rawequal(L, -1, -2)) {
		*obj = ud->obj;
		/* same type no casting needed. */
		return 1;
	} else if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		if((type->flags & OBJ_TYPE_IMPORT) == 0) {
			/* can't resolve internal type. */
			luaL_error(L, "Unknown object type(id=%d, name=%s)", type->id, type->name);
		}
		/* try to import external type. */
		if(obj_import_external_type(L, type)) {
			/* imported type, re-try metatable check. */
			goto recheck_metatable;
		}
		/* External type not yet available, so the object can't be compatible. */
	} else {
		/* Different types see if we can cast to the required type. */
		lua_rawgeti(L, -2, type->id);
		base = lua_touserdata(L, -1);
		lua_pop(L, 1); /* pop obj_base or nil */
		if(base != NULL) {
			*caster = base->bcaster;
			/* get the obj_type for this userdata. */
			lua_pushliteral(L, ".type");
			lua_rawget(L, -3); /* type's metatable. */
			ud_type = lua_touserdata(L, -1);
			lua_pop(L, 1); /* pop obj_type or nil */
			if(base == NULL) {
				luaL_error(L, "bad userdata, missing type info.");
				return 0;
			}
			/* check if userdata is a simple object. */
			if(ud_type->flags & OBJ_TYPE_SIMPLE) {
				*obj = ud;
			} else {
				*obj = ud->obj;
			}
			return 1;
		}
	}
	return 0;
}

static FUNC_UNUSED obj_udata *obj_udata_luacheck_internal(lua_State *L, int _index, void **obj, obj_type *type, int not_delete) {
	obj_udata *ud;
	base_caster_t caster = NULL;
	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			if(obj_udata_is_compatible(L, ud, obj, &(caster), type)) {
				lua_pop(L, 2); /* pop both metatables. */
				/* apply caster function if needed. */
				if(caster != NULL && *obj != NULL) {
					caster(obj);
				}
				/* check object pointer. */
				if(*obj == NULL) {
					if(not_delete) {
						luaL_error(L, "null %s", type->name); /* object was garbage collected? */
					}
					return NULL;
				}
				return ud;
			}
		}
	} else if(!lua_isnoneornil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
got_check_func:
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				*obj = *(void **)lua_topointer(L, _index);
				return ud;
			}
			lua_pop(L, 2);
		} else {
			lua_pop(L, 1); /* pop nil. */
			if(type->flags & OBJ_TYPE_IMPORT) {
				/* try to import external ffi type. */
				if(obj_import_external_ffi_type(L, type)) {
					/* imported type. */
					goto got_check_func;
				}
				/* External type not yet available, so the object can't be compatible. */
			}
		}
	}
	if(not_delete) {
		luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	}
	return NULL;
}

static FUNC_UNUSED void *obj_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	if(lua_isnoneornil(L, _index)) {
		return obj;
	}
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;
	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);
}

static FUNC_UNUSED void *obj_udata_luadelete_weak(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* remove object from weak table. */
	lua_pushlightuserdata(L, obj);
	lua_pushnil(L);
	lua_rawset(L, -3);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush_weak(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;

	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* lookup userdata instance from pointer. */
	lua_pushlightuserdata(L, obj);
	lua_rawget(L, -2);
	if(!lua_isnil(L, -1)) {
		lua_remove(L, -2);     /* remove objects table. */
		return;
	}
	lua_pop(L, 1);  /* pop nil. */

#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		lua_remove(L, -2);
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));

	/* init. obj_udata. */
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	/* add weak reference to object. */
	lua_pushlightuserdata(L, obj); /* push object pointer as the 'key' */
	lua_pushvalue(L, -2);          /* push object's udata */
	lua_rawset(L, -4);             /* add weak reference to object. */
	lua_remove(L, -2);     /* remove objects table. */
}

/* default object equal method. */
static FUNC_UNUSED int obj_udata_default_equal(lua_State *L) {
	obj_udata *ud1 = obj_udata_toobj(L, 1);
	obj_udata *ud2 = obj_udata_toobj(L, 2);

	lua_pushboolean(L, (ud1->obj == ud2->obj));
	return 1;
}

/* default object tostring method. */
static FUNC_UNUSED int obj_udata_default_tostring(lua_State *L) {
	obj_udata *ud = obj_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p, flags=%d", ud->obj, ud->flags);
	lua_concat(L, 2);

	return 1;
}

/*
 * Simple userdata objects.
 */
static FUNC_UNUSED void *obj_simple_udata_toobj(lua_State *L, int _index) {
	void *ud;

	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	return ud;
}

static FUNC_UNUSED void * obj_simple_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *ud;
	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			lua_pushlightuserdata(L, type);
			lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
recheck_metatable:
			if(lua_rawequal(L, -1, -2)) {
				lua_pop(L, 2); /* pop both metatables. */
				return ud;
			} else if(lua_isnil(L, -1)) {
				lua_pop(L, 1); /* pop nil. */
				if((type->flags & OBJ_TYPE_IMPORT) == 0) {
					/* can't resolve internal type. */
					luaL_error(L, "Unknown object type(id=%d, name=%s)", type->id, type->name);
				}
				/* try to import external type. */
				if(obj_import_external_type(L, type)) {
					/* imported type, re-try metatable check. */
					goto recheck_metatable;
				}
				/* External type not yet available, so the object can't be compatible. */
				return 0;
			}
		}
	} else if(!lua_isnoneornil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
got_check_func:
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				return (void *)lua_topointer(L, _index);
			}
		} else {
			if(type->flags & OBJ_TYPE_IMPORT) {
				/* try to import external ffi type. */
				if(obj_import_external_ffi_type(L, type)) {
					/* imported type. */
					goto got_check_func;
				}
				/* External type not yet available, so the object can't be compatible. */
			}
		}
	}
	luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	return NULL;
}

static FUNC_UNUSED void * obj_simple_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	if(lua_isnoneornil(L, _index)) {
		return NULL;
	}
	return obj_simple_udata_luacheck(L, _index, type);
}

static FUNC_UNUSED void * obj_simple_udata_luadelete(lua_State *L, int _index, obj_type *type) {
	void *obj;
	obj = obj_simple_udata_luacheck(L, _index, type);
	/* clear the metatable to invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void *obj_simple_udata_luapush(lua_State *L, void *obj, int size, obj_type *type)
{
	void *ud;
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_call(L, 1, 1);
		return obj;
	}
#endif
	/* create new userdata. */
	ud = lua_newuserdata(L, size);
	memcpy(ud, obj, size);
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	return ud;
}

/* default simple object equal method. */
static FUNC_UNUSED int obj_simple_udata_default_equal(lua_State *L) {
	void *ud1 = obj_simple_udata_toobj(L, 1);
	size_t len1 = lua_rawlen(L, 1);
	void *ud2 = obj_simple_udata_toobj(L, 2);
	size_t len2 = lua_rawlen(L, 2);

	if(len1 == len2) {
		lua_pushboolean(L, (memcmp(ud1, ud2, len1) == 0));
	} else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

/* default simple object tostring method. */
static FUNC_UNUSED int obj_simple_udata_default_tostring(lua_State *L) {
	void *ud = obj_simple_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p", ud);
	lua_concat(L, 2);

	return 1;
}

static int obj_constructor_call_wrapper(lua_State *L) {
	/* replace '__call' table with constructor function. */
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_replace(L, 1);

	/* call constructor function with all parameters after the '__call' table. */
	lua_call(L, lua_gettop(L) - 1, LUA_MULTRET);
	/* return all results from constructor. */
	return lua_gettop(L);
}

static void obj_type_register_constants(lua_State *L, const obj_const *constants, int tab_idx,
		int bidirectional) {
	/* register constants. */
	while(constants->name != NULL) {
		lua_pushstring(L, constants->name);
		switch(constants->type) {
		case CONST_BOOLEAN:
			lua_pushboolean(L, constants->num != 0.0);
			break;
		case CONST_NUMBER:
			lua_pushnumber(L, constants->num);
			break;
		case CONST_STRING:
			lua_pushstring(L, constants->str);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		/* map values back to keys. */
		if(bidirectional) {
			/* check if value already exists. */
			lua_pushvalue(L, -1);
			lua_rawget(L, tab_idx - 3);
			if(lua_isnil(L, -1)) {
				lua_pop(L, 1);
				/* add value->key mapping. */
				lua_pushvalue(L, -1);
				lua_pushvalue(L, -3);
				lua_rawset(L, tab_idx - 4);
			} else {
				/* value already exists. */
				lua_pop(L, 1);
			}
		}
		lua_rawset(L, tab_idx - 2);
		constants++;
	}
}

static void obj_type_register_package(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_Reg *reg_list = type_reg->pub_funcs;

	/* create public functions table. */
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_setfuncs(L, reg_list, 0);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	lua_pop(L, 1);  /* drop package table */
}

static void obj_type_register_meta(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_Reg *reg_list;

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_setfuncs(L, reg_list, 0);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	/* register methods. */
	luaL_setfuncs(L, type_reg->methods, 0);

	/* create metatable table. */
	lua_newtable(L);
	luaL_setfuncs(L, type_reg->metas, 0); /* fill metatable */
	/* setmetatable on meta-object. */
	lua_setmetatable(L, -2);

	lua_pop(L, 1);  /* drop meta-object */
}

static void obj_type_register(lua_State *L, const reg_sub_module *type_reg, int priv_table) {
	const luaL_Reg *reg_list;
	obj_type *type = type_reg->type;
	const obj_base *base = type_reg->bases;

	if(type_reg->req_type == REG_PACKAGE) {
		obj_type_register_package(L, type_reg);
		return;
	}
	if(type_reg->req_type == REG_META) {
		obj_type_register_meta(L, type_reg);
		return;
	}

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register "constructors" as to object's public API */
		luaL_setfuncs(L, reg_list, 0); /* fill public API table. */

		/* make public API table callable as the default constructor. */
		lua_newtable(L); /* create metatable */
		lua_pushliteral(L, "__call");
		lua_pushcfunction(L, reg_list[0].func); /* push first constructor function. */
		lua_pushcclosure(L, obj_constructor_call_wrapper, 1); /* make __call wrapper. */
		lua_rawset(L, -3);         /* metatable.__call = <default constructor> */

#if OBJ_DATA_HIDDEN_METATABLE
		lua_pushliteral(L, "__metatable");
		lua_pushboolean(L, 0);
		lua_rawset(L, -3);         /* metatable.__metatable = false */
#endif

		/* setmetatable on public API table. */
		lua_setmetatable(L, -2);

		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
	} else {
		/* register all methods as public functions. */
#if OBJ_DATA_HIDDEN_METATABLE
		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
#endif
	}

	luaL_setfuncs(L, type_reg->methods, 0); /* fill methods table. */

	luaL_newmetatable(L, type->name); /* create metatable */
	lua_pushliteral(L, ".name");
	lua_pushstring(L, type->name);
	lua_rawset(L, -3);    /* metatable['.name'] = "<object_name>" */
	lua_pushliteral(L, ".type");
	lua_pushlightuserdata(L, type);
	lua_rawset(L, -3);    /* metatable['.type'] = lightuserdata -> obj_type */
	lua_pushlightuserdata(L, type);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, LUA_REGISTRYINDEX);    /* REGISTRY[type] = metatable */

	/* add metatable to 'priv_table' */
	lua_pushstring(L, type->name);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, priv_table);    /* priv_table["<object_name>"] = metatable */

	luaL_setfuncs(L, type_reg->metas, 0); /* fill metatable */

	/* add obj_bases to metatable. */
	while(base->id >= 0) {
		lua_pushlightuserdata(L, (void *)base);
		lua_rawseti(L, -2, base->id);
		base++;
	}

	obj_type_register_constants(L, type_reg->constants, -2, type_reg->bidirectional_consts);

	obj_type_register_implements(L, type_reg->implements);

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table */
	lua_rawset(L, -3);                  /* metatable.__index = methods */
#if OBJ_DATA_HIDDEN_METATABLE
	lua_pushliteral(L, "__metatable");
	lua_pushboolean(L, 0);
	lua_rawset(L, -3);                  /* hide metatable:
	                                       metatable.__metatable = false */
#endif
	lua_pop(L, 2);                      /* drop metatable & methods */
}

static FUNC_UNUSED int lua_checktype_ref(lua_State *L, int _index, int _type) {
	luaL_checktype(L,_index,_type);
	lua_pushvalue(L,_index);
	return luaL_ref(L, LUA_REGISTRYINDEX);
}

/* use static pointer as key to weak callback_state table. */
static char obj_callback_state_weak_ref_key[] = "obj_callback_state_weak_ref_key";

static FUNC_UNUSED void *nobj_get_callback_state(lua_State *L, int owner_idx, int size) {
	void *cb_state;

	lua_pushlightuserdata(L, obj_callback_state_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		/* create weak table for callback_state */
		lua_newtable(L);               /* weak table. */
		lua_newtable(L);               /* metatable for weak table. */
		lua_pushliteral(L, "__mode");
		lua_pushliteral(L, "k");
		lua_rawset(L, -3);             /* metatable.__mode = 'k'  weak keys. */
		lua_setmetatable(L, -2);       /* add metatable to weak table. */
		lua_pushlightuserdata(L, obj_callback_state_weak_ref_key); /* key for weak table. */
		lua_pushvalue(L, -2);          /* dup weak table. */
		lua_rawset(L, LUA_REGISTRYINDEX);  /* add weak table to registry. */
	}

	/* check weak table for callback_state. */
	lua_pushvalue(L, owner_idx); /* dup. owner as lookup key. */
	lua_rawget(L, -2);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		lua_pushvalue(L, owner_idx); /* dup. owner as lookup key. */
		/* create new callback state. */
		cb_state = lua_newuserdata(L, size);
		lua_rawset(L, -3);
		lua_pop(L, 1); /* pop <weak table> */
	} else {
		/* got existing callback state. */
		cb_state = lua_touserdata(L, -1);
		lua_pop(L, 2); /* pop <weak table>, <callback_state> */
	}

	return cb_state;
}

static FUNC_UNUSED void *nobj_delete_callback_state(lua_State *L, int owner_idx) {
	void *cb_state = NULL;

	lua_pushlightuserdata(L, obj_callback_state_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil.  no weak table, so there is no callback state. */
		return NULL;
	}
	/* get callback state. */
	lua_pushvalue(L, owner_idx); /* dup. owner */
	lua_rawget(L, -2);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 2); /* pop <weak table>, nil.  No callback state for the owner. */
	} else {
		cb_state = lua_touserdata(L, -1);
		lua_pop(L, 1); /* pop <state> */
		/* remove callback state. */
		lua_pushvalue(L, owner_idx); /* dup. owner */
		lua_pushnil(L);
		lua_rawset(L, -3);
		lua_pop(L, 1); /* pop <weak table> */
	}

	return cb_state;
}



static char *obj_interfaces[] = {
  NULL,
};



#define obj_type_Type_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Type))
#define obj_type_Type_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Type))
#define obj_type_Type_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Type), flags)
#define obj_type_Type_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Type), flags)

#define obj_type_FunctionType_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_FunctionType))
#define obj_type_FunctionType_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_FunctionType))
#define obj_type_FunctionType_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_FunctionType), flags)
#define obj_type_FunctionType_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_FunctionType), flags)

#define obj_type_IntType_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_IntType))
#define obj_type_IntType_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_IntType))
#define obj_type_IntType_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_IntType), flags)
#define obj_type_IntType_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_IntType), flags)

#define obj_type_FloatType_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_FloatType))
#define obj_type_FloatType_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_FloatType))
#define obj_type_FloatType_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_FloatType), flags)
#define obj_type_FloatType_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_FloatType), flags)

#define obj_type_Module_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Module))
#define obj_type_Module_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Module))
#define obj_type_Module_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Module), flags)
#define obj_type_Module_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Module), flags)

#define obj_type_Context_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Context))
#define obj_type_Context_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Context))
#define obj_type_Context_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Context), flags)
#define obj_type_Context_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Context), flags)

#define obj_type_Value_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Value))
#define obj_type_Value_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Value))
#define obj_type_Value_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Value), flags)
#define obj_type_Value_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Value), flags)

#define obj_type_IntValue_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_IntValue))
#define obj_type_IntValue_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_IntValue))
#define obj_type_IntValue_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_IntValue), flags)
#define obj_type_IntValue_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_IntValue), flags)

#define obj_type_FloatValue_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_FloatValue))
#define obj_type_FloatValue_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_FloatValue))
#define obj_type_FloatValue_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_FloatValue), flags)
#define obj_type_FloatValue_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_FloatValue), flags)

#define obj_type_FunctionValue_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_FunctionValue))
#define obj_type_FunctionValue_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_FunctionValue))
#define obj_type_FunctionValue_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_FunctionValue), flags)
#define obj_type_FunctionValue_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_FunctionValue), flags)

#define obj_type_BasicBlock_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_BasicBlock))
#define obj_type_BasicBlock_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_BasicBlock))
#define obj_type_BasicBlock_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_BasicBlock), flags)
#define obj_type_BasicBlock_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_BasicBlock), flags)

#define obj_type_Builder_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Builder))
#define obj_type_Builder_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Builder))
#define obj_type_Builder_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Builder), flags)
#define obj_type_Builder_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Builder), flags)

#define obj_type_Opcode_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Opcode))
#define obj_type_Opcode_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Opcode))
#define obj_type_Opcode_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Opcode), flags)
#define obj_type_Opcode_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Opcode), flags)

#define obj_type_TypeKind_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_TypeKind))
#define obj_type_TypeKind_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_TypeKind))
#define obj_type_TypeKind_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_TypeKind), flags)
#define obj_type_TypeKind_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_TypeKind), flags)

#define obj_type_Linkage_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Linkage))
#define obj_type_Linkage_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Linkage))
#define obj_type_Linkage_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Linkage), flags)
#define obj_type_Linkage_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Linkage), flags)

#define obj_type_Visibility_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Visibility))
#define obj_type_Visibility_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Visibility))
#define obj_type_Visibility_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Visibility), flags)
#define obj_type_Visibility_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Visibility), flags)

#define obj_type_DLLStorageClass_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_DLLStorageClass))
#define obj_type_DLLStorageClass_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_DLLStorageClass))
#define obj_type_DLLStorageClass_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_DLLStorageClass), flags)
#define obj_type_DLLStorageClass_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_DLLStorageClass), flags)

#define obj_type_CallConv_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_CallConv))
#define obj_type_CallConv_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_CallConv))
#define obj_type_CallConv_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_CallConv), flags)
#define obj_type_CallConv_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_CallConv), flags)

#define obj_type_ValueKind_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_ValueKind))
#define obj_type_ValueKind_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_ValueKind))
#define obj_type_ValueKind_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_ValueKind), flags)
#define obj_type_ValueKind_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_ValueKind), flags)

#define obj_type_IntPredicate_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_IntPredicate))
#define obj_type_IntPredicate_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_IntPredicate))
#define obj_type_IntPredicate_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_IntPredicate), flags)
#define obj_type_IntPredicate_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_IntPredicate), flags)

#define obj_type_RealPredicate_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_RealPredicate))
#define obj_type_RealPredicate_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_RealPredicate))
#define obj_type_RealPredicate_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_RealPredicate), flags)
#define obj_type_RealPredicate_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_RealPredicate), flags)

#define obj_type_LandingPadClauseTy_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_LandingPadClauseTy))
#define obj_type_LandingPadClauseTy_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_LandingPadClauseTy))
#define obj_type_LandingPadClauseTy_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_LandingPadClauseTy), flags)
#define obj_type_LandingPadClauseTy_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_LandingPadClauseTy), flags)

#define obj_type_ThreadLocalMode_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_ThreadLocalMode))
#define obj_type_ThreadLocalMode_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_ThreadLocalMode))
#define obj_type_ThreadLocalMode_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_ThreadLocalMode), flags)
#define obj_type_ThreadLocalMode_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_ThreadLocalMode), flags)

#define obj_type_AtomicOrdering_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_AtomicOrdering))
#define obj_type_AtomicOrdering_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_AtomicOrdering))
#define obj_type_AtomicOrdering_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_AtomicOrdering), flags)
#define obj_type_AtomicOrdering_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_AtomicOrdering), flags)

#define obj_type_AtomicRMWBinOp_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_AtomicRMWBinOp))
#define obj_type_AtomicRMWBinOp_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_AtomicRMWBinOp))
#define obj_type_AtomicRMWBinOp_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_AtomicRMWBinOp), flags)
#define obj_type_AtomicRMWBinOp_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_AtomicRMWBinOp), flags)

#define obj_type_DiagnosticSeverity_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_DiagnosticSeverity))
#define obj_type_DiagnosticSeverity_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_DiagnosticSeverity))
#define obj_type_DiagnosticSeverity_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_DiagnosticSeverity), flags)
#define obj_type_DiagnosticSeverity_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_DiagnosticSeverity), flags)

#define obj_type_AttributeIndex_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_AttributeIndex))
#define obj_type_AttributeIndex_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_AttributeIndex))
#define obj_type_AttributeIndex_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_AttributeIndex), flags)
#define obj_type_AttributeIndex_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_AttributeIndex), flags)



      typedef struct LLVMOpaqueType Type;
  

      typedef Type FunctionType;
  

      typedef Type IntType;
  

      typedef Type FloatType;
  
      typedef struct LLVMOpaqueModule Module;
  
      typedef struct LLVMOpaqueContext Context;
  
      typedef struct LLVMOpaqueValue Value;
  

      typedef Value IntValue;
  

      typedef Value FloatValue;
  

      typedef Value FunctionValue;
  
      typedef struct LLVMOpaqueBasicBlock BasicBlock;
  
      typedef struct LLVMOpaqueBuilder Builder;
  
    typedef LLVMOpcode Opcode;
  
    typedef LLVMTypeKind TypeKind;
  
    typedef LLVMLinkage Linkage;
  
    typedef LLVMVisibility Visibility;
  
    typedef LLVMDLLStorageClass DLLStorageClass;
  
    typedef LLVMCallConv CallConv;
  
    typedef LLVMValueKind ValueKind;
  
    typedef LLVMIntPredicate IntPredicate;
  
    typedef LLVMRealPredicate RealPredicate;
  
    typedef LLVMLandingPadClauseTy LandingPadClauseTy;
  
    typedef LLVMThreadLocalMode ThreadLocalMode;
  
    typedef LLVMAtomicOrdering AtomicOrdering;
  
    typedef LLVMAtomicRMWBinOp AtomicRMWBinOp;
  
    typedef LLVMDiagnosticSeverity DiagnosticSeverity;
  
    typedef LLVMAttributeIndex AttributeIndex;
  


/* method: get_context */
static int Type__get_context__meth(lua_State *L) {
  Type * this1;
  Context * rc_LLVMGetTypeContext1;
  this1 = obj_type_Type_check(L,1);
  rc_LLVMGetTypeContext1 = LLVMGetTypeContext(this1);
  obj_type_Context_push(L, rc_LLVMGetTypeContext1, 0);
  return 1;
}

/* method: is_sized */
static int Type__is_sized__meth(lua_State *L) {
  Type * this1;
  bool rc_LLVMTypeIsSized1 = 0;
  this1 = obj_type_Type_check(L,1);
  rc_LLVMTypeIsSized1 = LLVMTypeIsSized(this1);
  lua_pushboolean(L, rc_LLVMTypeIsSized1);
  return 1;
}

/* method: dump */
static int Type__dump__meth(lua_State *L) {
  Type * this1;
  this1 = obj_type_Type_check(L,1);
  LLVMDumpType(this1);
  return 0;
}

/* method: void */
static int Type__void__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Type * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMVoidType();
      } else {
         this1 = LLVMVoidTypeInContext(ctx1);
      }
    
  obj_type_Type_push(L, this1, this_flags1);
  return 1;
}

/* method: label */
static int Type__label__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Type * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMLabelType();
      } else {
         this1 = LLVMLabelTypeInContext(ctx1);
      }
    
  obj_type_Type_push(L, this1, this_flags1);
  return 1;
}

/* method: x86mmx */
static int Type__x86mmx__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Type * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMX86MMXType();
      } else {
         this1 = LLVMX86MMXTypeInContext(ctx1);
      }
    
  obj_type_Type_push(L, this1, this_flags1);
  return 1;
}

/* method: new */
static int FunctionType__new__meth(lua_State *L) {
  Type * return_type1;
  bool var_arg3;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FunctionType * this1;
  return_type1 = obj_type_Type_check(L,1);
  var_arg3 = lua_toboolean(L,3);
      size_t n;
      Type ** arr;

      n = lua_rawlen(L, 2);
      arr = calloc(n, sizeof(Type *));

      for (int i=1; i<=n; i++) {
        lua_rawgeti(L, 2, i);
        arr[i-1] = obj_type_Type_check(L, -1);
        lua_pop(L, 1);
      }

      this1 = LLVMFunctionType(return_type1, arr, n, var_arg3);

      free(arr);
    
  obj_type_FunctionType_push(L, this1, this_flags1);
  return 1;
}

/* method: is_vararg */
static int FunctionType__is_vararg__meth(lua_State *L) {
  FunctionType * this1;
  bool rc_LLVMIsFunctionVarArg1 = 0;
  this1 = obj_type_FunctionType_check(L,1);
  rc_LLVMIsFunctionVarArg1 = LLVMIsFunctionVarArg(this1);
  lua_pushboolean(L, rc_LLVMIsFunctionVarArg1);
  return 1;
}

/* method: return_type */
static int FunctionType__return_type__meth(lua_State *L) {
  FunctionType * this1;
  Type * rc_LLVMGetReturnType1;
  this1 = obj_type_FunctionType_check(L,1);
  rc_LLVMGetReturnType1 = LLVMGetReturnType(this1);
  obj_type_Type_push(L, rc_LLVMGetReturnType1, 0);
  return 1;
}

/* method: count_param_types */
static int FunctionType__count_param_types__meth(lua_State *L) {
  FunctionType * this1;
  unsigned rc_LLVMCountParamTypes1 = 0;
  this1 = obj_type_FunctionType_check(L,1);
  rc_LLVMCountParamTypes1 = LLVMCountParamTypes(this1);
  lua_pushinteger(L, rc_LLVMCountParamTypes1);
  return 1;
}

/* method: param_types */
static int FunctionType__param_types__meth(lua_State *L) {
  FunctionType * this1;
  this1 = obj_type_FunctionType_check(L,1);
      size_t n = LLVMCountParamTypes(this1);
      Type ** arr = calloc(n, sizeof(Type *));

      lua_createtable(L, n, 0);

      LLVMGetParamTypes(this1, arr);

      for (int i=0; i<n; i++) {
        Type * ty = arr[i];
        obj_type_FunctionType_push(L, ty, 0);
        lua_rawseti(L, -2, i+1);
      }

      free(arr);
    
  return 1;
}

/* method: int1 */
static int IntType__int1__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMInt1Type();
      } else {
         this1 = LLVMInt1TypeInContext(ctx1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: int8 */
static int IntType__int8__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMInt8Type();
      } else {
         this1 = LLVMInt8TypeInContext(ctx1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: int16 */
static int IntType__int16__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMInt16Type();
      } else {
         this1 = LLVMInt16TypeInContext(ctx1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: int32 */
static int IntType__int32__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMInt32Type();
      } else {
         this1 = LLVMInt32TypeInContext(ctx1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: int64 */
static int IntType__int64__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMInt64Type();
      } else {
         this1 = LLVMInt64TypeInContext(ctx1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: int128 */
static int IntType__int128__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMInt128Type();
      } else {
         this1 = LLVMInt128TypeInContext(ctx1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: int */
static int IntType__int__meth(lua_State *L) {
  unsigned bits1;
  Context * ctx2;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntType * this1;
  bits1 = luaL_checkinteger(L,1);
  ctx2 = obj_type_Context_optional(L,2);
      if (ctx2 == NULL) {
         this1 = LLVMIntType(bits1);
      } else {
         this1 = LLVMIntTypeInContext(ctx2, bits1);
      }
    
  obj_type_IntType_push(L, this1, this_flags1);
  return 1;
}

/* method: get_int_width */
static int IntType__get_int_width__meth(lua_State *L) {
  IntType * this1;
  unsigned rc_LLVMGetIntTypeWidth1 = 0;
  this1 = obj_type_IntType_check(L,1);
  rc_LLVMGetIntTypeWidth1 = LLVMGetIntTypeWidth(this1);
  lua_pushinteger(L, rc_LLVMGetIntTypeWidth1);
  return 1;
}

/* method: half */
static int FloatType__half__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMHalfType();
      } else {
         this1 = LLVMHalfTypeInContext(ctx1);
      }
    
  obj_type_FloatType_push(L, this1, this_flags1);
  return 1;
}

/* method: float */
static int FloatType__float__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMFloatType();
      } else {
         this1 = LLVMFloatTypeInContext(ctx1);
      }
    
  obj_type_FloatType_push(L, this1, this_flags1);
  return 1;
}

/* method: double */
static int FloatType__double__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMDoubleType();
      } else {
         this1 = LLVMDoubleTypeInContext(ctx1);
      }
    
  obj_type_FloatType_push(L, this1, this_flags1);
  return 1;
}

/* method: x86fp80 */
static int FloatType__x86fp80__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMX86FP80Type();
      } else {
         this1 = LLVMX86FP80TypeInContext(ctx1);
      }
    
  obj_type_FloatType_push(L, this1, this_flags1);
  return 1;
}

/* method: fp128 */
static int FloatType__fp128__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMFP128Type();
      } else {
         this1 = LLVMFP128TypeInContext(ctx1);
      }
    
  obj_type_FloatType_push(L, this1, this_flags1);
  return 1;
}

/* method: ppcfp128 */
static int FloatType__ppcfp128__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatType * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMPPCFP128Type();
      } else {
         this1 = LLVMPPCFP128TypeInContext(ctx1);
      }
    
  obj_type_FloatType_push(L, this1, this_flags1);
  return 1;
}

/* method: create */
static int Module__create__meth(lua_State *L) {
  size_t identifier_len1;
  const char * identifier1;
  Context * ctx2;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Module * this1;
  identifier1 = luaL_checklstring(L,1,&(identifier_len1));
  ctx2 = obj_type_Context_optional(L,2);
      if (ctx2 == NULL) {
         this1 = LLVMModuleCreateWithName(identifier1);
      } else {
         this1 = LLVMModuleCreateWithNameInContext(identifier1, ctx2);
      }
    
  obj_type_Module_push(L, this1, this_flags1);
  return 1;
}

/* method: clone */
static int Module__clone__meth(lua_State *L) {
  Module * this1;
  Module * rc_LLVMCloneModule1;
  this1 = obj_type_Module_check(L,1);
  rc_LLVMCloneModule1 = LLVMCloneModule(this1);
  obj_type_Module_push(L, rc_LLVMCloneModule1, 0);
  return 1;
}

/* method: identifier */
static int Module__identifier__meth(lua_State *L) {
  Module * this1;
  const char * str1 = NULL;
  this1 = obj_type_Module_check(L,1);
      size_t sz;
      str1 = LLVMGetModuleIdentifier(this1, &sz);
    
  lua_pushstring(L, str1);
  return 1;
}

/* method: set_identifier */
static int Module__set_identifier__meth(lua_State *L) {
  Module * this1;
  size_t str_len2;
  const char * str2;
  this1 = obj_type_Module_check(L,1);
  str2 = luaL_checklstring(L,2,&(str_len2));
  LLVMSetModuleIdentifier(this1, str2, str_len2);
  return 0;
}

/* method: dump */
static int Module__dump__meth(lua_State *L) {
  Module * this1;
  this1 = obj_type_Module_check(L,1);
  LLVMDumpModule(this1);
  return 0;
}

/* method: target */
static int Module__target__meth(lua_State *L) {
  Module * this1;
  const char * rc_LLVMGetTarget1 = NULL;
  this1 = obj_type_Module_check(L,1);
  rc_LLVMGetTarget1 = LLVMGetTarget(this1);
  lua_pushstring(L, rc_LLVMGetTarget1);
  return 1;
}

/* method: set_target */
static int Module__set_target__meth(lua_State *L) {
  Module * this1;
  size_t target_triplet_len2;
  const char * target_triplet2;
  this1 = obj_type_Module_check(L,1);
  target_triplet2 = luaL_checklstring(L,2,&(target_triplet_len2));
  LLVMSetTarget(this1, target_triplet2);
  return 0;
}

/* method: add_function */
static int Module__add_function__meth(lua_State *L) {
  Module * this1;
  size_t name_len2;
  const char * name2;
  FunctionType * function_type3;
  FunctionValue * rc_LLVMAddFunction1;
  this1 = obj_type_Module_check(L,1);
  name2 = luaL_checklstring(L,2,&(name_len2));
  function_type3 = obj_type_FunctionType_check(L,3);
  rc_LLVMAddFunction1 = LLVMAddFunction(this1, name2, function_type3);
  obj_type_FunctionValue_push(L, rc_LLVMAddFunction1, 0);
  return 1;
}

/* method: get_function */
static int Module__get_function__meth(lua_State *L) {
  Module * this1;
  size_t name_len2;
  const char * name2;
  Value * rc_LLVMGetNamedFunction1;
  this1 = obj_type_Module_check(L,1);
  name2 = luaL_checklstring(L,2,&(name_len2));
  rc_LLVMGetNamedFunction1 = LLVMGetNamedFunction(this1, name2);
  obj_type_Value_push(L, rc_LLVMGetNamedFunction1, 0);
  return 1;
}

/* method: dispose */
static int Module__dispose__meth(lua_State *L) {
  int this_flags1 = 0;
  Module * this1;
  this1 = obj_type_Module_delete(L,1,&(this_flags1));
  if(!(this_flags1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  LLVMDisposeModule(this1);
  return 0;
}

/* method: create */
static int Context__create__meth(lua_State *L) {
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Context * this1;
  this1 = LLVMContextCreate();
  obj_type_Context_push(L, this1, this_flags1);
  return 1;
}

/* method: global_context */
static int Context__global_context__meth(lua_State *L) {
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Context * this1;
      this1 = LLVMGetGlobalContext();
      this_flags1 = 0;
    
  obj_type_Context_push(L, this1, this_flags1);
  return 1;
}

/* method: dispose */
static int Context__dispose__meth(lua_State *L) {
  int this_flags1 = 0;
  Context * this1;
  this1 = obj_type_Context_delete(L,1,&(this_flags1));
  if(!(this_flags1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  LLVMContextDispose(this1);
  return 0;
}

/* method: name */
static int Value__name__meth(lua_State *L) {
  Value * this1;
  const char * rc_LLVMGetValueName1 = NULL;
  this1 = obj_type_Value_check(L,1);
  rc_LLVMGetValueName1 = LLVMGetValueName(this1);
  lua_pushstring(L, rc_LLVMGetValueName1);
  return 1;
}

/* method: set_name */
static int Value__set_name__meth(lua_State *L) {
  Value * this1;
  size_t str_len2;
  const char * str2;
  this1 = obj_type_Value_check(L,1);
  str2 = luaL_checklstring(L,2,&(str_len2));
      LLVMSetValueName(this1, str2);
    
  return 0;
}

/* method: dump */
static int Value__dump__meth(lua_State *L) {
  Value * this1;
  this1 = obj_type_Value_check(L,1);
  LLVMDumpValue(this1);
  return 0;
}

/* method: is_constant */
static int Value__is_constant__meth(lua_State *L) {
  Value * this1;
  bool rc_LLVMIsConstant1 = 0;
  this1 = obj_type_Value_check(L,1);
  rc_LLVMIsConstant1 = LLVMIsConstant(this1);
  lua_pushboolean(L, rc_LLVMIsConstant1);
  return 1;
}

/* method: is_undef */
static int Value__is_undef__meth(lua_State *L) {
  Value * this1;
  bool rc_LLVMIsUndef1 = 0;
  this1 = obj_type_Value_check(L,1);
  rc_LLVMIsUndef1 = LLVMIsUndef(this1);
  lua_pushboolean(L, rc_LLVMIsUndef1);
  return 1;
}

/* method: is_null */
static int Value__is_null__meth(lua_State *L) {
  Value * this1;
  bool rc_LLVMIsNull1 = 0;
  this1 = obj_type_Value_check(L,1);
  rc_LLVMIsNull1 = LLVMIsNull(this1);
  lua_pushboolean(L, rc_LLVMIsNull1);
  return 1;
}

/* method: const */
static int IntValue__const__meth(lua_State *L) {
  IntType * ty1;
  uint64_t n2;
  bool sign_extend3;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntValue * this1;
  ty1 = obj_type_IntType_check(L,1);
  n2 = luaL_checkinteger(L,2);
  sign_extend3 = lua_toboolean(L,3);
  this1 = LLVMConstInt(ty1, n2, sign_extend3);
  obj_type_IntValue_push(L, this1, this_flags1);
  return 1;
}

/* method: const_of_string */
static int IntValue__const_of_string__meth(lua_State *L) {
  IntType * ty1;
  size_t str_len2;
  const char * str2;
  uint8_t radix3;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  IntValue * this1;
  ty1 = obj_type_IntType_check(L,1);
  str2 = luaL_checklstring(L,2,&(str_len2));
  radix3 = luaL_checkinteger(L,3);
  this1 = LLVMConstIntOfStringAndSize(ty1, str2, str_len2, radix3);
  obj_type_IntValue_push(L, this1, this_flags1);
  return 1;
}

/* method: zext */
static int IntValue__zext__meth(lua_State *L) {
  IntValue * this1;
  uint64_t rc_LLVMConstIntGetZExtValue1 = 0;
  this1 = obj_type_IntValue_check(L,1);
  rc_LLVMConstIntGetZExtValue1 = LLVMConstIntGetZExtValue(this1);
  lua_pushinteger(L, rc_LLVMConstIntGetZExtValue1);
  return 1;
}

/* method: sext */
static int IntValue__sext__meth(lua_State *L) {
  IntValue * this1;
  int64_t rc_LLVMConstIntGetSExtValue1 = 0;
  this1 = obj_type_IntValue_check(L,1);
  rc_LLVMConstIntGetSExtValue1 = LLVMConstIntGetSExtValue(this1);
  lua_pushinteger(L, rc_LLVMConstIntGetSExtValue1);
  return 1;
}

/* method: const */
static int FloatValue__const__meth(lua_State *L) {
  FloatType * ty1;
  double n2;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatValue * this1;
  ty1 = obj_type_FloatType_check(L,1);
  n2 = luaL_checknumber(L,2);
  this1 = LLVMConstReal(ty1, n2);
  obj_type_FloatValue_push(L, this1, this_flags1);
  return 1;
}

/* method: const_of_string */
static int FloatValue__const_of_string__meth(lua_State *L) {
  FloatType * ty1;
  size_t str_len2;
  const char * str2;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  FloatValue * this1;
  IntValue * rc_LLVMConstRealOfStringAndSize2;
  ty1 = obj_type_FloatType_check(L,1);
  str2 = luaL_checklstring(L,2,&(str_len2));
  rc_LLVMConstRealOfStringAndSize2 = LLVMConstRealOfStringAndSize(ty1, str2, str_len2);
  obj_type_FloatValue_push(L, this1, this_flags1);
  obj_type_IntValue_push(L, rc_LLVMConstRealOfStringAndSize2, 0);
  return 2;
}

/* method: value */
static int FloatValue__value__meth(lua_State *L) {
  FloatValue * this1;
  this1 = obj_type_FloatValue_check(L,1);
  return 0;
}

/* method: append */
static int BasicBlock__append__meth(lua_State *L) {
  FunctionValue * fn1;
  size_t name_len2;
  const char * name2;
  Context * ctx3;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  BasicBlock * this1;
  fn1 = obj_type_FunctionValue_check(L,1);
  name2 = luaL_checklstring(L,2,&(name_len2));
  ctx3 = obj_type_Context_optional(L,3);
      if (ctx3 == NULL) {
         this1 = LLVMAppendBasicBlock(fn1, name2);
      } else {
         this1 = LLVMAppendBasicBlockInContext(ctx3, fn1, name2);
      }
    
  obj_type_BasicBlock_push(L, this1, this_flags1);
  return 1;
}

/* method: name */
static int BasicBlock__name__meth(lua_State *L) {
  BasicBlock * this1;
  const char * rc_LLVMGetBasicBlockName1 = NULL;
  this1 = obj_type_BasicBlock_check(L,1);
  rc_LLVMGetBasicBlockName1 = LLVMGetBasicBlockName(this1);
  lua_pushstring(L, rc_LLVMGetBasicBlockName1);
  return 1;
}

/* method: create */
static int Builder__create__meth(lua_State *L) {
  Context * ctx1;
  int this_flags1 = OBJ_UDATA_FLAG_OWN;
  Builder * this1;
  ctx1 = obj_type_Context_optional(L,1);
      if (ctx1 == NULL) {
         this1 = LLVMCreateBuilder();
      } else {
         this1 = LLVMCreateBuilderInContext(ctx1);
      }
    
  obj_type_Builder_push(L, this1, this_flags1);
  return 1;
}

/* method: dispose */
static int Builder__dispose__meth(lua_State *L) {
  int this_flags1 = 0;
  Builder * this1;
  this1 = obj_type_Builder_delete(L,1,&(this_flags1));
  if(!(this_flags1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  LLVMDisposeBuilder(this1);
  return 0;
}

/* method: position_at_end */
static int Builder__position_at_end__meth(lua_State *L) {
  Builder * this1;
  BasicBlock * bb2;
  this1 = obj_type_Builder_check(L,1);
  bb2 = obj_type_BasicBlock_check(L,2);
  LLVMPositionBuilderAtEnd(this1, bb2);
  return 0;
}

/* method: build_ret */
static int Builder__build_ret__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rc_LLVMBuildRet1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rc_LLVMBuildRet1 = LLVMBuildRet(this1, lhs2);
  obj_type_Value_push(L, rc_LLVMBuildRet1, 0);
  return 1;
}

/* method: build_ret_void */
static int Builder__build_ret_void__meth(lua_State *L) {
  Builder * this1;
  Value * rc_LLVMBuildRetVoid1;
  this1 = obj_type_Builder_check(L,1);
  rc_LLVMBuildRetVoid1 = LLVMBuildRetVoid(this1);
  obj_type_Value_push(L, rc_LLVMBuildRetVoid1, 0);
  return 1;
}

/* method: build_add */
static int Builder__build_add__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildAdd1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildAdd1 = LLVMBuildAdd(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildAdd1, 0);
  return 1;
}

/* method: build_nswadd */
static int Builder__build_nswadd__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildNSWAdd1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildNSWAdd1 = LLVMBuildNSWAdd(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildNSWAdd1, 0);
  return 1;
}

/* method: build_nuwadd */
static int Builder__build_nuwadd__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildNUWAdd1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildNUWAdd1 = LLVMBuildNUWAdd(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildNUWAdd1, 0);
  return 1;
}

/* method: build_fadd */
static int Builder__build_fadd__meth(lua_State *L) {
  Builder * this1;
  FloatValue * lhs2;
  FloatValue * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildFAdd1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_FloatValue_check(L,2);
  rhs3 = obj_type_FloatValue_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFAdd1 = LLVMBuildFAdd(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildFAdd1, 0);
  return 1;
}

/* method: build_sub */
static int Builder__build_sub__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildSub1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildSub1 = LLVMBuildSub(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildSub1, 0);
  return 1;
}

/* method: build_nswsub */
static int Builder__build_nswsub__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildNSWSub1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildNSWSub1 = LLVMBuildNSWSub(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildNSWSub1, 0);
  return 1;
}

/* method: build_nuwsub */
static int Builder__build_nuwsub__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildNUWSub1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildNUWSub1 = LLVMBuildNUWSub(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildNUWSub1, 0);
  return 1;
}

/* method: build_fsub */
static int Builder__build_fsub__meth(lua_State *L) {
  Builder * this1;
  FloatValue * lhs2;
  FloatValue * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildFSub1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_FloatValue_check(L,2);
  rhs3 = obj_type_FloatValue_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFSub1 = LLVMBuildFSub(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildFSub1, 0);
  return 1;
}

/* method: build_mul */
static int Builder__build_mul__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildMul1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildMul1 = LLVMBuildMul(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildMul1, 0);
  return 1;
}

/* method: build_nswmul */
static int Builder__build_nswmul__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildNSWMul1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildNSWMul1 = LLVMBuildNSWMul(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildNSWMul1, 0);
  return 1;
}

/* method: build_nuwmul */
static int Builder__build_nuwmul__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildNUWMul1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildNUWMul1 = LLVMBuildNUWMul(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildNUWMul1, 0);
  return 1;
}

/* method: build_fmul */
static int Builder__build_fmul__meth(lua_State *L) {
  Builder * this1;
  FloatValue * lhs2;
  FloatValue * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildFMul1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_FloatValue_check(L,2);
  rhs3 = obj_type_FloatValue_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFMul1 = LLVMBuildFMul(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildFMul1, 0);
  return 1;
}

/* method: build_udiv */
static int Builder__build_udiv__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildUDiv1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildUDiv1 = LLVMBuildUDiv(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildUDiv1, 0);
  return 1;
}

/* method: build_exact_udiv */
static int Builder__build_exact_udiv__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildExactUDiv1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildExactUDiv1 = LLVMBuildExactUDiv(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildExactUDiv1, 0);
  return 1;
}

/* method: build_sdiv */
static int Builder__build_sdiv__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildSDiv1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildSDiv1 = LLVMBuildSDiv(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildSDiv1, 0);
  return 1;
}

/* method: build_exact_sdiv */
static int Builder__build_exact_sdiv__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildExactSDiv1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildExactSDiv1 = LLVMBuildExactSDiv(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildExactSDiv1, 0);
  return 1;
}

/* method: build_fdiv */
static int Builder__build_fdiv__meth(lua_State *L) {
  Builder * this1;
  FloatValue * lhs2;
  FloatValue * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildFDiv1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_FloatValue_check(L,2);
  rhs3 = obj_type_FloatValue_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFDiv1 = LLVMBuildFDiv(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildFDiv1, 0);
  return 1;
}

/* method: build_urem */
static int Builder__build_urem__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildURem1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildURem1 = LLVMBuildURem(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildURem1, 0);
  return 1;
}

/* method: build_srem */
static int Builder__build_srem__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildSRem1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildSRem1 = LLVMBuildSRem(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildSRem1, 0);
  return 1;
}

/* method: build_frem */
static int Builder__build_frem__meth(lua_State *L) {
  Builder * this1;
  FloatValue * lhs2;
  FloatValue * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildFRem1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_FloatValue_check(L,2);
  rhs3 = obj_type_FloatValue_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFRem1 = LLVMBuildFRem(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildFRem1, 0);
  return 1;
}

/* method: build_shl */
static int Builder__build_shl__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildShl1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildShl1 = LLVMBuildShl(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildShl1, 0);
  return 1;
}

/* method: build_lshr */
static int Builder__build_lshr__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildLShr1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildLShr1 = LLVMBuildLShr(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildLShr1, 0);
  return 1;
}

/* method: build_ashr */
static int Builder__build_ashr__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildAShr1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildAShr1 = LLVMBuildAShr(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildAShr1, 0);
  return 1;
}

/* method: build_and */
static int Builder__build_and__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildAnd1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildAnd1 = LLVMBuildAnd(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildAnd1, 0);
  return 1;
}

/* method: build_or */
static int Builder__build_or__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildOr1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildOr1 = LLVMBuildOr(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildOr1, 0);
  return 1;
}

/* method: build_xor */
static int Builder__build_xor__meth(lua_State *L) {
  Builder * this1;
  Value * lhs2;
  Value * rhs3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildXor1;
  this1 = obj_type_Builder_check(L,1);
  lhs2 = obj_type_Value_check(L,2);
  rhs3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildXor1 = LLVMBuildXor(this1, lhs2, rhs3, name4);
  obj_type_Value_push(L, rc_LLVMBuildXor1, 0);
  return 1;
}

/* method: build_neg */
static int Builder__build_neg__meth(lua_State *L) {
  Builder * this1;
  Value * v2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildNeg1;
  this1 = obj_type_Builder_check(L,1);
  v2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildNeg1 = LLVMBuildNeg(this1, v2, name3);
  obj_type_Value_push(L, rc_LLVMBuildNeg1, 0);
  return 1;
}

/* method: build_nswneg */
static int Builder__build_nswneg__meth(lua_State *L) {
  Builder * this1;
  Value * v2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildNSWNeg1;
  this1 = obj_type_Builder_check(L,1);
  v2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildNSWNeg1 = LLVMBuildNSWNeg(this1, v2, name3);
  obj_type_Value_push(L, rc_LLVMBuildNSWNeg1, 0);
  return 1;
}

/* method: build_nuwneg */
static int Builder__build_nuwneg__meth(lua_State *L) {
  Builder * this1;
  Value * v2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildNUWNeg1;
  this1 = obj_type_Builder_check(L,1);
  v2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildNUWNeg1 = LLVMBuildNUWNeg(this1, v2, name3);
  obj_type_Value_push(L, rc_LLVMBuildNUWNeg1, 0);
  return 1;
}

/* method: build_fneg */
static int Builder__build_fneg__meth(lua_State *L) {
  Builder * this1;
  FloatValue * v2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildFNeg1;
  this1 = obj_type_Builder_check(L,1);
  v2 = obj_type_FloatValue_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildFNeg1 = LLVMBuildFNeg(this1, v2, name3);
  obj_type_Value_push(L, rc_LLVMBuildFNeg1, 0);
  return 1;
}

/* method: build_not */
static int Builder__build_not__meth(lua_State *L) {
  Builder * this1;
  Value * v2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildNot1;
  this1 = obj_type_Builder_check(L,1);
  v2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildNot1 = LLVMBuildNot(this1, v2, name3);
  obj_type_Value_push(L, rc_LLVMBuildNot1, 0);
  return 1;
}

/* method: build_malloc */
static int Builder__build_malloc__meth(lua_State *L) {
  Builder * this1;
  Type * Tv2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildMalloc1;
  this1 = obj_type_Builder_check(L,1);
  Tv2 = obj_type_Type_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildMalloc1 = LLVMBuildMalloc(this1, Tv2, name3);
  obj_type_Value_push(L, rc_LLVMBuildMalloc1, 0);
  return 1;
}

/* method: build_array_malloc */
static int Builder__build_array_malloc__meth(lua_State *L) {
  Builder * this1;
  Type * ty2;
  Value * val3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildArrayMalloc1;
  this1 = obj_type_Builder_check(L,1);
  ty2 = obj_type_Type_check(L,2);
  val3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildArrayMalloc1 = LLVMBuildArrayMalloc(this1, ty2, val3, name4);
  obj_type_Value_push(L, rc_LLVMBuildArrayMalloc1, 0);
  return 1;
}

/* method: build_alloca */
static int Builder__build_alloca__meth(lua_State *L) {
  Builder * this1;
  Type * ty2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildAlloca1;
  this1 = obj_type_Builder_check(L,1);
  ty2 = obj_type_Type_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildAlloca1 = LLVMBuildAlloca(this1, ty2, name3);
  obj_type_Value_push(L, rc_LLVMBuildAlloca1, 0);
  return 1;
}

/* method: build_array_alloca */
static int Builder__build_array_alloca__meth(lua_State *L) {
  Builder * this1;
  Type * ty2;
  Value * val3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildArrayAlloca1;
  this1 = obj_type_Builder_check(L,1);
  ty2 = obj_type_Type_check(L,2);
  val3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildArrayAlloca1 = LLVMBuildArrayAlloca(this1, ty2, val3, name4);
  obj_type_Value_push(L, rc_LLVMBuildArrayAlloca1, 0);
  return 1;
}

/* method: build_free */
static int Builder__build_free__meth(lua_State *L) {
  Builder * this1;
  Value * ptr2;
  Value * rc_LLVMBuildFree1;
  this1 = obj_type_Builder_check(L,1);
  ptr2 = obj_type_Value_check(L,2);
  rc_LLVMBuildFree1 = LLVMBuildFree(this1, ptr2);
  obj_type_Value_push(L, rc_LLVMBuildFree1, 0);
  return 1;
}

/* method: build_load */
static int Builder__build_load__meth(lua_State *L) {
  Builder * this1;
  Value * ptr2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildLoad1;
  this1 = obj_type_Builder_check(L,1);
  ptr2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildLoad1 = LLVMBuildLoad(this1, ptr2, name3);
  obj_type_Value_push(L, rc_LLVMBuildLoad1, 0);
  return 1;
}

/* method: build_store */
static int Builder__build_store__meth(lua_State *L) {
  Builder * this1;
  Value * val2;
  Value * ptr3;
  Value * rc_LLVMBuildStore1;
  this1 = obj_type_Builder_check(L,1);
  val2 = obj_type_Value_check(L,2);
  ptr3 = obj_type_Value_check(L,3);
  rc_LLVMBuildStore1 = LLVMBuildStore(this1, val2, ptr3);
  obj_type_Value_push(L, rc_LLVMBuildStore1, 0);
  return 1;
}

/* method: build_Struct_GEP */
static int Builder__build_Struct_GEP__meth(lua_State *L) {
  Builder * this1;
  Value * ptr2;
  unsigned Idx3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildStructGEP1;
  this1 = obj_type_Builder_check(L,1);
  ptr2 = obj_type_Value_check(L,2);
  Idx3 = luaL_checkinteger(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildStructGEP1 = LLVMBuildStructGEP(this1, ptr2, Idx3, name4);
  obj_type_Value_push(L, rc_LLVMBuildStructGEP1, 0);
  return 1;
}

/* method: build_global_string */
static int Builder__build_global_string__meth(lua_State *L) {
  Builder * this1;
  size_t Str_len2;
  const char * Str2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildGlobalString1;
  this1 = obj_type_Builder_check(L,1);
  Str2 = luaL_checklstring(L,2,&(Str_len2));
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildGlobalString1 = LLVMBuildGlobalString(this1, Str2, name3);
  obj_type_Value_push(L, rc_LLVMBuildGlobalString1, 0);
  return 1;
}

/* method: build_global_string_ptr */
static int Builder__build_global_string_ptr__meth(lua_State *L) {
  Builder * this1;
  size_t Str_len2;
  const char * Str2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildGlobalStringPtr1;
  this1 = obj_type_Builder_check(L,1);
  Str2 = luaL_checklstring(L,2,&(Str_len2));
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildGlobalStringPtr1 = LLVMBuildGlobalStringPtr(this1, Str2, name3);
  obj_type_Value_push(L, rc_LLVMBuildGlobalStringPtr1, 0);
  return 1;
}

/* method: build_trunc */
static int Builder__build_trunc__meth(lua_State *L) {
  Builder * this1;
  IntValue * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildTrunc1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_IntValue_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildTrunc1 = LLVMBuildTrunc(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildTrunc1, 0);
  return 1;
}

/* method: build_zext */
static int Builder__build_zext__meth(lua_State *L) {
  Builder * this1;
  IntValue * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildZExt1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_IntValue_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildZExt1 = LLVMBuildZExt(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildZExt1, 0);
  return 1;
}

/* method: build_sext */
static int Builder__build_sext__meth(lua_State *L) {
  Builder * this1;
  IntValue * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildSExt1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_IntValue_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildSExt1 = LLVMBuildSExt(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildSExt1, 0);
  return 1;
}

/* method: build_fp_to_ui */
static int Builder__build_fp_to_ui__meth(lua_State *L) {
  Builder * this1;
  FloatValue * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildFPToUI1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_FloatValue_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFPToUI1 = LLVMBuildFPToUI(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildFPToUI1, 0);
  return 1;
}

/* method: build_fp_to_si */
static int Builder__build_fp_to_si__meth(lua_State *L) {
  Builder * this1;
  FloatValue * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildFPToSI1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_FloatValue_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFPToSI1 = LLVMBuildFPToSI(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildFPToSI1, 0);
  return 1;
}

/* method: build_ui_to_fp */
static int Builder__build_ui_to_fp__meth(lua_State *L) {
  Builder * this1;
  FloatValue * Val2;
  FloatType * DestTy3;
  size_t name_len4;
  const char * name4;
  FloatValue * rc_LLVMBuildUIToFP1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_FloatValue_check(L,2);
  DestTy3 = obj_type_FloatType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildUIToFP1 = LLVMBuildUIToFP(this1, Val2, DestTy3, name4);
  obj_type_FloatValue_push(L, rc_LLVMBuildUIToFP1, 0);
  return 1;
}

/* method: build_si_to_fp */
static int Builder__build_si_to_fp__meth(lua_State *L) {
  Builder * this1;
  IntValue * Val2;
  FloatType * DestTy3;
  size_t name_len4;
  const char * name4;
  FloatValue * rc_LLVMBuildSIToFP1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_IntValue_check(L,2);
  DestTy3 = obj_type_FloatType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildSIToFP1 = LLVMBuildSIToFP(this1, Val2, DestTy3, name4);
  obj_type_FloatValue_push(L, rc_LLVMBuildSIToFP1, 0);
  return 1;
}

/* method: build_fptrunc */
static int Builder__build_fptrunc__meth(lua_State *L) {
  Builder * this1;
  FloatValue * Val2;
  FloatType * DestTy3;
  size_t name_len4;
  const char * name4;
  FloatValue * rc_LLVMBuildFPTrunc1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_FloatValue_check(L,2);
  DestTy3 = obj_type_FloatType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFPTrunc1 = LLVMBuildFPTrunc(this1, Val2, DestTy3, name4);
  obj_type_FloatValue_push(L, rc_LLVMBuildFPTrunc1, 0);
  return 1;
}

/* method: build_fpext */
static int Builder__build_fpext__meth(lua_State *L) {
  Builder * this1;
  FloatValue * Val2;
  FloatType * DestTy3;
  size_t name_len4;
  const char * name4;
  FloatValue * rc_LLVMBuildFPExt1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_FloatValue_check(L,2);
  DestTy3 = obj_type_FloatType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFPExt1 = LLVMBuildFPExt(this1, Val2, DestTy3, name4);
  obj_type_FloatValue_push(L, rc_LLVMBuildFPExt1, 0);
  return 1;
}

/* method: build_ptr_to_int */
static int Builder__build_ptr_to_int__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildPtrToInt1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildPtrToInt1 = LLVMBuildPtrToInt(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildPtrToInt1, 0);
  return 1;
}

/* method: build_int_to_ptr */
static int Builder__build_int_to_ptr__meth(lua_State *L) {
  Builder * this1;
  IntValue * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildIntToPtr1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_IntValue_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildIntToPtr1 = LLVMBuildIntToPtr(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildIntToPtr1, 0);
  return 1;
}

/* method: build_bit_cast */
static int Builder__build_bit_cast__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildBitCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildBitCast1 = LLVMBuildBitCast(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildBitCast1, 0);
  return 1;
}

/* method: build_addr_space_cast */
static int Builder__build_addr_space_cast__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildAddrSpaceCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildAddrSpaceCast1 = LLVMBuildAddrSpaceCast(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildAddrSpaceCast1, 0);
  return 1;
}

/* method: build_zext_or_bit_cast */
static int Builder__build_zext_or_bit_cast__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildZExtOrBitCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildZExtOrBitCast1 = LLVMBuildZExtOrBitCast(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildZExtOrBitCast1, 0);
  return 1;
}

/* method: build_sext_or_bit_cast */
static int Builder__build_sext_or_bit_cast__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildSExtOrBitCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildSExtOrBitCast1 = LLVMBuildSExtOrBitCast(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildSExtOrBitCast1, 0);
  return 1;
}

/* method: build_trunc_or_bit_cast */
static int Builder__build_trunc_or_bit_cast__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildTruncOrBitCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildTruncOrBitCast1 = LLVMBuildTruncOrBitCast(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildTruncOrBitCast1, 0);
  return 1;
}

/* method: build_ptr_cast */
static int Builder__build_ptr_cast__meth(lua_State *L) {
  Builder * this1;
  Value * Val2;
  Type * DestTy3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildPointerCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_Value_check(L,2);
  DestTy3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildPointerCast1 = LLVMBuildPointerCast(this1, Val2, DestTy3, name4);
  obj_type_Value_push(L, rc_LLVMBuildPointerCast1, 0);
  return 1;
}

/* method: build_int_cast */
static int Builder__build_int_cast__meth(lua_State *L) {
  Builder * this1;
  IntValue * Val2;
  IntType * DestTy3;
  size_t name_len4;
  const char * name4;
  IntValue * rc_LLVMBuildIntCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_IntValue_check(L,2);
  DestTy3 = obj_type_IntType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildIntCast1 = LLVMBuildIntCast(this1, Val2, DestTy3, name4);
  obj_type_IntValue_push(L, rc_LLVMBuildIntCast1, 0);
  return 1;
}

/* method: build_fpcast */
static int Builder__build_fpcast__meth(lua_State *L) {
  Builder * this1;
  FloatValue * Val2;
  FloatType * DestTy3;
  size_t name_len4;
  const char * name4;
  FloatValue * rc_LLVMBuildFPCast1;
  this1 = obj_type_Builder_check(L,1);
  Val2 = obj_type_FloatValue_check(L,2);
  DestTy3 = obj_type_FloatType_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildFPCast1 = LLVMBuildFPCast(this1, Val2, DestTy3, name4);
  obj_type_FloatValue_push(L, rc_LLVMBuildFPCast1, 0);
  return 1;
}

/* method: build_icmp */
static int Builder__build_icmp__meth(lua_State *L) {
  Builder * this1;
  IntPredicate * Op2;
  IntValue * lhs3;
  IntValue * rhs4;
  size_t name_len5;
  const char * name5;
  Value * rc_LLVMBuildICmp1;
  this1 = obj_type_Builder_check(L,1);
  Op2 = obj_type_IntPredicate_check(L,2);
  lhs3 = obj_type_IntValue_check(L,3);
  rhs4 = obj_type_IntValue_check(L,4);
  name5 = luaL_checklstring(L,5,&(name_len5));
  rc_LLVMBuildICmp1 = LLVMBuildICmp(this1, *(Op2), lhs3, rhs4, name5);
  obj_type_Value_push(L, rc_LLVMBuildICmp1, 0);
  return 1;
}

/* method: build_fcmp */
static int Builder__build_fcmp__meth(lua_State *L) {
  Builder * this1;
  RealPredicate * Op2;
  FloatValue * lhs3;
  FloatValue * rhs4;
  size_t name_len5;
  const char * name5;
  Value * rc_LLVMBuildFCmp1;
  this1 = obj_type_Builder_check(L,1);
  Op2 = obj_type_RealPredicate_check(L,2);
  lhs3 = obj_type_FloatValue_check(L,3);
  rhs4 = obj_type_FloatValue_check(L,4);
  name5 = luaL_checklstring(L,5,&(name_len5));
  rc_LLVMBuildFCmp1 = LLVMBuildFCmp(this1, *(Op2), lhs3, rhs4, name5);
  obj_type_Value_push(L, rc_LLVMBuildFCmp1, 0);
  return 1;
}

/* method: build_phi */
static int Builder__build_phi__meth(lua_State *L) {
  Builder * this1;
  Type * Ty2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildPhi1;
  this1 = obj_type_Builder_check(L,1);
  Ty2 = obj_type_Type_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildPhi1 = LLVMBuildPhi(this1, Ty2, name3);
  obj_type_Value_push(L, rc_LLVMBuildPhi1, 0);
  return 1;
}

/* method: build_select */
static int Builder__build_select__meth(lua_State *L) {
  Builder * this1;
  Value * If2;
  Value * Then3;
  Value * Else4;
  size_t name_len5;
  const char * name5;
  Value * rc_LLVMBuildSelect1;
  this1 = obj_type_Builder_check(L,1);
  If2 = obj_type_Value_check(L,2);
  Then3 = obj_type_Value_check(L,3);
  Else4 = obj_type_Value_check(L,4);
  name5 = luaL_checklstring(L,5,&(name_len5));
  rc_LLVMBuildSelect1 = LLVMBuildSelect(this1, If2, Then3, Else4, name5);
  obj_type_Value_push(L, rc_LLVMBuildSelect1, 0);
  return 1;
}

/* method: build_vaarg */
static int Builder__build_vaarg__meth(lua_State *L) {
  Builder * this1;
  Value * list2;
  Type * ty3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildVAArg1;
  this1 = obj_type_Builder_check(L,1);
  list2 = obj_type_Value_check(L,2);
  ty3 = obj_type_Type_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildVAArg1 = LLVMBuildVAArg(this1, list2, ty3, name4);
  obj_type_Value_push(L, rc_LLVMBuildVAArg1, 0);
  return 1;
}

/* method: build_extract_element */
static int Builder__build_extract_element__meth(lua_State *L) {
  Builder * this1;
  Value * vecval2;
  Value * index3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildExtractElement1;
  this1 = obj_type_Builder_check(L,1);
  vecval2 = obj_type_Value_check(L,2);
  index3 = obj_type_Value_check(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildExtractElement1 = LLVMBuildExtractElement(this1, vecval2, index3, name4);
  obj_type_Value_push(L, rc_LLVMBuildExtractElement1, 0);
  return 1;
}

/* method: build_insert_element */
static int Builder__build_insert_element__meth(lua_State *L) {
  Builder * this1;
  Value * vecval2;
  Value * eltval3;
  Value * index4;
  size_t name_len5;
  const char * name5;
  Value * rc_LLVMBuildInsertElement1;
  this1 = obj_type_Builder_check(L,1);
  vecval2 = obj_type_Value_check(L,2);
  eltval3 = obj_type_Value_check(L,3);
  index4 = obj_type_Value_check(L,4);
  name5 = luaL_checklstring(L,5,&(name_len5));
  rc_LLVMBuildInsertElement1 = LLVMBuildInsertElement(this1, vecval2, eltval3, index4, name5);
  obj_type_Value_push(L, rc_LLVMBuildInsertElement1, 0);
  return 1;
}

/* method: build_shuffle_vector */
static int Builder__build_shuffle_vector__meth(lua_State *L) {
  Builder * this1;
  Value * v12;
  Value * v23;
  Value * mask4;
  size_t name_len5;
  const char * name5;
  Value * rc_LLVMBuildShuffleVector1;
  this1 = obj_type_Builder_check(L,1);
  v12 = obj_type_Value_check(L,2);
  v23 = obj_type_Value_check(L,3);
  mask4 = obj_type_Value_check(L,4);
  name5 = luaL_checklstring(L,5,&(name_len5));
  rc_LLVMBuildShuffleVector1 = LLVMBuildShuffleVector(this1, v12, v23, mask4, name5);
  obj_type_Value_push(L, rc_LLVMBuildShuffleVector1, 0);
  return 1;
}

/* method: build_extract_value */
static int Builder__build_extract_value__meth(lua_State *L) {
  Builder * this1;
  Value * aggval2;
  unsigned index3;
  size_t name_len4;
  const char * name4;
  Value * rc_LLVMBuildExtractValue1;
  this1 = obj_type_Builder_check(L,1);
  aggval2 = obj_type_Value_check(L,2);
  index3 = luaL_checkinteger(L,3);
  name4 = luaL_checklstring(L,4,&(name_len4));
  rc_LLVMBuildExtractValue1 = LLVMBuildExtractValue(this1, aggval2, index3, name4);
  obj_type_Value_push(L, rc_LLVMBuildExtractValue1, 0);
  return 1;
}

/* method: build_insert_value */
static int Builder__build_insert_value__meth(lua_State *L) {
  Builder * this1;
  Value * agg_val2;
  Value * elt_val3;
  unsigned index4;
  size_t name_len5;
  const char * name5;
  Value * rc_LLVMBuildInsertValue1;
  this1 = obj_type_Builder_check(L,1);
  agg_val2 = obj_type_Value_check(L,2);
  elt_val3 = obj_type_Value_check(L,3);
  index4 = luaL_checkinteger(L,4);
  name5 = luaL_checklstring(L,5,&(name_len5));
  rc_LLVMBuildInsertValue1 = LLVMBuildInsertValue(this1, agg_val2, elt_val3, index4, name5);
  obj_type_Value_push(L, rc_LLVMBuildInsertValue1, 0);
  return 1;
}

/* method: build_is_null */
static int Builder__build_is_null__meth(lua_State *L) {
  Builder * this1;
  Value * val2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildIsNull1;
  this1 = obj_type_Builder_check(L,1);
  val2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildIsNull1 = LLVMBuildIsNull(this1, val2, name3);
  obj_type_Value_push(L, rc_LLVMBuildIsNull1, 0);
  return 1;
}

/* method: build_is_not_null */
static int Builder__build_is_not_null__meth(lua_State *L) {
  Builder * this1;
  Value * val2;
  size_t name_len3;
  const char * name3;
  Value * rc_LLVMBuildIsNotNull1;
  this1 = obj_type_Builder_check(L,1);
  val2 = obj_type_Value_check(L,2);
  name3 = luaL_checklstring(L,3,&(name_len3));
  rc_LLVMBuildIsNotNull1 = LLVMBuildIsNotNull(this1, val2, name3);
  obj_type_Value_push(L, rc_LLVMBuildIsNotNull1, 0);
  return 1;
}



static const luaL_Reg obj_Type_pub_funcs[] = {
  {"void", Type__void__meth},
  {"label", Type__label__meth},
  {"x86mmx", Type__x86mmx__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Type_methods[] = {
  {"get_context", Type__get_context__meth},
  {"is_sized", Type__is_sized__meth},
  {"dump", Type__dump__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Type_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Type_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Type_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Type_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Type_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_FunctionType_pub_funcs[] = {
  {"new", FunctionType__new__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FunctionType_methods[] = {
  {"get_context", Type__get_context__meth},
  {"is_sized", Type__is_sized__meth},
  {"dump", Type__dump__meth},
  {"is_vararg", FunctionType__is_vararg__meth},
  {"return_type", FunctionType__return_type__meth},
  {"count_param_types", FunctionType__count_param_types__meth},
  {"param_types", FunctionType__param_types__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FunctionType_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_FunctionType_bases[] = {
  {0, NULL},
  {-1, NULL}
};

static const obj_field obj_FunctionType_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_FunctionType_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_FunctionType_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_IntType_pub_funcs[] = {
  {"int1", IntType__int1__meth},
  {"int8", IntType__int8__meth},
  {"int16", IntType__int16__meth},
  {"int32", IntType__int32__meth},
  {"int64", IntType__int64__meth},
  {"int128", IntType__int128__meth},
  {"int", IntType__int__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_IntType_methods[] = {
  {"get_context", Type__get_context__meth},
  {"is_sized", Type__is_sized__meth},
  {"dump", Type__dump__meth},
  {"get_int_width", IntType__get_int_width__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_IntType_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_IntType_bases[] = {
  {0, NULL},
  {-1, NULL}
};

static const obj_field obj_IntType_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_IntType_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_IntType_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_FloatType_pub_funcs[] = {
  {"half", FloatType__half__meth},
  {"float", FloatType__float__meth},
  {"double", FloatType__double__meth},
  {"x86fp80", FloatType__x86fp80__meth},
  {"fp128", FloatType__fp128__meth},
  {"ppcfp128", FloatType__ppcfp128__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FloatType_methods[] = {
  {"get_context", Type__get_context__meth},
  {"is_sized", Type__is_sized__meth},
  {"dump", Type__dump__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FloatType_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_FloatType_bases[] = {
  {0, NULL},
  {-1, NULL}
};

static const obj_field obj_FloatType_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_FloatType_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_FloatType_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Module_pub_funcs[] = {
  {"create", Module__create__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Module_methods[] = {
  {"clone", Module__clone__meth},
  {"identifier", Module__identifier__meth},
  {"set_identifier", Module__set_identifier__meth},
  {"dump", Module__dump__meth},
  {"target", Module__target__meth},
  {"set_target", Module__set_target__meth},
  {"add_function", Module__add_function__meth},
  {"get_function", Module__get_function__meth},
  {"dispose", Module__dispose__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Module_metas[] = {
  {"__gc", Module__dispose__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Module_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Module_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Module_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Module_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Context_pub_funcs[] = {
  {"create", Context__create__meth},
  {"global_context", Context__global_context__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Context_methods[] = {
  {"dispose", Context__dispose__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Context_metas[] = {
  {"__gc", Context__dispose__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Context_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Context_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Context_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Context_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Value_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Value_methods[] = {
  {"name", Value__name__meth},
  {"set_name", Value__set_name__meth},
  {"dump", Value__dump__meth},
  {"is_constant", Value__is_constant__meth},
  {"is_undef", Value__is_undef__meth},
  {"is_null", Value__is_null__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Value_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Value_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Value_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Value_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Value_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_IntValue_pub_funcs[] = {
  {"const", IntValue__const__meth},
  {"const_of_string", IntValue__const_of_string__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_IntValue_methods[] = {
  {"set_name", Value__set_name__meth},
  {"is_constant", Value__is_constant__meth},
  {"is_undef", Value__is_undef__meth},
  {"is_null", Value__is_null__meth},
  {"name", Value__name__meth},
  {"dump", Value__dump__meth},
  {"zext", IntValue__zext__meth},
  {"sext", IntValue__sext__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_IntValue_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_IntValue_bases[] = {
  {6, NULL},
  {-1, NULL}
};

static const obj_field obj_IntValue_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_IntValue_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_IntValue_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_FloatValue_pub_funcs[] = {
  {"const", FloatValue__const__meth},
  {"const_of_string", FloatValue__const_of_string__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FloatValue_methods[] = {
  {"set_name", Value__set_name__meth},
  {"is_constant", Value__is_constant__meth},
  {"is_undef", Value__is_undef__meth},
  {"is_null", Value__is_null__meth},
  {"name", Value__name__meth},
  {"dump", Value__dump__meth},
  {"value", FloatValue__value__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FloatValue_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_FloatValue_bases[] = {
  {6, NULL},
  {-1, NULL}
};

static const obj_field obj_FloatValue_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_FloatValue_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_FloatValue_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_FunctionValue_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_FunctionValue_methods[] = {
  {"set_name", Value__set_name__meth},
  {"is_constant", Value__is_constant__meth},
  {"is_undef", Value__is_undef__meth},
  {"is_null", Value__is_null__meth},
  {"name", Value__name__meth},
  {"dump", Value__dump__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_FunctionValue_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_FunctionValue_bases[] = {
  {6, NULL},
  {-1, NULL}
};

static const obj_field obj_FunctionValue_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_FunctionValue_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_FunctionValue_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_BasicBlock_pub_funcs[] = {
  {"append", BasicBlock__append__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_BasicBlock_methods[] = {
  {"name", BasicBlock__name__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_BasicBlock_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_BasicBlock_bases[] = {
  {-1, NULL}
};

static const obj_field obj_BasicBlock_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_BasicBlock_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_BasicBlock_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Builder_pub_funcs[] = {
  {"create", Builder__create__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Builder_methods[] = {
  {"dispose", Builder__dispose__meth},
  {"position_at_end", Builder__position_at_end__meth},
  {"build_ret", Builder__build_ret__meth},
  {"build_ret_void", Builder__build_ret_void__meth},
  {"build_add", Builder__build_add__meth},
  {"build_nswadd", Builder__build_nswadd__meth},
  {"build_nuwadd", Builder__build_nuwadd__meth},
  {"build_fadd", Builder__build_fadd__meth},
  {"build_sub", Builder__build_sub__meth},
  {"build_nswsub", Builder__build_nswsub__meth},
  {"build_nuwsub", Builder__build_nuwsub__meth},
  {"build_fsub", Builder__build_fsub__meth},
  {"build_mul", Builder__build_mul__meth},
  {"build_nswmul", Builder__build_nswmul__meth},
  {"build_nuwmul", Builder__build_nuwmul__meth},
  {"build_fmul", Builder__build_fmul__meth},
  {"build_udiv", Builder__build_udiv__meth},
  {"build_exact_udiv", Builder__build_exact_udiv__meth},
  {"build_sdiv", Builder__build_sdiv__meth},
  {"build_exact_sdiv", Builder__build_exact_sdiv__meth},
  {"build_fdiv", Builder__build_fdiv__meth},
  {"build_urem", Builder__build_urem__meth},
  {"build_srem", Builder__build_srem__meth},
  {"build_frem", Builder__build_frem__meth},
  {"build_shl", Builder__build_shl__meth},
  {"build_lshr", Builder__build_lshr__meth},
  {"build_ashr", Builder__build_ashr__meth},
  {"build_and", Builder__build_and__meth},
  {"build_or", Builder__build_or__meth},
  {"build_xor", Builder__build_xor__meth},
  {"build_neg", Builder__build_neg__meth},
  {"build_nswneg", Builder__build_nswneg__meth},
  {"build_nuwneg", Builder__build_nuwneg__meth},
  {"build_fneg", Builder__build_fneg__meth},
  {"build_not", Builder__build_not__meth},
  {"build_malloc", Builder__build_malloc__meth},
  {"build_array_malloc", Builder__build_array_malloc__meth},
  {"build_alloca", Builder__build_alloca__meth},
  {"build_array_alloca", Builder__build_array_alloca__meth},
  {"build_free", Builder__build_free__meth},
  {"build_load", Builder__build_load__meth},
  {"build_store", Builder__build_store__meth},
  {"build_Struct_GEP", Builder__build_Struct_GEP__meth},
  {"build_global_string", Builder__build_global_string__meth},
  {"build_global_string_ptr", Builder__build_global_string_ptr__meth},
  {"build_trunc", Builder__build_trunc__meth},
  {"build_zext", Builder__build_zext__meth},
  {"build_sext", Builder__build_sext__meth},
  {"build_fp_to_ui", Builder__build_fp_to_ui__meth},
  {"build_fp_to_si", Builder__build_fp_to_si__meth},
  {"build_ui_to_fp", Builder__build_ui_to_fp__meth},
  {"build_si_to_fp", Builder__build_si_to_fp__meth},
  {"build_fptrunc", Builder__build_fptrunc__meth},
  {"build_fpext", Builder__build_fpext__meth},
  {"build_ptr_to_int", Builder__build_ptr_to_int__meth},
  {"build_int_to_ptr", Builder__build_int_to_ptr__meth},
  {"build_bit_cast", Builder__build_bit_cast__meth},
  {"build_addr_space_cast", Builder__build_addr_space_cast__meth},
  {"build_zext_or_bit_cast", Builder__build_zext_or_bit_cast__meth},
  {"build_sext_or_bit_cast", Builder__build_sext_or_bit_cast__meth},
  {"build_trunc_or_bit_cast", Builder__build_trunc_or_bit_cast__meth},
  {"build_ptr_cast", Builder__build_ptr_cast__meth},
  {"build_int_cast", Builder__build_int_cast__meth},
  {"build_fpcast", Builder__build_fpcast__meth},
  {"build_icmp", Builder__build_icmp__meth},
  {"build_fcmp", Builder__build_fcmp__meth},
  {"build_phi", Builder__build_phi__meth},
  {"build_select", Builder__build_select__meth},
  {"build_vaarg", Builder__build_vaarg__meth},
  {"build_extract_element", Builder__build_extract_element__meth},
  {"build_insert_element", Builder__build_insert_element__meth},
  {"build_shuffle_vector", Builder__build_shuffle_vector__meth},
  {"build_extract_value", Builder__build_extract_value__meth},
  {"build_insert_value", Builder__build_insert_value__meth},
  {"build_is_null", Builder__build_is_null__meth},
  {"build_is_not_null", Builder__build_is_not_null__meth},
  {NULL, NULL}
};

static const luaL_Reg obj_Builder_metas[] = {
  {"__gc", Builder__dispose__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Builder_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Builder_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Builder_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Builder_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Opcode_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Opcode_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Opcode_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Opcode_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Opcode_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Opcode_constants[] = {
#ifdef LLVMInsertValue
  {"InsertValue", NULL, LLVMInsertValue, CONST_NUMBER},
#endif
#ifdef LLVMSub
  {"Sub", NULL, LLVMSub, CONST_NUMBER},
#endif
#ifdef LLVMCatchSwitch
  {"CatchSwitch", NULL, LLVMCatchSwitch, CONST_NUMBER},
#endif
#ifdef LLVMIntToPtr
  {"IntToPtr", NULL, LLVMIntToPtr, CONST_NUMBER},
#endif
#ifdef LLVMICmp
  {"ICmp", NULL, LLVMICmp, CONST_NUMBER},
#endif
#ifdef LLVMSwitch
  {"Switch", NULL, LLVMSwitch, CONST_NUMBER},
#endif
#ifdef LLVMIndirectBr
  {"IndirectBr", NULL, LLVMIndirectBr, CONST_NUMBER},
#endif
#ifdef LLVMFDiv
  {"FDiv", NULL, LLVMFDiv, CONST_NUMBER},
#endif
#ifdef LLVMCatchRet
  {"CatchRet", NULL, LLVMCatchRet, CONST_NUMBER},
#endif
#ifdef LLVMFRem
  {"FRem", NULL, LLVMFRem, CONST_NUMBER},
#endif
#ifdef LLVMUDiv
  {"UDiv", NULL, LLVMUDiv, CONST_NUMBER},
#endif
#ifdef LLVMSRem
  {"SRem", NULL, LLVMSRem, CONST_NUMBER},
#endif
#ifdef LLVMFMul
  {"FMul", NULL, LLVMFMul, CONST_NUMBER},
#endif
#ifdef LLVMMul
  {"Mul", NULL, LLVMMul, CONST_NUMBER},
#endif
#ifdef LLVMPtrToInt
  {"PtrToInt", NULL, LLVMPtrToInt, CONST_NUMBER},
#endif
#ifdef LLVMBr
  {"Br", NULL, LLVMBr, CONST_NUMBER},
#endif
#ifdef LLVMURem
  {"URem", NULL, LLVMURem, CONST_NUMBER},
#endif
#ifdef LLVMAddrSpaceCast
  {"AddrSpaceCast", NULL, LLVMAddrSpaceCast, CONST_NUMBER},
#endif
#ifdef LLVMInsertElement
  {"InsertElement", NULL, LLVMInsertElement, CONST_NUMBER},
#endif
#ifdef LLVMOr
  {"Or", NULL, LLVMOr, CONST_NUMBER},
#endif
#ifdef LLVMAlloca
  {"Alloca", NULL, LLVMAlloca, CONST_NUMBER},
#endif
#ifdef LLVMSelect
  {"Select", NULL, LLVMSelect, CONST_NUMBER},
#endif
#ifdef LLVMUserOp2
  {"UserOp2", NULL, LLVMUserOp2, CONST_NUMBER},
#endif
#ifdef LLVMShuffleVector
  {"ShuffleVector", NULL, LLVMShuffleVector, CONST_NUMBER},
#endif
#ifdef LLVMFence
  {"Fence", NULL, LLVMFence, CONST_NUMBER},
#endif
#ifdef LLVMLoad
  {"Load", NULL, LLVMLoad, CONST_NUMBER},
#endif
#ifdef LLVMGetElementPtr
  {"GetElementPtr", NULL, LLVMGetElementPtr, CONST_NUMBER},
#endif
#ifdef LLVMRet
  {"Ret", NULL, LLVMRet, CONST_NUMBER},
#endif
#ifdef LLVMLandingPad
  {"LandingPad", NULL, LLVMLandingPad, CONST_NUMBER},
#endif
#ifdef LLVMAShr
  {"AShr", NULL, LLVMAShr, CONST_NUMBER},
#endif
#ifdef LLVMExtractElement
  {"ExtractElement", NULL, LLVMExtractElement, CONST_NUMBER},
#endif
#ifdef LLVMAtomicCmpXchg
  {"AtomicCmpXchg", NULL, LLVMAtomicCmpXchg, CONST_NUMBER},
#endif
#ifdef LLVMStore
  {"Store", NULL, LLVMStore, CONST_NUMBER},
#endif
#ifdef LLVMPHI
  {"PHI", NULL, LLVMPHI, CONST_NUMBER},
#endif
#ifdef LLVMFPToSI
  {"FPToSI", NULL, LLVMFPToSI, CONST_NUMBER},
#endif
#ifdef LLVMFSub
  {"FSub", NULL, LLVMFSub, CONST_NUMBER},
#endif
#ifdef LLVMZExt
  {"ZExt", NULL, LLVMZExt, CONST_NUMBER},
#endif
#ifdef LLVMUIToFP
  {"UIToFP", NULL, LLVMUIToFP, CONST_NUMBER},
#endif
#ifdef LLVMFPTrunc
  {"FPTrunc", NULL, LLVMFPTrunc, CONST_NUMBER},
#endif
#ifdef LLVMSIToFP
  {"SIToFP", NULL, LLVMSIToFP, CONST_NUMBER},
#endif
#ifdef LLVMFPToUI
  {"FPToUI", NULL, LLVMFPToUI, CONST_NUMBER},
#endif
#ifdef LLVMFPExt
  {"FPExt", NULL, LLVMFPExt, CONST_NUMBER},
#endif
#ifdef LLVMSExt
  {"SExt", NULL, LLVMSExt, CONST_NUMBER},
#endif
#ifdef LLVMInvoke
  {"Invoke", NULL, LLVMInvoke, CONST_NUMBER},
#endif
#ifdef LLVMAdd
  {"Add", NULL, LLVMAdd, CONST_NUMBER},
#endif
#ifdef LLVMExtractValue
  {"ExtractValue", NULL, LLVMExtractValue, CONST_NUMBER},
#endif
#ifdef LLVMAnd
  {"And", NULL, LLVMAnd, CONST_NUMBER},
#endif
#ifdef LLVMUnreachable
  {"Unreachable", NULL, LLVMUnreachable, CONST_NUMBER},
#endif
#ifdef LLVMLShr
  {"LShr", NULL, LLVMLShr, CONST_NUMBER},
#endif
#ifdef LLVMBitCast
  {"BitCast", NULL, LLVMBitCast, CONST_NUMBER},
#endif
#ifdef LLVMFCmp
  {"FCmp", NULL, LLVMFCmp, CONST_NUMBER},
#endif
#ifdef LLVMFAdd
  {"FAdd", NULL, LLVMFAdd, CONST_NUMBER},
#endif
#ifdef LLVMVAArg
  {"VAArg", NULL, LLVMVAArg, CONST_NUMBER},
#endif
#ifdef LLVMTrunc
  {"Trunc", NULL, LLVMTrunc, CONST_NUMBER},
#endif
#ifdef LLVMUserOp1
  {"UserOp1", NULL, LLVMUserOp1, CONST_NUMBER},
#endif
#ifdef LLVMXor
  {"Xor", NULL, LLVMXor, CONST_NUMBER},
#endif
#ifdef LLVMShl
  {"Shl", NULL, LLVMShl, CONST_NUMBER},
#endif
#ifdef LLVMResume
  {"Resume", NULL, LLVMResume, CONST_NUMBER},
#endif
#ifdef LLVMCall
  {"Call", NULL, LLVMCall, CONST_NUMBER},
#endif
#ifdef LLVMSDiv
  {"SDiv", NULL, LLVMSDiv, CONST_NUMBER},
#endif
#ifdef LLVMCleanupPad
  {"CleanupPad", NULL, LLVMCleanupPad, CONST_NUMBER},
#endif
#ifdef LLVMCleanupRet
  {"CleanupRet", NULL, LLVMCleanupRet, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMW
  {"AtomicRMW", NULL, LLVMAtomicRMW, CONST_NUMBER},
#endif
#ifdef LLVMCatchPad
  {"CatchPad", NULL, LLVMCatchPad, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Opcode_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_TypeKind_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_TypeKind_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_TypeKind_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_TypeKind_bases[] = {
  {-1, NULL}
};

static const obj_field obj_TypeKind_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_TypeKind_constants[] = {
#ifdef LLVMVoidTypeKind
  {"Void", NULL, LLVMVoidTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMVectorTypeKind
  {"Vector", NULL, LLVMVectorTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMFloatTypeKind
  {"Float", NULL, LLVMFloatTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMTokenTypeKind
  {"Token", NULL, LLVMTokenTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMHalfTypeKind
  {"Half", NULL, LLVMHalfTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMStructTypeKind
  {"Struct", NULL, LLVMStructTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMDoubleTypeKind
  {"Double", NULL, LLVMDoubleTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMArrayTypeKind
  {"Array", NULL, LLVMArrayTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMFP128TypeKind
  {"FP128", NULL, LLVMFP128TypeKind, CONST_NUMBER},
#endif
#ifdef LLVMMetadataTypeKind
  {"Metadata", NULL, LLVMMetadataTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMFunctionTypeKind
  {"Function", NULL, LLVMFunctionTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMX86_MMXTypeKind
  {"X86_MMX", NULL, LLVMX86_MMXTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMPPC_FP128TypeKind
  {"PPC_FP128", NULL, LLVMPPC_FP128TypeKind, CONST_NUMBER},
#endif
#ifdef LLVMX86_FP80TypeKind
  {"X86_FP80", NULL, LLVMX86_FP80TypeKind, CONST_NUMBER},
#endif
#ifdef LLVMLabelTypeKind
  {"Label", NULL, LLVMLabelTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMPointerTypeKind
  {"Pointer", NULL, LLVMPointerTypeKind, CONST_NUMBER},
#endif
#ifdef LLVMIntegerTypeKind
  {"Integer", NULL, LLVMIntegerTypeKind, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_TypeKind_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Linkage_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Linkage_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Linkage_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Linkage_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Linkage_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Linkage_constants[] = {
#ifdef LLVMGhostLinkage
  {"Ghost", NULL, LLVMGhostLinkage, CONST_NUMBER},
#endif
#ifdef LLVMLinkerPrivateLinkage
  {"LinkerPrivate", NULL, LLVMLinkerPrivateLinkage, CONST_NUMBER},
#endif
#ifdef LLVMLinkOnceODRLinkage
  {"LinkOnceODR", NULL, LLVMLinkOnceODRLinkage, CONST_NUMBER},
#endif
#ifdef LLVMDLLImportLinkage
  {"DLLImport", NULL, LLVMDLLImportLinkage, CONST_NUMBER},
#endif
#ifdef LLVMAvailableExternallyLinkage
  {"AvailableExternally", NULL, LLVMAvailableExternallyLinkage, CONST_NUMBER},
#endif
#ifdef LLVMPrivateLinkage
  {"Private", NULL, LLVMPrivateLinkage, CONST_NUMBER},
#endif
#ifdef LLVMLinkerPrivateWeakLinkage
  {"LLVMLinkerPrivateWeak", NULL, LLVMLinkerPrivateWeakLinkage, CONST_NUMBER},
#endif
#ifdef LLVMCommonLinkage
  {"Common", NULL, LLVMCommonLinkage, CONST_NUMBER},
#endif
#ifdef LLVMLinkOnceODRAutoHideLinkage
  {"LinkOnceODRAutoHide", NULL, LLVMLinkOnceODRAutoHideLinkage, CONST_NUMBER},
#endif
#ifdef LLVMAppendingLinkage
  {"Appending", NULL, LLVMAppendingLinkage, CONST_NUMBER},
#endif
#ifdef LLVMExternalWeakLinkage
  {"ExternalWeak", NULL, LLVMExternalWeakLinkage, CONST_NUMBER},
#endif
#ifdef LLVMExternalLinkage
  {"External", NULL, LLVMExternalLinkage, CONST_NUMBER},
#endif
#ifdef LLVMLinkOnceAnyLinkage
  {"LinkOnceAny", NULL, LLVMLinkOnceAnyLinkage, CONST_NUMBER},
#endif
#ifdef LLVMWeakAnyLinkage
  {"WeakAny", NULL, LLVMWeakAnyLinkage, CONST_NUMBER},
#endif
#ifdef LLVMWeakODRLinkage
  {"WeakODR", NULL, LLVMWeakODRLinkage, CONST_NUMBER},
#endif
#ifdef LLVMDLLExportLinkage
  {"DLLExport", NULL, LLVMDLLExportLinkage, CONST_NUMBER},
#endif
#ifdef LLVMInternalLinkage
  {"Internal", NULL, LLVMInternalLinkage, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Linkage_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Visibility_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Visibility_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_Visibility_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Visibility_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Visibility_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Visibility_constants[] = {
#ifdef LLVMHiddenVisibility
  {"Hidden", NULL, LLVMHiddenVisibility, CONST_NUMBER},
#endif
#ifdef LLVMDefaultVisibility
  {"Default", NULL, LLVMDefaultVisibility, CONST_NUMBER},
#endif
#ifdef LLVMProtectedVisibility
  {"Protected", NULL, LLVMProtectedVisibility, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_Visibility_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_DLLStorageClass_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_DLLStorageClass_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_DLLStorageClass_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_DLLStorageClass_bases[] = {
  {-1, NULL}
};

static const obj_field obj_DLLStorageClass_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_DLLStorageClass_constants[] = {
#ifdef LLVMDefaultStorageClass
  {"Default", NULL, LLVMDefaultStorageClass, CONST_NUMBER},
#endif
#ifdef LLVMDLLImportStorageClass
  {"DLLImport", NULL, LLVMDLLImportStorageClass, CONST_NUMBER},
#endif
#ifdef LLVMDLLExportStorageClass
  {"DLLExport", NULL, LLVMDLLExportStorageClass, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_DLLStorageClass_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_CallConv_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_CallConv_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_CallConv_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_CallConv_bases[] = {
  {-1, NULL}
};

static const obj_field obj_CallConv_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_CallConv_constants[] = {
#ifdef LLVMAnyRegCallConv
  {"AnyReg", NULL, LLVMAnyRegCallConv, CONST_NUMBER},
#endif
#ifdef LLVMX86StdcallCallConv
  {"X86Stdcall", NULL, LLVMX86StdcallCallConv, CONST_NUMBER},
#endif
#ifdef LLVMWebKitJSCallConv
  {"WebKitJS", NULL, LLVMWebKitJSCallConv, CONST_NUMBER},
#endif
#ifdef LLVMX86FastcallCallConv
  {"X86Fastcall", NULL, LLVMX86FastcallCallConv, CONST_NUMBER},
#endif
#ifdef LLVMFastCallConv
  {"Fast", NULL, LLVMFastCallConv, CONST_NUMBER},
#endif
#ifdef LLVMColdCallConv
  {"Cold", NULL, LLVMColdCallConv, CONST_NUMBER},
#endif
#ifdef LLVMCCallConv
  {"C", NULL, LLVMCCallConv, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_CallConv_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_ValueKind_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_ValueKind_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_ValueKind_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_ValueKind_bases[] = {
  {-1, NULL}
};

static const obj_field obj_ValueKind_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_ValueKind_constants[] = {
#ifdef LLVMConstantVectorValueKind
  {"ConstantVectorValueKind", NULL, LLVMConstantVectorValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantTokenNoneValueKind
  {"ConstantTokenNoneValueKind", NULL, LLVMConstantTokenNoneValueKind, CONST_NUMBER},
#endif
#ifdef LLVMInstructionValueKind
  {"InstructionValueKind", NULL, LLVMInstructionValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantStructValueKind
  {"ConstantStructValueKind", NULL, LLVMConstantStructValueKind, CONST_NUMBER},
#endif
#ifdef LLVMMemoryPhiValueKind
  {"MemoryPhiValueKind", NULL, LLVMMemoryPhiValueKind, CONST_NUMBER},
#endif
#ifdef LLVMGlobalAliasValueKind
  {"GlobalAliasValueKind", NULL, LLVMGlobalAliasValueKind, CONST_NUMBER},
#endif
#ifdef LLVMGlobalVariableValueKind
  {"GlobalVariableValueKind", NULL, LLVMGlobalVariableValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantArrayValueKind
  {"ConstantArrayValueKind", NULL, LLVMConstantArrayValueKind, CONST_NUMBER},
#endif
#ifdef LLVMMemoryDefValueKind
  {"MemoryDefValueKind", NULL, LLVMMemoryDefValueKind, CONST_NUMBER},
#endif
#ifdef LLVMUndefValueValueKind
  {"UndefValueValueKind", NULL, LLVMUndefValueValueKind, CONST_NUMBER},
#endif
#ifdef LLVMFunctionValueKind
  {"FunctionValueKind", NULL, LLVMFunctionValueKind, CONST_NUMBER},
#endif
#ifdef LLVMArgumentValueKind
  {"ArgumentValueKind", NULL, LLVMArgumentValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantPointerNullValueKind
  {"ConstantPointerNullValueKind", NULL, LLVMConstantPointerNullValueKind, CONST_NUMBER},
#endif
#ifdef LLVMBlockAddressValueKind
  {"BlockAddressValueKind", NULL, LLVMBlockAddressValueKind, CONST_NUMBER},
#endif
#ifdef LLVMMemoryUseValueKind
  {"MemoryUseValueKind", NULL, LLVMMemoryUseValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantExprValueKind
  {"ConstantExprValueKind", NULL, LLVMConstantExprValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantAggregateZeroValueKind
  {"ConstantAggregateZeroValueKind", NULL, LLVMConstantAggregateZeroValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantDataVectorValueKind
  {"ConstantDataVectorValueKind", NULL, LLVMConstantDataVectorValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantDataArrayValueKind
  {"ConstantDataArrayValueKind", NULL, LLVMConstantDataArrayValueKind, CONST_NUMBER},
#endif
#ifdef LLVMInlineAsmValueKind
  {"InlineAsmValueKind", NULL, LLVMInlineAsmValueKind, CONST_NUMBER},
#endif
#ifdef LLVMMetadataAsValueValueKind
  {"MetadataAsValueValueKind", NULL, LLVMMetadataAsValueValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantIntValueKind
  {"ConstantIntValueKind", NULL, LLVMConstantIntValueKind, CONST_NUMBER},
#endif
#ifdef LLVMGlobalIFuncValueKind
  {"GlobalIFuncValueKind", NULL, LLVMGlobalIFuncValueKind, CONST_NUMBER},
#endif
#ifdef LLVMBasicBlockValueKind
  {"BasicBlockValueKind", NULL, LLVMBasicBlockValueKind, CONST_NUMBER},
#endif
#ifdef LLVMConstantFPValueKind
  {"ConstantFPValueKind", NULL, LLVMConstantFPValueKind, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_ValueKind_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_IntPredicate_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_IntPredicate_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_IntPredicate_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_IntPredicate_bases[] = {
  {-1, NULL}
};

static const obj_field obj_IntPredicate_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_IntPredicate_constants[] = {
#ifdef LLVMIntSLE
  {"SLE", NULL, LLVMIntSLE, CONST_NUMBER},
#endif
#ifdef LLVMIntEQ
  {"EQ", NULL, LLVMIntEQ, CONST_NUMBER},
#endif
#ifdef LLVMIntSGE
  {"SGE", NULL, LLVMIntSGE, CONST_NUMBER},
#endif
#ifdef LLVMIntSLT
  {"SLT", NULL, LLVMIntSLT, CONST_NUMBER},
#endif
#ifdef LLVMIntUGE
  {"UGE", NULL, LLVMIntUGE, CONST_NUMBER},
#endif
#ifdef LLVMIntSGT
  {"SGT", NULL, LLVMIntSGT, CONST_NUMBER},
#endif
#ifdef LLVMIntUGT
  {"UGT", NULL, LLVMIntUGT, CONST_NUMBER},
#endif
#ifdef LLVMIntNE
  {"NE", NULL, LLVMIntNE, CONST_NUMBER},
#endif
#ifdef LLVMIntULE
  {"ULE", NULL, LLVMIntULE, CONST_NUMBER},
#endif
#ifdef LLVMIntULT
  {"ULT", NULL, LLVMIntULT, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_IntPredicate_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_RealPredicate_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_RealPredicate_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_RealPredicate_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_RealPredicate_bases[] = {
  {-1, NULL}
};

static const obj_field obj_RealPredicate_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_RealPredicate_constants[] = {
#ifdef LLVMRealOGE
  {"OGE", NULL, LLVMRealOGE, CONST_NUMBER},
#endif
#ifdef LLVMRealUNE
  {"UNE", NULL, LLVMRealUNE, CONST_NUMBER},
#endif
#ifdef LLVMRealOGT
  {"OGT", NULL, LLVMRealOGT, CONST_NUMBER},
#endif
#ifdef LLVMRealULE
  {"ULE", NULL, LLVMRealULE, CONST_NUMBER},
#endif
#ifdef LLVMRealONE
  {"ONE", NULL, LLVMRealONE, CONST_NUMBER},
#endif
#ifdef LLVMRealOLT
  {"OLT", NULL, LLVMRealOLT, CONST_NUMBER},
#endif
#ifdef LLVMRealOEQ
  {"OEQ", NULL, LLVMRealOEQ, CONST_NUMBER},
#endif
#ifdef LLVMRealUNO
  {"UNO", NULL, LLVMRealUNO, CONST_NUMBER},
#endif
#ifdef LLVMRealUEQ
  {"UEQ", NULL, LLVMRealUEQ, CONST_NUMBER},
#endif
#ifdef LLVMRealUGT
  {"UGT", NULL, LLVMRealUGT, CONST_NUMBER},
#endif
#ifdef LLVMRealUGE
  {"UGE", NULL, LLVMRealUGE, CONST_NUMBER},
#endif
#ifdef LLVMRealORD
  {"ORD", NULL, LLVMRealORD, CONST_NUMBER},
#endif
#ifdef LLVMRealPredicateFalse
  {"False", NULL, LLVMRealPredicateFalse, CONST_NUMBER},
#endif
#ifdef LLVMRealOLE
  {"OLE", NULL, LLVMRealOLE, CONST_NUMBER},
#endif
#ifdef LLVMRealPredicateTrue
  {"True", NULL, LLVMRealPredicateTrue, CONST_NUMBER},
#endif
#ifdef LLVMRealULT
  {"ULT", NULL, LLVMRealULT, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_RealPredicate_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_LandingPadClauseTy_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_LandingPadClauseTy_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_LandingPadClauseTy_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_LandingPadClauseTy_bases[] = {
  {-1, NULL}
};

static const obj_field obj_LandingPadClauseTy_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_LandingPadClauseTy_constants[] = {
#ifdef LLVMLandingPadCatch
  {"Catch", NULL, LLVMLandingPadCatch, CONST_NUMBER},
#endif
#ifdef LLVMLandingPadFilter
  {"Filter", NULL, LLVMLandingPadFilter, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_LandingPadClauseTy_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_ThreadLocalMode_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_ThreadLocalMode_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_ThreadLocalMode_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_ThreadLocalMode_bases[] = {
  {-1, NULL}
};

static const obj_field obj_ThreadLocalMode_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_ThreadLocalMode_constants[] = {
#ifdef LLVMInitialExecTLSModel
  {"InitialExecTLSModel", NULL, LLVMInitialExecTLSModel, CONST_NUMBER},
#endif
#ifdef LLVMLocalExecTLSModel
  {"LocalExecTLSModel", NULL, LLVMLocalExecTLSModel, CONST_NUMBER},
#endif
#ifdef LLVMNotThreadLocal
  {"NotThreadLocal", NULL, LLVMNotThreadLocal, CONST_NUMBER},
#endif
#ifdef LLVMGeneralDynamicTLSModel
  {"GeneralDynamicTLSModel", NULL, LLVMGeneralDynamicTLSModel, CONST_NUMBER},
#endif
#ifdef LLVMLocalDynamicTLSModel
  {"LocalDynamicTLSModel", NULL, LLVMLocalDynamicTLSModel, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_ThreadLocalMode_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AtomicOrdering_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AtomicOrdering_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AtomicOrdering_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_AtomicOrdering_bases[] = {
  {-1, NULL}
};

static const obj_field obj_AtomicOrdering_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_AtomicOrdering_constants[] = {
#ifdef LLVMAtomicOrderingAcquire
  {"Acquire", NULL, LLVMAtomicOrderingAcquire, CONST_NUMBER},
#endif
#ifdef LLVMAtomicOrderingUnordered
  {"Unordered", NULL, LLVMAtomicOrderingUnordered, CONST_NUMBER},
#endif
#ifdef LLVMAtomicOrderingMonotonic
  {"Monotonic", NULL, LLVMAtomicOrderingMonotonic, CONST_NUMBER},
#endif
#ifdef LLVMAtomicOrderingAcquireRelease
  {"AcquireRelease", NULL, LLVMAtomicOrderingAcquireRelease, CONST_NUMBER},
#endif
#ifdef LLVMAtomicOrderingNotAtomic
  {"NotAtomic", NULL, LLVMAtomicOrderingNotAtomic, CONST_NUMBER},
#endif
#ifdef LLVMAtomicOrderingSequentiallyConsistent
  {"SequentiallyConsistent", NULL, LLVMAtomicOrderingSequentiallyConsistent, CONST_NUMBER},
#endif
#ifdef LLVMAtomicOrderingRelease
  {"Release", NULL, LLVMAtomicOrderingRelease, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_AtomicOrdering_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AtomicRMWBinOp_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AtomicRMWBinOp_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AtomicRMWBinOp_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_AtomicRMWBinOp_bases[] = {
  {-1, NULL}
};

static const obj_field obj_AtomicRMWBinOp_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_AtomicRMWBinOp_constants[] = {
#ifdef LLVMAtomicRMWBinOpXor
  {"Xor", NULL, LLVMAtomicRMWBinOpXor, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpSub
  {"Sub", NULL, LLVMAtomicRMWBinOpSub, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpUMax
  {"UMax", NULL, LLVMAtomicRMWBinOpUMax, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpNand
  {"Nand", NULL, LLVMAtomicRMWBinOpNand, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpMax
  {"Max", NULL, LLVMAtomicRMWBinOpMax, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpUMin
  {"UMin", NULL, LLVMAtomicRMWBinOpUMin, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpXchg
  {"Xchg", NULL, LLVMAtomicRMWBinOpXchg, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpOr
  {"Or", NULL, LLVMAtomicRMWBinOpOr, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpAnd
  {"And", NULL, LLVMAtomicRMWBinOpAnd, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpAdd
  {"Add", NULL, LLVMAtomicRMWBinOpAdd, CONST_NUMBER},
#endif
#ifdef LLVMAtomicRMWBinOpMin
  {"Min", NULL, LLVMAtomicRMWBinOpMin, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_AtomicRMWBinOp_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_DiagnosticSeverity_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_DiagnosticSeverity_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_DiagnosticSeverity_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_DiagnosticSeverity_bases[] = {
  {-1, NULL}
};

static const obj_field obj_DiagnosticSeverity_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_DiagnosticSeverity_constants[] = {
#ifdef LLVMDSError
  {"Error", NULL, LLVMDSError, CONST_NUMBER},
#endif
#ifdef LLVMDSWarning
  {"Warning", NULL, LLVMDSWarning, CONST_NUMBER},
#endif
#ifdef LLVMDSRemark
  {"Remark", NULL, LLVMDSRemark, CONST_NUMBER},
#endif
#ifdef LLVMDSNote
  {"Note", NULL, LLVMDSNote, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_DiagnosticSeverity_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AttributeIndex_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AttributeIndex_methods[] = {
  {NULL, NULL}
};

static const luaL_Reg obj_AttributeIndex_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_AttributeIndex_bases[] = {
  {-1, NULL}
};

static const obj_field obj_AttributeIndex_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_AttributeIndex_constants[] = {
#ifdef LLVMAttributeReturnIndex
  {"AttributeReturnIndex", NULL, LLVMAttributeReturnIndex, CONST_NUMBER},
#endif
#ifdef LLVMAttributeFunctionIndex
  {"AttributeFunctionIndex", NULL, LLVMAttributeFunctionIndex, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_AttributeIndex_implements[] = {
  {NULL, NULL}
};

static const luaL_Reg llvm_function[] = {
  {NULL, NULL}
};

static const obj_const llvm_constants[] = {
  {NULL, NULL, 0.0 , 0}
};



static const reg_sub_module reg_sub_modules[] = {
  { &(obj_type_Type), REG_OBJECT, obj_Type_pub_funcs, obj_Type_methods, obj_Type_metas, obj_Type_bases, obj_Type_fields, obj_Type_constants, obj_Type_implements, 0},
  { &(obj_type_FunctionType), REG_OBJECT, obj_FunctionType_pub_funcs, obj_FunctionType_methods, obj_FunctionType_metas, obj_FunctionType_bases, obj_FunctionType_fields, obj_FunctionType_constants, obj_FunctionType_implements, 0},
  { &(obj_type_IntType), REG_OBJECT, obj_IntType_pub_funcs, obj_IntType_methods, obj_IntType_metas, obj_IntType_bases, obj_IntType_fields, obj_IntType_constants, obj_IntType_implements, 0},
  { &(obj_type_FloatType), REG_OBJECT, obj_FloatType_pub_funcs, obj_FloatType_methods, obj_FloatType_metas, obj_FloatType_bases, obj_FloatType_fields, obj_FloatType_constants, obj_FloatType_implements, 0},
  { &(obj_type_Module), REG_OBJECT, obj_Module_pub_funcs, obj_Module_methods, obj_Module_metas, obj_Module_bases, obj_Module_fields, obj_Module_constants, obj_Module_implements, 0},
  { &(obj_type_Context), REG_OBJECT, obj_Context_pub_funcs, obj_Context_methods, obj_Context_metas, obj_Context_bases, obj_Context_fields, obj_Context_constants, obj_Context_implements, 0},
  { &(obj_type_Value), REG_OBJECT, obj_Value_pub_funcs, obj_Value_methods, obj_Value_metas, obj_Value_bases, obj_Value_fields, obj_Value_constants, obj_Value_implements, 0},
  { &(obj_type_IntValue), REG_OBJECT, obj_IntValue_pub_funcs, obj_IntValue_methods, obj_IntValue_metas, obj_IntValue_bases, obj_IntValue_fields, obj_IntValue_constants, obj_IntValue_implements, 0},
  { &(obj_type_FloatValue), REG_OBJECT, obj_FloatValue_pub_funcs, obj_FloatValue_methods, obj_FloatValue_metas, obj_FloatValue_bases, obj_FloatValue_fields, obj_FloatValue_constants, obj_FloatValue_implements, 0},
  { &(obj_type_FunctionValue), REG_OBJECT, obj_FunctionValue_pub_funcs, obj_FunctionValue_methods, obj_FunctionValue_metas, obj_FunctionValue_bases, obj_FunctionValue_fields, obj_FunctionValue_constants, obj_FunctionValue_implements, 0},
  { &(obj_type_BasicBlock), REG_OBJECT, obj_BasicBlock_pub_funcs, obj_BasicBlock_methods, obj_BasicBlock_metas, obj_BasicBlock_bases, obj_BasicBlock_fields, obj_BasicBlock_constants, obj_BasicBlock_implements, 0},
  { &(obj_type_Builder), REG_OBJECT, obj_Builder_pub_funcs, obj_Builder_methods, obj_Builder_metas, obj_Builder_bases, obj_Builder_fields, obj_Builder_constants, obj_Builder_implements, 0},
  { &(obj_type_Opcode), REG_OBJECT, obj_Opcode_pub_funcs, obj_Opcode_methods, obj_Opcode_metas, obj_Opcode_bases, obj_Opcode_fields, obj_Opcode_constants, obj_Opcode_implements, 0},
  { &(obj_type_TypeKind), REG_OBJECT, obj_TypeKind_pub_funcs, obj_TypeKind_methods, obj_TypeKind_metas, obj_TypeKind_bases, obj_TypeKind_fields, obj_TypeKind_constants, obj_TypeKind_implements, 0},
  { &(obj_type_Linkage), REG_OBJECT, obj_Linkage_pub_funcs, obj_Linkage_methods, obj_Linkage_metas, obj_Linkage_bases, obj_Linkage_fields, obj_Linkage_constants, obj_Linkage_implements, 0},
  { &(obj_type_Visibility), REG_OBJECT, obj_Visibility_pub_funcs, obj_Visibility_methods, obj_Visibility_metas, obj_Visibility_bases, obj_Visibility_fields, obj_Visibility_constants, obj_Visibility_implements, 0},
  { &(obj_type_DLLStorageClass), REG_OBJECT, obj_DLLStorageClass_pub_funcs, obj_DLLStorageClass_methods, obj_DLLStorageClass_metas, obj_DLLStorageClass_bases, obj_DLLStorageClass_fields, obj_DLLStorageClass_constants, obj_DLLStorageClass_implements, 0},
  { &(obj_type_CallConv), REG_OBJECT, obj_CallConv_pub_funcs, obj_CallConv_methods, obj_CallConv_metas, obj_CallConv_bases, obj_CallConv_fields, obj_CallConv_constants, obj_CallConv_implements, 0},
  { &(obj_type_ValueKind), REG_OBJECT, obj_ValueKind_pub_funcs, obj_ValueKind_methods, obj_ValueKind_metas, obj_ValueKind_bases, obj_ValueKind_fields, obj_ValueKind_constants, obj_ValueKind_implements, 0},
  { &(obj_type_IntPredicate), REG_OBJECT, obj_IntPredicate_pub_funcs, obj_IntPredicate_methods, obj_IntPredicate_metas, obj_IntPredicate_bases, obj_IntPredicate_fields, obj_IntPredicate_constants, obj_IntPredicate_implements, 0},
  { &(obj_type_RealPredicate), REG_OBJECT, obj_RealPredicate_pub_funcs, obj_RealPredicate_methods, obj_RealPredicate_metas, obj_RealPredicate_bases, obj_RealPredicate_fields, obj_RealPredicate_constants, obj_RealPredicate_implements, 0},
  { &(obj_type_LandingPadClauseTy), REG_OBJECT, obj_LandingPadClauseTy_pub_funcs, obj_LandingPadClauseTy_methods, obj_LandingPadClauseTy_metas, obj_LandingPadClauseTy_bases, obj_LandingPadClauseTy_fields, obj_LandingPadClauseTy_constants, obj_LandingPadClauseTy_implements, 0},
  { &(obj_type_ThreadLocalMode), REG_OBJECT, obj_ThreadLocalMode_pub_funcs, obj_ThreadLocalMode_methods, obj_ThreadLocalMode_metas, obj_ThreadLocalMode_bases, obj_ThreadLocalMode_fields, obj_ThreadLocalMode_constants, obj_ThreadLocalMode_implements, 0},
  { &(obj_type_AtomicOrdering), REG_OBJECT, obj_AtomicOrdering_pub_funcs, obj_AtomicOrdering_methods, obj_AtomicOrdering_metas, obj_AtomicOrdering_bases, obj_AtomicOrdering_fields, obj_AtomicOrdering_constants, obj_AtomicOrdering_implements, 0},
  { &(obj_type_AtomicRMWBinOp), REG_OBJECT, obj_AtomicRMWBinOp_pub_funcs, obj_AtomicRMWBinOp_methods, obj_AtomicRMWBinOp_metas, obj_AtomicRMWBinOp_bases, obj_AtomicRMWBinOp_fields, obj_AtomicRMWBinOp_constants, obj_AtomicRMWBinOp_implements, 0},
  { &(obj_type_DiagnosticSeverity), REG_OBJECT, obj_DiagnosticSeverity_pub_funcs, obj_DiagnosticSeverity_methods, obj_DiagnosticSeverity_metas, obj_DiagnosticSeverity_bases, obj_DiagnosticSeverity_fields, obj_DiagnosticSeverity_constants, obj_DiagnosticSeverity_implements, 0},
  { &(obj_type_AttributeIndex), REG_OBJECT, obj_AttributeIndex_pub_funcs, obj_AttributeIndex_methods, obj_AttributeIndex_metas, obj_AttributeIndex_bases, obj_AttributeIndex_fields, obj_AttributeIndex_constants, obj_AttributeIndex_implements, 0},
  {NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0}
};





#if LUAJIT_FFI
static const ffi_export_symbol llvm_ffi_export[] = {
  {NULL, { NULL } }
};
#endif




static const luaL_Reg submodule_libs[] = {
  {NULL, NULL}
};



static void create_object_instance_cache(lua_State *L) {
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(!lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop weak table. */
		return;
	}
	lua_pop(L, 1); /* pop nil. */
	/* create weak table for object instance references. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_newtable(L);               /* weak table. */
	lua_newtable(L);               /* metatable for weak table. */
	lua_pushliteral(L, "__mode");
	lua_pushliteral(L, "v");
	lua_rawset(L, -3);             /* metatable.__mode = 'v'  weak values. */
	lua_setmetatable(L, -2);       /* add metatable to weak table. */
	lua_rawset(L, LUA_REGISTRYINDEX);  /* create reference to weak table. */
}

LUA_NOBJ_API int luaopen_llvm(lua_State *L) {
	const reg_sub_module *reg = reg_sub_modules;
	const luaL_Reg *submodules = submodule_libs;
	int priv_table = -1;

	/* register interfaces */
	obj_register_interfaces(L, obj_interfaces);

	/* private table to hold reference to object metatables. */
	lua_newtable(L);
	priv_table = lua_gettop(L);
	lua_pushlightuserdata(L, obj_udata_private_key);
	lua_pushvalue(L, priv_table);
	lua_rawset(L, LUA_REGISTRYINDEX);  /* store private table in registry. */

	/* create object cache. */
	create_object_instance_cache(L);

	/* module table. */
#if REG_MODULES_AS_GLOBALS
	luaL_register(L, "llvm", llvm_function);
#else
	lua_newtable(L);
	luaL_setfuncs(L, llvm_function, 0);
#endif

	/* register module constants. */
	obj_type_register_constants(L, llvm_constants, -1, 0);

	for(; submodules->func != NULL ; submodules++) {
		lua_pushcfunction(L, submodules->func);
		lua_pushstring(L, submodules->name);
		lua_call(L, 1, 0);
	}

	/* register objects */
	for(; reg->type != NULL ; reg++) {
		lua_newtable(L); /* create public API table for object. */
		lua_pushvalue(L, -1); /* dup. object's public API table. */
		lua_setfield(L, -3, reg->type->name); /* module["<object_name>"] = <object public API> */
#if REG_OBJECTS_AS_GLOBALS
		lua_pushvalue(L, -1);                 /* dup value. */
		lua_setglobal(L, reg->type->name);    /* global: <object_name> = <object public API> */
#endif
		obj_type_register(L, reg, priv_table);
	}

#if LUAJIT_FFI
	if(nobj_check_ffi_support(L)) {
		nobj_try_loading_ffi(L, "llvm.nobj.ffi.lua", llvm_ffi_lua_code,
			llvm_ffi_export, priv_table);
	}
#endif



	return 1;
}


