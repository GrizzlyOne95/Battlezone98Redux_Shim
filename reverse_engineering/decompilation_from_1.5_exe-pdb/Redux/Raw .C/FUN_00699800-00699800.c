
undefined4 * FUN_00699800(int param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_1c;
  byte *local_14;
  byte *local_10;
  undefined4 *local_c;
  
  bVar2 = false;
  local_c = *(undefined4 **)(param_1 + 0xc);
  do {
    if (bVar2) {
      return local_c;
    }
    if (local_c == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    local_14 = (byte *)*local_c;
    local_10 = param_2;
    do {
      bVar1 = *local_10;
      bVar2 = bVar1 < *local_14;
      if (bVar1 != *local_14) {
LAB_0069987a:
        local_1c = -(uint)bVar2 | 1;
        goto LAB_00699882;
      }
      if (bVar1 == 0) break;
      bVar1 = local_10[1];
      bVar2 = bVar1 < local_14[1];
      if (bVar1 != local_14[1]) goto LAB_0069987a;
      local_10 = local_10 + 2;
      local_14 = local_14 + 2;
    } while (bVar1 != 0);
    local_1c = 0;
LAB_00699882:
    bVar2 = local_1c == 0;
    if (!bVar2) {
      local_c = (undefined4 *)local_c[3];
    }
  } while( true );
}

