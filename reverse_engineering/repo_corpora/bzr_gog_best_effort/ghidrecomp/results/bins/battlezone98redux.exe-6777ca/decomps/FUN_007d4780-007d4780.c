
void __fastcall FUN_007d4780(undefined4 param_1)

{
  undefined4 uVar1;
  undefined *local_43c;
  uint local_438;
  uint local_430;
  undefined1 local_428 [528];
  undefined *local_218 [17];
  undefined *puStack_1d4;
  undefined4 uStack_16c;
  undefined *puStack_164;
  undefined4 uStack_160;
  undefined *puStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_12c;
  undefined *puStack_11c;
  undefined4 uStack_114;
  undefined *puStack_10c;
  undefined *puStack_108;
  undefined *puStack_104;
  undefined *puStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined *puStack_c8;
  undefined *puStack_c0;
  undefined *puStack_b4;
  undefined4 uStack_a4;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined *puStack_80;
  undefined *puStack_6c;
  undefined4 uStack_64;
  undefined *puStack_5c;
  undefined *puStack_54;
  undefined *puStack_44;
  undefined *puStack_34;
  undefined *puStack_28;
  undefined *puStack_14;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = 0xffffffff;
  if (DAT_009456d8 != (code *)0x0) {
    memset(local_428,0,0x210);
    memset(local_218,0,0x210);
    puStack_15c = &DAT_010000ff;
    puStack_108 = &DAT_010000ff;
    puStack_100 = &DAT_010000ff;
    puStack_104 = &DAT_010000ff;
    puStack_11c = &DAT_010000ff;
    puStack_6c = &DAT_010000ff;
    puStack_c8 = &DAT_010000ff;
    puStack_c0 = &DAT_010000ff;
    puStack_14 = &DAT_010000ff;
    puStack_5c = &DAT_0100ff00;
    puStack_b4 = &DAT_0100ff00;
    puStack_28 = &DAT_0100ff00;
    puStack_80 = &DAT_0100ff00;
    puStack_54 = &DAT_0100ff00;
    puStack_34 = &DAT_0100ff00;
    puStack_10c = &DAT_0100ff00;
    puStack_164 = &DAT_0100ff00;
    puStack_44 = &DAT_0100ff00;
    uStack_144 = 0x1ff0000;
    uStack_140 = 0x1ff0000;
    uStack_a4 = 0x1ff0000;
    uStack_154 = 0x1ff0000;
    uStack_160 = 0x1ff0000;
    uStack_fc = 0x1ff0000;
    uStack_158 = 0x1ff0000;
    uStack_e8 = 0x1ff0000;
    uStack_9c = 0x1ff0000;
    uStack_f4 = 0x1ff0000;
    uStack_f8 = 0x1ff0000;
    uStack_ec = 0x1ff0000;
    uStack_150 = 0x1ff0000;
    uStack_13c = 0x1ff0000;
    uStack_98 = 0x1ff0000;
    uStack_12c = 0x1ff0000;
    uStack_64 = 0x1ff0000;
    uStack_16c = 0x1ff0000;
    uStack_114 = 0x1ff0000;
    local_218[1] = &DAT_01800080;
    puStack_1d4 = &DAT_01800080;
    for (local_430 = 0; local_430 < 0xc; local_430 = local_430 + 1) {
      local_43c = &DAT_0100ffff;
      if (6 < local_430) {
        local_43c = (undefined *)0x1ffff00;
      }
      local_218[(local_430 + 3 >> 8 & 0xff) * 0x16 + (local_430 + 3 & 0xff)] = local_43c;
    }
    for (local_438 = 0; local_438 < 0xc; local_438 = local_438 + 1) {
      local_218[(local_438 + 0x102 >> 8 & 0xff) * 0x16 + (local_438 + 0x102 & 0xff)] =
           (undefined *)0x1ff0000;
    }
    (*DAT_009456d8)(8,local_428,0);
  }
  FUN_0083e885(param_1,uVar1);
  return;
}

