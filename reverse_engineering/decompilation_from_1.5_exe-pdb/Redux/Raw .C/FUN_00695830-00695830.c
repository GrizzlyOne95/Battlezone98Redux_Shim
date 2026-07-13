
void FUN_00695830(undefined4 param_1,int *param_2,int *param_3,int *param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(*(int *)(param_3[0x20] +
                           ((int)(param_2[4] + (param_2[4] >> 0x1f & 0xfU)) >> 4) * 4) +
                  ((int)(param_2[3] + (param_2[3] >> 0x1f & 0xfU)) >> 4) * 4);
  iVar2 = FUN_006a9020(*param_3,*param_2);
  if ((iVar2 == 1) && (iVar2 = FUN_006a9020(*param_3,param_2[1]), iVar2 == 1)) {
    *(float *)(iVar1 + 0x60) =
         *(float *)(iVar1 + 0x60) +
         *(float *)(param_3[0x18] + 0x228 + (*(uint *)(param_2[5] + 0x24) >> 10 & 0xff) * 4);
    *param_4 = *param_4 + 1;
    if ((float)*param_5 < *(float *)(iVar1 + 0x60)) {
      *param_5 = (int)*(float *)(iVar1 + 0x60);
    }
  }
  else if (*param_3 == *param_2) {
    FUN_00696080(param_3,param_2[3],param_2[4],(char)param_2[6]);
    *(float *)(iVar1 + 100) =
         *(float *)(iVar1 + 100) +
         *(float *)(param_3[0x18] + 0x228 + (*(uint *)(param_2[5] + 0x24) >> 10 & 0xff) * 4);
  }
  return;
}

