
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0083e420(undefined4 *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  void **_Src;
  uint local_44;
  void *local_40 [4];
  undefined4 local_30;
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00865457;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_44;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xffffffb0;
  ExceptionList = &local_c;
  local_44 = 0;
  if ((DAT_00914d14 & 1) == 0) {
    DAT_00914d14 = DAT_00914d14 | 1;
    local_4 = 0;
    DAT_00914d10 = 0xf;
    _DAT_00914d0c = 0;
    DAT_00914cfc._0_1_ = 0;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_00914cfc,"Unknown error",0xd);
    FUN_0083e979(&LAB_008681f0,uVar2);
  }
  local_4 = 0xffffffff;
  pcVar3 = strerror(param_2);
  if (pcVar3 == (char *)0x0) {
    local_2c = 0xf;
    local_30 = 0;
    local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               local_40,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&DAT_00914cfc,0,0xffffffff);
    _Src = local_40;
    uVar2 = 2;
  }
  else {
    local_14 = 0xf;
    local_18 = 0;
    local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
    if (*pcVar3 == '\0') {
      uVar2 = 0;
    }
    else {
      pcVar4 = pcVar3;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      uVar2 = (int)pcVar4 - (int)(pcVar3 + 1);
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               local_28,pcVar3,uVar2);
    _Src = local_28;
    local_4 = 1;
    uVar2 = 1;
  }
  param_1[5] = 0xf;
  param_1[4] = 0;
  *(undefined1 *)param_1 = 0;
  local_44 = uVar2;
  if (_Src[5] < (void *)0x10) {
    if ((int)_Src[4] + 1U != 0) {
      memmove(param_1,_Src,(int)_Src[4] + 1U);
    }
  }
  else {
    *param_1 = *_Src;
    *_Src = (void *)0x0;
  }
  param_1[4] = _Src[4];
  param_1[5] = _Src[5];
  _Src[5] = (void *)0xf;
  _Src[4] = (void *)0x0;
  *(undefined1 *)_Src = 0;
  if ((uVar2 & 2) != 0) {
    uVar2 = uVar2 & 0xfffffffd;
    if (0xf < local_2c) {
      operator_delete(local_40[0]);
    }
    local_2c = 0xf;
    local_30 = 0;
    local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  }
  if (((uVar2 & 1) != 0) && (0xf < local_14)) {
    operator_delete(local_28[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

