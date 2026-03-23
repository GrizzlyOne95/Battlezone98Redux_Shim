
undefined4 __fastcall FUN_005c18a0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00572a70(param_1);
  if ((iVar1 == 0) && ((*(uint *)(DAT_0094672c + 0x30) & 0x200) != 0)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

