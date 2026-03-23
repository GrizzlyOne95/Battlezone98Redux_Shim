
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_007ae9f0(int param_1)

{
  uint uVar1;
  float10 fVar2;
  undefined8 uVar3;
  undefined4 local_10;
  
  FUN_007d37f0();
  if (((((DAT_009455b0 == 0 && DAT_009455b4 == 0) && (*(char *)(param_1 + 0x19e) == '\0')) &&
       (*(char *)(param_1 + 0x19c) == '\0')) &&
      ((*(char *)(param_1 + 0x19f) == '\0' && (*(char *)(param_1 + 0x19d) == '\0')))) &&
     ((*(char *)(param_1 + 0x1a0) == '\0' && (*(char *)(param_1 + 0x1a1) == '\0')))) {
    *(undefined1 *)(param_1 + 0x1a2) = 0;
    FUN_007d2db0(0x3f800000);
  }
  else if (*(char *)(param_1 + 0x1a2) == '\0') {
    *(undefined1 *)(param_1 + 0x1a2) = 1;
    uVar3 = FUN_00822ea0();
    *(undefined8 *)(param_1 + 0x1a8) = uVar3;
  }
  else {
    uVar3 = FUN_00822ea0();
    if (((int)((ulonglong)uVar3 >> 0x20) - *(int *)(param_1 + 0x1ac) !=
         (uint)((uint)uVar3 < *(uint *)(param_1 + 0x1a8))) ||
       (500 < (uint)uVar3 - *(uint *)(param_1 + 0x1a8))) {
      fVar2 = (float10)FUN_007d2d90();
      if ((float)fVar2 == 0.2) {
        local_10 = 0x3f800000;
      }
      else {
        local_10 = 0x3e4ccccd;
      }
      FUN_007d2db0(local_10);
      *(undefined8 *)(param_1 + 0x1a8) = uVar3;
    }
  }
  if (DAT_009455b0 != 0 || DAT_009455b4 != 0) {
    uVar3 = FUN_00822ea0();
    uVar1 = (uint)((ulonglong)uVar3 >> 0x20);
    if ((DAT_009455b4 <= uVar1) && ((DAT_009455b4 < uVar1 || (DAT_009455b0 < (uint)uVar3)))) {
      FUN_007ae480(1);
      _DAT_009455b0 = 0;
    }
  }
  return;
}

