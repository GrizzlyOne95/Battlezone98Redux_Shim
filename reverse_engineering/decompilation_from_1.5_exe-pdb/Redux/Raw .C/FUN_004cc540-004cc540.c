
void FUN_004cc540(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  char *_Filename;
  FILE *_File;
  char *_Mode;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849f18;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  if (DAT_00915554 != 0) {
    FUN_00426a60(&DAT_02cf1000,0);
    local_8 = 0;
    FUN_00426af0("io_in.txt");
    uVar2 = FUN_00417fd0(local_44);
    _Mode = "a";
    _Filename = (char *)FUN_0041f870(&DAT_0087964c,uVar1,uVar2);
    _File = fopen(_Filename,_Mode);
    ~basic_string<>();
    fprintf(_File,"BAD Pointer %p in %s\n",param_2,param_1);
    fclose(_File);
    local_8 = 0xffffffff;
    FUN_004180b0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

