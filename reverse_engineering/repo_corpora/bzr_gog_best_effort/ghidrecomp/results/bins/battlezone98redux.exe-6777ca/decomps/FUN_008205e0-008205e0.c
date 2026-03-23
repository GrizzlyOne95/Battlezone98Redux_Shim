
void FUN_008205e0(void)

{
  undefined4 *puVar1;
  uint _Seed;
  void *pvVar2;
  long lVar3;
  int iVar4;
  int local_160;
  char *local_15c;
  int local_158;
  char *local_154;
  int local_150;
  undefined2 *local_14c;
  char *local_148;
  char local_142;
  char local_141;
  FILE *local_140;
  int local_13c;
  char local_135;
  undefined4 auStack_134 [9];
  undefined2 uStack_10d;
  undefined1 auStack_10b [259];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uStack_10d._1_1_ = 0;
  memset(auStack_10b,0,0x103);
  if (DAT_0094672c == (undefined4 *)0x0) {
    _Seed = FUN_0056f760(0);
    srand(_Seed);
    local_150 = rand();
    local_150 = local_150 % 10;
    if (local_150 < 3) {
      local_150 = 3;
    }
    for (local_13c = 0; local_13c < local_150; local_13c = local_13c + 1) {
      pvVar2 = malloc(0x40);
      auStack_134[local_13c] = pvVar2;
    }
    DAT_0094672c = malloc(0x50);
    for (local_13c = 0; local_13c < local_150; local_13c = local_13c + 1) {
      free((void *)auStack_134[local_13c]);
    }
  }
  memset(DAT_0094672c,0,0x50);
  puVar1 = DAT_0094672c;
  DAT_0094672c[5] = PTR_DAT_008fe224;
  puVar1[6] = DAT_008fe228;
  puVar1[7] = DAT_008fe22c;
  puVar1[8] = DAT_008fe230;
  puVar1[9] = DAT_008fe234;
  *(undefined2 *)(puVar1 + 10) = DAT_008fe238;
  *(undefined1 *)((int)DAT_0094672c + 0x25) = 1;
  *(undefined1 *)(DAT_0094672c + 9) = 0;
  *(undefined1 *)((int)DAT_0094672c + 0x26) = 0;
  *(undefined1 *)((int)DAT_0094672c + 0x27) = 1;
  *(undefined1 *)(DAT_0094672c + 10) = 1;
  *(undefined1 *)((int)DAT_0094672c + 0x29) = 2;
  *(undefined1 *)((int)DAT_0094672c + 0x2a) = 8;
  *(undefined1 *)((int)DAT_0094672c + 0x2b) = 8;
  *(undefined1 *)(DAT_0094672c + 0xb) = 8;
  *(undefined1 *)((int)DAT_0094672c + 0x2d) = 0x40;
  *(undefined1 *)((int)DAT_0094672c + 0x2e) = 1;
  *(undefined1 *)((int)DAT_0094672c + 0x2f) = 0;
  DAT_0094672c[0xc] = 0x70;
  DAT_0094672c[0xd] = 0;
  DAT_0094672c[0xe] = 3;
  DAT_0094672c[0xf] = 5;
  DAT_0094672c[0x10] = DAT_025cfa1c;
  DAT_0094672c[0x11] = 0;
  DAT_0094672c[0x12] = 0;
  DAT_0094672c[0x13] = 0;
  DAT_0094672c[2] = 0;
  DAT_0094672c[3] = 0;
  DAT_0094672c[4] = 0;
  *DAT_0094672c = 0;
  DAT_0094672c[1] = 0;
  local_15c = &DAT_02cf2000;
  local_154 = (char *)((int)&uStack_10d + 1);
  do {
    local_135 = *local_15c;
    *local_154 = local_135;
    local_15c = local_15c + 1;
    local_154 = local_154 + 1;
  } while (local_135 != '\0');
  local_14c = &uStack_10d;
  do {
    local_141 = *(char *)((int)local_14c + 1);
    local_14c = (undefined2 *)((int)local_14c + 1);
  } while (local_141 != '\0');
  *local_14c = 0x5c;
  local_148 = (char *)((int)&uStack_10d + 1);
  do {
    local_142 = *local_148;
    local_148 = local_148 + 1;
  } while (local_142 != '\0');
  strncat((char *)((int)&uStack_10d + 1),"BZPLYR.DEF",0x103 - ((int)local_148 - (int)auStack_10b));
  local_140 = fopen((char *)((int)&uStack_10d + 1),"rb");
  if (local_140 == (FILE *)0x0) {
    FUN_007d6b70("%s not found; using defaults\n",(int)&uStack_10d + 1);
  }
  else {
    fseek(local_140,0,2);
    lVar3 = ftell(local_140);
    if (lVar3 == 0x58) {
      local_160 = 0;
      local_158 = 0;
      fseek(local_140,0,0);
      fread(&local_160,4,1,local_140);
      if (local_160 == 0x52594c50) {
        fread(&local_158,4,1,local_140);
        if (local_158 == 1) {
          fread(DAT_0094672c,1,0x50,local_140);
        }
        else {
          FUN_007d6c70("%s is version %d but expected versoin %d; using defaults\n",
                       (int)&uStack_10d + 1,local_158,1);
        }
      }
      else {
        FUN_007d6c70("%s is not a valid player definition file; using defaults\n",
                     (int)&uStack_10d + 1);
      }
    }
    else {
      FUN_007d6c70("%s is %d bytes but expected %d bytes; using defaults\n",(int)&uStack_10d + 1,
                   lVar3,0x58);
    }
    fclose(local_140);
  }
  if ((*(byte *)(DAT_0094672c + 5) < 8) &&
     (*(undefined1 *)(DAT_0094672c + 5) = 8, DAT_008fe220 != 0)) {
    FUN_00820b90();
  }
  iVar4 = FUN_00820da0(DAT_0094672c[0xc]);
  DAT_00918430 = (uint)(iVar4 != 0);
  DAT_0094672c[0xc] = DAT_0094672c[0xc] & 0xfffffcf0;
  iVar4 = FUN_004344a0();
  if (iVar4 == 2) {
    *(undefined1 *)((int)DAT_0094672c + 0x27) = 1;
    *(undefined1 *)((int)DAT_0094672c + 0x25) = 1;
    *(undefined1 *)(DAT_0094672c + 10) = 0;
  }
  DAT_008fe220 = 0;
  FUN_0083e885();
  return;
}

