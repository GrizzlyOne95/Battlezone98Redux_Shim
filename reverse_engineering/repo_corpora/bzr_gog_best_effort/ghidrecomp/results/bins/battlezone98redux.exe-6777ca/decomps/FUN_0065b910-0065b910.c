
undefined4 __fastcall FUN_0065b910(int param_1)

{
  char cVar1;
  float10 fVar2;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  local_c = *(undefined4 *)(param_1 + 0xcc);
  local_8 = param_1;
  cVar1 = FUN_005c84d0(&local_c);
  if ((cVar1 == '\0') &&
     (fVar2 = (float10)FUN_005cced0(*(undefined4 *)(local_8 + 0xcc)), (float)fVar2 <= 0.0)) {
    *(undefined4 *)(local_8 + 0x180) = 100;
    fVar2 = (float10)FUN_004b1670("ch08lsed.des");
    FUN_0045c0f0((float)fVar2 + 2.0);
    return 1;
  }
  fVar2 = (float10)FUN_005c9800(*(undefined4 *)(local_8 + 200),"break_point",0);
  if ((float)fVar2 < 50.0) {
    *(undefined4 *)(local_8 + 0x68) = 0x40000000;
  }
  local_c = *(undefined4 *)(local_8 + 0xcc);
  cVar1 = FUN_005c84d0(&local_c);
  if ((cVar1 == '\0') && (*(float *)(local_8 + 0x68) == 0.0)) {
    FUN_004b1670();
    *(float *)(local_8 + 0x68) = (float)extraout_ST0 + 25.0;
  }
  else if ((*(float *)(local_8 + 0x68) <= 2.0) ||
          (FUN_004b1670(),
          (float)extraout_ST0_00 < *(float *)(local_8 + 0x68) ||
          (float)extraout_ST0_00 == *(float *)(local_8 + 0x68))) {
    if ((*(float *)(local_8 + 0x68) == 1.0) &&
       (FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 200)),
       100.0 < (float)extraout_ST0_02)) {
      FUN_00437d30("ch08005.wav");
      *(undefined4 *)(local_8 + 0x180) = 100;
      fVar2 = (float10)FUN_004b1670("ch08lsee.des");
      FUN_0045c0f0((float)fVar2 + 20.0);
      return 1;
    }
  }
  else {
    FUN_005c9780(*(undefined4 *)(local_8 + 0xcc),*(undefined4 *)(local_8 + 200));
    if (100.0 < (float)extraout_ST0_01) {
      FUN_00437d30("ch08005.wav");
      *(undefined4 *)(local_8 + 0x180) = 100;
      fVar2 = (float10)FUN_004b1670("ch08lseb.des");
      FUN_0045c0f0((float)fVar2 + 20.0);
      return 1;
    }
    *(undefined4 *)(local_8 + 0x68) = 0x3f800000;
  }
  local_10 = 0;
  while( true ) {
    if (3 < local_10) {
      return 0;
    }
    local_c = *(undefined4 *)(local_8 + 0xbc + local_10 * 4);
    cVar1 = FUN_005c84d0(&local_c);
    if (cVar1 == '\0') break;
    local_10 = local_10 + 1;
  }
  *(undefined4 *)(local_8 + 0x180) = 100;
  fVar2 = (float10)FUN_004b1670("ch08lsed.des");
  FUN_0045c0f0((float)fVar2 + 2.0);
  return 1;
}

