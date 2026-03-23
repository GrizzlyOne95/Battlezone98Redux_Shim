
float10 FUN_006a4f60(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_3 + 0x44) * *(int *)(param_1 + 0x88) + *(int *)(param_1 + 0x88) / 2;
  iVar2 = *(int *)(param_3 + 0x40) * *(int *)(param_1 + 0x88) + *(int *)(param_1 + 0x88) / 2;
  return (float10)(SQRT((double)((*(int *)(param_2 + 4) - iVar1) * (*(int *)(param_2 + 4) - iVar1) +
                                (*(int *)(param_2 + 8) - iVar2) * (*(int *)(param_2 + 8) - iVar2)))
                  * 5.0);
}

