
uint __fastcall FUN_005f8660(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0xc) = 1;
    uVar2 = 1;
  }
  else {
    uVar3 = FUN_0045bdf0();
    iVar1 = FUN_00477d50(uVar3);
    uVar2 = *(uint *)(iVar1 + 8);
    if ((uVar2 == 5) || (uVar2 == 8)) {
      *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0xc) = 2;
      uVar2 = CONCAT31((int3)((uint)*(undefined4 *)(param_1 + 0x24) >> 8),1);
    }
    else {
      uVar2 = uVar2 & 0xffffff00;
    }
  }
  return uVar2;
}

