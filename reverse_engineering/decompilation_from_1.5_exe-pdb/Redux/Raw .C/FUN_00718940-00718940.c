
void FUN_00718940(int param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00858210;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 0x20) {
    construct<>(param_3,param_1);
    param_3 = param_3 + 0x20;
  }
  FUN_007189d7();
  return;
}

