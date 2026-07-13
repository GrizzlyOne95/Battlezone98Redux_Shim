
void FUN_00696a70(int param_1,int param_2,int param_3,int param_4,byte param_5,undefined1 param_6,
                 int param_7,undefined4 param_8,undefined4 param_9)

{
  int iVar1;
  
  param_3 = *(int *)(param_2 + 0x44) + param_3;
  param_4 = *(int *)(param_2 + 0x40) + param_4;
  if (((((-1 < param_3) && (-1 < param_4)) && (param_3 < *(int *)(DAT_00920f04 + 0x84))) &&
      ((param_4 < *(int *)(DAT_00920f04 + 0x80) &&
       (iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + param_4 * 4) + param_3 * 4),
       *(int *)(iVar1 + 0x14) != 0)))) &&
     ((*(int *)(iVar1 + 0x74) == 0 && ((*(int *)(iVar1 + 4) == 6 || (*(int *)(iVar1 + 4) == 1))))))
  {
    *(undefined4 *)(iVar1 + 0x74) = 2;
    *(undefined1 *)(iVar1 + 0x78) = param_6;
    if (param_7 < 0) {
      FUN_006a4ed0(*(undefined4 *)(iVar1 + 0x14),param_2,param_9);
    }
    else {
      FUN_006a4ed0(*(undefined4 *)(iVar1 + 0x14),param_2,param_9);
    }
    *(byte *)(param_2 + 0x78) = *(byte *)(param_2 + 0x78) | param_5;
  }
  return;
}

