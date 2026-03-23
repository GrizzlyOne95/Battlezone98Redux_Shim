
undefined4 __fastcall FUN_00439b20(int param_1)

{
  MMRESULT MVar1;
  char local_c [4];
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x7c) == 1) {
    mmioClose(*(HMMIO *)(param_1 + 4),0);
    *(undefined4 *)(local_8 + 4) = 0;
  }
  else {
    *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x34) | 0x10000000;
    if (*(int *)(param_1 + 4) == 0) {
      return 0x800401f0;
    }
    MVar1 = mmioSetInfo(*(HMMIO *)(param_1 + 4),(LPCMMIOINFO)(param_1 + 0x34),0);
    if (MVar1 != 0) {
      return 0x80004005;
    }
    MVar1 = mmioAscend(*(HMMIO *)(local_8 + 4),(LPMMCKINFO)(local_8 + 8),0);
    if (MVar1 != 0) {
      return 0x80004005;
    }
    MVar1 = mmioAscend(*(HMMIO *)(local_8 + 4),(LPMMCKINFO)(local_8 + 0x1c),0);
    if (MVar1 != 0) {
      return 0x80004005;
    }
    mmioSeek(*(HMMIO *)(local_8 + 4),0,0);
    MVar1 = mmioDescend(*(HMMIO *)(local_8 + 4),(LPMMCKINFO)(local_8 + 0x1c),(MMCKINFO *)0x0,0);
    if (MVar1 != 0) {
      return 0x80004005;
    }
    *(undefined4 *)(local_8 + 8) = 0x74636166;
    MVar1 = mmioDescend(*(HMMIO *)(local_8 + 4),(LPMMCKINFO)(local_8 + 8),
                        (MMCKINFO *)(local_8 + 0x1c),0x10);
    if (MVar1 == 0) {
      local_c[0] = '\0';
      local_c[1] = '\0';
      local_c[2] = '\0';
      local_c[3] = '\0';
      mmioWrite(*(HMMIO *)(local_8 + 4),local_c,4);
      mmioAscend(*(HMMIO *)(local_8 + 4),(LPMMCKINFO)(local_8 + 8),0);
    }
    MVar1 = mmioAscend(*(HMMIO *)(local_8 + 4),(LPMMCKINFO)(local_8 + 0x1c),0);
    if (MVar1 != 0) {
      return 0x80004005;
    }
    mmioClose(*(HMMIO *)(local_8 + 4),0);
    *(undefined4 *)(local_8 + 4) = 0;
  }
  return 0;
}

