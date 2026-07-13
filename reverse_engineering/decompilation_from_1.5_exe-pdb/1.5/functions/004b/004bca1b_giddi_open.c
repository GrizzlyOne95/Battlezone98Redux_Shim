/*
 * Entry: 004bca1b
 * Name: giddi_open
 * Namespace: Global
 * Signature: int giddi_open(_GIDDI_DEVDESC * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl giddi_open(_GIDDI_DEVDESC *param_1)

{
  int *piVar1;
  MMRESULT MVar2;
  int iVar3;
  int iVar4;
  joyinfoex_tag local_1d0;
  tagJOYCAPSA local_19c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_19c.szOEMVxD + 0x94);
  piVar1 = param_1->data;
  generate_remap();
  if (piVar1 != (int *)0x0) {
    mHdl = Mono_Register(Joy_Refresh);
    iVar3 = *piVar1;
    MVar2 = joyGetDevCapsA((uint)(iVar3 != 0),&local_19c,0x194);
    if ((MVar2 != 6) && (MVar2 != 0xb)) {
      local_1d0.dwSize = 0x34;
      local_1d0.dwFlags = 0x483;
      MVar2 = joyGetPosEx((uint)(iVar3 != 0),&local_1d0);
      if (MVar2 == 0) {
        piVar1[1] = 0x483;
        piVar1[2] = local_19c.wNumButtons;
        piVar1[3] = local_19c.wXmin;
        piVar1[9] = local_19c.wXmax;
        piVar1[4] = local_19c.wYmin;
        piVar1[10] = local_19c.wYmax;
        if (((byte)local_19c.wCaps & 1) != 0) {
          piVar1[1] = 0x487;
          piVar1[5] = local_19c.wZmin;
          piVar1[0xb] = local_19c.wZmax;
        }
        if (((byte)local_19c.wCaps & 2) != 0) {
          piVar1[1] = piVar1[1] | 8;
          piVar1[6] = local_19c.wRmin;
          piVar1[0xc] = local_19c.wRmax;
        }
        if (((byte)local_19c.wCaps & 4) != 0) {
          piVar1[1] = piVar1[1] | 0x10;
          piVar1[7] = local_19c.wUmin;
          piVar1[0xd] = local_19c.wUmax;
        }
        if (((byte)local_19c.wCaps & 8) != 0) {
          piVar1[1] = piVar1[1] | 0x20;
          piVar1[8] = local_19c.wVmin;
          piVar1[0xe] = local_19c.wVmax;
        }
        if (((byte)local_19c.wCaps & 0x10) != 0) {
          piVar1[1] = piVar1[1] | 0x40;
          piVar1[0xf] = (int)local_19c.wNumButtons >> 5;
          piVar1[0x10] = (int)(local_19c.wNumButtons + 1) >> 5;
          piVar1[0x13] = 1 << ((byte)local_19c.wNumButtons & 0x1f);
          piVar1[0x11] = (int)(local_19c.wNumButtons + 2) >> 5;
          piVar1[0x14] = 1 << ((byte)(local_19c.wNumButtons + 1) & 0x1f);
          iVar3 = local_19c.wNumButtons + 3;
          piVar1[0x12] = iVar3 >> 5;
          piVar1[0x15] = 1 << ((byte)(local_19c.wNumButtons + 2) & 0x1f);
          local_19c.wNumButtons = local_19c.wNumButtons + 4;
          piVar1[0x16] = 1 << ((byte)iVar3 & 0x1f);
        }
        piVar1[0x17] = (uint)(piVar1[3] * 3 + piVar1[9]) >> 2;
        piVar1[0x18] = (int)local_19c.wNumButtons >> 5;
        piVar1[0x1b] = (int)(local_19c.wNumButtons + 1) >> 5;
        piVar1[0x19] = 1 << ((byte)local_19c.wNumButtons & 0x1f);
        piVar1[0x1a] = (uint)(piVar1[9] * 3 + piVar1[3]) >> 2;
        piVar1[0x1c] = 1 << ((byte)(local_19c.wNumButtons + 1) & 0x1f);
        piVar1[0x1d] = (uint)(piVar1[4] * 3 + piVar1[10]) >> 2;
        piVar1[0x1e] = (int)(local_19c.wNumButtons + 2) >> 5;
        piVar1[0x21] = (int)(local_19c.wNumButtons + 3) >> 5;
        piVar1[0x1f] = 1 << ((byte)(local_19c.wNumButtons + 2) & 0x1f);
        piVar1[0x20] = (uint)(piVar1[10] * 3 + piVar1[4]) >> 2;
        iVar3 = local_19c.wNumButtons + 4;
        piVar1[0x22] = 1 << ((byte)(local_19c.wNumButtons + 3) & 0x1f);
        if (((byte)local_19c.wCaps & 1) != 0) {
          piVar1[0x23] = (uint)(piVar1[5] * 3 + piVar1[0xb]) >> 2;
          piVar1[0x24] = iVar3 >> 5;
          piVar1[0x27] = (int)(local_19c.wNumButtons + 5) >> 5;
          piVar1[0x25] = 1 << ((byte)iVar3 & 0x1f);
          piVar1[0x26] = (uint)(piVar1[0xb] * 3 + piVar1[5]) >> 2;
          iVar3 = local_19c.wNumButtons + 6;
          piVar1[0x28] = 1 << ((byte)(local_19c.wNumButtons + 5) & 0x1f);
        }
        if (((byte)local_19c.wCaps & 2) != 0) {
          piVar1[0x29] = (uint)(piVar1[6] * 3 + piVar1[0xc]) >> 2;
          piVar1[0x2a] = iVar3 >> 5;
          iVar4 = iVar3 + 1;
          piVar1[0x2d] = iVar4 >> 5;
          piVar1[0x2b] = 1 << ((byte)iVar3 & 0x1f);
          piVar1[0x2c] = (uint)(piVar1[0xc] * 3 + piVar1[6]) >> 2;
          iVar3 = iVar3 + 2;
          piVar1[0x2e] = 1 << ((byte)iVar4 & 0x1f);
        }
        if (((byte)local_19c.wCaps & 4) != 0) {
          piVar1[0x2f] = (uint)(piVar1[7] * 3 + piVar1[0xd]) >> 2;
          piVar1[0x30] = iVar3 >> 5;
          iVar4 = iVar3 + 1;
          piVar1[0x33] = iVar4 >> 5;
          piVar1[0x31] = 1 << ((byte)iVar3 & 0x1f);
          piVar1[0x32] = (uint)(piVar1[0xd] * 3 + piVar1[7]) >> 2;
          iVar3 = iVar3 + 2;
          piVar1[0x34] = 1 << ((byte)iVar4 & 0x1f);
        }
        if (((byte)local_19c.wCaps & 8) != 0) {
          piVar1[0x35] = (uint)(piVar1[8] * 3 + piVar1[0xe]) >> 2;
          piVar1[0x36] = iVar3 >> 5;
          piVar1[0x39] = iVar3 + 1 >> 5;
          piVar1[0x37] = 1 << ((byte)iVar3 & 0x1f);
          piVar1[0x38] = (uint)(piVar1[0xe] * 3 + piVar1[8]) >> 2;
          piVar1[0x3a] = 1 << ((byte)(iVar3 + 1) & 0x1f);
        }
        return 0;
      }
    }
  }
  return 1;
}
