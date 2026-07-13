
undefined4 __thiscall
FUN_0067b3e0(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    uVar1 = FUN_0066be00();
    if (uVar1 < param_2) {
      FUN_00423e40();
    }
    else {
      uVar1 = param_2;
      std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
      uVar2 = FUN_0067b8d0(uVar1);
      *(undefined4 *)param_1 = uVar2;
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)param_1;
      *(uint *)(param_1 + 8) = *(int *)param_1 + param_2 * 4;
    }
    uVar2 = 1;
  }
  return uVar2;
}

