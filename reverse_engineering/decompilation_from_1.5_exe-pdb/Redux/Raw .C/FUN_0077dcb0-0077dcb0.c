
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0077dcb0(void)

{
  undefined4 *puVar1;
  uint uVar2;
  float10 fVar3;
  size_t local_104c;
  int local_1048;
  int local_1044;
  void *local_1040;
  undefined4 *local_103c;
  undefined4 *local_1038;
  byte *local_1034;
  float local_1030;
  int local_102c;
  int local_1028;
  int local_1024;
  size_t local_1020;
  int local_101c;
  char *local_1018;
  char local_1012;
  char local_1011;
  FILE *local_1010;
  undefined1 local_100c [4];
  char local_1008 [4];
  undefined1 local_1004 [4092];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1010 = (FILE *)0x0;
  local_101c = 0;
  local_102c = 1;
  memset(&DAT_02cd5120,0,0x4000);
  for (local_100c = (undefined1  [4])0x0; (int)local_100c < 0x4000;
      local_100c = (undefined1  [4])((int)local_100c + 1)) {
    if (*(undefined **)(&DAT_02cc5108 + (int)local_100c * 4) != &DAT_02c119d0) {
      (&DAT_02cd5120)[(int)local_100c] = (undefined1)local_102c;
      local_102c = local_102c + 1;
    }
  }
  local_1020 = local_102c << 0x10;
  DAT_009454c4 = malloc(local_1020);
  if (DAT_009454c4 == (byte *)0x0) {
    FUN_007d65d0("Memory allocation failed");
  }
  memset(DAT_009454c4,0,local_1020);
  sprintf(local_1008,"%s",&DAT_02cc40c0);
  local_1018 = strrchr(local_1008,0x2e);
  if (local_1018 != (char *)0x0) {
    *local_1018 = '\0';
  }
  puVar1 = (undefined4 *)(local_100c + 3);
  do {
    local_1038 = puVar1;
    local_1011 = *(char *)((int)local_1038 + 1);
    puVar1 = (undefined4 *)((int)local_1038 + 1);
  } while (local_1011 != '\0');
  *puVar1 = 0x74676c2e;
  *(undefined1 *)((int)local_1038 + 5) = 0;
  local_1038 = puVar1;
  local_1040 = (void *)FUN_00829130(local_1008,&local_104c);
  if (local_1040 != (void *)0x0) {
    if (local_104c == local_1020) {
      memcpy(DAT_009454c4,local_1040,local_104c);
      local_101c = 1;
    }
    FUN_0062f240(local_1040);
  }
  if (local_101c == 0) {
    sprintf(local_1008,"%s%s%s",&DAT_02cf3000,&DAT_00871328,&DAT_02cc40c0);
    local_1018 = strrchr(local_1008,0x2e);
    if (local_1018 != (char *)0x0) {
      *local_1018 = '\0';
    }
    puVar1 = (undefined4 *)(local_100c + 3);
    do {
      local_103c = puVar1;
      local_1012 = *(char *)((int)local_103c + 1);
      puVar1 = (undefined4 *)((int)local_103c + 1);
    } while (local_1012 != '\0');
    *puVar1 = 0x74676c2e;
    *(undefined1 *)((int)local_103c + 5) = 0;
    local_103c = puVar1;
    local_1010 = fopen(local_1008,"r+bc");
    if (local_1010 == (FILE *)0x0) {
      local_1010 = fopen(local_1008,"w+bc");
      if (local_1010 == (FILE *)0x0) {
        FUN_007d65d0("Failed to open/create illumination file %s",local_1008);
      }
    }
  }
  DAT_02cd94e8 = 0.0;
  DAT_02ce99cc = 4096.0;
  for (local_100c = (undefined1  [4])0x0; (int)local_100c < 0x4000;
      local_100c = (undefined1  [4])((int)local_100c + 1)) {
    if (*(undefined **)(&DAT_02cc5108 + (int)local_100c * 4) != &DAT_02c119d0) {
      uVar2 = (uint)local_100c & 0x8000007f;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xffffff80) + 1;
      }
      local_1044 = uVar2 * 0x100 + -0x1800;
      local_1048 = ((int)((int)local_100c + ((int)local_100c >> 0x1f & 0x7fU)) >> 7) * 0x100 +
                   -0x1800;
      for (local_1028 = 0; local_1028 < 0x100; local_1028 = local_1028 + 1) {
        for (local_1024 = 0; local_1024 < 0x100; local_1024 = local_1024 + 1) {
          fVar3 = (float10)FUN_0077d410(local_1044 + local_1024,local_1048 + local_1028);
          local_1030 = (float)fVar3;
          if (DAT_02cd94e8 < local_1030) {
            DAT_02cd94e8 = local_1030;
          }
          if (local_1030 < DAT_02ce99cc) {
            DAT_02ce99cc = local_1030;
          }
          if (local_101c == 0) {
            FUN_0077dc00(local_1044 + local_1024,local_1048 + local_1028);
          }
        }
      }
    }
  }
  DAT_02cd94e8 = DAT_02cd94e8 * 5.0;
  DAT_02ce99cc = DAT_02ce99cc * 5.0;
  if (local_101c == 0) {
    local_1034 = DAT_009454c4;
    FUN_00783630();
    for (local_100c = (undefined1  [4])0x0; (int)local_100c < (int)local_1020;
        local_100c = (undefined1  [4])((int)local_100c + 1)) {
      if ((int)(uint)*local_1034 < _DAT_008f05ec) {
        *local_1034 = DAT_008f05ec;
      }
      local_1034 = local_1034 + 1;
    }
  }
  if ((local_101c == 0) && (local_1010 != (FILE *)0x0)) {
    fwrite(DAT_009454c4,1,local_1020,local_1010);
  }
  if (local_1010 != (FILE *)0x0) {
    fclose(local_1010);
  }
  FUN_0083e885();
  return;
}

