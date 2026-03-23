
void __thiscall FUN_004c4560(int param_1,ushort *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if ((*(int *)(param_1 + 0xec) < 1) && (*(int *)(param_1 + 0xf0) < 1)) {
    if ((*param_2 & 0xfff) != *(uint *)(param_1 + 0x34)) {
      FUN_004c10a0(param_3,param_4,*param_2,param_5);
      *param_2 = *(ushort *)(param_1 + 0x34);
      FUN_00780b80(param_3 + -2,param_4 + -2,param_3 + 2,param_4 + 2);
    }
  }
  else {
    iVar4 = param_3 - *(int *)(param_1 + 0xec) / 2;
    iVar2 = iVar4 + *(int *)(param_1 + 0xec);
    iVar6 = param_4 - *(int *)(param_1 + 0xf0) / 2;
    iVar5 = iVar6 + *(int *)(param_1 + 0xf0);
    iVar1 = iVar6;
    if (param_5 != 0) {
      FUN_004c10a0(param_3,param_4,*param_2,1);
    }
    while (param_4 = iVar1, param_3 = iVar4, param_4 <= iVar5) {
      for (; param_3 <= iVar2; param_3 = param_3 + 1) {
        puVar3 = (ushort *)FUN_00492d60(param_3,param_4);
        if ((*puVar3 & 0xfff) != *(uint *)(param_1 + 0x34)) {
          FUN_004c10d0(param_3,param_4,*puVar3);
          *puVar3 = *(ushort *)(param_1 + 0x34);
        }
      }
      iVar1 = param_4 + 1;
    }
    FUN_00780b80(iVar4 + -2,iVar6 + -2,iVar2 + 2,iVar5 + 2);
  }
  return;
}

