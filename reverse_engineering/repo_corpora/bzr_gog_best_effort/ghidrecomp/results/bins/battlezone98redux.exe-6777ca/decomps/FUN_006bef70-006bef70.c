
void __fastcall FUN_006bef70(char *param_1)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  char *pcStack_68;
  code *pcVar2;
  undefined1 local_5c [8];
  char local_54 [8];
  undefined1 *local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 local_40 [8];
  char *local_38;
  char *local_34;
  char *local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00851788;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_30 = param_1;
  if (*param_1 == '\0') {
    local_4c = (undefined1 *)&pcStack_68;
    local_44 = shared_ptr<>(&stack0x00000004);
    local_48 = FUN_006cbe40(local_40);
    local_8._0_1_ = 1;
    pcStack_68 = local_54;
    FUN_00421ec0();
    FUN_006cc020();
    pcStack_68 = (char *)0x6beffb;
    pcStack_68 = (char *)FUN_006ab780();
    local_8._0_1_ = 2;
    pcVar2 = FUN_004bc8c0;
    local_38 = pcStack_68;
    local_34 = pcStack_68;
    FUN_0081e820("BZRNetInterface reset active_con due to websocket connection setup failure: ");
    uVar1 = FUN_0081e660();
    uVar1 = FUN_004bc590(uVar1);
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar1);
    pcStack_68 = (char *)0x6bf03c;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar2);
    local_8._0_1_ = 1;
    ~basic_string<>();
    std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
              ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_30 + 0x2e0));
    pcStack_68 = (char *)0x6bf066;
    FUN_006cb140();
    pcStack_68 = local_30;
    FUN_006db740(local_5c,FUN_006c35c0);
    pcStack_68 = (char *)0x6bf091;
    FUN_006db780();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006ca8c0();
  }
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

