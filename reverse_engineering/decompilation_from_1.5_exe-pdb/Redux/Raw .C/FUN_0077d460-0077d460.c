
void FUN_0077d460(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_10 [12];
  
  if ((*(int *)(param_1 + 0x84) != 0x51) && (*(int *)(param_1 + 0x84) != 0xb)) {
    puVar1 = (undefined4 *)FUN_004e0040(local_10,param_1);
    *(undefined4 *)(param_1 + 0xa0) = *puVar1;
    *(undefined4 *)(param_1 + 0xa4) = puVar1[1];
    *(undefined4 *)(param_1 + 0xa8) = puVar1[2];
    fVar2 = (float10)FUN_0062e590(param_1,*(undefined4 *)(param_1 + 0xa0),
                                  *(undefined4 *)(param_1 + 0xa4),*(undefined4 *)(param_1 + 0xa8));
    *(float *)(param_1 + 0xac) = (float)fVar2;
  }
  if (DAT_02cd9440 == 0) {
    DAT_02cd9440 = param_1;
  }
  else {
    *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(DAT_02cd9440 + 0x7c);
    *(int *)(DAT_02cd9440 + 0x7c) = param_1;
  }
  return;
}

