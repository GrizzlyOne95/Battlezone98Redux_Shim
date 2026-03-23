
undefined4 FUN_007c6e00(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int *local_c;
  int local_8;
  
  iVar1 = FUN_007c6320();
  if (iVar1 == 0) {
    *(undefined1 *)(local_8 + 0x19) = 1;
    if (*(int *)(local_8 + 0x14) == 0) {
      uVar2 = 1;
    }
    else {
      iVar1 = FUN_0044d2a0();
      local_c = *(int **)(iVar1 + 0xc);
      (**(code **)(*local_c + 0x148))(local_20,local_1c,local_18,local_14,local_10);
      uVar2 = (**(code **)(**(int **)(local_8 + 0x14) + 0x1c))(*param_1,param_1[1],param_2);
    }
  }
  else {
    FUN_007c6980();
    uVar2 = 0;
  }
  return uVar2;
}

