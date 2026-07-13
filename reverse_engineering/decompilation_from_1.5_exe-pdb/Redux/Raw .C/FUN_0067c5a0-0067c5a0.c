
void FUN_0067c5a0(int param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084f5e0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 4) {
    construct<>(param_3,param_1);
    param_3 = param_3 + 4;
  }
  FUN_0067c637();
  return;
}

