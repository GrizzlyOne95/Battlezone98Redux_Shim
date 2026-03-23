
void FUN_00667ed0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  allocator<char> *paVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  undefined4 *puVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this;
  undefined1 *puVar8;
  undefined1 *puVar9;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar10;
  undefined1 local_2e4 [8];
  undefined1 local_2dc [4];
  undefined1 local_2d8 [4];
  undefined1 local_2d4 [8];
  undefined1 local_2cc [8];
  undefined1 local_2c4 [8];
  undefined1 local_2bc [8];
  undefined4 local_2b4;
  int local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_2a4;
  undefined4 local_2a0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_27c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  uint local_248;
  undefined1 local_244 [8];
  undefined4 local_23c;
  int local_238;
  uint local_234;
  int local_230 [13];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_1fc [24];
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined1 local_1dc [24];
  undefined1 local_1c4 [24];
  undefined1 local_1ac [24];
  undefined1 local_194 [24];
  undefined1 local_17c [24];
  undefined1 local_164 [24];
  undefined1 local_14c [24];
  undefined1 local_134 [24];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e52b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  local_234 = FUN_00669ca0(0x2f,0xffffffff);
  local_248 = FUN_00669ca0(0x5c,0xffffffff);
  if ((local_234 == 0xffffffff) || ((local_248 != 0xffffffff && (local_234 < local_248)))) {
    local_234 = local_248;
  }
  basic_string<>(uVar2);
  local_8 = 0;
  if (local_234 != 0xffffffff) {
    local_290 = FUN_0045e1d0(local_134,0,local_234 + 1);
    FUN_0045e0f0(local_290);
    ~basic_string<>();
  }
  FUN_006678e0(local_8c,local_238 + 4,param_1);
  local_8._0_1_ = 1;
  FUN_00666890(param_4,0);
  local_8._0_1_ = 2;
  cVar1 = FUN_00667410(local_5c);
  if (cVar1 == '\0') {
    local_8._0_1_ = 1;
    FUN_004180b0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    vector<>();
    local_8._0_1_ = 3;
    FUN_004fbb60();
    FUN_004fbb60();
    FUN_00667590();
    local_8._0_1_ = 4;
    FUN_006675b0(local_5c,local_2cc);
    local_8._0_1_ = 5;
    cVar1 = FUN_004c85a0();
    if (cVar1 != '\0') {
      FUN_006676e0(local_2c4);
      local_8._0_1_ = 6;
      while (cVar1 = FUN_0066e6d0(local_244,local_2d4), cVar1 != '\0') {
        puVar9 = local_2bc;
        puVar8 = local_2e4;
        FUN_0066add0(puVar8,puVar9);
        FUN_006674d0(puVar8,puVar9);
        local_2b0 = get();
        if (local_2b0 == 3) {
          paVar3 = (allocator<char> *)FUN_0066add0();
          uVar4 = std::allocator<char>::allocator<char>(paVar3);
          FUN_0066aee0(uVar4);
        }
        else {
          iVar5 = FUN_00667170();
          if (iVar5 == 0) {
            FUN_006686b0();
            local_8._0_1_ = 7;
            local_230[0] = local_238;
            puVar9 = local_d4;
            paVar3 = (allocator<char> *)FUN_0066add0(puVar9);
            std::allocator<char>::allocator<char>(paVar3);
            local_280 = FUN_008405e0(puVar9);
            local_8._0_1_ = 8;
            local_270 = local_280;
            local_2a8 = FUN_00417fd0(local_bc);
            local_8._0_1_ = 9;
            local_288 = local_2a8;
            uVar4 = FUN_0041f870();
            local_2a0 = FUN_0048b7d0(local_164,local_44,uVar4);
            FUN_0045e0f0(local_2a0);
            ~basic_string<>();
            local_8._0_1_ = 8;
            ~basic_string<>();
            local_8._0_1_ = 7;
            FUN_004180b0();
            puVar9 = local_ec;
            paVar3 = (allocator<char> *)FUN_0066add0(puVar9);
            std::allocator<char>::allocator<char>(paVar3);
            local_260 = FUN_008405e0(puVar9);
            local_8._0_1_ = 10;
            local_258 = local_260;
            local_26c = FUN_00417fd0(local_1c4);
            local_8._0_1_ = 0xb;
            local_264 = local_26c;
            pcVar6 = (char *)FUN_0041f870();
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            operator=(local_1fc,pcVar6);
            local_8._0_1_ = 10;
            ~basic_string<>();
            local_8._0_1_ = 7;
            FUN_004180b0();
            FID_conflict_operator_(local_44);
            paVar3 = (allocator<char> *)FUN_0066add0();
            uVar4 = std::allocator<char>::allocator<char>(paVar3);
            local_1e4 = FUN_00667440(uVar4);
            local_1e0 = local_1e4;
            FUN_00669fe0(local_230);
            local_8._0_1_ = 6;
            FUN_00667da0();
          }
        }
        FUN_0066ae00();
      }
      local_8._0_1_ = 5;
      FUN_00667660();
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(local_238 + 4));
    local_8 = CONCAT31(local_8._1_3_,0xc);
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      local_274 = FUN_006678e0(local_11c,local_238 + 4,local_44);
      FUN_0045e0f0(local_274);
      ~basic_string<>();
      iVar5 = FUN_004170c0();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                (local_2c,iVar5 - 1);
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              (local_2c,"/*");
    basic_string<>(&DAT_008922f8);
    local_8._0_1_ = 0xd;
    if (local_234 == 0xffffffff) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (local_74,param_1);
    }
    else {
      local_27c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  FUN_0045e1d0(local_14c,local_234 + 1,0xffffffff);
      local_8._0_1_ = 0xe;
      local_278 = local_27c;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (local_74,local_27c);
      local_8._0_1_ = 0xd;
      ~basic_string<>();
    }
    puVar7 = (undefined4 *)FUN_0042d8c0(local_2d8);
    local_23c = *puVar7;
    puVar7 = (undefined4 *)FID_conflict_begin(local_2dc);
    local_284 = *puVar7;
    cVar1 = FUN_00420f10(&local_284);
    if (cVar1 != '\0') {
      FID_conflict_operator_(local_44);
      puVar9 = local_1ac;
      FUN_004305e0(puVar9);
      local_294 = FUN_008405e0(puVar9);
      local_8._0_1_ = 0xf;
      local_28c = local_294;
      local_2a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  FUN_00417fd0(local_17c);
      local_8._0_1_ = 0x10;
      pbVar10 = local_74;
      local_29c = local_2a4;
      this = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             append(local_2c,local_2a4);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (this,pbVar10);
      local_8._0_1_ = 0xf;
      ~basic_string<>();
      local_8._0_1_ = 0xd;
      FUN_004180b0();
      puVar9 = local_104;
      FUN_004305e0(puVar9);
      local_2b4 = FUN_008405e0(puVar9);
      local_8._0_1_ = 0x11;
      local_2ac = local_2b4;
      local_298 = FUN_00417fd0(local_194);
      local_8._0_1_ = 0x12;
      local_25c = local_298;
      local_268 = FUN_0048b7d0(local_1dc,param_4,&DAT_008922f8);
      local_8._0_1_ = 0x13;
      local_254 = local_268;
      FUN_00426a20(local_a4,local_268,local_25c);
      local_8._0_1_ = 0x15;
      ~basic_string<>();
      local_8._0_1_ = 0x16;
      ~basic_string<>();
      local_8._0_1_ = 0x17;
      FUN_004180b0();
      FUN_00667ed0(local_2c,param_2,param_3,local_a4);
      local_8 = CONCAT31(local_8._1_3_,0xd);
      ~basic_string<>();
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
    local_8._0_1_ = 0xc;
    ~basic_string<>();
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8._0_1_ = 4;
    FUN_00667660();
    local_8._0_1_ = 3;
    FUN_00667660();
    local_8._0_1_ = 2;
    FUN_0066aec0();
    local_8._0_1_ = 1;
    FUN_004180b0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

