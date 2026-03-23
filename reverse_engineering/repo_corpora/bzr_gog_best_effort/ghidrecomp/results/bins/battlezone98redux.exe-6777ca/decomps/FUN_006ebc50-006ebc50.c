
void FUN_006ebc50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  bool *pbVar3;
  EHExceptionRecord **ppEVar4;
  _StaticAllocator<int> *p_Var5;
  _Wrap_alloc<struct__StaticAllocator<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>_>_>
  *this;
  _Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_> *p_Var6;
  uint uStack_44;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854be0;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_44;
  ExceptionList = &local_10;
  uVar1 = FUN_006f2630();
  puVar2 = (undefined1 *)FUN_00425000(uVar1);
  *puVar2 = 0;
  puVar2 = (undefined1 *)FUN_004242d0(uVar1);
  *puVar2 = 0;
  local_8 = 0;
  pbVar3 = (bool *)FUN_00417780(param_3);
  ppEVar4 = (EHExceptionRecord **)FUN_00417780(param_2);
  p_Var5 = (_StaticAllocator<int> *)FUN_00417780(param_1);
  uVar1 = FUN_00424300(uVar1);
  this = (_Wrap_alloc<struct__StaticAllocator<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>_>_>
          *)Getal(&local_15);
  p_Var6 = (_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_> *)
           FUN_00417780(uVar1);
  std::
  _Wrap_alloc<struct__StaticAllocator<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>_>_>
  ::
  construct<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>,struct__StaticAllocator<int>_const&,struct_EHExceptionRecord*&,bool>
            (this,p_Var6,p_Var5,ppEVar4,pbVar3);
  FUN_006ebd38();
  return;
}

