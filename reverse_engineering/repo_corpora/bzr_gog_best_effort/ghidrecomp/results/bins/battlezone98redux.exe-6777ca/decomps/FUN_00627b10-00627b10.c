
void FUN_00627b10(ulong *param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,
                 ulong param_6)

{
  std::_Init_atomic_counter(param_1,DAT_00917584);
  FUN_00689d10(param_1,param_2,param_3 + 1,param_4 + 1,param_5);
  std::_Init_atomic_counter(param_1,param_6);
  FUN_00689d10(param_1,param_2,param_3,param_4,param_5);
  return;
}

