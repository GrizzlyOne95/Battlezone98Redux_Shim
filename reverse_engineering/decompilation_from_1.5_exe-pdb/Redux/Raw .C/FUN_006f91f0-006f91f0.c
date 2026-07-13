
void FUN_006f91f0(void)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  basic_istream<char,struct_std::char_traits<char>_> local_100 [168];
  undefined4 local_58;
  int local_54;
  int local_50;
  basic_istream<char,struct_std::char_traits<char>_> *local_4c;
  char local_45;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855a1b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_006b8190(local_14);
  if (cVar1 != '\0') {
    basic_string<>("Sec-WebSocket-Version");
    local_8 = 0;
    FUN_006b7490(local_44);
    local_45 = FUN_0041f890();
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (local_45 == '\0') {
      basic_string<>("Sec-WebSocket-Version");
      local_8 = 1;
      uVar5 = 1;
      uVar4 = 1;
      uVar3 = FUN_006b7490(local_2c);
      FUN_006ca8e0(uVar3,uVar4,uVar5);
      local_8 = CONCAT31(local_8._1_3_,3);
      ~basic_string<>();
      local_4c = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                           (local_100,&local_50);
      bVar2 = std::ios_base::fail((ios_base *)(local_4c + *(int *)(*(int *)local_4c + 4)));
      if (bVar2) {
        local_58 = 0xffffffff;
        local_8 = 0xffffffff;
        FUN_006b95c0();
      }
      else {
        local_54 = local_50;
        local_8 = 0xffffffff;
        FUN_006b95c0();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

