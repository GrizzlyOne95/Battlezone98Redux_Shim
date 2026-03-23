
void FUN_00827ff0(undefined4 param_1)

{
  int iVar1;
  wchar_t *_Dest;
  char *_Source;
  size_t _Count;
  undefined1 local_438 [48];
  undefined1 local_408 [256];
  undefined1 local_308 [512];
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  do {
    iVar1 = FUN_008276b0(local_108,0x100,param_1);
    if (iVar1 == 0) break;
  } while (local_108[0] != '-');
  while ((iVar1 = FUN_008276b0(local_108,0x100,param_1), iVar1 != 0 && (local_108[0] != '-'))) {
    sscanf(local_108,"%s %s",local_408,local_308);
    FUN_00426a60(&DAT_02cf0000,0);
    FUN_00426af0(local_308);
    iVar1 = FUN_00829680();
    FUN_00829570(iVar1 + 1);
    _Dest = std::
            basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
            back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                  *)&DAT_0260c218);
    _Count = 0x1000;
    FUN_00417fd0(local_438);
    _Source = (char *)FUN_0041f870();
    strncpy((char *)_Dest,_Source,_Count);
    ~basic_string<>();
    _Dest[0x800] = L'\0';
    _Dest[0x801] = L'\0';
    FUN_004180b0();
  }
  FUN_0083e885();
  return;
}

