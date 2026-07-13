
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_004f47c0(void)

{
  float10 fVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_00917b1c != 0) {
    fVar1 = (float10)FUN_00822da0();
    local_20 = (float)fVar1;
    if (10.0 <= local_20 - _DAT_00917b18) {
      DAT_00917b1c = 0;
    }
    else {
      uVar2 = FUN_00689eb0();
      local_c = 0x3f428f5c;
      fVar3 = -160.0;
      fVar4 = -180.0;
      local_10 = 2.0;
      FUN_00689ec0((float)uVar2 * 0.76,(float)((ulonglong)uVar2 >> 0x20) * 0.76,0xc3200000,
                   0xc3340000);
      local_8 = FUN_0041f870();
      local_28 = 0;
      local_24 = 0;
      FUN_00689ab0(DAT_0091552c,local_8,&local_28,&local_24);
      local_18 = (float)DAT_02cecf00 * 0.5 + fVar3;
      local_14 = (float)DAT_02cecf04 * 0.5 + fVar4;
      std::_Init_atomic_counter(DAT_0091552c,DAT_00917584);
      FUN_00689d10(DAT_0091552c,DAT_00917580,(int)(local_18 + local_10),(int)(local_14 + local_10),
                   local_8);
      std::_Init_atomic_counter(DAT_0091552c,DAT_0091755c);
      FUN_00689d10(DAT_0091552c,DAT_00917580,(int)local_18,(int)local_14,local_8);
      FUN_00689ec0(uVar2);
    }
  }
  return DAT_00917b1c != 0;
}

