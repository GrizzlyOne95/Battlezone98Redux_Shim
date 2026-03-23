
void __fastcall FUN_005c2af0(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((0 < param_1[0xbb]) && ((*(uint *)(param_1[0x37] + 0x14) & 0x80) == 0)) {
    iVar2 = FUN_00572a70();
    if (iVar2 == 0) {
      uVar3 = (**(code **)(*param_1 + 0xc))(param_1[0xbb]);
      FUN_005c65a0(uVar3);
    }
    else {
      cVar1 = FUN_00571c50();
      if ((cVar1 == '\0') && (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
        uVar3 = (**(code **)(*param_1 + 0xc))(param_1[0xbb] / 2);
        FUN_005c65a0(uVar3);
      }
    }
  }
  FUN_004ad070();
  return;
}

