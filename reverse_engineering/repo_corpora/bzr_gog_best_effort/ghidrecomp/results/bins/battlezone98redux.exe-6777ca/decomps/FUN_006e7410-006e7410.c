
/* WARNING: Removing unreachable block (ram,0x006e7605) */

void FUN_006e7410(void)

{
  char cVar1;
  undefined1 *puVar2;
  undefined1 auStack_124 [28];
  undefined4 uStack_108;
  undefined4 uStack_104;
  int iStack_100;
  undefined1 *puStack_fc;
  char *pcStack_f8;
  uint uStack_f4;
  undefined1 local_f0 [8];
  undefined4 local_e8;
  undefined1 *local_dc;
  undefined1 local_d8 [8];
  undefined4 local_d0;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  CDHtmlElementEventSink *local_b0;
  undefined1 local_ac [128];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008546b1;
  local_10 = ExceptionList;
  uStack_f4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_f8 = (char *)0x400;
  puStack_fc = (undefined1 *)0x6e745b;
  local_14 = uStack_f4;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_f8 = "asio connection proxy_read";
    puStack_fc = (undefined1 *)0x400;
    iStack_100 = 0x6e747a;
    FUN_006d08b0();
  }
  pcStack_f8 = (char *)0x6e7488;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    pcStack_f8 = "assertion failed: !m_proxy_data in asio::connection::proxy_read";
    puStack_fc = (undefined1 *)0x2;
    iStack_100 = 0x6e74a4;
    FUN_006d47b0();
    pcStack_f8 = "\x05\\\x01";
    FUN_00421ec0();
    pcStack_f8 = (char *)0x6e74be;
    FUN_00421ec0();
    pcStack_f8 = (char *)0x6e74c5;
    FUN_006d70d0();
    pcStack_f8 = (char *)0x1;
    puStack_fc = local_f0;
    iStack_100 = 0x6e74d3;
    pcStack_f8 = (char *)make_error_code();
    puStack_fc = (undefined1 *)0x6e74df;
    FUN_006cadd0();
    local_8 = 0xffffffff;
    pcStack_f8 = (char *)0x6e74ee;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  else {
    pcStack_f8 = "\r\n\r\n";
    puStack_fc = (undefined1 *)0x6e750d;
    basic_string<>();
    local_8._0_1_ = 1;
    pcStack_f8 = local_d8;
    puStack_fc = (undefined1 *)0x6e7523;
    local_c4 = FUN_006d6530();
    local_8._0_1_ = 2;
    local_dc = auStack_124;
    local_c0 = local_c4;
    local_e8 = FUN_006f1ee0(auStack_124,FUN_006e7710,local_c4,&stack0x00000004,_1_exref,_2_exref);
    puVar2 = local_ac;
    FUN_00421ec0(puVar2);
    pcStack_f8 = (char *)FUN_006f1f50(puVar2);
    local_8._0_1_ = 3;
    puStack_fc = local_2c;
    iStack_100 = 0x6e75bc;
    local_d0 = pcStack_f8;
    local_c8 = pcStack_f8;
    iStack_100 = FUN_00421ec0();
    iStack_100 = iStack_100 + 0x110;
    uStack_104 = 0x6e75cd;
    CDHtmlElementEventSink::~CDHtmlElementEventSink(local_b0);
    uStack_108 = 0x6e75d3;
    FUN_006f1fd0();
    local_8._0_1_ = 2;
    pcStack_f8 = (char *)0x6e75e5;
    ~_String_val<>();
    local_8._0_1_ = 1;
    pcStack_f8 = (char *)0x6e75f4;
    FUN_006ca8c0();
    local_8 = (uint)local_8._1_3_ << 8;
    pcStack_f8 = (char *)0x6e7600;
    ~basic_string<>();
    local_8 = 0xffffffff;
    pcStack_f8 = (char *)0x6e76e6;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  ExceptionList = local_10;
  uStack_f4 = 0x6e76fb;
  FUN_0083e885();
  return;
}

