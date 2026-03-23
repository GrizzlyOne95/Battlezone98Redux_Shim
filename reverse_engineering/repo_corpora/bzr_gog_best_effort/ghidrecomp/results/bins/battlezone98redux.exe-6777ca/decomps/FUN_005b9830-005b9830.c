
undefined4 * __fastcall FUN_005b9830(undefined4 *param_1)

{
  FUN_0047ff00();
  *param_1 = RepairDepotClass::vftable;
  param_1[5] = 0x52444550;
  param_1[6] = "repairdepot";
  param_1[0x4f] = 0x3c;
  param_1[0x50] = 0x40;
  param_1[0x58] = 0x41f00000;
  param_1[0x59] = 0x3f800000;
  param_1[0x5a] = 0x42c80000;
  strncpy((char *)(param_1 + 0x5b),"repair.wav",0x10);
  return param_1;
}

