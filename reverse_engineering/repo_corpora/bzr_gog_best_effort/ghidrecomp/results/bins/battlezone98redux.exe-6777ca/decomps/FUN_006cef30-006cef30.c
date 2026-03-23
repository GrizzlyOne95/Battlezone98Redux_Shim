
void __thiscall
FUN_006cef30(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,uint param_2)

{
  char *pcVar1;
  int iVar2;
  void *_Src;
  void *_Dst;
  undefined4 *puVar3;
  char *pcVar4;
  char *pcVar5;
  size_t _Size;
  undefined1 local_30 [12];
  undefined4 local_24;
  int local_20;
  int local_1c;
  uint local_18;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852cf8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = param_1;
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  local_20 = FUN_006cf0f0(0);
  local_20 = (int)pcVar1 - local_20;
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_14);
  iVar2 = FUN_006cf0f0(0);
  local_18 = (int)pcVar1 - iVar2;
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(local_14);
  local_1c = FUN_006cf0f0(0);
  local_1c = (int)pcVar1 - local_1c;
  if (local_1c - local_18 < param_2) {
    if (local_20 != 0) {
      _Size = local_18 - local_20;
      local_18 = _Size;
      iVar2 = FUN_006cf0f0(0);
      _Src = (void *)(iVar2 + local_20);
      _Dst = (void *)FUN_006cf0f0(0);
      memmove(_Dst,_Src,_Size);
    }
    if (local_1c - local_18 < param_2) {
      if ((*(uint *)(local_14 + 0x38) < param_2) || (*(int *)(local_14 + 0x38) - param_2 < local_18)
         ) {
        FUN_006ab600("boost::asio::streambuf too long");
        local_8 = 0;
        FUN_006dd5d0(local_30);
        local_8 = 0xffffffff;
        FUN_006ab660();
      }
      else {
        local_1c = local_18 + param_2;
        local_24 = 1;
        puVar3 = (undefined4 *)_Max_value<>(&local_1c,&local_24);
        FUN_006d2f00(*puVar3);
      }
    }
    iVar2 = FUN_006cf0f0(0);
    pcVar1 = (char *)(iVar2 + local_18);
    pcVar4 = (char *)FUN_006cf0f0(0);
    pcVar5 = (char *)FUN_006cf0f0(0);
    std::basic_streambuf<char,struct_std::char_traits<char>_>::setg(local_14,pcVar5,pcVar4,pcVar1);
    iVar2 = FUN_006cf0f0(0);
    pcVar1 = (char *)(iVar2 + local_1c);
    iVar2 = FUN_006cf0f0(0);
    std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
              (local_14,(char *)(iVar2 + local_18),pcVar1);
  }
  ExceptionList = local_10;
  return;
}

