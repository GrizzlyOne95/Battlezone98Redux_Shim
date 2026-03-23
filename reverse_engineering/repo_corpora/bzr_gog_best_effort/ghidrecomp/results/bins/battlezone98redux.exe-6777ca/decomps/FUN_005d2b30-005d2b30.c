
void FUN_005d2b30(int param_1)

{
  float fVar1;
  undefined4 *puVar2;
  float10 fVar3;
  
  fVar3 = (float10)FUN_005d2ab0(DAT_009182e8,param_1);
  fVar1 = (float)fVar3;
  puVar2 = (undefined4 *)(param_1 + 0x24);
  if (3.0 <= fVar1) {
    if (fVar1 <= 20.0) {
      if (7.0 <= fVar1) {
        *puVar2 = 0x40a00000;
      }
      else {
        *puVar2 = 0x40000000;
      }
    }
    else {
      *puVar2 = 0x447a0000;
    }
  }
  else {
    *puVar2 = 0x3f800000;
  }
  return;
}

