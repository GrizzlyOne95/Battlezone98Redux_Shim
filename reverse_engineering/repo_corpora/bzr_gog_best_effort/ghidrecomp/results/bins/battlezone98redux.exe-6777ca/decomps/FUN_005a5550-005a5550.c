
uint __fastcall FUN_005a5550(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if ((iVar1 != 0) && (iVar1 = FUN_0045bdf0(), iVar1 == 0)) {
    uVar2 = FUN_004e6360();
    return uVar2;
  }
  uVar2 = FUN_00601200();
  *(undefined4 *)(param_1 + 8) = 0xd;
  return uVar2 & 0xffffff00;
}

