
undefined4 * __fastcall FUN_00481220(undefined4 *param_1)

{
  FUN_00586300();
  *param_1 = BulletClass::vftable;
  param_1[3] = 0x424c4c54;
  param_1[4] = "bullet";
  param_1[0x13] = 1;
  param_1[0x14] = 0x40a00000;
  param_1[0x16] = 0x41200000;
  *(undefined2 *)(param_1 + 0x17) = 1;
  param_1[0x15] = 0x43480000;
  return param_1;
}

