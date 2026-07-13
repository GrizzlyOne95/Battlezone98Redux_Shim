
void __thiscall FUN_00439930(int param_1,void *param_2,size_t param_3,size_t *param_4)

{
  MMRESULT MVar1;
  uint local_5c;
  uint local_58;
  _MMIOINFO local_50;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(char *)(param_1 + 0x80) == '\0') {
    if (((*(int *)(param_1 + 4) != 0) && (param_2 != (void *)0x0)) && (param_4 != (size_t *)0x0)) {
      if (param_4 != (size_t *)0x0) {
        *param_4 = 0;
      }
      MVar1 = mmioGetInfo(*(HMMIO *)(param_1 + 4),&local_50,0);
      if (MVar1 == 0) {
        local_58 = param_3;
        if (*(uint *)(param_1 + 0xc) < param_3) {
          local_58 = *(uint *)(param_1 + 0xc);
        }
        *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - local_58;
        for (local_5c = 0; local_5c < local_58; local_5c = local_5c + 1) {
          if ((local_50.pchNext == local_50.pchEndRead) &&
             ((MVar1 = mmioAdvance(*(HMMIO *)(param_1 + 4),&local_50,0), MVar1 != 0 ||
              (local_50.pchNext == local_50.pchEndRead)))) goto LAB_00439b07;
          *(char *)((int)param_2 + local_5c) = *local_50.pchNext;
          local_50.pchNext = local_50.pchNext + 1;
        }
        MVar1 = mmioSetInfo(*(HMMIO *)(param_1 + 4),&local_50,0);
        if ((MVar1 == 0) && (param_4 != (size_t *)0x0)) {
          *param_4 = local_58;
        }
      }
    }
  }
  else if (*(int *)(param_1 + 0x88) != 0) {
    if (param_4 != (size_t *)0x0) {
      *param_4 = 0;
    }
    if ((uint)(*(int *)(param_1 + 0x84) + *(int *)(param_1 + 0x8c)) <
        *(int *)(param_1 + 0x88) + param_3) {
      param_3 = *(int *)(param_1 + 0x8c) - (*(int *)(param_1 + 0x88) - *(int *)(param_1 + 0x84));
    }
    memcpy(param_2,*(void **)(param_1 + 0x88),param_3);
    if (param_4 != (size_t *)0x0) {
      *param_4 = param_3;
    }
  }
LAB_00439b07:
  FUN_0083e885();
  return;
}

