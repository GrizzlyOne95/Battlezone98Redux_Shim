
void __thiscall
FUN_004910c0(int param_1,int *param_2,undefined4 *param_3,undefined4 *param_4,float param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float fVar4;
  
  if ((param_2 != (int *)0x0) && (*(uint *)(param_1 + 0x25030) < param_1 + 0x25030U)) {
    fVar4 = (float)*param_2 + param_5 * (float)param_2[2];
    iVar1 = *param_2;
    iVar2 = param_2[1];
    if (fVar4 < (float)(iVar1 + iVar2)) {
      puVar3 = *(undefined4 **)(param_1 + 0x25030);
      *(int *)(param_1 + 0x25030) = *(int *)(param_1 + 0x25030) + 0x40;
      *puVar3 = *param_3;
      puVar3[1] = param_3[1];
      puVar3[2] = param_3[2];
      puVar3[3] = param_3[3];
      puVar3[4] = param_3[4];
      puVar3[5] = param_3[5];
      puVar3[6] = *param_4;
      puVar3[7] = param_4[1];
      puVar3[8] = param_4[2];
      puVar3[9] = fVar4;
      puVar3[10] = (float)param_2[1];
      puVar3[0xb] = (float)(iVar1 + iVar2);
      puVar3[0xc] = param_2[2];
      puVar3[0xd] = param_5 * (float)param_2[4] + (float)param_2[3];
      puVar3[0xe] = param_2[4];
    }
  }
  return;
}

