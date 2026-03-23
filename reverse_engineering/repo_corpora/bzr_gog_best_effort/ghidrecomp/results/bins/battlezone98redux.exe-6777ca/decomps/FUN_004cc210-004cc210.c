
void FUN_004cc210(char param_1)

{
  uint uVar1;
  char *_Filename;
  FILE *_File;
  char *_Mode;
  char *local_50;
  undefined4 local_4c;
  char *local_48;
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
    DAT_00917a58 = 0;
    FUN_00426a60(&DAT_02cf1000,0);
    local_8 = 0;
    if (param_1 == '\0') {
      local_48 = "io_in.txt";
    }
    else {
      local_48 = "io_out.txt";
    }
    local_50 = local_48;
    FUN_004cfa00(&local_50);
    local_4c = FUN_00417fd0(local_44);
    _Mode = "w";
    _Filename = (char *)FUN_0041f870(&DAT_0087675c,uVar1);
    _File = fopen(_Filename,_Mode);
    ~basic_string<>();
    fclose(_File);
    local_8 = 0xffffffff;
    FUN_004180b0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

