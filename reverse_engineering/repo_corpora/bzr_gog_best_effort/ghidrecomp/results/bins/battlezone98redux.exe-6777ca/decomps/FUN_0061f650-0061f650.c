
void FUN_0061f650(byte *param_1,char *param_2)

{
  int iVar1;
  bool bVar2;
  uint local_2d4;
  uint local_2d0;
  uint local_2cc;
  uint local_2c4;
  byte local_2c0 [4];
  char *local_2bc;
  byte *local_2b8;
  char *local_2b4;
  byte *local_2b0;
  byte *local_2ac;
  byte *local_2a8;
  byte *local_2a4;
  byte *local_2a0;
  byte *local_29c;
  byte *local_298;
  FILE *local_294;
  byte local_28d;
  byte local_28c;
  byte local_28b;
  byte local_28a;
  byte local_289;
  byte local_288;
  byte local_287;
  byte local_286;
  char local_285;
  char local_284 [260];
  char local_180 [256];
  byte local_80 [40];
  char local_58 [40];
  byte local_30 [40];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_284,"%s%s%s",&DAT_02cf2000,&DAT_00871328,"input.map");
  local_294 = fopen(local_284,"r");
  if (local_294 == (FILE *)0x0) {
    sprintf(local_284,"%s%s%s",&DAT_02cf0000,&DAT_00871328,"input.map");
    local_294 = fopen(local_284,"r");
  }
  DAT_0091fef8 = 0;
  DAT_0091a454 = local_284;
LAB_0061f700:
  do {
    iVar1 = FUN_0061e470(local_180,0xff,local_294);
    if (iVar1 == 0) {
      fclose(local_294);
LAB_0061fb10:
      DAT_0091a454 = (undefined1 *)0x0;
      FUN_0083e885();
      return;
    }
    iVar1 = sscanf(local_180,"%s {",local_30);
    if (iVar1 != 1) {
      FUN_007d6830("%s line %d: read error.",DAT_0091a454,DAT_0091fef8);
      goto LAB_0061fb10;
    }
    local_2b0 = param_1;
    local_2a8 = local_30;
    do {
      local_28b = *local_2a8;
      bVar2 = local_28b < *local_2b0;
      if (local_28b != *local_2b0) {
LAB_0061f7dc:
        local_2d0 = -(uint)bVar2 | 1;
        goto LAB_0061f7e7;
      }
      if (local_28b == 0) break;
      local_287 = local_2a8[1];
      bVar2 = local_287 < local_2b0[1];
      if (local_287 != local_2b0[1]) goto LAB_0061f7dc;
      local_2a8 = local_2a8 + 2;
      local_2b0 = local_2b0 + 2;
    } while (local_287 != 0);
    local_2d0 = 0;
LAB_0061f7e7:
  } while (local_2d0 != 0);
  iVar1 = FUN_0061e420(local_30);
  if (*(int *)(iVar1 + 8) != 1) {
    if (*(int *)(iVar1 + 8) != 2) goto LAB_0061f700;
    local_2ac = (byte *)0x88c19c;
    local_2b8 = local_30;
    do {
      local_288 = *local_2b8;
      bVar2 = local_288 < *local_2ac;
      if (local_288 != *local_2ac) {
LAB_0061f8a3:
        local_2cc = -(uint)bVar2 | 1;
        goto LAB_0061f8ae;
      }
      if (local_288 == 0) break;
      local_28a = local_2b8[1];
      bVar2 = local_28a < local_2ac[1];
      if (local_28a != local_2ac[1]) goto LAB_0061f8a3;
      local_2b8 = local_2b8 + 2;
      local_2ac = local_2ac + 2;
    } while (local_28a != 0);
    local_2cc = 0;
LAB_0061f8ae:
    if (local_2cc != 0) goto LAB_0061f700;
  }
  while ((iVar1 = FUN_0061e470(local_180,0xff,local_294), iVar1 != 0 && (local_180[0] != '}'))) {
    iVar1 = sscanf(local_180," %1[+-] %s %s",local_2c0,local_80,local_58);
    if (iVar1 != 3) {
      FUN_007d6830("%s line %d: read error - \"%s\"",DAT_0091a454,DAT_0091fef8,local_30);
      goto LAB_0061fb10;
    }
    local_2a0 = (byte *)0x873c3c;
    local_29c = local_80;
    do {
      local_28c = *local_29c;
      bVar2 = local_28c < *local_2a0;
      if (local_28c != *local_2a0) {
LAB_0061f9ce:
        local_2d4 = -(uint)bVar2 | 1;
        goto LAB_0061f9d9;
      }
      if (local_28c == 0) break;
      local_28d = local_29c[1];
      bVar2 = local_28d < local_2a0[1];
      if (local_28d != local_2a0[1]) goto LAB_0061f9ce;
      local_29c = local_29c + 2;
      local_2a0 = local_2a0 + 2;
    } while (local_28d != 0);
    local_2d4 = 0;
LAB_0061f9d9:
    if (local_2d4 == 0) {
      local_2a4 = &DAT_0088cba8;
      local_298 = local_2c0;
      do {
        local_286 = *local_298;
        bVar2 = local_286 < *local_2a4;
        if (local_286 != *local_2a4) {
LAB_0061fa66:
          local_2c4 = -(uint)bVar2 | 1;
          goto LAB_0061fa71;
        }
        if (local_286 == 0) break;
        local_289 = local_298[1];
        bVar2 = local_289 < local_2a4[1];
        if (local_289 != local_2a4[1]) goto LAB_0061fa66;
        local_298 = local_298 + 2;
        local_2a4 = local_2a4 + 2;
      } while (local_289 != 0);
      local_2c4 = 0;
LAB_0061fa71:
      if (local_2c4 == 0) {
        local_2bc = local_58;
        local_2b4 = param_2;
        do {
          local_285 = *local_2bc;
          *local_2b4 = local_285;
          local_2bc = local_2bc + 1;
          local_2b4 = local_2b4 + 1;
        } while (local_285 != '\0');
      }
    }
  }
  goto LAB_0061f700;
}

