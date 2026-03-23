
void FUN_004fdf00(int param_1)

{
  undefined4 uVar1;
  char *_Filename;
  int iVar2;
  undefined1 local_68 [24];
  undefined1 local_50 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((0 < param_1) && (param_1 < 0xb)) {
    FUN_00426a60(&DAT_02ceefe0,0);
    basic_string<>(&DAT_0087bb64);
    uVar1 = FUN_00482630(local_50,param_1);
    FUN_00449810(uVar1);
    ~basic_string<>();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_20,".sav");
    FUN_004fed70(local_20);
    FUN_00417fd0(local_68);
    _Filename = (char *)FUN_0041f870();
    iVar2 = remove(_Filename);
    ~basic_string<>(iVar2 == 0);
    ~basic_string<>();
    FUN_004180b0();
  }
  FUN_0083e885();
  return;
}

