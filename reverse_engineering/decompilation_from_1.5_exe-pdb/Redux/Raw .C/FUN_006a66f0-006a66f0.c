
void FUN_006a66f0(int param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fc10;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 8) {
    construct<>(param_3,param_1);
    param_3 = param_3 + 8;
  }
  FUN_006a6787();
  return;
}

