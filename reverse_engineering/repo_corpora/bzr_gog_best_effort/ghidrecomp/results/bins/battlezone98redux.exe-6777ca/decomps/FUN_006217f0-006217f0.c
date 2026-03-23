
undefined4 FUN_006217f0(ushort param_1)

{
  undefined4 uVar1;
  
  if ((short)param_1 < 0) {
    uVar1 = 0;
  }
  else if (param_1 < 0x1000) {
    uVar1 = CONCAT22((short)param_1 >> 0xf,(ushort)(byte)(&DAT_00918850)[(short)param_1]);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

