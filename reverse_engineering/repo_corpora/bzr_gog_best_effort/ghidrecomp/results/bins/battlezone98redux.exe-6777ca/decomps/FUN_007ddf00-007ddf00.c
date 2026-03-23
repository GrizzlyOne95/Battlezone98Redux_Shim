
void __thiscall FUN_007ddf00(undefined4 *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863480;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_2 == param_1) {
    FUN_007de005();
    return;
  }
  local_8 = 0;
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    *param_1 = *param_2;
    cVar1 = FUN_007d7500();
    if (cVar1 == '\0') {
      puVar2 = (undefined4 *)FUN_007d9580();
      (*(code *)*puVar2)(param_2 + 2,param_1 + 2,1);
    }
    else {
      param_1[2] = param_2[2];
      param_1[3] = param_2[3];
      param_1[4] = param_2[4];
      param_1[5] = param_2[5];
      param_1[6] = param_2[6];
      param_1[7] = param_2[7];
    }
    *param_2 = 0;
  }
  else {
    FUN_007d8c30();
  }
  FUN_007ddff5();
  return;
}

