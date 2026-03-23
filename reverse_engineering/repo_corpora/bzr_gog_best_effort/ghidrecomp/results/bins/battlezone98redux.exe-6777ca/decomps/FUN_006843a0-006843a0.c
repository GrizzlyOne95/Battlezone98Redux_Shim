
void FUN_006843a0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uStack_40;
  uint local_1c;
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f8b0;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_40;
  ExceptionList = &local_10;
  local_1c = 0;
  _Distance<>(param_2,param_3,&local_1c);
  if (local_1c != 0) {
    uVar1 = FUN_00423eb0();
    if (uVar1 < local_1c) {
      iVar2 = size();
      iVar3 = FUN_0066be00();
      if ((uint)(iVar3 - iVar2) < local_1c) {
        FUN_00423e40();
      }
      iVar2 = size();
      uVar4 = FID_conflict__Grow_to(iVar2 + local_1c);
      std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(local_18);
      uVar4 = FUN_0067b8d0(uVar4);
      local_8 = 0;
      uVar4 = FUN_006846e0(*(undefined4 *)local_18,param_1,uVar4);
      uVar4 = FUN_00684760(param_2,param_3,uVar4);
      FUN_006846e0(param_1,*(undefined4 *)(local_18 + 4),uVar4);
      FUN_006844ec();
      return;
    }
    FUN_00684760(param_2,param_3,*(undefined4 *)(local_18 + 4));
    rotate<>(param_1,*(undefined4 *)(local_18 + 4),*(int *)(local_18 + 4) + local_1c * 4);
    *(uint *)(local_18 + 4) = *(int *)(local_18 + 4) + local_1c * 4;
    FUN_00422c10(param_1,*(undefined4 *)(local_18 + 4));
  }
  ExceptionList = local_10;
  return;
}

