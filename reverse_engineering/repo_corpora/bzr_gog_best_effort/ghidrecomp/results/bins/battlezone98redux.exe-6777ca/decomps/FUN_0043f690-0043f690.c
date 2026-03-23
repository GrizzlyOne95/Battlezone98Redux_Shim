
undefined4 FUN_0043f690(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (1 < param_1)) {
    uVar1 = 0;
  }
  else if ((&DAT_0260cad9)[param_1 * 0x310] == '\0') {
    FUN_007d6a70("OggManager::Resume index %d is not playing",param_1);
    uVar1 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
    if (*(int *)(&DAT_0260cae4 + param_1 * 0x310) == 0) {
      FUN_007d6a70("UHOH - OggManager::Resume index %d has NO pStreamingSound but is playing. Attempting to fix\n"
                   ,param_1);
      ov_clear(&DAT_0260cae8 + param_1 * 0x310);
      (&DAT_0260cad9)[param_1 * 0x310] = 0;
      memset(&DAT_0260cae8 + param_1 * 0x310,0,0x2d0);
    }
    else {
      FUN_00439650(0,1);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
    uVar1 = 1;
  }
  return uVar1;
}

