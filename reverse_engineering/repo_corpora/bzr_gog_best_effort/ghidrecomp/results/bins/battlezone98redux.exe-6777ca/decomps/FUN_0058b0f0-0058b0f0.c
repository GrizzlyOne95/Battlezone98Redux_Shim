
void FUN_0058b0f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 uVar1;
  bool *pbVar2;
  EHExceptionRecord **ppEVar3;
  _StaticAllocator<int> *p_Var4;
  _Wrap_alloc<struct__StaticAllocator<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>_>_>
  *this;
  _Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_> *p_Var5;
  uint uStack_44;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bd80;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_44;
  ExceptionList = &local_10;
  uVar1 = FUN_0044f820(param_1,param_2);
  local_8 = 0;
  pbVar2 = (bool *)FUN_00417780(param_5);
  ppEVar3 = (EHExceptionRecord **)FUN_00417780(param_4);
  p_Var4 = (_StaticAllocator<int> *)FUN_00417780(param_3);
  uVar1 = FUN_004242f0(uVar1);
  this = (_Wrap_alloc<struct__StaticAllocator<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>_>_>
          *)Getal(&local_15);
  p_Var5 = (_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_> *)
           FUN_00417780(uVar1);
  std::
  _Wrap_alloc<struct__StaticAllocator<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>_>_>
  ::
  construct<class_std::_Ref_count_obj_alloc<class___ExceptionPtr,struct__StaticAllocator<int>_>,struct__StaticAllocator<int>_const&,struct_EHExceptionRecord*&,bool>
            (this,p_Var5,p_Var4,ppEVar3,pbVar2);
  FUN_0058b1cf(param_2);
  return;
}

