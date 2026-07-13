
/* WARNING: Removing unreachable block (ram,0x00826aa9) */
/* WARNING: Removing unreachable block (ram,0x00826b03) */

void FUN_008268e0(uint *param_1,char *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_38;
  byte *local_30;
  byte *local_2c;
  byte *local_28;
  uint local_18;
  char local_14 [4];
  undefined1 uStack_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  for (local_18 = 0; local_18 < 7; local_18 = local_18 + 1) {
    if ((((*(uint *)(&DAT_008fe5f4 + local_18 * 8) & 0xff) << 8 |
         *(uint *)(&DAT_008fe5f4 + local_18 * 8) >> 8 & 0xff) << 0x10 |
        (*(uint *)(&DAT_008fe5f4 + local_18 * 8) >> 0x10 & 0xff) << 8 |
        *(uint *)(&DAT_008fe5f4 + local_18 * 8) >> 0x18) == *param_1) {
      if (local_18 != 0) {
        if (param_1[2] != *(uint *)(&DAT_008fe5f8 + local_18 * 8)) {
          strncpy(local_14,(char *)param_1,4);
          uStack_10 = 0;
          FUN_007d6830("Bad revision for %s chunk in file %s",local_14,param_2);
        }
        goto LAB_00826b2a;
      }
      local_30 = (byte *)strrchr(param_2,0x2e);
      if (local_30 == (byte *)0x0) {
        local_30 = &DAT_008a1ad8;
      }
      local_18 = 0;
      goto LAB_008269ad;
    }
  }
  strncpy(local_14,(char *)param_1,4);
  uStack_10 = 0;
  FUN_007d6830("Unknown revision chunk % found in %s",local_14,param_2);
LAB_00826b2a:
  FUN_0083e885();
  return;
LAB_008269ad:
  if (9 < local_18) goto LAB_00826a54;
  local_28 = local_30;
  local_2c = (&PTR_DAT_008fe538)[local_18 * 2];
  do {
    bVar1 = *local_2c;
    bVar2 = bVar1 < *local_28;
    if (bVar1 != *local_28) {
LAB_00826a07:
      local_38 = -(uint)bVar2 | 1;
      goto LAB_00826a0f;
    }
    if (bVar1 == 0) break;
    bVar1 = local_2c[1];
    bVar2 = bVar1 < local_28[1];
    if (bVar1 != local_28[1]) goto LAB_00826a07;
    local_2c = local_2c + 2;
    local_28 = local_28 + 2;
  } while (bVar1 != 0);
  local_38 = 0;
LAB_00826a0f:
  if (local_38 == 0) {
    if (param_1[2] != *(uint *)(&DAT_008fe53c + local_18 * 8)) {
      FUN_007d6830("Bad BWD revision for file %s",param_2);
    }
    goto LAB_00826b2a;
  }
  local_18 = local_18 + 1;
  goto LAB_008269ad;
LAB_00826a54:
  FUN_007d6830("Unknown file type found: %s",param_2);
  goto LAB_00826b2a;
}

