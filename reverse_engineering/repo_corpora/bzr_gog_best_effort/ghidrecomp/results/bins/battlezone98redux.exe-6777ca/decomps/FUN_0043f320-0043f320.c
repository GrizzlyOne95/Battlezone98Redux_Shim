
undefined4 FUN_0043f320(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 < 0) || (1 < param_1)) {
    uVar2 = 0;
  }
  else if ((&DAT_0260cad9)[param_1 * 0x310] == '\0') {
    FUN_007d6a70("OggManager::Play index %d is not playing",param_1);
    uVar2 = 0;
  }
  else if (*(int *)(&DAT_0260cae4 + param_1 * 0x310) == 0) {
    FUN_007d6a70("OggManager::Play index %d has no pStreamingSound",param_1);
    uVar2 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
    iVar1 = FUN_00416cf0();
    if (iVar1 < 0) {
      LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
      FUN_007d6a70("OggManager::Play index %d Reset() failed",param_1);
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_00439610(0);
      iVar1 = FUN_00416e10(uVar2,(&DAT_0260cad8)[param_1 * 0x310]);
      if (iVar1 < 0) {
        LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
        FUN_007d6a70("OggManager::Play index %d FillBufferWithSound() failed",param_1);
        uVar2 = 0;
      }
      else {
        iVar1 = FUN_00439650(0,1);
        if (iVar1 < 0) {
          LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
          FUN_007d6a70("OggManager::Play index %d Play() failed",param_1);
          uVar2 = 0;
        }
        else {
          LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + param_1 * 0x310));
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}

