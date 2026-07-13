
undefined4 FUN_007510d0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_14 [12];
  int *local_8;
  
  iVar1 = FUN_006aa1b0();
  if (iVar1 == 0) {
    FUN_0073a6b0();
  }
  else {
    local_8 = (int *)FUN_006aa1b0();
    uVar2 = (**(code **)(*local_8 + 8))(local_14);
    FUN_0073a6e0(uVar2);
  }
  return param_1;
}

