
undefined4 * __fastcall FUN_004cad80(undefined4 *param_1)

{
  undefined4 **ppuVar1;
  undefined4 *local_c;
  undefined4 *local_8;
  
  *param_1 = ExplosionClass::vftable;
  ppuVar1 = &local_c;
  local_c = param_1;
  local_8 = param_1;
  FID_conflict__Immortalize<class_std::_Generic_error_category>(ppuVar1);
  FUN_0041fe40(ppuVar1);
  local_8[2] = 0x4558504c;
  local_8[3] = "explosion";
  local_8[4] = 0;
  local_8[5] = 0;
  local_8[10] = local_8;
  local_8[0xb] = 0;
  local_8[6] = 0;
  local_8[7] = 0;
  local_8[8] = 0;
  local_8[9] = 0;
  local_8[0xc] = 0;
  local_8[0xd] = 0;
  local_8[0xe] = 0x44160000;
  local_8[0xf] = 0;
  local_8[0x10] = 0;
  local_8[0x11] = 0;
  local_8[0x12] = 0;
  local_8[0x13] = 0;
  local_8[0x14] = 0;
  local_8[0x15] = 0;
  *(undefined2 *)(local_8 + 0x16) = 0;
  local_8[0x17] = 0;
  local_8[0x19] = 0;
  local_8[0x1a] = 0;
  memset(local_8 + 0x8b,0,0x40);
  memset(local_8 + 0x1b,0,0x40);
  memset(local_8 + 0x2b,0,0xc0);
  memset(local_8 + 0x5b,0,0xc0);
  return local_8;
}

