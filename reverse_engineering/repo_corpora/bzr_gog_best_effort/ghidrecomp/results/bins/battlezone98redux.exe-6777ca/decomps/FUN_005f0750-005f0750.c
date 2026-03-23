
void __fastcall FUN_005f0750(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x2c0);
  uVar2 = FUN_005ca740(param_1 + 0x108,*(undefined4 *)(param_1 + 0x174),
                       *(undefined4 *)(param_1 + 0x2c0));
  *(undefined4 *)(param_1 + 0x2c0) = uVar2;
  if ((*(int *)(param_1 + 0x2c0) == 0) || (iVar1 != 0)) {
    if ((*(int *)(param_1 + 0x2c0) == 0) && (iVar1 != 0)) {
      FUN_005ca980(*(undefined4 *)(param_1 + 0xf4));
    }
  }
  else {
    FUN_005ca920(*(undefined4 *)(param_1 + 0xf4));
  }
  return;
}

