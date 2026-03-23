
void __fastcall FUN_006d7850(shared_ptr<struct_Concurrency::details::_ExceptionHolder> *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  *(int *)(param_1 + 8) = iVar1 + 1;
  FUN_00421ec0();
  iVar2 = FUN_006d8500();
  if (iVar1 + 1 == iVar2) {
    std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset(param_1);
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

