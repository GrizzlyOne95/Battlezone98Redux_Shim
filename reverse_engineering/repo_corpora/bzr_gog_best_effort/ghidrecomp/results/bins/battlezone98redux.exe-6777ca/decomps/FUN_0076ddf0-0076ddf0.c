
void FUN_0076ddf0(undefined4 param_1,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int local_64;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845218;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  iVar4 = FUN_00666640(0x2a,0);
  if (iVar4 == -1) {
    FUN_00427310(param_2,param_1);
  }
  else {
    bVar1 = false;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_2);
    local_8 = 0;
    local_64 = FUN_00666640(0x2a,0);
    while (local_64 != -1) {
      if (local_64 != 0) {
        uVar5 = FUN_0045e1d0(local_5c,0,local_64);
        iVar4 = AddRequestHeaders(uVar5,local_64);
        ~basic_string<>();
        if ((iVar4 == -1) || ((iVar4 != 0 && (!bVar1)))) {
          local_8 = 0xffffffff;
          ~basic_string<>();
          goto LAB_0076dffb;
        }
      }
      bVar1 = true;
      uVar5 = FUN_0045e1d0(local_44,local_64 + 1,0xffffffff);
      FUN_0045e0f0(uVar5);
      ~basic_string<>();
      local_64 = FUN_00666640(0x2a,0);
    }
    cVar2 = FUN_0041f890(uVar3);
    if (cVar2 == '\0') {
      uVar3 = FUN_004170c0();
      uVar6 = FUN_004170c0();
      if (uVar3 < uVar6) {
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        AddRequestHeaders(local_2c,uVar3 - uVar6);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    else {
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
LAB_0076dffb:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

