
void FUN_0083cca2(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_1c [2];
  undefined8 local_14;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  local_c = 0xffffffff;
  local_1c[0] = 5;
  local_14 = 0;
  if (param_2 == 0) {
    iVar1 = FUN_0083c468(param_3);
    if (iVar1 == 0) {
      FUN_0083c7b7(param_1,param_3);
    }
    FUN_0083be46(param_1,0x12,param_3,local_1c);
  }
  else if (param_2 == 1) {
    FUN_0083bf3d(param_1,param_3);
  }
  else if (param_2 == 2) {
    FUN_0083c7b7(param_1,param_3);
    FUN_0083be46(param_1,0x14,param_3,local_1c);
  }
  return;
}

