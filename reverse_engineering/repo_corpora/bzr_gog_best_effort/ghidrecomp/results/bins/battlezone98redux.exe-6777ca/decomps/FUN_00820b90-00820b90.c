
void FUN_00820b90(void)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  FILE *_File;
  char *local_124;
  char *local_120;
  char *local_11c;
  char *local_118;
  char local_10d;
  char local_10c [260];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_124 = &DAT_02cf2000;
  local_120 = local_10c;
  do {
    local_10d = *local_124;
    *local_120 = local_10d;
    local_124 = local_124 + 1;
    local_120 = local_120 + 1;
  } while (local_10d != '\0');
  local_11c = &local_10d;
  do {
    pcVar1 = local_11c + 1;
    local_11c = local_11c + 1;
  } while (*pcVar1 != '\0');
  local_11c[0] = '\\';
  local_11c[1] = '\0';
  local_118 = local_10c;
  do {
    cVar2 = *local_118;
    local_118 = local_118 + 1;
  } while (cVar2 != '\0');
  strncat(local_10c,"BZPLYR.DEF",0x103 - ((int)local_118 - (int)(local_10c + 1)));
  _File = fopen(local_10c,"wb");
  if (_File != (FILE *)0x0) {
    uVar3 = *(undefined4 *)(DAT_0094672c + 0x30);
    *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffcf0;
    fwrite(&DAT_00873ab8,4,1,_File);
    fwrite(&DAT_008739b4,4,1,_File);
    fwrite((void *)DAT_0094672c,1,0x50,_File);
    fclose(_File);
    *(undefined4 *)(DAT_0094672c + 0x30) = uVar3;
  }
  FUN_0083e885();
  return;
}

