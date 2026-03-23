
void __fastcall FUN_005ac070(int *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  FUN_005af7b0();
  if (param_1[0xbd] != 0) {
    FUN_004e2ce0();
    FUN_00468a70(param_1 + -6,0);
    FUN_00444f20(param_1[0x36]);
  }
  iVar2 = FUN_005e10b0();
  iVar4 = *(int *)(param_1[0x38] + 0x600);
  iVar3 = FUN_005e1190();
  iVar3 = (iVar2 + iVar4) - iVar3;
  if ((0 < iVar3) && ((*(uint *)(param_1[0x37] + 0x14) & 0x80) == 0)) {
    iVar4 = FUN_00572a70();
    if (iVar4 == 0) {
      uVar5 = (**(code **)(*param_1 + 0xc))(iVar3);
      FUN_005c65a0(uVar5);
    }
    else {
      cVar1 = FUN_00571c50();
      if ((cVar1 == '\0') && (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
        uVar5 = (**(code **)(*param_1 + 0xc))(iVar3 / 2);
        FUN_005c65a0(uVar5);
      }
    }
  }
  FUN_004ad070();
  return;
}

