
/* WARNING: Removing unreachable block (ram,0x006d3eae) */

void FUN_006d3990(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  CDHtmlElementEventSink *this;
  undefined4 in_stack_0000002c;
  undefined1 *puVar4;
  undefined1 auStack_2c0 [28];
  undefined4 uStack_2a4;
  undefined1 *puStack_2a0;
  _ATL_BASE_MODULE70 *p_Stack_29c;
  code *pcStack_298;
  undefined4 *puStack_294;
  undefined1 *puStack_290;
  undefined1 *puStack_28c;
  char *pcStack_288;
  code *pcStack_284;
  uint uStack_280;
  undefined1 auStack_26c [160];
  undefined1 local_1cc [8];
  undefined1 local_1c4 [12];
  undefined1 local_1b8 [8];
  undefined4 local_1b0;
  undefined4 local_1a8;
  undefined1 *local_1a4;
  undefined1 local_1a0 [8];
  undefined4 local_198;
  undefined1 local_194 [8];
  undefined1 local_18c [12];
  undefined1 *local_180;
  undefined1 *local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined1 local_158 [16];
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_134;
  undefined4 local_128;
  undefined1 local_124 [8];
  undefined1 *local_11c;
  undefined1 *local_118;
  undefined4 local_114;
  undefined1 local_110 [72];
  _ATL_BASE_MODULE70 local_c8 [128];
  undefined1 local_48 [28];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008532e1;
  local_10 = ExceptionList;
  uStack_280 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 3;
  pcStack_284 = (code *)0x0;
  pcStack_288 = (char *)0x3e3;
  puStack_28c = (undefined1 *)0x6d39da;
  local_14 = uStack_280;
  FUN_006d8cc0();
  pcStack_284 = (code *)local_194;
  pcStack_288 = (char *)in_stack_0000002c;
  puStack_28c = (undefined1 *)0x6d39ea;
  cVar1 = FUN_006ab920();
  if (cVar1 == '\0') {
    pcStack_284 = (code *)local_1cc;
    pcStack_288 = (char *)0x6d3a03;
    FUN_00421ec0();
    pcStack_288 = (char *)0x6d3a0a;
    puVar2 = (undefined4 *)FUN_006d7120();
    pcStack_284 = (code *)puVar2[1];
    pcStack_288 = (char *)*puVar2;
    puStack_28c = (undefined1 *)0x6d3a16;
    cVar1 = FUN_006de530();
    if (cVar1 == '\0') {
      pcStack_284 = (code *)0x6d3a78;
      FUN_00421ec0();
      pcStack_284 = (code *)0x6d3a7f;
      FUN_006d70d0();
      pcStack_284 = (code *)0x6d3a87;
      iVar3 = FUN_00667170();
      if (iVar3 == 0) {
        pcStack_284 = (code *)0x400;
        pcStack_288 = (char *)0x6d3b06;
        cVar1 = FUN_006d4590();
        if (cVar1 != '\0') {
          pcStack_284 = (code *)0x1;
          pcStack_288 = (char *)0x3;
          puStack_28c = (undefined1 *)0x6d3b20;
          FUN_00574400();
          local_8._0_1_ = 4;
          if (&stack0x00000000 == (undefined1 *)0x27c) {
            local_11c = (undefined1 *)0x0;
          }
          else {
            local_11c = auStack_26c;
          }
          pcStack_284 = (code *)0x898be4;
          pcStack_288 = local_11c;
          puStack_28c = (undefined1 *)0x6d3b5a;
          FUN_004bc590();
          pcStack_284 = (code *)0x6d3b68;
          _String_const_iterator<>();
          local_8._0_1_ = 5;
          pcStack_284 = (code *)0x6d3b77;
          _String_const_iterator<>();
          local_8 = CONCAT31(local_8._1_3_,6);
          pcStack_284 = (code *)&stack0x00000030;
          pcStack_288 = (char *)0x6d3b8a;
          FUN_006d4f10();
          while( true ) {
            pcStack_284 = (code *)local_18c;
            pcStack_288 = local_158;
            puStack_28c = (undefined1 *)0x6d3baa;
            cVar1 = FUN_006d7060();
            if (cVar1 == '\0') break;
            if (&stack0x00000000 == (undefined1 *)0x27c) {
              local_118 = (undefined1 *)0x0;
            }
            else {
              local_118 = auStack_26c;
            }
            pcStack_284 = (code *)&DAT_0088d764;
            pcStack_288 = local_48;
            puStack_28c = (undefined1 *)0x6d3bed;
            FUN_006d7020();
            puStack_28c = (undefined1 *)0x6d3bf4;
            pcStack_288 = (char *)FUN_006d72c0();
            puStack_28c = local_118;
            puStack_290 = (undefined1 *)0x6d3c01;
            pcStack_288 = (char *)FUN_006da360();
            puStack_28c = (undefined1 *)0x6d3c0a;
            FUN_004bc590();
            pcStack_284 = (code *)0x6d3b97;
            FUN_006d7040();
          }
          pcStack_284 = (code *)local_2c;
          pcStack_288 = (char *)0x6d3c21;
          pcStack_284 = (code *)GetPolicy();
          local_8._0_1_ = 7;
          pcStack_288 = (char *)0x400;
          puStack_28c = (undefined1 *)0x6d3c51;
          local_140 = pcStack_284;
          local_13c = pcStack_284;
          FUN_006d4480();
          local_8._0_1_ = 6;
          pcStack_284 = (code *)0x6d3c5d;
          ~basic_string<>();
          local_8._0_1_ = 5;
          pcStack_284 = (code *)0x6d3c6c;
          FUN_006cd590();
          local_8._0_1_ = 4;
          pcStack_284 = (code *)0x6d3c7b;
          FUN_006cd590();
          local_8 = CONCAT31(local_8._1_3_,3);
          pcStack_284 = (code *)0x6d3c8a;
          FUN_00417f10();
        }
        pcStack_284 = (code *)0x898bcc;
        pcStack_288 = (char *)0x400;
        puStack_28c = (undefined1 *)0x6d3ca2;
        FUN_006d08b0();
        pcStack_284 = (code *)0x6d3cad;
        FUN_0068b0a0();
        local_8._0_1_ = 8;
        local_148 = local_114;
        pcStack_284 = _1_exref;
        pcStack_288 = &stack0x00000014;
        puStack_28c = local_124;
        puStack_290 = &stack0x00000004;
        puStack_294 = &local_148;
        pcStack_298 = FUN_006d6190;
        p_Stack_29c = local_c8;
        puStack_2a0 = (undefined1 *)0x6d3ceb;
        p_Stack_29c = (_ATL_BASE_MODULE70 *)FUN_006de6c0();
        local_8._0_1_ = 9;
        local_17c = (undefined1 *)&pcStack_298;
        puStack_2a0 = (undefined1 *)0x6d3d1b;
        local_168 = p_Stack_29c;
        local_160 = p_Stack_29c;
        local_1a8 = FUN_006de740();
        p_Stack_29c = (_ATL_BASE_MODULE70 *)0x1388;
        puStack_2a0 = local_1b8;
        uStack_2a4 = 0x6d3d35;
        FUN_00421ec0();
        uStack_2a4 = 0x6d3d3c;
        pcStack_284 = (code *)FUN_006d4050();
        pcStack_288 = (char *)0x6d3d60;
        local_178 = pcStack_284;
        local_170 = pcStack_284;
        FID_conflict_operator_();
        pcStack_284 = (code *)0x6d3d6b;
        FUN_006ca8c0();
        local_8._0_1_ = 8;
        pcStack_284 = (code *)0x6d3d7a;
        ATL::_ATL_BASE_MODULE70::~_ATL_BASE_MODULE70(local_c8);
        local_174 = local_114;
        local_180 = auStack_2c0;
        local_198 = FUN_006de6c0(auStack_2c0,FUN_006d62e0,&local_174,&stack0x00000004,local_124,
                                 &stack0x00000014,_1_exref);
        local_8._0_1_ = 10;
        puVar4 = local_1a0;
        local_134 = local_198;
        FUN_00421ec0(puVar4);
        local_15c = FUN_006d42b0(puVar4);
        local_8._0_1_ = 0xb;
        puVar4 = local_110;
        local_128 = local_15c;
        FUN_00421ec0(puVar4);
        local_8._0_1_ = 0xc;
        pcStack_284 = (code *)FUN_006de7b0(puVar4);
        local_8._0_1_ = 0xd;
        local_1a4 = (undefined1 *)&puStack_290;
        puStack_294 = (undefined4 *)&stack0x00000030;
        pcStack_298 = (code *)0x6d3e59;
        local_16c = pcStack_284;
        local_144 = pcStack_284;
        local_1b0 = FUN_006d4f40();
        local_8._0_1_ = 0xe;
        puStack_294 = (undefined4 *)0x6d3e77;
        local_164 = local_1b0;
        this = (CDHtmlElementEventSink *)FUN_00421ec0();
        puStack_294 = (undefined4 *)0x6d3e7e;
        CDHtmlElementEventSink::~CDHtmlElementEventSink(this);
        local_8._0_1_ = 0xd;
        pcStack_298 = (code *)0x6d3e88;
        FUN_006de830();
        local_8._0_1_ = 0xc;
        pcStack_284 = (code *)0x6d3e9a;
        ~_String_val<>();
        local_8._0_1_ = 8;
        pcStack_284 = (code *)0x6d3ea9;
        FUN_006ca8c0();
        local_8._0_1_ = 3;
        pcStack_284 = (code *)0x6d3f6c;
        FUN_006ca8c0();
        local_8._0_1_ = 2;
        pcStack_284 = (code *)0x6d3f78;
        FUN_006ca8c0();
        local_8._0_1_ = 1;
        pcStack_284 = (code *)0x6d3f84;
        FUN_006ca8c0();
        local_8 = (uint)local_8._1_3_ << 8;
        pcStack_284 = (code *)0x6d3f90;
        std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                  ((function<void___cdecl(void)> *)&stack0x00000014);
        local_8 = 0xffffffff;
        pcStack_284 = (code *)0x6d3f9f;
        FUN_006cd590();
      }
      else {
        pcStack_284 = (code *)in_stack_0000002c;
        pcStack_288 = "asio async_resolve";
        puStack_28c = (undefined1 *)0x4;
        puStack_290 = (undefined1 *)0x6d3aa1;
        FUN_006de570();
        pcStack_284 = (code *)0x3;
        pcStack_288 = local_1c4;
        puStack_28c = (undefined1 *)0x6d3aaf;
        pcStack_284 = (code *)make_error_code();
        pcStack_288 = (char *)0x6d3abb;
        FUN_006cadd0();
        local_8._0_1_ = 2;
        pcStack_284 = (code *)0x6d3ac7;
        FUN_006ca8c0();
        local_8._0_1_ = 1;
        pcStack_284 = (code *)0x6d3ad3;
        FUN_006ca8c0();
        local_8 = (uint)local_8._1_3_ << 8;
        pcStack_284 = (code *)0x6d3adf;
        std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                  ((function<void___cdecl(void)> *)&stack0x00000014);
        local_8 = 0xffffffff;
        pcStack_284 = (code *)0x6d3aee;
        FUN_006cd590();
      }
      goto LAB_006d3f9f;
    }
  }
  pcStack_284 = (code *)0x898bb4;
  pcStack_288 = (char *)0x400;
  puStack_28c = (undefined1 *)0x6d3a38;
  FUN_006d08b0();
  local_8._0_1_ = 2;
  pcStack_284 = (code *)0x6d3a44;
  FUN_006ca8c0();
  local_8._0_1_ = 1;
  pcStack_284 = (code *)0x6d3a50;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  pcStack_284 = (code *)0x6d3a5c;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000014);
  local_8 = 0xffffffff;
  pcStack_284 = (code *)0x6d3a6b;
  FUN_006cd590();
LAB_006d3f9f:
  ExceptionList = local_10;
  uStack_280 = 0x6d3fb4;
  FUN_0083e885();
  return;
}

