-- Copyright (C) 2017 Afonso Bordado
--
-- Licensed under the MIT license <http://opensource.org/licenses/MIT>,
-- This file may not be copied, modified, or distributed except according
-- to the terms of that license.

object "Opcode" {
	export_definitions {
		-- Terminator Instructions
		Ret = "LLVMRet",
		Br = "LLVMBr",
		Switch = "LLVMSwitch",
		IndirectBr = "LLVMIndirectBr",
		Invoke = "LLVMInvoke",
		-- removed 6 due to API changes
		Unreachable = "LLVMUnreachable",

		-- Standard Binary Operators
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

		-- Logical Operators
		Shl = "LLVMShl",
		LShr = "LLVMLShr",
		AShr = "LLVMAShr",
		And = "LLVMAnd",
		Or = "LLVMOr",
		Xor = "LLVMXor",

		-- Memory Operators
		Alloca = "LLVMAlloca",
		Load = "LLVMLoad",
		Store = "LLVMStore",
		GetElementPtr = "LLVMGetElementPtr",

		-- Cast Operators
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

		-- Other Operators
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

		-- Atomic operators
		Fence = "LLVMFence",
		AtomicCmpXchg = "LLVMAtomicCmpXchg",
		AtomicRMW = "LLVMAtomicRMW",

		-- Exception Handling Operators
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
		LLVMLinkerPrivateWeak = "LLVMLinkerPrivateWeakLinkage"
	}
}

object "Visibility" {
	export_definitions {
		Default = "LLVMDefaultVisibility",
		Hidden = "LLVMHiddenVisibility",
		Protected = "LLVMProtectedVisibility",
	}
}

object "DLLStorageClass" {
	export_definitions {
		Default = "LLVMDefaultStorageClass",
		DLLImport = "LLVMDLLImportStorageClass",
		DLLExport = "LLVMDLLExportStorageClass",
	}
}

object "CallConv" {
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
	export_definitions {
		ArgumentValueKind = "LLVMArgumentValueKind",
		BasicBlockValueKind = "LLVMBasicBlockValueKind",
		MemoryUseValueKind = "LLVMMemoryUseValueKind",
		MemoryDefValueKind = "LLVMMemoryDefValueKind",
		MemoryPhiValueKind = "LLVMMemoryPhiValueKind",
		FunctionValueKind = "LLVMFunctionValueKind",
		GlobalAliasValueKind = "LLVMGlobalAliasValueKind",
		GlobalIFuncValueKind = "LLVMGlobalIFuncValueKind",
		GlobalVariableValueKind = "LLVMGlobalVariableValueKind",
		BlockAddressValueKind = "LLVMBlockAddressValueKind",
		ConstantExprValueKind = "LLVMConstantExprValueKind",
		ConstantArrayValueKind = "LLVMConstantArrayValueKind",
		ConstantStructValueKind = "LLVMConstantStructValueKind",
		ConstantVectorValueKind = "LLVMConstantVectorValueKind",
		UndefValueValueKind = "LLVMUndefValueValueKind",
		ConstantAggregateZeroValueKind = "LLVMConstantAggregateZeroValueKind",
		ConstantDataArrayValueKind = "LLVMConstantDataArrayValueKind",
		ConstantDataVectorValueKind = "LLVMConstantDataVectorValueKind",
		ConstantIntValueKind = "LLVMConstantIntValueKind",
		ConstantFPValueKind = "LLVMConstantFPValueKind",
		ConstantPointerNullValueKind = "LLVMConstantPointerNullValueKind",
		ConstantTokenNoneValueKind = "LLVMConstantTokenNoneValueKind",
		MetadataAsValueValueKind = "LLVMMetadataAsValueValueKind",
		InlineAsmValueKind = "LLVMInlineAsmValueKind",
		InstructionValueKind = "LLVMInstructionValueKind",
	}
}

object "IntPredicate" {
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
	export_definitions {
		Catch = "LLVMLandingPadCatch",
		Filter = "LLVMLandingPadFilter",
	}
}

object "ThreadLocalMode" {
	export_definitions {
		NotThreadLocal = "LLVMNotThreadLocal",
		GeneralDynamicTLSModel = "LLVMGeneralDynamicTLSModel",
		LocalDynamicTLSModel = "LLVMLocalDynamicTLSModel",
		InitialExecTLSModel = "LLVMInitialExecTLSModel",
		LocalExecTLSModel = "LLVMLocalExecTLSModel",
	}
}

object "AtomicOrdering" {
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
	export_definitions {
		Error = "LLVMDSError",
		Warning = "LLVMDSWarning",
		Remark = "LLVMDSRemark",
		Note = "LLVMDSNote",
	}
}

object "AttributeIndex" {
	export_definitions {
   AttributeReturnIndex = "LLVMAttributeReturnIndex",
   AttributeFunctionIndex = "LLVMAttributeFunctionIndex",
	}
}
