
void FUN_005c8f80(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_0045c490();
    *(undefined4 *)(iVar1 + 0x24) = *param_2;
    *(undefined4 *)(iVar1 + 0x28) = param_2[1];
    *(undefined4 *)(iVar1 + 0x2c) = param_2[2];
  }
  return;
}

