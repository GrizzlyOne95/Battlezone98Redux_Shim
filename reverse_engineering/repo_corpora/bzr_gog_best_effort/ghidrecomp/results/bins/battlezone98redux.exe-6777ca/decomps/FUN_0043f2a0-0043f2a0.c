
undefined4 FUN_0043f2a0(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (1 < param_1)) {
    uVar1 = 0;
  }
  else if ((&DAT_0260cad9)[param_1 * 0x310] == '\0') {
    FUN_007d6a70("OggManager::GetDSBuffer index %d is not playing",param_1);
    uVar1 = 0;
  }
  else if (*(int *)(&DAT_0260cae4 + param_1 * 0x310) == 0) {
    FUN_007d6a70("OggManager::GetDSBuffer index %d has no pStreamingSound",param_1);
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00439610(0);
  }
  return uVar1;
}

