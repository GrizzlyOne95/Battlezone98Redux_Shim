
undefined4 __fastcall FUN_00472cf0(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0046fc10(param_1);
  if (uVar1 == 0) {
    uVar2 = 0;
  }
  else if (uVar1 == 1) {
    uVar2 = 3;
  }
  else if (uVar1 < 0x1b) {
    uVar2 = 0;
  }
  else {
    uVar1 = *(uint *)(uVar1 + 0x14);
    if (uVar1 < 0x524b4955) {
      if (uVar1 == 0x524b4954) {
        return 10;
      }
      if (uVar1 == 0x414d4d4f) {
        return 0xb;
      }
      if (uVar1 == 0x43504f44) {
        return 0xd;
      }
    }
    else {
      if (uVar1 == 0x5745504e) {
        return 0xc;
      }
      if (uVar1 == 0x5752434b) {
        return 0xe;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}

