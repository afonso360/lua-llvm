-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.


-- TODO: The c_source blocks with the defines are to fix a bug
-- in lua native objects

object "Opcode" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMOpcode Opcode;
  ]],

	c_source [[
    #define LLVMRet LLVMRet
    #define LLVMBr LLVMBr
    #define LLVMSwitch LLVMSwitch
    #define LLVMIndirectBr LLVMIndirectBr
    #define LLVMInvoke LLVMInvoke
    #define LLVMUnreachable LLVMUnreachable
    #define LLVMAdd LLVMAdd
    #define LLVMFAdd LLVMFAdd
    #define LLVMSub LLVMSub
    #define LLVMFSub LLVMFSub
    #define LLVMMul LLVMMul
    #define LLVMFMul LLVMFMul
    #define LLVMUDiv LLVMUDiv
    #define LLVMSDiv LLVMSDiv
    #define LLVMFDiv LLVMFDiv
    #define LLVMURem LLVMURem
    #define LLVMSRem LLVMSRem
    #define LLVMFRem LLVMFRem
    #define LLVMShl LLVMShl
    #define LLVMLShr LLVMLShr
    #define LLVMAShr LLVMAShr
    #define LLVMAnd LLVMAnd
    #define LLVMOr LLVMOr
    #define LLVMXor LLVMXor
    #define LLVMAlloca LLVMAlloca
    #define LLVMLoad LLVMLoad
    #define LLVMStore LLVMStore
    #define LLVMGetElementPtr LLVMGetElementPtr
    #define LLVMTrunc LLVMTrunc
    #define LLVMZExt LLVMZExt
    #define LLVMSExt LLVMSExt
    #define LLVMFPToUI LLVMFPToUI
    #define LLVMFPToSI LLVMFPToSI
    #define LLVMUIToFP LLVMUIToFP
    #define LLVMSIToFP LLVMSIToFP
    #define LLVMFPTrunc LLVMFPTrunc
    #define LLVMFPExt LLVMFPExt
    #define LLVMPtrToInt LLVMPtrToInt
    #define LLVMIntToPtr LLVMIntToPtr
    #define LLVMBitCast LLVMBitCast
    #define LLVMAddrSpaceCast LLVMAddrSpaceCast
    #define LLVMICmp LLVMICmp
    #define LLVMFCmp LLVMFCmp
    #define LLVMPHI LLVMPHI
    #define LLVMCall LLVMCall
    #define LLVMSelect LLVMSelect
    #define LLVMUserOp1 LLVMUserOp1
    #define LLVMUserOp2 LLVMUserOp2
    #define LLVMVAArg LLVMVAArg
    #define LLVMExtractElement LLVMExtractElement
    #define LLVMInsertElement LLVMInsertElement
    #define LLVMShuffleVector LLVMShuffleVector
    #define LLVMExtractValue LLVMExtractValue
    #define LLVMInsertValue LLVMInsertValue
    #define LLVMFence LLVMFence
    #define LLVMAtomicCmpXchg LLVMAtomicCmpXchg
    #define LLVMAtomicRMW LLVMAtomicRMW
    #define LLVMResume LLVMResume
    #define LLVMLandingPad LLVMLandingPad
    #define LLVMCleanupRet LLVMCleanupRet
    #define LLVMCatchRet LLVMCatchRet
    #define LLVMCatchPad LLVMCatchPad
    #define LLVMCleanupPad LLVMCleanupPad
    #define LLVMCatchSwitch LLVMCatchSwitch
  ]],

	export_definitions {
		Ret = "LLVMRet",
		Br = "LLVMBr",
		Switch = "LLVMSwitch",
		IndirectBr = "LLVMIndirectBr",
		Invoke = "LLVMInvoke",
		Unreachable = "LLVMUnreachable",
		Add = "LLVMAdd",
		FAdd = "LLVMFAdd",
		Sub = "LLVMSub",
		FSub = "LLVMFSub",
		Mul = "LLVMMul",
		FMul = "LLVMFMul",
		UDiv = "LLVMUDiv",
		SDiv = "LLVMSDiv",
		FDiv = "LLVMFDiv",
		URem = "LLVMURem",
		SRem = "LLVMSRem",
		FRem = "LLVMFRem",
		Shl = "LLVMShl",
		LShr = "LLVMLShr",
		AShr = "LLVMAShr",
		And = "LLVMAnd",
		Or = "LLVMOr",
		Xor = "LLVMXor",
		Alloca = "LLVMAlloca",
		Load = "LLVMLoad",
		Store = "LLVMStore",
		GetElementPtr = "LLVMGetElementPtr",
		Trunc = "LLVMTrunc",
		ZExt = "LLVMZExt",
		SExt = "LLVMSExt",
		FPToUI = "LLVMFPToUI",
		FPToSI = "LLVMFPToSI",
		UIToFP = "LLVMUIToFP",
		SIToFP = "LLVMSIToFP",
		FPTrunc = "LLVMFPTrunc",
		FPExt = "LLVMFPExt",
		PtrToInt = "LLVMPtrToInt",
		IntToPtr = "LLVMIntToPtr",
		BitCast = "LLVMBitCast",
		AddrSpaceCast = "LLVMAddrSpaceCast",
		ICmp = "LLVMICmp",
		FCmp = "LLVMFCmp",
		PHI = "LLVMPHI",
		Call = "LLVMCall",
		Select = "LLVMSelect",
		UserOp1 = "LLVMUserOp1",
		UserOp2 = "LLVMUserOp2",
		VAArg = "LLVMVAArg",
		ExtractElement = "LLVMExtractElement",
		InsertElement = "LLVMInsertElement",
		ShuffleVector = "LLVMShuffleVector",
		ExtractValue = "LLVMExtractValue",
		InsertValue = "LLVMInsertValue",
		Fence = "LLVMFence",
		AtomicCmpXchg = "LLVMAtomicCmpXchg",
		AtomicRMW = "LLVMAtomicRMW",
		Resume = "LLVMResume",
		LandingPad = "LLVMLandingPad",
		CleanupRet = "LLVMCleanupRet",
		CatchRet = "LLVMCatchRet",
		CatchPad = "LLVMCatchPad",
		CleanupPad = "LLVMCleanupPad",
		CatchSwitch = "LLVMCatchSwitch",
	}
}

object "TypeKind" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMTypeKind TypeKind;
  ]],

	c_source [[
    #define LLVMVoidTypeKind LLVMVoidTypeKind
    #define LLVMHalfTypeKind LLVMHalfTypeKind
    #define LLVMFloatTypeKind LLVMFloatTypeKind
    #define LLVMDoubleTypeKind LLVMDoubleTypeKind
    #define LLVMX86_FP80TypeKind LLVMX86_FP80TypeKind
    #define LLVMFP128TypeKind LLVMFP128TypeKind
    #define LLVMPPC_FP128TypeKind LLVMPPC_FP128TypeKind
    #define LLVMLabelTypeKind LLVMLabelTypeKind
    #define LLVMIntegerTypeKind LLVMIntegerTypeKind
    #define LLVMFunctionTypeKind LLVMFunctionTypeKind
    #define LLVMStructTypeKind LLVMStructTypeKind
    #define LLVMArrayTypeKind LLVMArrayTypeKind
    #define LLVMPointerTypeKind LLVMPointerTypeKind
    #define LLVMVectorTypeKind LLVMVectorTypeKind
    #define LLVMMetadataTypeKind LLVMMetadataTypeKind
    #define LLVMX86_MMXTypeKind LLVMX86_MMXTypeKind
    #define LLVMTokenTypeKind LLVMTokenTypeKind
	]],

  export_definitions {
		Void = "LLVMVoidTypeKind",
		Half = "LLVMHalfTypeKind",
		Float = "LLVMFloatTypeKind",
		Double = "LLVMDoubleTypeKind",
		X86_FP80 = "LLVMX86_FP80TypeKind",
		FP128 = "LLVMFP128TypeKind",
		PPC_FP128 = "LLVMPPC_FP128TypeKind",
		Label = "LLVMLabelTypeKind",
		Integer = "LLVMIntegerTypeKind",
		Function = "LLVMFunctionTypeKind",
		Struct = "LLVMStructTypeKind",
		Array = "LLVMArrayTypeKind",
		Pointer = "LLVMPointerTypeKind",
		Vector = "LLVMVectorTypeKind",
		Metadata = "LLVMMetadataTypeKind",
		X86_MMX = "LLVMX86_MMXTypeKind",
		Token = "LLVMTokenTypeKind",
	}
}

object "Linkage" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMLinkage Linkage;
  ]],

	c_source [[
    #define LLVMExternalLinkage LLVMExternalLinkage
    #define LLVMAvailableExternallyLinkage LLVMAvailableExternallyLinkage
    #define LLVMLinkOnceAnyLinkage LLVMLinkOnceAnyLinkage
    #define LLVMLinkOnceODRLinkage LLVMLinkOnceODRLinkage
    #define LLVMLinkOnceODRAutoHideLinkage LLVMLinkOnceODRAutoHideLinkage
    #define LLVMWeakAnyLinkage LLVMWeakAnyLinkage
    #define LLVMWeakODRLinkage LLVMWeakODRLinkage
    #define LLVMAppendingLinkage LLVMAppendingLinkage
    #define LLVMInternalLinkage LLVMInternalLinkage
    #define LLVMPrivateLinkage LLVMPrivateLinkage
    #define LLVMDLLImportLinkage LLVMDLLImportLinkage
    #define LLVMDLLExportLinkage LLVMDLLExportLinkage
    #define LLVMExternalWeakLinkage LLVMExternalWeakLinkage
    #define LLVMGhostLinkage LLVMGhostLinkage
    #define LLVMCommonLinkage LLVMCommonLinkage
    #define LLVMLinkerPrivateLinkage LLVMLinkerPrivateLinkage
    #define LLVMLinkerPrivateWeakLinkag LLVMLinkerPrivateWeakLinkag
	]],

  export_definitions {
		External = "LLVMExternalLinkage",
		AvailableExternally = "LLVMAvailableExternallyLinkage",
		LinkOnceAny = "LLVMLinkOnceAnyLinkage",
		LinkOnceODR = "LLVMLinkOnceODRLinkage",
		LinkOnceODRAutoHide = "LLVMLinkOnceODRAutoHideLinkage",
		WeakAny = "LLVMWeakAnyLinkage",
		WeakODR = "LLVMWeakODRLinkage",
		Appending = "LLVMAppendingLinkage",
		Internal = "LLVMInternalLinkage",
		Private = "LLVMPrivateLinkage",
		DLLImport = "LLVMDLLImportLinkage",
		DLLExport = "LLVMDLLExportLinkage",
		ExternalWeak = "LLVMExternalWeakLinkage",
		Ghost = "LLVMGhostLinkage",
		Common = "LLVMCommonLinkage",
		LinkerPrivate = "LLVMLinkerPrivateLinkage",
		LinkerPrivateWeak = "LLVMLinkerPrivateWeakLinkage"
	}
}

object "Visibility" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMVisibility Visibility;
  ]],

	c_source [[
    #define LLVMDefaultVisibility LLVMDefaultVisibility
    #define LLVMHiddenVisibility LLVMHiddenVisibility
    #define LLVMProtectedVisibility LLVMProtectedVisibility
	]],

  export_definitions {
		Default = "LLVMDefaultVisibility",
		Hidden = "LLVMHiddenVisibility",
		Protected = "LLVMProtectedVisibility",
	}
}

object "DLLStorageClass" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMDLLStorageClass DLLStorageClass;
  ]],

	c_source [[
    #define LLVMDefaultStorageClass LLVMDefaultStorageClass
    #define LLVMDLLImportStorageClass LLVMDLLImportStorageClass
    #define LLVMDLLExportStorageClass LLVMDLLExportStorageClass
	]],

  export_definitions {
		Default = "LLVMDefaultStorageClass",
		DLLImport = "LLVMDLLImportStorageClass",
		DLLExport = "LLVMDLLExportStorageClass",
	}
}

object "CallConv" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMCallConv CallConv;
  ]],

	c_source [[
    #define LLVMCCallConv LLVMCCallConv
    #define LLVMFastCallConv LLVMFastCallConv
    #define LLVMColdCallConv LLVMColdCallConv
    #define LLVMWebKitJSCallConv LLVMWebKitJSCallConv
    #define LLVMAnyRegCallConv LLVMAnyRegCallConv
    #define LLVMX86StdcallCallConv LLVMX86StdcallCallConv
    #define LLVMX86FastcallCallConv LLVMX86FastcallCallConv
	]],

  export_definitions {
		C = "LLVMCCallConv",
		Fast = "LLVMFastCallConv",
		Cold = "LLVMColdCallConv",
		WebKitJS = "LLVMWebKitJSCallConv",
		AnyReg = "LLVMAnyRegCallConv",
		X86Stdcall = "LLVMX86StdcallCallConv",
		X86Fastcall = "LLVMX86FastcallCallConv",
	}
}

object "ValueKind" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMValueKind ValueKind;
  ]],

	c_source [[
    #define LLVMArgumentValueKind LLVMArgumentValueKind
    #define LLVMBasicBlockValueKind LLVMBasicBlockValueKind
    #define LLVMMemoryUseValueKind LLVMMemoryUseValueKind
    #define LLVMMemoryDefValueKind LLVMMemoryDefValueKind
    #define LLVMMemoryPhiValueKind LLVMMemoryPhiValueKind
    #define LLVMFunctionValueKind LLVMFunctionValueKind
    #define LLVMGlobalAliasValueKind LLVMGlobalAliasValueKind
    #define LLVMGlobalIFuncValueKind LLVMGlobalIFuncValueKind
    #define LLVMGlobalVariableValueKind LLVMGlobalVariableValueKind
    #define LLVMBlockAddressValueKind LLVMBlockAddressValueKind
    #define LLVMConstantExprValueKind LLVMConstantExprValueKind
    #define LLVMConstantArrayValueKind LLVMConstantArrayValueKind
    #define LLVMConstantStructValueKind LLVMConstantStructValueKind
    #define LLVMConstantVectorValueKind LLVMConstantVectorValueKind
    #define LLVMUndefValueValueKind LLVMUndefValueValueKind
    #define LLVMConstantAggregateZeroValueKind LLVMConstantAggregateZeroValueKind
    #define LLVMConstantDataArrayValueKind LLVMConstantDataArrayValueKind
    #define LLVMConstantDataVectorValueKind LLVMConstantDataVectorValueKind
    #define LLVMConstantIntValueKind LLVMConstantIntValueKind
    #define LLVMConstantFPValueKind LLVMConstantFPValueKind
    #define LLVMConstantPointerNullValueKind LLVMConstantPointerNullValueKind
    #define LLVMConstantTokenNoneValueKind LLVMConstantTokenNoneValueKind
    #define LLVMMetadataAsValueValueKind LLVMMetadataAsValueValueKind
    #define LLVMInlineAsmValueKind LLVMInlineAsmValueKind
    #define LLVMInstructionValueKind LLVMInstructionValueKind
	]],

  export_definitions {
		Argument = "LLVMArgumentValueKind",
		BasicBlock = "LLVMBasicBlockValueKind",
		MemoryUse = "LLVMMemoryUseValueKind",
		MemoryDef = "LLVMMemoryDefValueKind",
		MemoryPhi = "LLVMMemoryPhiValueKind",
		Function = "LLVMFunctionValueKind",
		GlobalAlias = "LLVMGlobalAliasValueKind",
		GlobalIFunc = "LLVMGlobalIFuncValueKind",
		GlobalVariable = "LLVMGlobalVariableValueKind",
		BlockAddress = "LLVMBlockAddressValueKind",
		ConstantExpr = "LLVMConstantExprValueKind",
		ConstantArray = "LLVMConstantArrayValueKind",
		ConstantStruct = "LLVMConstantStructValueKind",
		ConstantVector = "LLVMConstantVectorValueKind",
		UndefValue = "LLVMUndefValueValueKind",
		ConstantAggregateZero = "LLVMConstantAggregateZeroValueKind",
		ConstantDataArray = "LLVMConstantDataArrayValueKind",
		ConstantDataVector = "LLVMConstantDataVectorValueKind",
		ConstantInt = "LLVMConstantIntValueKind",
		ConstantFP = "LLVMConstantFPValueKind",
		ConstantPointerNull = "LLVMConstantPointerNullValueKind",
		ConstantTokenNone = "LLVMConstantTokenNoneValueKind",
		MetadataAsValue = "LLVMMetadataAsValueValueKind",
		InlineAsm = "LLVMInlineAsmValueKind",
		Instruction = "LLVMInstructionValueKind",
	}
}

object "IntPredicate" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMIntPredicate IntPredicate;
  ]],

	c_source [[
    #define LLVMIntEQ LLVMIntEQ
    #define LLVMIntNE LLVMIntNE
    #define LLVMIntUGT LLVMIntUGT
    #define LLVMIntUGE LLVMIntUGE
    #define LLVMIntULT LLVMIntULT
    #define LLVMIntULE LLVMIntULE
    #define LLVMIntSGT LLVMIntSGT
    #define LLVMIntSGE LLVMIntSGE
    #define LLVMIntSLT LLVMIntSLT
    #define LLVMIntSLE LLVMIntSLE
	]],

  export_definitions {
		EQ = "LLVMIntEQ",
		NE = "LLVMIntNE",
		UGT = "LLVMIntUGT",
		UGE = "LLVMIntUGE",
		ULT = "LLVMIntULT",
		ULE = "LLVMIntULE",
		SGT = "LLVMIntSGT",
		SGE = "LLVMIntSGE",
		SLT = "LLVMIntSLT",
		SLE = "LLVMIntSLE",
	}
}

object "RealPredicate" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMRealPredicate RealPredicate;
  ]],

	c_source [[
    #define LLVMRealPredicateFalse LLVMRealPredicateFalse
    #define LLVMRealOEQ LLVMRealOEQ
    #define LLVMRealOGT LLVMRealOGT
    #define LLVMRealOGE LLVMRealOGE
    #define LLVMRealOLT LLVMRealOLT
    #define LLVMRealOLE LLVMRealOLE
    #define LLVMRealONE LLVMRealONE
    #define LLVMRealORD LLVMRealORD
    #define LLVMRealUNO LLVMRealUNO
    #define LLVMRealUEQ LLVMRealUEQ
    #define LLVMRealUGT LLVMRealUGT
    #define LLVMRealUGE LLVMRealUGE
    #define LLVMRealULT LLVMRealULT
    #define LLVMRealULE LLVMRealULE
    #define LLVMRealUNE LLVMRealUNE
    #define LLVMRealPredicateTrue LLVMRealPredicateTrue
	]],

  export_definitions {
		False = "LLVMRealPredicateFalse",
		OEQ = "LLVMRealOEQ",
		OGT = "LLVMRealOGT",
		OGE = "LLVMRealOGE",
		OLT = "LLVMRealOLT",
		OLE = "LLVMRealOLE",
		ONE = "LLVMRealONE",
		ORD = "LLVMRealORD",
		UNO = "LLVMRealUNO",
		UEQ = "LLVMRealUEQ",
		UGT = "LLVMRealUGT",
		UGE = "LLVMRealUGE",
		ULT = "LLVMRealULT",
		ULE = "LLVMRealULE",
		UNE = "LLVMRealUNE",
		True = "LLVMRealPredicateTrue",
	}
}

object "LandingPadClauseTy" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMLandingPadClauseTy LandingPadClauseTy;
  ]],

	c_source [[
    #define LLVMLandingPadCatch LLVMLandingPadCatch
    #define LLVMLandingPadFilter LLVMLandingPadFilter
	]],

  export_definitions {
		Catch = "LLVMLandingPadCatch",
		Filter = "LLVMLandingPadFilter",
	}
}

object "ThreadLocalMode" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMThreadLocalMode ThreadLocalMode;
  ]],

	c_source [[
    #define LLVMNotThreadLocal LLVMNotThreadLocal
    #define LLVMGeneralDynamicTLSModel LLVMGeneralDynamicTLSModel
    #define LLVMLocalDynamicTLSModel LLVMLocalDynamicTLSModel
    #define LLVMInitialExecTLSModel LLVMInitialExecTLSModel
    #define LLVMLocalExecTLSModel LLVMLocalExecTLSModel
	]],

  export_definitions {
		NotThreadLocal = "LLVMNotThreadLocal",
		GeneralDynamicTLSModel = "LLVMGeneralDynamicTLSModel",
		LocalDynamicTLSModel = "LLVMLocalDynamicTLSModel",
		InitialExecTLSModel = "LLVMInitialExecTLSModel",
		LocalExecTLSModel = "LLVMLocalExecTLSModel",
	}
}

object "AtomicOrdering" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMAtomicOrdering AtomicOrdering;
  ]],

	c_source [[
    #define LLVMAtomicOrderingNotAtomic LLVMAtomicOrderingNotAtomic
    #define LLVMAtomicOrderingUnordered LLVMAtomicOrderingUnordered
    #define LLVMAtomicOrderingMonotonic LLVMAtomicOrderingMonotonic
    #define LLVMAtomicOrderingAcquire LLVMAtomicOrderingAcquire
    #define LLVMAtomicOrderingRelease LLVMAtomicOrderingRelease
    #define LLVMAtomicOrderingAcquireRelease LLVMAtomicOrderingAcquireRelease
    #define LLVMAtomicOrderingSequentiallyConsistent LLVMAtomicOrderingSequentiallyConsistent
	]],

  export_definitions {
		NotAtomic = "LLVMAtomicOrderingNotAtomic",
		Unordered = "LLVMAtomicOrderingUnordered",
		Monotonic = "LLVMAtomicOrderingMonotonic",
		Acquire = "LLVMAtomicOrderingAcquire",
		Release = "LLVMAtomicOrderingRelease",
		AcquireRelease = "LLVMAtomicOrderingAcquireRelease",
		SequentiallyConsistent = "LLVMAtomicOrderingSequentiallyConsistent",
	}
}

object "AtomicRMWBinOp" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMAtomicRMWBinOp AtomicRMWBinOp;
  ]],

  c_source [[
    #define LLVMAtomicRMWBinOpXchg LLVMAtomicRMWBinOpXchg
    #define LLVMAtomicRMWBinOpAdd LLVMAtomicRMWBinOpAdd
    #define LLVMAtomicRMWBinOpSub LLVMAtomicRMWBinOpSub
    #define LLVMAtomicRMWBinOpAnd LLVMAtomicRMWBinOpAnd
    #define LLVMAtomicRMWBinOpNand LLVMAtomicRMWBinOpNand
    #define LLVMAtomicRMWBinOpOr LLVMAtomicRMWBinOpOr
    #define LLVMAtomicRMWBinOpXor LLVMAtomicRMWBinOpXor
    #define LLVMAtomicRMWBinOpMax LLVMAtomicRMWBinOpMax
    #define LLVMAtomicRMWBinOpMin LLVMAtomicRMWBinOpMin
    #define LLVMAtomicRMWBinOpUMax LLVMAtomicRMWBinOpUMax
    #define LLVMAtomicRMWBinOpUMin LLVMAtomicRMWBinOpUMin
  ]],

  export_definitions {
		Xchg = "LLVMAtomicRMWBinOpXchg",
		Add = "LLVMAtomicRMWBinOpAdd",
		Sub = "LLVMAtomicRMWBinOpSub",
		And = "LLVMAtomicRMWBinOpAnd",
		Nand = "LLVMAtomicRMWBinOpNand",
		Or = "LLVMAtomicRMWBinOpOr",
		Xor = "LLVMAtomicRMWBinOpXor",
		Max = "LLVMAtomicRMWBinOpMax",
		Min = "LLVMAtomicRMWBinOpMin",
		UMax = "LLVMAtomicRMWBinOpUMax",
		UMin = "LLVMAtomicRMWBinOpUMin",
	}
}

object "DiagnosticSeverity" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMDiagnosticSeverity DiagnosticSeverity;
  ]],

  c_source [[
    #define LLVMDSError LLVMDSError
    #define LLVMDSWarning LLVMDSWarning
    #define LLVMDSRemark LLVMDSRemark
    #define LLVMDSNote LLVMDSNote
  ]],

  export_definitions {
		Error = "LLVMDSError",
		Warning = "LLVMDSWarning",
		Remark = "LLVMDSRemark",
		Note = "LLVMDSNote",
	}
}

object "AttributeIndex" {
  userdata_type = 'simple',
	c_source [[
    typedef LLVMAttributeIndex AttributeIndex;
  ]],

  c_source [[
    #define LLVMAttributeReturnIndex LLVMAttributeReturnIndex
    #define LLVMAttributeFunctionIndex LLVMAttributeFunctionIndex
  ]],

  export_definitions {
   AttributeReturnIndex = "LLVMAttributeReturnIndex",
   AttributeFunctionIndex = "LLVMAttributeFunctionIndex",
	}
}
