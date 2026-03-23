
/* WARNING: Removing unreachable block (ram,0x006f2c70) */

void FUN_006f2a90(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 auStack_160 [40];
  undefined4 uStack_138;
  undefined1 *puStack_134;
  undefined1 auStack_130 [40];
  undefined4 uStack_108;
  undefined1 *puStack_104;
  CDHtmlElementEventSink *pCStack_100;
  undefined1 *puStack_fc;
  uint uStack_f8;
  undefined1 local_f0 [8];
  undefined1 local_e8 [4];
  undefined1 *local_e4;
  undefined4 local_e0;
  undefined1 *local_dc;
  undefined4 local_cc;
  undefined1 local_c8 [12];
  undefined1 local_bc [4];
  undefined4 local_b8;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a4;
  undefined4 local_98;
  undefined4 local_94;
  CDHtmlElementEventSink *local_90;
  undefined1 local_8c [120];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00855341;
  local_10 = ExceptionList;
  uStack_f8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_fc = (undefined1 *)0x6f2ad4;
  local_14 = uStack_f8;
  FUN_00423890();
  puStack_fc = local_bc;
  pCStack_100 = (CDHtmlElementEventSink *)0x6f2ae3;
  puVar2 = (undefined4 *)FUN_0041fc00();
  local_94 = *puVar2;
  while( true ) {
    puStack_fc = local_e8;
    pCStack_100 = (CDHtmlElementEventSink *)0x6f2b07;
    puStack_fc = (undefined1 *)FUN_0041fc60();
    pCStack_100 = (CDHtmlElementEventSink *)0x6f2b13;
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    puStack_fc = (undefined1 *)0x6f2b25;
    iVar3 = get();
    puStack_fc = *(undefined1 **)(iVar3 + 4);
    pCStack_100 = (CDHtmlElementEventSink *)0x6f2b34;
    puVar2 = (undefined4 *)get();
    pCStack_100 = (CDHtmlElementEventSink *)*puVar2;
    puStack_104 = local_f0;
    uStack_108 = 0x6f2b43;
    puStack_fc = (undefined1 *)FUN_006ae490();
    pCStack_100 = (CDHtmlElementEventSink *)0x6f2b55;
    FUN_006e6cb0();
    puStack_fc = (undefined1 *)0x6f2af8;
    FUN_00496680();
  }
  puStack_fc = local_c8;
  pCStack_100 = (CDHtmlElementEventSink *)0x6f2b76;
  local_b0 = FUN_006d6530();
  local_8._0_1_ = 1;
  local_e4 = auStack_130;
  local_dc = auStack_160;
  local_a4 = local_b0;
  local_cc = FUN_006f1ee0(auStack_160,FUN_006f5e70,local_b0,&stack0x00000008,_1_exref,_2_exref);
  local_e0 = FUN_006feeb0(auStack_130,local_90 + 0x4c8);
  puStack_134 = local_8c;
  uStack_138 = 0x6f2c0b;
  local_b8 = local_e0;
  FUN_00421ec0();
  uStack_138 = 0x6f2c12;
  puStack_fc = (undefined1 *)FUN_006fef60();
  local_8._0_1_ = 2;
  pCStack_100 = local_90 + 0x78;
  puStack_104 = (undefined1 *)0x6f2c44;
  local_ac = puStack_fc;
  local_98 = puStack_fc;
  CDHtmlElementEventSink::~CDHtmlElementEventSink(local_90);
  uStack_108 = 0x6f2c4a;
  FUN_006fefe0();
  local_8._0_1_ = 1;
  puStack_fc = (undefined1 *)0x6f2c5c;
  ~_String_val<>();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_fc = (undefined1 *)0x6f2c6b;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  puStack_fc = (undefined1 *)0x6f2d4d;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000008);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

