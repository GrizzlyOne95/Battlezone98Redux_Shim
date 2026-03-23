
undefined4 __fastcall FUN_004786c0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0xc) = 1;
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_0045bdf0();
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0xc) = 1;
      uVar2 = 1;
    }
    else {
      iVar1 = FUN_00477d50();
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0xc) = 1;
        uVar2 = 1;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
        if ((iVar1 == 5) || ((6 < iVar1 && (iVar1 < 0xb)))) {
          *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x24);
          *(undefined4 *)(param_1 + 0xc) = 2;
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
      }
    }
  }
  return uVar2;
}

