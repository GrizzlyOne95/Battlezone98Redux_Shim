
/* WARNING: Removing unreachable block (ram,0x007000a8) */

void FUN_006fff30(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_154 [40];
  undefined4 uStack_12c;
  undefined1 *puStack_128;
  undefined1 auStack_124 [40];
  undefined4 uStack_fc;
  undefined1 *puStack_f8;
  CDHtmlElementEventSink *pCStack_f4;
  undefined1 *puStack_f0;
  uint uStack_ec;
  undefined1 local_e4 [8];
  undefined1 *local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined1 local_c0 [8];
  undefined1 *local_b8;
  undefined4 local_b4;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a0;
  undefined4 local_94;
  CDHtmlElementEventSink *local_90;
  undefined1 local_8c [120];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00856221;
  local_10 = ExceptionList;
  uStack_ec = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_f0 = (undefined1 *)param_2;
  pCStack_f4 = (CDHtmlElementEventSink *)param_1;
  puStack_f8 = local_e4;
  uStack_fc = 0x6fff7d;
  local_14 = uStack_ec;
  puStack_f0 = (undefined1 *)FUN_006ae490();
  pCStack_f4 = (CDHtmlElementEventSink *)0x6fff8f;
  FUN_006e6cb0();
  puStack_f0 = local_c0;
  pCStack_f4 = (CDHtmlElementEventSink *)0x6fffae;
  local_ac = FUN_006d6530();
  local_8._0_1_ = 1;
  local_b8 = auStack_124;
  local_dc = auStack_154;
  local_a0 = local_ac;
  local_d8 = FUN_006f1ee0(auStack_154,FUN_006f5e70,local_ac,&stack0x0000000c,_1_exref,_2_exref);
  local_d4 = FUN_006feeb0(auStack_124,local_90 + 0x4c8);
  puStack_128 = local_8c;
  uStack_12c = 0x700043;
  local_b4 = local_d4;
  FUN_00421ec0();
  uStack_12c = 0x70004a;
  puStack_f0 = (undefined1 *)FUN_006fef60();
  local_8._0_1_ = 2;
  pCStack_f4 = local_90 + 0x78;
  puStack_f8 = (undefined1 *)0x70007c;
  local_a8 = puStack_f0;
  local_94 = puStack_f0;
  CDHtmlElementEventSink::~CDHtmlElementEventSink(local_90);
  uStack_fc = 0x700082;
  FUN_006fefe0();
  local_8._0_1_ = 1;
  puStack_f0 = (undefined1 *)0x700094;
  ~_String_val<>();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_f0 = (undefined1 *)0x7000a3;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  puStack_f0 = (undefined1 *)0x700185;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x0000000c);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

