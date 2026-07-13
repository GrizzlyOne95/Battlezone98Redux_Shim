
void FUN_0061f1c0(byte *param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  uint local_3c0;
  uint local_3bc;
  uint local_3b8;
  byte *local_3b4;
  byte *local_3b0;
  byte *local_3ac;
  byte *local_3a8;
  byte *local_3a4;
  byte *local_3a0;
  FILE *local_39c;
  byte local_398 [4];
  FILE *local_394;
  byte local_38e;
  byte local_38d;
  byte local_38c;
  byte local_38b;
  byte local_38a;
  byte local_389;
  char local_388 [260];
  char local_284 [260];
  undefined1 local_180 [40];
  char local_158 [256];
  byte local_58 [40];
  byte local_30 [40];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_388,"%s%s%s",&DAT_02cf2000,&DAT_00871328,"temp.map");
  sprintf(local_284,"%s%s%s",&DAT_02cf2000,&DAT_00871328,"input.map");
  local_39c = fopen(local_284,"r");
  if (local_39c == (FILE *)0x0) {
    sprintf(local_284,"%s%s%s",&DAT_02cf0000,&DAT_00871328,"input.map");
    local_39c = fopen(local_284,"r");
  }
  local_394 = fopen(local_388,"w");
  DAT_0091fef8 = 0;
  DAT_0091a454 = local_284;
  do {
    iVar1 = FUN_0061e530(local_158,0xff,local_39c);
    if (iVar1 == 0) {
      fclose(local_394);
      fclose(local_39c);
      FUN_0061f060();
LAB_0061f63c:
      DAT_0091a454 = (undefined1 *)0x0;
      FUN_0083e885();
      return;
    }
    iVar1 = sscanf(local_158,"%s {",local_58);
    if (iVar1 != 1) {
      FUN_007d6830("%s line %d: read error.",DAT_0091a454,DAT_0091fef8);
      goto LAB_0061f63c;
    }
    fprintf(local_394,"%s\n",local_158);
    local_3a4 = param_1;
    local_3b4 = local_58;
    do {
      local_38b = *local_3b4;
      bVar2 = local_38b < *local_3a4;
      if (local_38b != *local_3a4) {
LAB_0061f3a6:
        local_3bc = -(uint)bVar2 | 1;
        goto LAB_0061f3b1;
      }
      if (local_38b == 0) break;
      local_38c = local_3b4[1];
      bVar2 = local_38c < local_3a4[1];
      if (local_38c != local_3a4[1]) goto LAB_0061f3a6;
      local_3b4 = local_3b4 + 2;
      local_3a4 = local_3a4 + 2;
    } while (local_38c != 0);
    local_3bc = 0;
LAB_0061f3b1:
    if (local_3bc == 0) {
LAB_0061f3ca:
      do {
        iVar1 = FUN_0061e530(local_158,0xff,local_39c);
        if (iVar1 == 0) break;
        if (local_158[0] == '}') {
          fprintf(local_394,"%s\n",local_158);
          fprintf(local_394,"\n");
          break;
        }
        iVar1 = sscanf(local_158," %1[+-] %s %s",local_398,local_30,local_180);
        if (iVar1 != 3) {
          FUN_007d6830("%s line %d: read error - \"%s\"",DAT_0091a454,DAT_0091fef8,local_58);
          goto LAB_0061f63c;
        }
        local_3ac = (byte *)0x873c3c;
        local_3a8 = local_30;
        do {
          local_38e = *local_3a8;
          bVar2 = local_38e < *local_3ac;
          if (local_38e != *local_3ac) {
LAB_0061f504:
            local_3b8 = -(uint)bVar2 | 1;
            goto LAB_0061f50f;
          }
          if (local_38e == 0) break;
          local_38d = local_3a8[1];
          bVar2 = local_38d < local_3ac[1];
          if (local_38d != local_3ac[1]) goto LAB_0061f504;
          local_3a8 = local_3a8 + 2;
          local_3ac = local_3ac + 2;
        } while (local_38d != 0);
        local_3b8 = 0;
LAB_0061f50f:
        if (local_3b8 == 0) {
          local_3b0 = &DAT_0088cba8;
          local_3a0 = local_398;
          do {
            local_38a = *local_3a0;
            bVar2 = local_38a < *local_3b0;
            if (local_38a != *local_3b0) {
LAB_0061f59c:
              local_3c0 = -(uint)bVar2 | 1;
              goto LAB_0061f5a7;
            }
            if (local_38a == 0) break;
            local_389 = local_3a0[1];
            bVar2 = local_389 < local_3b0[1];
            if (local_389 != local_3b0[1]) goto LAB_0061f59c;
            local_3a0 = local_3a0 + 2;
            local_3b0 = local_3b0 + 2;
          } while (local_389 != 0);
          local_3c0 = 0;
LAB_0061f5a7:
          if (local_3c0 == 0) {
            fprintf(local_394,"\t%s %s %s\n",local_398,local_30,param_2);
            goto LAB_0061f3ca;
          }
        }
        fprintf(local_394,"%s\n",local_158);
      } while( true );
    }
  } while( true );
}

