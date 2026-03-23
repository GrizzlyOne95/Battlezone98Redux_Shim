
void __fastcall FUN_005d3d60(int *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar2 = FUN_005e10b0();
  iVar4 = *(int *)(param_1[0x38] + 0x160);
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
  FUN_0047f330();
  return;
}

