
void __thiscall FUN_007d5010(undefined4 param_1,undefined4 param_2)

{
  uint local_224;
  uint local_220;
  undefined4 local_218 [132];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_009456d8 != (code *)0x0) {
    memset(local_218,0,0x210);
    for (local_220 = 0; local_220 < 6; local_220 = local_220 + 1) {
      for (local_224 = 0; local_224 < 0x16; local_224 = local_224 + 1) {
        local_218[local_220 * 0x16 + local_224] = param_2;
      }
    }
    (*DAT_009456d8)(2,local_218,0);
  }
  FUN_0083e885(param_1);
  return;
}

