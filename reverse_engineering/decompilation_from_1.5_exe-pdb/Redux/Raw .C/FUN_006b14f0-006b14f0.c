
void __thiscall FUN_006b14f0(int param_1,undefined4 *param_2)

{
  *param_2 = 0xffffffff;
  *(undefined1 *)(param_2 + 1) = 0;
  std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
            ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(param_2 + 2));
  FUN_006c8ce0(param_1 + 0x10);
  param_2[5] = *(undefined4 *)(param_1 + 0x28);
  param_2[6] = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    *(undefined4 **)(*(int *)(param_1 + 0x28) + 0x18) = param_2;
  }
  *(undefined4 **)(param_1 + 0x28) = param_2;
  FUN_006c8d50();
  return;
}

