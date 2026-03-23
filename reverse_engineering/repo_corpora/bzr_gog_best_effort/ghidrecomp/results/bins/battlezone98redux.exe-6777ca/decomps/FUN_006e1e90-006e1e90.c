
void FUN_006e1e90(undefined4 param_1,undefined4 param_2,undefined4 param_3,ios_base *param_4,
                 byte param_5,SchedulerBase *param_6)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uStack_438;
  undefined4 uStack_434;
  undefined4 uStack_430;
  ios_base *piStack_42c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_428;
  undefined1 local_414 [152];
  undefined1 local_37c [152];
  undefined1 local_2e4 [36];
  undefined1 local_2c0 [8];
  undefined1 local_2b8 [8];
  undefined1 local_2b0 [8];
  undefined1 local_2a8 [8];
  undefined1 local_2a0 [8];
  undefined1 local_298 [8];
  undefined1 local_290 [8];
  undefined1 *local_288;
  undefined4 local_284;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_210;
  int *local_20c;
  char local_207;
  char local_206;
  char local_205;
  char local_204;
  char local_203;
  char local_202;
  char local_201;
  undefined4 local_200 [9];
  undefined1 local_1dc [48];
  undefined1 local_1ac [24];
  undefined1 local_194 [24];
  undefined1 local_17c [24];
  undefined1 local_164 [24];
  undefined1 local_14c [48];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [48];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008540f9;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_6);
  if (bVar1) {
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x6e1ee1;
    FUN_006c9b00();
    FUN_006c97f0();
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  (uint)param_5;
    piStack_42c = param_4;
    uStack_430 = param_3;
    uStack_434 = param_2;
    uStack_438 = param_1;
    (**(code **)(*local_20c + 0x14))();
  }
  else {
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x6e1f2b;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(local_20c + 2));
    local_8 = 0;
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_2a8;
    piStack_42c = (ios_base *)0x6e1f43;
    FUN_006f0e20();
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  &DAT_008962b0;
    piStack_42c = (ios_base *)local_2b0;
    uStack_430 = 0x6e1f58;
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  FUN_006f0e20();
    piStack_42c = (ios_base *)local_2c;
    uStack_430 = 0x6e1f65;
    FUN_006f0e50();
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_2b8;
    piStack_42c = (ios_base *)0x6e1f79;
    FUN_006f0e20();
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  &DAT_00896224;
    piStack_42c = (ios_base *)local_298;
    uStack_430 = 0x6e1f8e;
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  FUN_006f0e20();
    piStack_42c = (ios_base *)local_2c;
    uStack_430 = 0x6e1f9b;
    FUN_006f0e50();
    basic_string<>();
    local_8._0_1_ = 1;
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe858;
    piStack_42c = (ios_base *)0x6e1fbb;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_2a0;
      piStack_42c = (ios_base *)0x6e1fd5;
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    FUN_006c9b20();
      piStack_42c = (ios_base *)local_8c;
      uStack_430 = 0x6e1fe2;
      local_22c = FUN_006e4fd0();
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e1ffa;
      FUN_0045e0f0();
      ~basic_string<>();
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e2015;
      local_278 = std::ios_base::getloc(param_4);
      local_8._0_1_ = 2;
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e2037;
      local_240 = local_278;
      FUN_006dc5e0();
      local_203 = FUN_006d1560();
      local_8._0_1_ = 1;
      FUN_00417b50();
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e2064;
      basic_string<>();
      local_8._0_1_ = 3;
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e2078;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
                (local_74,local_203);
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e2084;
      FUN_00449810();
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    &PTR_DAT_008fe858;
      piStack_42c = (ios_base *)local_2c;
      uStack_430 = 0x6e2096;
      FUN_006f0ea0();
      local_8._0_1_ = 1;
      ~basic_string<>();
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe838;
    piStack_42c = (ios_base *)0x6e20b6;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_ec;
      piStack_42c = (ios_base *)0x6e20d0;
      local_218 = FUN_006e47c0();
      local_207 = FUN_0041f890();
      ~basic_string<>();
      if (local_207 == '\0') {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e211f;
        local_228 = GetPrompt();
        local_8._0_1_ = 4;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&PTR_DAT_008fe838;
        piStack_42c = (ios_base *)local_2c;
        uStack_430 = 0x6e214a;
        local_220 = local_228;
        FUN_006f0ea0();
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
      else {
        pbStack_428 = local_2c;
        piStack_42c = (ios_base *)0x6e210b;
        FUN_006f0ef0();
      }
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe850;
    piStack_42c = (ios_base *)0x6e216d;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_a4;
      piStack_42c = (ios_base *)0x6e2187;
      local_230 = FUN_006e47c0();
      local_202 = FUN_0041f890();
      ~basic_string<>();
      if (local_202 == '\0') {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_194;
        piStack_42c = (ios_base *)0x6e2258;
        local_23c = FUN_006e47c0();
        local_8._0_1_ = 7;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&PTR_DAT_008fe850;
        piStack_42c = (ios_base *)local_2c;
        uStack_430 = 0x6e2283;
        local_234 = local_23c;
        FUN_006f0ea0();
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
      else {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x2;
        piStack_42c = (ios_base *)0x6e21c7;
        FUN_006ca050();
        local_8._0_1_ = 5;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x20;
        piStack_42c = (ios_base *)local_37c;
        uStack_430 = 0x6e21e0;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)FUN_006d9650();
        piStack_42c = (ios_base *)0x6e21e9;
        FUN_004bc590();
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e21fe;
        local_268 = GetPolicy();
        local_8._0_1_ = 6;
        pbStack_428 = local_2c;
        piStack_42c = (ios_base *)0x6e2224;
        local_258 = local_268;
        FUN_006f0f40();
        local_8._0_1_ = 5;
        ~basic_string<>();
        local_8._0_1_ = 1;
        FUN_006b3a50();
      }
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe844;
    piStack_42c = (ios_base *)0x6e22a6;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_bc;
      piStack_42c = (ios_base *)0x6e22c0;
      local_244 = FUN_006e47c0();
      local_204 = FUN_0041f890();
      ~basic_string<>();
      if (local_204 == '\0') {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_11c;
        piStack_42c = (ios_base *)0x6e2391;
        local_264 = FUN_006e47c0();
        local_8._0_1_ = 10;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&PTR_DAT_008fe844;
        piStack_42c = (ios_base *)local_2c;
        uStack_430 = 0x6e23bc;
        local_25c = local_264;
        FUN_006f0ea0();
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
      else {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x2;
        piStack_42c = (ios_base *)0x6e2300;
        FUN_006ca050();
        local_8._0_1_ = 8;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x20;
        piStack_42c = (ios_base *)local_414;
        uStack_430 = 0x6e2319;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)FUN_006d9650();
        piStack_42c = (ios_base *)0x6e2322;
        FUN_004bc590();
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e2337;
        local_254 = GetPolicy();
        local_8._0_1_ = 9;
        pbStack_428 = local_2c;
        piStack_42c = (ios_base *)0x6e235d;
        local_24c = local_254;
        FUN_006f0f40();
        local_8._0_1_ = 8;
        ~basic_string<>();
        local_8._0_1_ = 1;
        FUN_006b3a50();
      }
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe824;
    piStack_42c = (ios_base *)0x6e23de;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_14c;
      piStack_42c = (ios_base *)0x6e23f8;
      local_26c = FUN_006e47c0();
      local_206 = FUN_0041f890();
      ~basic_string<>();
      if (local_206 == '\0') {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_17c;
        piStack_42c = (ios_base *)0x6e2449;
        local_27c = FUN_006e47c0();
        local_8._0_1_ = 0xb;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&PTR_DAT_008fe824;
        piStack_42c = (ios_base *)local_2c;
        uStack_430 = 0x6e2474;
        local_274 = local_27c;
        FUN_006f0ea0();
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
      else {
        pbStack_428 = local_2c;
        piStack_42c = (ios_base *)0x6e2433;
        FUN_006f0ef0();
      }
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe83c;
    piStack_42c = (ios_base *)0x6e2497;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_1ac;
      piStack_42c = (ios_base *)0x6e24b1;
      local_238 = FUN_006e47c0();
      local_201 = FUN_0041f890();
      ~basic_string<>();
      if (local_201 == '\0') {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_1dc;
        piStack_42c = (ios_base *)0x6e2502;
        local_260 = FUN_006e47c0();
        local_8._0_1_ = 0xc;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&PTR_DAT_008fe83c;
        piStack_42c = (ios_base *)local_2c;
        uStack_430 = 0x6e252d;
        local_21c = local_260;
        FUN_006f0ea0();
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
      else {
        pbStack_428 = local_2c;
        piStack_42c = (ios_base *)0x6e24ec;
        FUN_006f0ef0();
      }
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe84c;
    piStack_42c = (ios_base *)0x6e2550;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      cVar2 = FUN_0041f890();
      if (cVar2 != '\0') {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_290;
        piStack_42c = (ios_base *)0x6e2575;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)FUN_006c9b20();
        piStack_42c = (ios_base *)local_104;
        uStack_430 = 0x6e2582;
        local_248 = FUN_006e4fd0();
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e259a;
        FUN_0045e0f0();
        ~basic_string<>();
      }
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    &PTR_DAT_008fe84c;
      piStack_42c = (ios_base *)local_2c;
      uStack_430 = 0x6e25b7;
      FUN_006f0ea0();
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008fe828;
    piStack_42c = (ios_base *)0x6e25cb;
    iVar3 = FUN_005871b0();
    if (iVar3 != -1) {
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_2c0;
      piStack_42c = (ios_base *)0x6e25e5;
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    FUN_006c9b20();
      piStack_42c = (ios_base *)local_164;
      uStack_430 = 0x6e25f2;
      local_224 = FUN_006e4fd0();
      pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x6e260a;
      FUN_0045e0f0();
      ~basic_string<>();
      iVar3 = FUN_004170c0();
      if (iVar3 == 0) {
        pbStack_428 = local_2c;
        piStack_42c = (ios_base *)0x6e26cf;
        FUN_006f0ef0();
      }
      else {
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e2635;
        local_270 = std::ios_base::getloc(param_4);
        local_8._0_1_ = 0xd;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e2657;
        local_210 = local_270;
        FUN_006dc5e0();
        local_205 = FUN_006d1560();
        local_8._0_1_ = 1;
        FUN_00417b50();
        basic_string<>();
        local_8._0_1_ = 0xe;
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e2692;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        operator+=(local_5c,local_205);
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x6e269e;
        FUN_00449810();
        pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&PTR_DAT_008fe828;
        piStack_42c = (ios_base *)local_2c;
        uStack_430 = 0x6e26b0;
        FUN_006f0ea0();
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
    }
    pbStack_428 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_2e4;
    piStack_42c = (ios_base *)0x6e26e2;
    puVar4 = (undefined4 *)FUN_006be2c0();
    puVar5 = local_200;
    for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    local_288 = (undefined1 *)&uStack_438;
    local_284 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)&uStack_438,local_2c);
    (**(code **)(*local_20c + 0x18))(param_1,param_2,param_3,param_4,param_5,local_200);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  uStack_430 = 0x6e2772;
  FUN_0083e885();
  return;
}

