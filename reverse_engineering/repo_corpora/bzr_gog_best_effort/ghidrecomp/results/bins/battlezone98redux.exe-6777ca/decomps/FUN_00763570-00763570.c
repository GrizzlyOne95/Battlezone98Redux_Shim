
undefined4 FUN_00763570(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  undefined1 auStack_28 [8];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_c;
  int *local_8;
  
  uStack_14 = 0x76357e;
  local_8 = (int *)FUN_00763430();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    if (param_4 == 0) {
      local_c = 3;
    }
    else {
      local_c = 2;
    }
    uStack_14 = 0;
    uStack_18 = local_c;
    uStack_1c = param_3;
    uStack_20 = param_2;
    FUN_0073a9b0(auStack_28);
    uVar1 = (**(code **)(*local_8 + 4))();
  }
  return uVar1;
}

