
void FUN_00694b20(int *param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(DAT_00920f04 + *param_1 * 4);
  iVar3 = *(int *)(*(int *)(*(int *)(iVar2 + 0x80) +
                           (param_1[4] / *(int *)(DAT_00920f04 + 0x88)) * 4) +
                  (param_1[3] / *(int *)(DAT_00920f04 + 0x88)) * 4);
  fVar1 = *(float *)(iVar3 + 100);
  if (*(float *)(iVar2 + 0x74) <= fVar1 && fVar1 != *(float *)(iVar2 + 0x74)) {
    *(undefined4 *)(iVar2 + 0x74) = *(undefined4 *)(iVar3 + 100);
  }
  return;
}

