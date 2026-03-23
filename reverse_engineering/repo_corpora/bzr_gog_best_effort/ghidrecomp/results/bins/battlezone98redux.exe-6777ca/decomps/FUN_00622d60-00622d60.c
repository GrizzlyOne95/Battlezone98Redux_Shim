
void FUN_00622d60(UINT *param_1,undefined4 *param_2,DWORD *param_3)

{
  int iVar1;
  MMRESULT MVar2;
  undefined4 uVar3;
  int local_40;
  joyinfoex_tag local_3c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((param_3 != (DWORD *)0x0) && (param_2 != (undefined4 *)0x0)) {
    for (local_40 = 0; local_40 < 6; local_40 = local_40 + 1) {
      param_2[local_40] = 0;
    }
    param_3[1] = 0;
    *param_3 = 0;
    iVar1 = FUN_00437540(&DAT_02cecee0);
    if (iVar1 != 0) {
      memset(&local_3c,0,0x34);
      local_3c.dwFlags = param_1[1];
      local_3c.dwSize = 0x34;
      MVar2 = joyGetPosEx(*param_1,&local_3c);
      switch(MVar2) {
      case 0:
        param_1[0x3b] = 0;
        *param_3 = local_3c.dwButtons;
        if ((param_1[1] & 0x40) != 0) {
          if (local_3c.dwPOV < 0x4651) {
            if (local_3c.dwPOV == 18000) {
              param_3[param_1[0x11]] = param_3[param_1[0x11]] | param_1[0x15];
            }
            else if (local_3c.dwPOV < 0x2329) {
              if (local_3c.dwPOV == 9000) {
                param_3[param_1[0x10]] = param_3[param_1[0x10]] | param_1[0x14];
              }
              else if (local_3c.dwPOV == 0) {
                param_3[param_1[0xf]] = param_3[param_1[0xf]] | param_1[0x13];
              }
              else if (local_3c.dwPOV == 0x1194) {
                param_3[param_1[0x10]] = param_3[param_1[0x10]] | param_1[0x14];
                param_3[param_1[0xf]] = param_3[param_1[0xf]] | param_1[0x13];
              }
            }
            else if (local_3c.dwPOV == 0x34bc) {
              param_3[param_1[0x10]] = param_3[param_1[0x10]] | param_1[0x14];
              param_3[param_1[0x11]] = param_3[param_1[0x11]] | param_1[0x15];
            }
          }
          else if (local_3c.dwPOV == 0x57e4) {
            param_3[param_1[0x12]] = param_3[param_1[0x12]] | param_1[0x16];
            param_3[param_1[0x11]] = param_3[param_1[0x11]] | param_1[0x15];
          }
          else if (local_3c.dwPOV == 27000) {
            param_3[param_1[0x12]] = param_3[param_1[0x12]] | param_1[0x16];
          }
          else if (local_3c.dwPOV == 0x7b0c) {
            param_3[param_1[0x12]] = param_3[param_1[0x12]] | param_1[0x16];
            param_3[param_1[0xf]] = param_3[param_1[0xf]] | param_1[0x13];
          }
        }
        uVar3 = FUN_00621b50(local_3c.dwXpos,param_1[3],param_1[9]);
        *param_2 = uVar3;
        if (local_3c.dwXpos < param_1[0x17]) {
          param_3[param_1[0x18]] = param_3[param_1[0x18]] | param_1[0x19];
        }
        if (param_1[0x1a] < local_3c.dwXpos) {
          param_3[param_1[0x1b]] = param_3[param_1[0x1b]] | param_1[0x1c];
        }
        uVar3 = FUN_00621b50(local_3c.dwYpos,param_1[4],param_1[10]);
        param_2[1] = uVar3;
        if (local_3c.dwYpos < param_1[0x1d]) {
          param_3[param_1[0x1e]] = param_3[param_1[0x1e]] | param_1[0x1f];
        }
        if (param_1[0x20] < local_3c.dwYpos) {
          param_3[param_1[0x21]] = param_3[param_1[0x21]] | param_1[0x22];
        }
        local_40 = 2;
        iVar1 = local_40;
        if ((param_1[1] & 4) != 0) {
          uVar3 = FUN_00621b50(local_3c.dwZpos,param_1[5],param_1[0xb]);
          param_2[2] = uVar3;
          local_40 = 3;
          if (local_3c.dwZpos < param_1[0x23]) {
            param_3[param_1[0x24]] = param_3[param_1[0x24]] | param_1[0x25];
          }
          iVar1 = 3;
          if (param_1[0x26] < local_3c.dwZpos) {
            param_3[param_1[0x27]] = param_3[param_1[0x27]] | param_1[0x28];
            iVar1 = local_40;
          }
        }
        local_40 = iVar1;
        if ((param_1[1] & 8) != 0) {
          uVar3 = FUN_00621b50(local_3c.dwRpos,param_1[6],param_1[0xc]);
          param_2[local_40] = uVar3;
          local_40 = local_40 + 1;
          if (local_3c.dwRpos < param_1[0x29]) {
            param_3[param_1[0x2a]] = param_3[param_1[0x2a]] | param_1[0x2b];
          }
          if (param_1[0x2c] < local_3c.dwRpos) {
            param_3[param_1[0x2d]] = param_3[param_1[0x2d]] | param_1[0x2e];
          }
        }
        if ((param_1[1] & 0x10) != 0) {
          uVar3 = FUN_00621b50(local_3c.dwUpos,param_1[7],param_1[0xd]);
          param_2[local_40] = uVar3;
          local_40 = local_40 + 1;
          if (local_3c.dwUpos < param_1[0x2f]) {
            param_3[param_1[0x30]] = param_3[param_1[0x30]] | param_1[0x31];
          }
          if (param_1[0x32] < local_3c.dwUpos) {
            param_3[param_1[0x33]] = param_3[param_1[0x33]] | param_1[0x34];
          }
        }
        if ((param_1[1] & 0x20) != 0) {
          uVar3 = FUN_00621b50(local_3c.dwVpos,param_1[8],param_1[0xe]);
          param_2[local_40] = uVar3;
          if (local_3c.dwVpos < param_1[0x35]) {
            param_3[param_1[0x36]] = param_3[param_1[0x36]] | param_1[0x37];
          }
          if (param_1[0x38] < local_3c.dwVpos) {
            param_3[param_1[0x39]] = param_3[param_1[0x39]] | param_1[0x3a];
          }
        }
        break;
      default:
        if (param_1[0x3b] == 0) {
          uVar3 = FUN_0081cb40("multi_error","joystick5");
          FUN_007d6700(uVar3);
          param_1[0x3b] = 1;
        }
        break;
      case 2:
        if (param_1[0x3b] == 0) {
          uVar3 = FUN_0081cb40("multi_error","joystick3");
          FUN_007d6700(uVar3);
          param_1[0x3b] = 1;
        }
        break;
      case 6:
        if (param_1[0x3b] == 0) {
          uVar3 = FUN_0081cb40("multi_error","joystick1");
          FUN_007d6700(uVar3);
          param_1[0x3b] = 1;
        }
        break;
      case 0xb:
        if (param_1[0x3b] == 0) {
          uVar3 = FUN_0081cb40("multi_error","joystick2");
          FUN_007d6700(uVar3);
          param_1[0x3b] = 1;
        }
        break;
      case 0xa7:
        if (param_1[0x3b] == 0) {
          uVar3 = FUN_0081cb40("multi_error","joystick4");
          FUN_007d6700(uVar3);
          param_1[0x3b] = 1;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

