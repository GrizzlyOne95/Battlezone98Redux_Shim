
/* WARNING: Removing unreachable block (ram,0x006ffe06) */

void FUN_006ffbc0(uint param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 *puVar2;
  undefined1 auStack_238 [40];
  undefined4 uStack_210;
  undefined1 *puStack_20c;
  undefined1 auStack_208 [32];
  undefined4 uStack_1e8;
  undefined1 *puStack_1e4;
  undefined4 uStack_1e0;
  undefined1 *puStack_1dc;
  char *pcStack_1d8;
  uint uVar3;
  undefined1 auStack_1b8 [168];
  undefined1 local_110 [8];
  undefined4 local_108;
  undefined1 *local_100;
  undefined4 local_fc;
  undefined1 local_f0 [20];
  undefined1 *local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_bc;
  undefined4 local_b0;
  undefined1 *local_ac;
  CDHtmlElementEventSink *local_a8;
  undefined1 local_a4 [144];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008561c4;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_1d8 = (char *)0x6ffc0c;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_1d8 = (char *)0x3;
    puStack_1dc = (undefined1 *)0x6ffc26;
    FUN_00574400();
    local_8._0_1_ = 1;
    if (&stack0x00000000 == (undefined1 *)0x1c8) {
      local_ac = (undefined1 *)0x0;
    }
    else {
      local_ac = auStack_1b8;
    }
    pcStack_1d8 = "asio async_read_at_least: ";
    puStack_1dc = local_ac;
    uStack_1e0 = 0x6ffc64;
    uVar3 = param_1;
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    pcStack_1d8 = (char *)0x6ffc6f;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar3);
    pcStack_1d8 = (char *)0x6ffc7e;
    local_c8 = GetPolicy();
    local_8._0_1_ = 2;
    pcStack_1d8 = (char *)0x400;
    puStack_1dc = (undefined1 *)0x6ffcae;
    local_bc = local_c8;
    FUN_006d4480();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
  }
  pcStack_1d8 = (char *)0x6ffce8;
  local_d8 = FUN_006d6530();
  local_8._0_1_ = 3;
  local_100 = auStack_208;
  local_dc = auStack_238;
  local_d0 = local_d8;
  local_108 = FUN_006f1ee0(auStack_238,FUN_00704fe0,local_d8,&stack0x00000010,_1_exref,_2_exref);
  local_fc = FUN_006feeb0(auStack_208,local_a8 + 0xc0);
  puStack_20c = local_a4;
  uStack_210 = 0x6ffd7d;
  local_d4 = local_fc;
  FUN_00421ec0();
  uStack_210 = 0x6ffd84;
  local_cc = FUN_006fef60();
  local_8._0_1_ = 4;
  pcStack_1d8 = (char *)param_1;
  puStack_1dc = local_f0;
  uStack_1e0 = 0x6ffdb1;
  local_b0 = local_cc;
  puVar2 = (undefined4 *)make_move_iterator<>();
  pcStack_1d8 = (char *)*puVar2;
  puStack_1dc = (undefined1 *)param_3;
  uStack_1e0 = param_2;
  puStack_1e4 = local_110;
  uStack_1e8 = 0x6ffdcb;
  puStack_1dc = (undefined1 *)FUN_006ae490();
  uStack_1e0 = 0x6ffdda;
  CDHtmlElementEventSink::~CDHtmlElementEventSink(local_a8);
  puStack_1e4 = (undefined1 *)0x6ffde0;
  FUN_0070ebb0();
  local_8._0_1_ = 3;
  ~_String_val<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000010);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

