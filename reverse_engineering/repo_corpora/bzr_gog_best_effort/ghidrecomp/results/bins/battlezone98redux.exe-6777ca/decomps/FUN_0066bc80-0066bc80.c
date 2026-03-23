
void __fastcall FUN_0066bc80(_Container_base0 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)param_1 != 0) {
    std::_Container_base0::_Orphan_all(param_1);
    FUN_0066c6d0(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    iVar1 = (*(int *)(param_1 + 8) - *(int *)param_1) / 0x1c;
    uVar2 = *(undefined4 *)param_1;
    std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr
              ((_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)param_1);
    FUN_004b3230(uVar2,iVar1);
    *(undefined4 *)param_1 = 0;
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

