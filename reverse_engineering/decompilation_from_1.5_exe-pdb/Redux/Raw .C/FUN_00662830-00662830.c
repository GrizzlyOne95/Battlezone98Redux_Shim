
void FUN_00662830(int param_1,uint param_2,uint param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int local_2c;
  uint local_28;
  uint local_24;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  iVar1 = (int)(param_2 + ((int)param_2 >> 0x1f & 0xfU)) >> 4;
  local_8 = param_3;
  local_c = param_3;
  local_10 = param_3;
  local_14 = param_3;
  uVar11 = 0x239b961b;
  uVar10 = 0xab0e9789;
  uVar9 = 0x38b34ae5;
  uVar8 = 0xa1e38b93;
  iVar6 = iVar1 * 0x10 + param_1;
  for (local_2c = -iVar1; local_2c != 0; local_2c = local_2c + 1) {
    iVar2 = FUN_006627e0(iVar6,local_2c << 2);
    iVar3 = FUN_006627e0(iVar6,local_2c * 4 + 1);
    iVar4 = FUN_006627e0(iVar6,local_2c * 4 + 2);
    iVar5 = FUN_006627e0(iVar6,local_2c * 4 + 3);
    local_8 = local_8 ^ (iVar2 * -0x34f28000 | (uint)(iVar2 * 0x239b961b) >> 0x11) * -0x54f16877;
    local_8 = ((local_8 << 0x13 | local_8 >> 0xd) + local_c) * 5 + 0x561ccd1b;
    local_c = local_c ^ (iVar3 * -0x68770000 | (uint)(iVar3 * -0x54f16877) >> 0x10) * 0x38b34ae5;
    local_c = ((local_c << 0x11 | local_c >> 0xf) + local_10) * 5 + 0xbcaa747;
    local_10 = local_10 ^ (iVar4 * -0x6a360000 | (uint)(iVar4 * 0x38b34ae5) >> 0xf) * -0x5e1c746d;
    local_10 = ((local_10 << 0xf | local_10 >> 0x11) + local_14) * 5 + 0x96cd1c35;
    local_14 = local_14 ^ (iVar5 * 0x2e4c0000 | (uint)(iVar5 * -0x5e1c746d) >> 0xe) * 0x239b961b;
    local_14 = ((local_14 << 0xd | local_14 >> 0x13) + local_8) * 5 + 0x32ac3b17;
  }
  pbVar7 = (byte *)(iVar1 * 0x10 + param_1);
  local_24 = 0;
  local_1c = 0;
  local_18 = 0;
  local_28 = 0;
  switch(param_2 & 0xf) {
  case 0xf:
    local_28 = (uint)pbVar7[0xe] << 0x10;
  case 0xe:
    local_28 = (uint)pbVar7[0xd] << 8 ^ local_28;
  case 0xd:
    local_14 = local_14 ^
               ((pbVar7[0xc] ^ local_28) * 0x2e4c0000 |
               (pbVar7[0xc] ^ local_28) * -0x5e1c746d >> 0xe) * 0x239b961b;
  case 0xc:
    local_18 = (uint)pbVar7[0xb] << 0x18;
  case 0xb:
    local_18 = (uint)pbVar7[10] << 0x10 ^ local_18;
  case 10:
    local_18 = (uint)pbVar7[9] << 8 ^ local_18;
  case 9:
    local_10 = local_10 ^
               ((pbVar7[8] ^ local_18) * -0x6a360000 | (pbVar7[8] ^ local_18) * 0x38b34ae5 >> 0xf) *
               -0x5e1c746d;
  case 8:
    local_1c = (uint)pbVar7[7] << 0x18;
  case 7:
    local_1c = (uint)pbVar7[6] << 0x10 ^ local_1c;
  case 6:
    local_1c = (uint)pbVar7[5] << 8 ^ local_1c;
  case 5:
    local_c = local_c ^ ((pbVar7[4] ^ local_1c) * -0x68770000 |
                        (pbVar7[4] ^ local_1c) * -0x54f16877 >> 0x10) * 0x38b34ae5;
  case 4:
    local_24 = (uint)pbVar7[3] << 0x18;
  case 3:
    local_24 = (uint)pbVar7[2] << 0x10 ^ local_24;
  case 2:
    local_24 = (uint)pbVar7[1] << 8 ^ local_24;
  case 1:
    local_8 = local_8 ^ ((*pbVar7 ^ local_24) * -0x34f28000 |
                        (*pbVar7 ^ local_24) * 0x239b961b >> 0x11) * -0x54f16877;
  default:
    iVar1 = (local_8 ^ param_2) + (local_c ^ param_2) + (local_10 ^ param_2) + (local_14 ^ param_2);
    iVar6 = FUN_006627f0(iVar1,uVar8,uVar9,uVar10,uVar11);
    iVar2 = FUN_006627f0((local_c ^ param_2) + iVar1);
    iVar3 = FUN_006627f0((local_10 ^ param_2) + iVar1);
    iVar1 = FUN_006627f0((local_14 ^ param_2) + iVar1);
    iVar6 = iVar6 + iVar2 + iVar3 + iVar1;
    *param_4 = iVar6;
    param_4[1] = iVar2 + iVar6;
    param_4[2] = iVar3 + iVar6;
    param_4[3] = iVar1 + iVar6;
    return;
  }
}

