
undefined4 FUN_0043f780(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (1 < param_1)) {
    uVar1 = 0;
  }
  else if ((&DAT_0260cad9)[param_1 * 0x310] == '\0') {
    FUN_007d6a70("OggManager::Release index %d is not playing",param_1);
    uVar1 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
    if (*(int *)(&DAT_0260cae4 + param_1 * 0x310) == 0) {
      FUN_007d6a70("UHOH - OggManager::Release index %d has NO pStreamingSound but is playing. Attempting to fix\n"
                   ,param_1);
    }
    else if (*(int *)(&DAT_0260cae4 + param_1 * 0x310) != 0) {
      if (*(undefined4 **)(&DAT_0260cae4 + param_1 * 0x310) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(&DAT_0260cae4 + param_1 * 0x310))(1);
      }
      *(undefined4 *)(&DAT_0260cae4 + param_1 * 0x310) = 0;
    }
    ov_clear(&DAT_0260cae8 + param_1 * 0x310);
    (&DAT_0260cad9)[param_1 * 0x310] = 0;
    memset(&DAT_0260cae8 + param_1 * 0x310,0,0x2d0);
    LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
    uVar1 = 1;
  }
  return uVar1;
}

