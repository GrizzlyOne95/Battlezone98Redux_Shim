
/* WARNING: Removing unreachable block (ram,0x006d06e9) */

void FUN_006d00a0(void)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 auStack_304 [28];
  undefined4 uStack_2e8;
  undefined1 *puStack_2e4;
  undefined4 uStack_2e0;
  undefined1 *puStack_2dc;
  code *pcStack_2d8;
  undefined4 *puStack_2d4;
  char *pcStack_2cc;
  char local_2c0 [8];
  char local_2b8 [8];
  undefined4 local_2b0;
  undefined1 *local_2ac;
  char local_2a8 [8];
  undefined1 *local_2a0;
  undefined1 *local_29c;
  undefined4 local_298;
  undefined1 local_294 [8];
  undefined4 local_28c;
  undefined1 local_288 [8];
  char local_280 [4];
  undefined4 local_27c [2];
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  char *local_23c;
  char *local_234;
  undefined4 local_230;
  char *local_22c;
  undefined4 local_228;
  char *local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_214;
  undefined1 local_210 [8];
  char local_208 [8];
  undefined4 local_200;
  undefined1 local_1fc [136];
  undefined1 local_174 [56];
  char local_13c [224];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  char local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853004;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 2;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    pcStack_2cc = local_280;
    select_on_container_copy_construction();
    pcStack_2cc = local_2a8;
    local_268 = FUN_006dd910();
    pcStack_2cc = (char *)0x6d0131;
    FID_conflict_operator_();
    FUN_006ca8c0();
  }
  local_2ac = (undefined1 *)&pcStack_2cc;
  puStack_2d4 = (undefined4 *)0x6d0150;
  local_298 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                        ((shared_ptr<class___ExceptionPtr> *)&pcStack_2cc,
                         (shared_ptr<class___ExceptionPtr> *)&stack0x0000000c);
  FUN_00421ec0();
  FUN_006d3fc0();
  FUN_00421ec0();
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006d4030();
  pcStack_2cc = (char *)0x6d017d;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_5c,pbVar2);
  local_8._0_1_ = 3;
  basic_string<>();
  local_8._0_1_ = 4;
  basic_string<>();
  local_8._0_1_ = 5;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    FUN_006ab750();
    pcStack_2cc = local_208;
    FUN_006dcb50();
    local_8._0_1_ = 6;
    FUN_00421ec0();
    cVar1 = FUN_006b5d20();
    if (cVar1 == '\0') {
      pcStack_2cc = local_2b8;
      make_error_code();
      pcStack_2cc = (char *)0x6d024a;
      FUN_006cadd0();
      local_8._0_1_ = 5;
      FUN_006ca8c0();
      local_8._0_1_ = 4;
      ~basic_string<>();
      local_8._0_1_ = 3;
      ~basic_string<>();
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8._0_1_ = 1;
      FUN_006ca8c0();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x00000014);
      goto LAB_006d07dd;
    }
    pcStack_2cc = (char *)0x6d02b8;
    FUN_00421ec0();
    pcStack_2cc = (char *)0x6d02bf;
    local_270 = FUN_006b5e90();
    local_8._0_1_ = 7;
    pcStack_2cc = local_2c0;
    local_248 = local_270;
    FUN_00421ec0();
    puVar3 = (undefined4 *)FUN_006d42f0();
    local_218 = *puVar3;
    local_214 = puVar3[1];
    local_8._0_1_ = 6;
    ~basic_string<>();
    cVar1 = FUN_006ab7d0();
    if (cVar1 != '\0') {
      pcStack_2cc = (char *)0x6d0333;
      FUN_006cadd0();
      local_8._0_1_ = 5;
      FUN_006ca8c0();
      local_8._0_1_ = 4;
      ~basic_string<>();
      local_8._0_1_ = 3;
      ~basic_string<>();
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8._0_1_ = 1;
      FUN_006ca8c0();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x00000014);
      goto LAB_006d07dd;
    }
    FUN_00421ec0();
    FUN_00583e30();
    pcStack_2cc = (char *)0x6d03ad;
    FID_conflict_operator_();
    pcStack_2cc = (char *)0x6d03bf;
    FUN_00421ec0();
    pcStack_2cc = (char *)0x6d03c6;
    local_220 = FUN_006b5f70();
    pcStack_2cc = (char *)0x6d03db;
    FUN_0045e0f0();
    ~basic_string<>();
    local_8._0_1_ = 5;
    FUN_006ca8c0();
  }
  else {
    FUN_00421ec0();
    FUN_00583e30();
    pcStack_2cc = (char *)0x6d01c0;
    FID_conflict_operator_();
    pcStack_2cc = (char *)0x6d01cc;
    FUN_00421ec0();
    pcStack_2cc = (char *)0x6d01d3;
    local_260 = FUN_006b5f70();
    pcStack_2cc = (char *)0x6d01e8;
    FUN_0045e0f0();
    ~basic_string<>();
  }
  pcStack_2cc = local_44;
  puStack_2d4 = (undefined4 *)0x6d040d;
  FUN_006d4d90();
  local_8._0_1_ = 8;
  pcStack_2cc = (char *)0x6d0424;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_2cc = "starting async DNS resolve for ";
    puStack_2d4 = (undefined4 *)0x6d0444;
    pcStack_2cc = (char *)FUN_0066e860();
    local_8._0_1_ = 9;
    puStack_2d4 = (undefined4 *)0x6d0475;
    local_22c = pcStack_2cc;
    local_224 = pcStack_2cc;
    pcStack_2cc = (char *)FUN_0045f170();
    local_8._0_1_ = 10;
    puStack_2d4 = (undefined4 *)0x6d04a5;
    local_23c = pcStack_2cc;
    local_234 = pcStack_2cc;
    local_24c = FUN_00426a20();
    local_8._0_1_ = 0xb;
    pcStack_2cc = (char *)0x400;
    local_244 = local_24c;
    FUN_006d4480();
    local_8._0_1_ = 10;
    ~basic_string<>();
    local_8._0_1_ = 9;
    ~basic_string<>();
    local_8._0_1_ = 8;
    ~basic_string<>();
  }
  FUN_0068b0a0();
  local_8._0_1_ = 0xc;
  local_254 = local_200;
  pcStack_2cc = &stack0x00000014;
  puStack_2d4 = &local_254;
  pcStack_2d8 = FUN_006d3850;
  puStack_2dc = local_174;
  uStack_2e0 = 0x6d0549;
  uStack_2e0 = FUN_006dd9f0();
  local_8._0_1_ = 0xd;
  local_29c = (undefined1 *)&puStack_2dc;
  puStack_2e4 = (undefined1 *)0x6d0579;
  local_264 = uStack_2e0;
  local_25c = uStack_2e0;
  local_2b0 = FUN_006dda60();
  uStack_2e0 = 5000;
  puStack_2e4 = local_288;
  uStack_2e8 = 0x6d0593;
  FUN_00421ec0();
  uStack_2e8 = 0x6d059a;
  local_274 = FUN_006d4050();
  pcStack_2cc = (char *)0x6d05be;
  local_26c = local_274;
  FID_conflict_operator_();
  FUN_006ca8c0();
  local_8._0_1_ = 0xc;
  ~<>();
  local_27c[0] = local_200;
  local_2a0 = auStack_304;
  local_28c = FUN_006ddad0(auStack_304,FUN_006d3990,local_27c,&stack0x00000004,local_210,
                           &stack0x00000014,_1_exref,_2_exref);
  local_8._0_1_ = 0xe;
  puVar4 = local_294;
  local_250 = local_28c;
  FUN_00421ec0(puVar4);
  local_228 = FUN_006d42b0(puVar4);
  local_8._0_1_ = 0xf;
  puVar4 = local_1fc;
  local_21c = local_228;
  FUN_00421ec0(puVar4);
  local_8._0_1_ = 0x10;
  local_258 = FUN_006ddb50(puVar4);
  local_8._0_1_ = 0x11;
  pcStack_2cc = local_13c;
  local_230 = local_258;
  FUN_00421ec0();
  FUN_006ddbd0();
  local_8._0_1_ = 0x10;
  ~_String_val<>();
  local_8._0_1_ = 0xc;
  FUN_006ca8c0();
  local_8._0_1_ = 8;
  FUN_006ca8c0();
  local_8._0_1_ = 5;
  FUN_006d1230();
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8._0_1_ = 3;
  ~basic_string<>();
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8._0_1_ = 1;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000014);
LAB_006d07dd:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

