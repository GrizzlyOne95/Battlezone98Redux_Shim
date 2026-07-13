
void FUN_006e7710(void)

{
  char cVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 in_stack_0000001c;
  undefined1 *puStack_200;
  char *pcStack_1fc;
  bool bVar3;
  undefined1 auStack_1d4 [160];
  basic_istream<char,struct_std::char_traits<char>_> local_134 [136];
  undefined1 *local_ac;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined1 *local_7c;
  int local_78;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085471f;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    FUN_006d08b0();
  }
  FUN_006d8cc0();
  cVar1 = FUN_006ab920();
  if (cVar1 == '\0') {
    FUN_00421ec0();
    FUN_00421ec0();
    FUN_006d7120();
    cVar1 = FUN_006de530();
    if (cVar1 == '\0') {
      FUN_00421ec0();
      FUN_00421ec0();
      FUN_006d70d0();
      iVar2 = FUN_00667170();
      if (iVar2 == 0) {
        cVar1 = FUN_006ab7d0();
        if (cVar1 == '\0') {
          FUN_006d47b0();
          make_error_code();
          FUN_006cadd0();
          local_8 = 0xffffffff;
          std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                    ((function<void___cdecl(void)> *)&stack0x00000004);
          goto LAB_006e7b9d;
        }
        bVar3 = false;
        iVar2 = FUN_00421ec0();
        std::basic_istream<char,struct_std::char_traits<char>_>::
        basic_istream<char,struct_std::char_traits<char>_>
                  (local_134,(basic_streambuf<char,struct_std::char_traits<char>_> *)(iVar2 + 0x110)
                   ,bVar3);
        local_8._0_1_ = 3;
        FUN_00421ec0();
        FUN_006b95f0();
        FUN_00421ec0();
        cVar1 = FUN_006b8ef0();
        if (cVar1 == '\0') {
          make_error_code();
          FUN_006cadd0();
          local_8 = (uint)local_8._1_3_ << 8;
          std::basic_istream<char,struct_std::char_traits<char>_>::_vbase_destructor_(local_134);
          local_8 = 0xffffffff;
          std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                    ((function<void___cdecl(void)> *)&stack0x00000004);
          goto LAB_006e7b9d;
        }
        FUN_00421ec0();
        local_88 = FUN_006b9760();
        local_8._0_1_ = 4;
        local_80 = local_88;
        FUN_006d4480();
        local_8._0_1_ = 3;
        ~basic_string<>();
        FUN_00421ec0();
        iVar2 = FUN_006b8f30();
        if (iVar2 != 200) {
          FUN_00574400();
          local_8._0_1_ = 5;
          if (&stack0x00000000 == (undefined1 *)0x1e4) {
            local_7c = (undefined1 *)0x0;
          }
          else {
            local_7c = auStack_1d4;
          }
          FUN_00421ec0();
          FUN_006b8f50();
          FUN_00421ec0();
          iVar2 = FUN_006b8f30();
          pcStack_1fc = "Proxy connection error: ";
          puStack_200 = local_7c;
          this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
          pcStack_1fc = (char *)0x6e7aa7;
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar2);
          pcStack_1fc = (char *)0x6e7aad;
          FUN_004bc590();
          FUN_00574730();
          FUN_004bc590();
          local_98 = GetPolicy();
          local_8._0_1_ = 6;
          local_90 = local_98;
          FUN_006d46a0();
          local_8._0_1_ = 5;
          ~basic_string<>();
          make_error_code();
          FUN_006cadd0();
          local_8._0_1_ = 3;
          FUN_00417f10();
          local_8 = (uint)local_8._1_3_ << 8;
          std::basic_istream<char,struct_std::char_traits<char>_>::_vbase_destructor_(local_134);
          local_8 = 0xffffffff;
          std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                    ((function<void___cdecl(void)> *)&stack0x00000004);
          goto LAB_006e7b9d;
        }
        std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                  ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_78 + 0x5c));
        local_ac = (undefined1 *)&puStack_200;
        local_a0 = function<>(&stack0x00000004);
        FUN_006e6310();
        local_8 = (uint)local_8._1_3_ << 8;
        std::basic_istream<char,struct_std::char_traits<char>_>::_vbase_destructor_(local_134);
      }
      else {
        local_9c = FUN_004486a0();
        local_8._0_1_ = 1;
        local_84 = local_9c;
        local_94 = FUN_006dd7f0();
        local_8._0_1_ = 2;
        local_8c = local_94;
        FUN_006d46a0();
        local_8._0_1_ = 1;
        ~basic_string<>();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        make_error_code();
        FUN_006cadd0();
      }
      local_8 = 0xffffffff;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x00000004);
      goto LAB_006e7b9d;
    }
  }
  FUN_006d47b0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
LAB_006e7b9d:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

