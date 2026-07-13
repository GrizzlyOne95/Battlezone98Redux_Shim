
void FUN_0083c362(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(*param_1 + 0xc);
  uVar1 = (param_3 - param_2) - 1;
  uVar3 = (int)uVar1 >> 0x1f;
  if (0x1ffff < (int)((uVar1 ^ uVar3) - uVar3)) {
    FUN_008390b7(param_1[3],"control structure too long");
  }
  *(uint *)(iVar2 + param_2 * 4) =
       ((param_3 - param_2) + 0x1fffe) * 0x4000 ^ *(uint *)(iVar2 + param_2 * 4) & 0x3fff;
  return;
}

