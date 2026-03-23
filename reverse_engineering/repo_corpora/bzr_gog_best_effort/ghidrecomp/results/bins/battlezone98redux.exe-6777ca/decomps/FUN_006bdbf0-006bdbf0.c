
void FUN_006bdbf0(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  int local_174;
  int local_168;
  uint local_164;
  uint local_160;
  uint local_15c [15];
  int iStack_120;
  uint local_1c [6];
  
  local_1c[5] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c[0] = 0x67452301;
  local_1c[1] = 0xefcdab89;
  local_1c[2] = 0x98badcfe;
  local_1c[3] = 0x10325476;
  local_1c[4] = 0xc3d2e1f0;
  local_160 = 0;
  if (0x3f < param_2) {
    while (local_160 <= param_2 - 0x40) {
      uVar1 = local_160 + 0x40;
      local_174 = 0;
      for (; local_160 < uVar1; local_160 = local_160 + 4) {
        local_15c[local_174] =
             CONCAT13(*(undefined1 *)(param_1 + local_160),
                      CONCAT12(*(undefined1 *)(param_1 + local_160 + 1),
                               CONCAT11(*(undefined1 *)(param_1 + local_160 + 2),
                                        *(undefined1 *)(param_1 + local_160 + 3))));
        local_174 = local_174 + 1;
      }
      FUN_006bd7b0(local_1c,local_15c);
    }
  }
  FUN_006bd780(local_15c);
  for (local_164 = 0; local_164 < param_2 - local_160; local_164 = local_164 + 1) {
    *(uint *)((int)local_15c + (local_164 & 0xfffffffc)) =
         (uint)*(byte *)(param_1 + local_164 + local_160) <<
         (('\x03' - ((byte)local_164 & 3)) * '\b' & 0x1f) |
         *(uint *)((int)local_15c + (local_164 & 0xfffffffc));
  }
  *(uint *)((int)local_15c + (local_164 & 0xfffffffc)) =
       0x80 << (('\x03' - ((byte)local_164 & 3)) * '\b' & 0x1f) |
       *(uint *)((int)local_15c + (local_164 & 0xfffffffc));
  if (0x37 < param_2 - local_160) {
    FUN_006bd7b0(local_1c,local_15c);
    FUN_006bd780(local_15c);
  }
  iStack_120 = param_2 << 3;
  FUN_006bd7b0(local_1c,local_15c);
  local_168 = 0x14;
  while (local_168 = local_168 + -1, -1 < local_168) {
    *(char *)(param_3 + local_168) =
         (char)(local_1c[local_168 >> 2] >> (sbyte)((3U - local_168 & 3) << 3));
  }
  FUN_0083e885();
  return;
}

