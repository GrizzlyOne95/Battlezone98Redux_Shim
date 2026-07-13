
void FUN_004ce1c0(undefined4 param_1,byte *param_2)

{
  byte *pbVar1;
  byte bVar2;
  uint _Count;
  byte *local_2c;
  byte *local_28;
  byte *local_24;
  byte local_1c;
  undefined1 local_1b [19];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,0xff,0);
    local_24 = param_2;
    do {
      bVar2 = *local_24;
      local_24 = local_24 + 1;
    } while (bVar2 != 0);
    _Count = (int)local_24 - (int)(param_2 + 1);
    FUN_004ce0b0();
    strncpy((char *)&local_1c,DAT_0260db08,_Count);
    if (0x13 < _Count) {
      ___report_rangecheckfailure();
    }
    local_1b[_Count - 1] = 0;
    local_28 = &local_1c;
    local_2c = param_2;
    do {
      if (((*local_2c != *local_28) || (*local_2c == 0)) ||
         (pbVar1 = local_2c + 1, *pbVar1 != local_28[1])) break;
      local_2c = local_2c + 2;
      local_28 = local_28 + 2;
    } while (*pbVar1 != 0);
    FUN_004ce100();
  }
  FUN_0083e885();
  return;
}

