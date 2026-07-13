
uint FUN_00468980(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_0077d640(param_1,param_2);
  iVar2 = FUN_0077d640(param_1 + 1,param_2);
  uVar3 = iVar1 - iVar2 >> 0x1f;
  uVar3 = (iVar1 - iVar2 ^ uVar3) - uVar3;
  if ((int)uVar3 < 0x32) {
    iVar1 = FUN_0077d640(param_1 + 1,param_2);
    iVar2 = FUN_0077d640(param_1 + 1,param_2 + 1);
    uVar3 = iVar1 - iVar2 >> 0x1f;
    uVar3 = (iVar1 - iVar2 ^ uVar3) - uVar3;
    if ((int)uVar3 < 0x32) {
      iVar1 = FUN_0077d640(param_1 + 1,param_2 + 1);
      iVar2 = FUN_0077d640(param_1,param_2 + 1);
      uVar3 = iVar1 - iVar2 >> 0x1f;
      uVar3 = (iVar1 - iVar2 ^ uVar3) - uVar3;
      if ((int)uVar3 < 0x32) {
        iVar1 = FUN_0077d640(param_1,param_2 + 1);
        iVar2 = FUN_0077d640(param_1,param_2);
        uVar3 = iVar1 - iVar2 >> 0x1f;
        uVar3 = (iVar1 - iVar2 ^ uVar3) - uVar3;
        if ((int)uVar3 < 0x32) {
          return uVar3 & 0xffffff00;
        }
      }
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),1);
}

