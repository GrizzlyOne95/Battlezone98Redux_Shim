
void FUN_006311a0(undefined4 param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084d3a0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_2 != param_3; param_2 = param_2 + 4) {
    FUN_00438e40(param_1,param_2);
  }
  FUN_00631240();
  return;
}

