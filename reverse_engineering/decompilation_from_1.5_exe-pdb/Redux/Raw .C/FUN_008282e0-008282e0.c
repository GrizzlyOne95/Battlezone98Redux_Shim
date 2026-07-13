
void FUN_008282e0(void)

{
  char *_Filename;
  FILE *_File;
  undefined4 uVar1;
  int iVar2;
  char *_Mode;
  undefined1 local_50 [24];
  undefined1 local_38 [48];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00426a60(&DAT_02cf0000,0);
  FUN_004cfa00(&stack0x00000004);
  _Mode = "rt";
  FUN_00417fd0(local_50);
  _Filename = (char *)FUN_0041f870();
  _File = fopen(_Filename,_Mode);
  ~basic_string<>();
  if (_File == (FILE *)0x0) {
    FUN_00417fd0(local_38);
    uVar1 = FUN_0041f870();
    sprintf(&DAT_009467c0,"Couldn\'t open file \"%s\"",uVar1);
    ~basic_string<>();
    FUN_004180b0();
  }
  else {
    iVar2 = FUN_00829680();
    iVar2 = FUN_00827ff0(_File,iVar2 + -1);
    if (iVar2 == 0) {
      FUN_004180b0(0);
    }
    else {
      fclose(_File);
      FUN_004180b0();
    }
  }
  FUN_0083e885();
  return;
}

