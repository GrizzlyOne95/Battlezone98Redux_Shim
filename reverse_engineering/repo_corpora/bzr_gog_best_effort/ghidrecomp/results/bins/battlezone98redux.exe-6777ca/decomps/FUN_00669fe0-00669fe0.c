
void __thiscall
FUN_00669fe0(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,
            undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = FUN_00417780(param_2);
  cVar1 = FUN_00422af0(uVar2);
  if (cVar1 == '\0') {
    if (*(int *)(param_1 + 4) == *(int *)(param_1 + 8)) {
      FUN_0066b700(1);
    }
    FUN_00422c10(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 4));
    uVar2 = *(undefined4 *)(param_1 + 4);
    std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
    construct<>(uVar2,param_2);
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 0x54;
  }
  else {
    iVar3 = FUN_00417780(param_2);
    iVar4 = *(int *)param_1;
    if (*(int *)(param_1 + 4) == *(int *)(param_1 + 8)) {
      FUN_0066b700(1);
    }
    FUN_00422c10(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 4));
    iVar4 = ((iVar3 - iVar4) / 0x54) * 0x54 + *(int *)param_1;
    uVar2 = *(undefined4 *)(param_1 + 4);
    std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
    construct<>(uVar2,iVar4);
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 0x54;
  }
  return;
}

