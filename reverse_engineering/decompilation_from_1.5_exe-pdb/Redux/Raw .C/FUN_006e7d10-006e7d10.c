
/* WARNING: Removing unreachable block (ram,0x006e7d26) */

undefined4 __fastcall FUN_006e7d10(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  
  uVar1 = FUN_006b2540(param_1);
  if ((uVar1 & 3) == 0) {
    uVar2 = FUN_006b2540(param_1);
    uVar1 = (uVar2 & 0xffff) / 100;
    if ((uVar2 & 0xffff) % 100 == 0) {
      uVar2 = FUN_006b2540(param_1);
      uVar1 = 0;
      if ((uVar2 & 0xffff) % 400 != 0) goto LAB_006e7d66;
    }
    uVar3 = 1;
  }
  else {
LAB_006e7d66:
    uVar1 = 0;
    uVar3 = 0;
  }
  return CONCAT31((int3)(uVar1 >> 8),uVar3);
}

