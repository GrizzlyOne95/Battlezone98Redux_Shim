
/* WARNING: Removing unreachable block (ram,0x006e68c8) */

void FUN_006e6560(void)

{
  char cVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined1 *puVar3;
  undefined1 auStack_178 [12];
  undefined4 uStack_16c;
  undefined1 *puStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined1 *puStack_15c;
  code *pcStack_158;
  undefined1 *puStack_154;
  CDHtmlElementEventSink *pCStack_150;
  code *pcStack_14c;
  uint uStack_148;
  undefined1 local_144 [8];
  undefined1 local_13c [8];
  undefined4 local_134;
  undefined1 local_130 [8];
  undefined1 *local_128;
  undefined1 *local_11c;
  undefined1 local_118 [8];
  undefined1 local_110 [8];
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  CDHtmlElementEventSink *local_c8;
  undefined1 local_c4 [56];
  undefined1 local_8c [96];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008545e7;
  local_10 = ExceptionList;
  uStack_148 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_14c = (code *)0x400;
  pCStack_150 = (CDHtmlElementEventSink *)0x6e65ab;
  local_14 = uStack_148;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_14c = (code *)0x898d08;
    pCStack_150 = (CDHtmlElementEventSink *)0x400;
    puStack_154 = (undefined1 *)0x6e65ca;
    FUN_006d08b0();
  }
  pcStack_14c = (code *)0x6e65d8;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    pcStack_14c = (code *)0x898d40;
    pCStack_150 = (CDHtmlElementEventSink *)0x2;
    puStack_154 = (undefined1 *)0x6e65f4;
    FUN_006d47b0();
    pcStack_14c = (code *)0x1;
    pCStack_150 = (CDHtmlElementEventSink *)local_144;
    puStack_154 = (undefined1 *)0x6e6602;
    pcStack_14c = (code *)make_error_code();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e660e;
    FUN_006cadd0();
    local_8 = 0xffffffff;
    pcStack_14c = (code *)0x6e661d;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  else {
    pcStack_14c = (code *)local_2c;
    pCStack_150 = (CDHtmlElementEventSink *)0x6e6634;
    FUN_00421ec0();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e663b;
    pcStack_14c = (code *)FUN_006b87d0();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e6656;
    local_dc = pcStack_14c;
    FUN_00421ec0();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e6662;
    FUN_0045e0f0();
    pcStack_14c = (code *)0x6e666a;
    ~basic_string<>();
    pcStack_14c = (code *)0x6e6678;
    FUN_00421ec0();
    pcStack_14c = (code *)0x6e6684;
    pcStack_14c = (code *)FUN_004170c0();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e6693;
    FUN_00421ec0();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e669f;
    pCStack_150 = (CDHtmlElementEventSink *)FUN_00430770();
    puStack_154 = local_13c;
    pcStack_158 = (code *)0x6e66ac;
    pcStack_14c = (code *)FUN_006ae490();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e66be;
    FUN_006e6cb0();
    pcStack_14c = (code *)0x6e66cc;
    iVar2 = FUN_00421ec0();
    pcStack_14c = (code *)(iVar2 + 0xf8);
    pCStack_150 = (CDHtmlElementEventSink *)0x400;
    puStack_154 = (undefined1 *)0x6e66e5;
    FUN_006d4480();
    pcStack_14c = (code *)local_110;
    pCStack_150 = (CDHtmlElementEventSink *)0x6e66f7;
    puStack_154 = (undefined1 *)FUN_006d6530();
    local_8._0_1_ = 1;
    pcStack_14c = _1_exref;
    pCStack_150 = (CDHtmlElementEventSink *)&stack0x00000004;
    pcStack_158 = FUN_006e70d0;
    puStack_15c = local_8c;
    uStack_160 = 0x6e672f;
    local_fc = puStack_154;
    local_f4 = puStack_154;
    uStack_164 = FUN_006f0920();
    local_8._0_1_ = 2;
    local_11c = (undefined1 *)&uStack_160;
    puStack_168 = (undefined1 *)0x6e675f;
    local_104 = uStack_164;
    local_f8 = uStack_164;
    local_108 = FUN_006f0980();
    uStack_164 = 0x6e6773;
    iVar2 = FUN_00421ec0();
    uStack_164 = *(undefined4 *)(iVar2 + 0x158);
    puStack_168 = local_118;
    uStack_16c = 0x6e678c;
    pcStack_14c = (code *)FUN_006d4050();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e67b3;
    local_ec = pcStack_14c;
    local_d8 = pcStack_14c;
    FUN_00421ec0();
    pCStack_150 = (CDHtmlElementEventSink *)0x6e67bf;
    FID_conflict_operator_();
    pcStack_14c = (code *)0x6e67ca;
    FUN_006ca8c0();
    local_8._0_1_ = 1;
    pcStack_14c = (code *)0x6e67d9;
    FUN_006e4380();
    local_8._0_1_ = 0;
    pcStack_14c = (code *)0x6e67e8;
    FUN_006ca8c0();
    pcStack_14c = (code *)local_130;
    pCStack_150 = (CDHtmlElementEventSink *)0x6e6807;
    local_f0 = FUN_006d6530();
    local_8._0_1_ = 3;
    local_128 = auStack_178;
    local_e0 = local_f0;
    local_134 = FUN_006f0920(auStack_178,FUN_006e71d0,local_f0,&stack0x00000004,_1_exref);
    puVar3 = local_c4;
    FUN_00421ec0(puVar3);
    pcStack_14c = (code *)FUN_006f1c30(puVar3);
    local_8._0_1_ = 4;
    pCStack_150 = local_c8 + 0x78;
    puStack_154 = (undefined1 *)0x6e689c;
    local_100 = pcStack_14c;
    local_e8 = pcStack_14c;
    CDHtmlElementEventSink::~CDHtmlElementEventSink(local_c8);
    pcStack_158 = (code *)0x6e68a2;
    puStack_154 = (undefined1 *)extraout_EAX;
    FUN_006f1cb0();
    local_8._0_1_ = 3;
    pcStack_14c = (code *)0x6e68b4;
    ~_String_val<>();
    local_8 = (uint)local_8._1_3_ << 8;
    pcStack_14c = (code *)0x6e68c3;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    pcStack_14c = (code *)0x6e6977;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  ExceptionList = local_10;
  uStack_148 = 0x6e698c;
  FUN_0083e885();
  return;
}

