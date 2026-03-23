
void FUN_00676300(int param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084f010;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 0x1c) {
    construct<>(param_3,param_1);
    param_3 = param_3 + 0x1c;
  }
  FUN_00676397();
  return;
}

