
void FUN_006223a0(int param_1)

{
  uint *puVar1;
  UINT UVar2;
  MMRESULT MVar3;
  uint uVar4;
  uint local_1d8;
  joyinfoex_tag local_1d0;
  tagJOYCAPSA local_19c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = *(uint **)(param_1 + 0x70);
  if (DAT_008ec244 != 0) {
    FUN_006219b0();
  }
  if (puVar1 != (uint *)0x0) {
    uVar4 = *puVar1;
    UVar2 = joyGetNumDevs();
    if (uVar4 < UVar2) {
      memset(&local_19c,0,0x194);
      FUN_007d6a70("Calling JoyGetDevCaps from giddi_open \n");
      MVar3 = joyGetDevCapsA(uVar4,&local_19c,0x194);
      if ((MVar3 != 6) && (MVar3 != 0xb)) {
        local_1d0.dwSize = 0x34;
        local_1d0.dwFlags = 0x483;
        MVar3 = joyGetPosEx(uVar4,&local_1d0);
        if (MVar3 == 0) {
          puVar1[1] = 0x483;
          puVar1[2] = local_19c.wNumButtons;
          puVar1[3] = local_19c.wXmin;
          puVar1[9] = local_19c.wXmax;
          puVar1[4] = local_19c.wYmin;
          puVar1[10] = local_19c.wYmax;
          if ((local_19c.wCaps & 1) != 0) {
            puVar1[1] = puVar1[1] | 4;
            puVar1[5] = local_19c.wZmin;
            puVar1[0xb] = local_19c.wZmax;
          }
          if ((local_19c.wCaps & 2) != 0) {
            puVar1[1] = puVar1[1] | 8;
            puVar1[6] = local_19c.wRmin;
            puVar1[0xc] = local_19c.wRmax;
          }
          if ((local_19c.wCaps & 4) != 0) {
            puVar1[1] = puVar1[1] | 0x10;
            puVar1[7] = local_19c.wUmin;
            puVar1[0xd] = local_19c.wUmax;
          }
          if ((local_19c.wCaps & 8) != 0) {
            puVar1[1] = puVar1[1] | 0x20;
            puVar1[8] = local_19c.wVmin;
            puVar1[0xe] = local_19c.wVmax;
          }
          local_1d8 = local_19c.wNumButtons;
          if ((local_19c.wCaps & 0x10) != 0) {
            puVar1[1] = puVar1[1] | 0x40;
            puVar1[0xf] = (int)local_19c.wNumButtons >> 5;
            puVar1[0x13] = 1 << ((byte)local_19c.wNumButtons & 0x1f);
            puVar1[0x10] = (int)(local_19c.wNumButtons + 1) >> 5;
            puVar1[0x14] = 1 << ((byte)(local_19c.wNumButtons + 1) & 0x1f);
            puVar1[0x11] = (int)(local_19c.wNumButtons + 2) >> 5;
            puVar1[0x15] = 1 << ((byte)(local_19c.wNumButtons + 2) & 0x1f);
            puVar1[0x12] = (int)(local_19c.wNumButtons + 3) >> 5;
            puVar1[0x16] = 1 << ((byte)(local_19c.wNumButtons + 3) & 0x1f);
            local_1d8 = local_19c.wNumButtons + 4;
          }
          puVar1[0x17] = puVar1[3] * 3 + puVar1[9] >> 2;
          puVar1[0x18] = (int)local_1d8 >> 5;
          puVar1[0x19] = 1 << ((byte)local_1d8 & 0x1f);
          puVar1[0x1a] = puVar1[3] + puVar1[9] * 3 >> 2;
          puVar1[0x1b] = (int)(local_1d8 + 1) >> 5;
          puVar1[0x1c] = 1 << ((byte)(local_1d8 + 1) & 0x1f);
          puVar1[0x1d] = puVar1[4] * 3 + puVar1[10] >> 2;
          puVar1[0x1e] = (int)(local_1d8 + 2) >> 5;
          puVar1[0x1f] = 1 << ((byte)(local_1d8 + 2) & 0x1f);
          puVar1[0x20] = puVar1[4] + puVar1[10] * 3 >> 2;
          puVar1[0x21] = (int)(local_1d8 + 3) >> 5;
          puVar1[0x22] = 1 << ((byte)(local_1d8 + 3) & 0x1f);
          uVar4 = local_1d8 + 4;
          if ((local_19c.wCaps & 1) != 0) {
            puVar1[0x23] = puVar1[5] * 3 + puVar1[0xb] >> 2;
            puVar1[0x24] = (int)uVar4 >> 5;
            puVar1[0x25] = 1 << ((byte)uVar4 & 0x1f);
            puVar1[0x26] = puVar1[5] + puVar1[0xb] * 3 >> 2;
            puVar1[0x27] = (int)(local_1d8 + 5) >> 5;
            puVar1[0x28] = 1 << ((byte)(local_1d8 + 5) & 0x1f);
            uVar4 = local_1d8 + 6;
          }
          local_1d8 = uVar4;
          if ((local_19c.wCaps & 2) != 0) {
            puVar1[0x29] = puVar1[6] * 3 + puVar1[0xc] >> 2;
            puVar1[0x2a] = (int)local_1d8 >> 5;
            puVar1[0x2b] = 1 << ((byte)local_1d8 & 0x1f);
            puVar1[0x2c] = puVar1[6] + puVar1[0xc] * 3 >> 2;
            puVar1[0x2d] = (int)(local_1d8 + 1) >> 5;
            puVar1[0x2e] = 1 << ((byte)(local_1d8 + 1) & 0x1f);
            local_1d8 = local_1d8 + 2;
          }
          if ((local_19c.wCaps & 4) != 0) {
            puVar1[0x2f] = puVar1[7] * 3 + puVar1[0xd] >> 2;
            puVar1[0x30] = (int)local_1d8 >> 5;
            puVar1[0x31] = 1 << ((byte)local_1d8 & 0x1f);
            puVar1[0x32] = puVar1[7] + puVar1[0xd] * 3 >> 2;
            puVar1[0x33] = (int)(local_1d8 + 1) >> 5;
            puVar1[0x34] = 1 << ((byte)(local_1d8 + 1) & 0x1f);
            local_1d8 = local_1d8 + 2;
          }
          if ((local_19c.wCaps & 8) != 0) {
            puVar1[0x35] = puVar1[8] * 3 + puVar1[0xe] >> 2;
            puVar1[0x36] = (int)local_1d8 >> 5;
            puVar1[0x37] = 1 << ((byte)local_1d8 & 0x1f);
            puVar1[0x38] = puVar1[8] + puVar1[0xe] * 3 >> 2;
            puVar1[0x39] = (int)(local_1d8 + 1) >> 5;
            puVar1[0x3a] = 1 << ((byte)(local_1d8 + 1) & 0x1f);
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

