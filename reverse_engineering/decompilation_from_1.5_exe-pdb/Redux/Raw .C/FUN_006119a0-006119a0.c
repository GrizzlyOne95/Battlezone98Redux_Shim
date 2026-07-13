
undefined4 * __fastcall FUN_006119a0(undefined4 *param_1)

{
  undefined4 **ppuVar1;
  undefined4 *local_c;
  undefined4 *local_8;
  
  *param_1 = WeaponClass::vftable;
  ppuVar1 = &local_c;
  local_c = param_1;
  local_8 = param_1;
  FID_conflict__Immortalize<class_std::_Generic_error_category>(ppuVar1);
  FUN_0041fe40(ppuVar1);
  local_8[2] = local_8;
  local_8[3] = 0x5745504e;
  local_8[4] = "weapon";
  local_8[6] = 0;
  local_8[7] = 0;
  local_8[8] = 0;
  local_8[9] = 0;
  local_8[10] = 0;
  local_8[0xb] = 0;
  local_8[0xc] = 0;
  local_8[0xe] = 0;
  local_8[0xf] = 0;
  local_8[0x10] = 0;
  local_8[0x11] = 0;
  local_8[0x12] = 0;
  local_8[0x13] = 0;
  local_8[0x14] = 0;
  local_8[0x15] = 0;
  *(undefined1 *)(local_8 + 0x16) = 0;
  local_8[0x1a] = 0;
  local_8[0x1b] = 0;
  *(undefined1 *)(local_8 + 0x1e) = 0;
  *(undefined1 *)((int)local_8 + 0x79) = 0;
  return local_8;
}

