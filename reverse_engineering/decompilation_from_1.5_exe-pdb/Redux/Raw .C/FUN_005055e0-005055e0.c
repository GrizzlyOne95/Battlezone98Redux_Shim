
uint FUN_005055e0(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  if (*param_1 + 8U < param_2) {
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\b';
    puVar1 = (undefined4 *)*param_1;
    *puVar1 = param_3;
    puVar1[1] = param_4;
    iVar2 = *param_1;
    *param_1 = iVar2 + 8;
    uVar3 = CONCAT31((int3)((uint)(iVar2 + 8) >> 8),1);
  }
  else {
    uVar3 = (uint)param_1 & 0xffffff00;
  }
  return uVar3;
}

