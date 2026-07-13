
void FUN_004cc300(char param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  char *_Filename;
  char *_Mode;
  char *local_50;
  char *local_4c;
  FILE *local_48;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849eb8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if (DAT_00915554 != 0) {
    FUN_00426a60(&DAT_02cf1000,0);
    local_8 = 0;
    if (param_1 == '\0') {
      local_4c = "io_in.txt";
    }
    else {
      local_4c = "io_out.txt";
    }
    local_50 = local_4c;
    FUN_004cfa00(&local_50);
    uVar2 = FUN_00417fd0(local_44);
    _Mode = "a";
    _Filename = (char *)FUN_0041f870(&DAT_0087964c,uVar1,uVar2);
    local_48 = fopen(_Filename,_Mode);
    ~basic_string<>();
    DAT_00917a58 = DAT_00917a58 + 1;
    fprintf(local_48,"Binary IO record number %lu type %ld size %ld\n",DAT_00917a58,param_2,param_3)
    ;
    fclose(local_48);
    local_8 = 0xffffffff;
    FUN_004180b0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

