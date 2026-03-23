
uint FUN_0083619b(uint param_1,byte *param_2,int param_3)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = *param_2;
  if (bVar1 == 0x25) {
    uVar2 = FUN_00835e4f(param_1,param_2[1]);
    return uVar2;
  }
  if (bVar1 != 0x2e) {
    if (bVar1 != 0x5b) {
      return (uint)(bVar1 == param_1);
    }
    uVar2 = FUN_00835f1e(param_1,param_2,param_3 + -1);
    return uVar2;
  }
  return 1;
}

