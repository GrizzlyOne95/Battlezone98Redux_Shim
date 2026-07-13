
uint FUN_0082ec27(int *param_1)

{
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  
  piVar1 = param_1;
  pbVar2 = (byte *)(*(code *)param_1[2])(param_1[4],param_1[3],&param_1);
  if ((pbVar2 == (byte *)0x0) || (param_1 == (int *)0x0)) {
    uVar3 = 0xffffffff;
  }
  else {
    piVar1[1] = (int)pbVar2;
    *piVar1 = (int)param_1 + -1;
    uVar3 = (uint)*pbVar2;
    piVar1[1] = (int)(pbVar2 + 1);
  }
  return uVar3;
}

