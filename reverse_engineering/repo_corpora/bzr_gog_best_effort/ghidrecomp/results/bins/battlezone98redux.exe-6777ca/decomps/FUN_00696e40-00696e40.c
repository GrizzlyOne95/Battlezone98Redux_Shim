
void FUN_00696e40(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_1 == 1) {
    if (param_4 != 0) {
      param_2 = param_2 / *(int *)(DAT_00920f04 + 0x88);
      param_3 = param_3 / *(int *)(DAT_00920f04 + 0x88);
    }
    iVar1 = *(int *)(*(int *)(*(int *)(*(int *)(DAT_00920f04 + 4) + 0x80) + param_3 * 4) +
                    param_2 * 4);
    if ((((*(int *)(iVar1 + 0x74) == 1) && (*(char *)(iVar1 + 0x78) != '\0')) &&
        (*(int *)(iVar1 + 0x50) < 1)) && (*(float *)(iVar1 + 0x60) <= 1e-05)) {
      FUN_00696d10(*(int *)(DAT_00920f04 + 4),iVar1);
      *(undefined4 *)(iVar1 + 0x74) = 0;
    }
  }
  return;
}

