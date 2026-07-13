
undefined * FUN_004184d0(byte *param_1)

{
  byte bVar1;
  bool bVar2;
  uint local_18;
  byte *local_14;
  byte *local_10;
  uint local_c;
  
  if (param_1 != (byte *)0x0) {
    for (local_c = 0; local_c < 7; local_c = local_c + 1) {
      local_14 = (&PTR_s_cloak_008e7030)[local_c * 2];
      local_10 = param_1;
      do {
        bVar1 = *local_10;
        bVar2 = bVar1 < *local_14;
        if (bVar1 != *local_14) {
LAB_0041854b:
          local_18 = -(uint)bVar2 | 1;
          goto LAB_00418553;
        }
        if (bVar1 == 0) break;
        bVar1 = local_10[1];
        bVar2 = bVar1 < local_14[1];
        if (bVar1 != local_14[1]) goto LAB_0041854b;
        local_10 = local_10 + 2;
        local_14 = local_14 + 2;
      } while (bVar1 != 0);
      local_18 = 0;
LAB_00418553:
      if (local_18 == 0) {
        return (&PTR_FUN_008e7034)[local_c * 2];
      }
    }
  }
  return (undefined *)0x0;
}

