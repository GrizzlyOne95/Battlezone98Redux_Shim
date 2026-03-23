
void FUN_00821450(int param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  float10 fVar4;
  uint local_18;
  char *local_14;
  char *local_10;
  char *local_c;
  
  iVar1 = *(int *)(param_1 + 8);
  if (((*(uint *)(iVar1 + 0x5c) & 8) == 0) || (*(int *)(iVar1 + 0x20) != *(int *)(iVar1 + 0x10) + 1)
     ) {
    local_10 = (char *)(*(int *)(iVar1 + 0x20) * 0x58 + *(int *)(iVar1 + 0x28));
    local_18 = 0;
    for (local_c = param_2; *local_c != '\0'; local_c = local_c + 1) {
      FUN_00689a20(DAT_0091552c,(short)*local_c);
      local_18 = FUN_008445c0((double)(int)local_18 +
                              (double)(&DAT_008a2fd0)[-((int)local_18 >> 0x1f)]);
      if ((local_c == param_2 + *(int *)(iVar1 + 0x14)) || (*(uint *)(iVar1 + 8) < local_18)) {
        bVar2 = false;
        iVar3 = isspace((int)*local_c);
        if (iVar3 == 0) {
          for (local_14 = local_c; param_2 <= local_14; local_14 = local_14 + -1) {
            iVar3 = isspace((int)*local_14);
            if (iVar3 != 0) {
              local_c = local_14 + 1;
              break;
            }
          }
        }
        else {
          bVar2 = true;
        }
        strncpy(local_10,param_2,(int)local_c - (int)param_2);
        local_10[(int)local_c - (int)param_2] = '\0';
        fVar4 = (float10)FUN_00822da0();
        *(float *)(local_10 + 0x50) = (float)fVar4 + *(float *)(iVar1 + 0x54);
        *(undefined4 *)(local_10 + 0x54) = param_3;
        FUN_008213c0(iVar1);
        if (((*(uint *)(iVar1 + 0x5c) & 8) != 0) &&
           (*(int *)(iVar1 + 0x20) == *(int *)(iVar1 + 0x10) + 1)) {
          return;
        }
        local_10 = (char *)(*(int *)(iVar1 + 0x20) * 0x58 + *(int *)(iVar1 + 0x28));
        *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) | 0x80000000;
        param_2 = local_c;
        if (bVar2) {
          param_2 = local_c + 1;
        }
        local_18 = 0;
      }
    }
    if (*param_2 != '\0') {
      strncpy(local_10,param_2,*(size_t *)(iVar1 + 0x14));
      local_10[*(int *)(iVar1 + 0x14)] = '\0';
      fVar4 = (float10)FUN_00822da0();
      *(float *)(local_10 + 0x50) = (float)fVar4 + *(float *)(iVar1 + 0x54);
      *(undefined4 *)(local_10 + 0x54) = param_3;
      FUN_008213c0(iVar1);
      *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) | 0x80000000;
    }
  }
  return;
}

