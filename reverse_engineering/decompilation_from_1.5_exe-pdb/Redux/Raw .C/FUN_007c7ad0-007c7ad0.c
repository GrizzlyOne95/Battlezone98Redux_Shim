
void __thiscall FUN_007c7ad0(char *param_1,int param_2)

{
  int iVar1;
  void *pvVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_4f0 [8];
  undefined4 uStack_4e8;
  undefined4 uStack_4e4;
  char *pcStack_4e0;
  char *local_38c;
  char *local_388;
  char *local_380;
  char *local_37c;
  char *local_378;
  char *local_374;
  char *local_370;
  char *local_368;
  char *local_364;
  char *local_360;
  char *local_358;
  char *local_354;
  char *local_350;
  char *local_348;
  char *local_344;
  char *local_340;
  char *local_334;
  char *local_330;
  char *local_328;
  char *local_324;
  char *local_320;
  char *local_318;
  char *local_314;
  char *local_310;
  char *local_308;
  char *local_304;
  char *local_300;
  char *local_2f8;
  char *local_2f4;
  char *local_2e4;
  char *local_2d4;
  char *local_2c4;
  char *local_2b4;
  char *local_2a4;
  char *local_294;
  char *local_284;
  char *local_274;
  char *local_264;
  char *local_254;
  char *local_250;
  char *local_240;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008623a7;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007c6920();
  param_1[0x18] = '\0';
  pcStack_4e0 = "Creating screen of type %d\n";
  uStack_4e4 = 0x7c7b28;
  uStack_4e4 = FUN_0081e820();
  uStack_4e8 = 0x7c7b2e;
  FUN_0081e710();
  local_240 = (char *)0x0;
  switch(param_2) {
  case 1:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c7b7b;
    FUN_007d4530();
    FUN_00764790();
    FUN_0076a030();
    pcStack_4e0 = (char *)0x7c7b95;
    pvVar2 = operator_new(0x17c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_37c = (char *)0x0;
    }
    else {
      local_37c = (char *)FUN_0078e670();
    }
    local_8 = 0xffffffff;
    local_240 = local_37c;
    break;
  case 2:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c7bfd;
    FUN_007d4530();
    FUN_00764790();
    FUN_0076a030();
    pcStack_4e0 = (char *)0x7c7c17;
    pvVar2 = operator_new(0x180);
    local_8 = 1;
    if (pvVar2 == (void *)0x0) {
      local_38c = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c7c42;
      local_38c = (char *)FUN_007bf440();
    }
    local_8 = 0xffffffff;
    local_240 = local_38c;
    break;
  case 3:
    iVar1 = FUN_004344a0();
    if (iVar1 == 2) {
      pcStack_4e0 = (char *)0x7c81dc;
      pvVar2 = operator_new(0x1a8);
      local_8 = 0xd;
      if (pvVar2 == (void *)0x0) {
        local_350 = (char *)0x0;
      }
      else {
        local_350 = (char *)FUN_007abee0();
      }
      local_240 = local_350;
    }
    else {
      pcStack_4e0 = (char *)0x7c823e;
      pvVar2 = operator_new(0x144);
      local_8 = 0xe;
      if (pvVar2 == (void *)0x0) {
        local_318 = (char *)0x0;
      }
      else {
        local_318 = (char *)FUN_007b61a0();
      }
      local_240 = local_318;
    }
    local_8 = 0xffffffff;
    break;
  case 4:
    pcStack_4e0 = (char *)0x7c82a3;
    pvVar2 = operator_new(0x168);
    local_8 = 0xf;
    if (pvVar2 == (void *)0x0) {
      local_370 = (char *)0x0;
    }
    else {
      local_370 = (char *)FUN_007b6b90();
    }
    local_8 = 0xffffffff;
    local_240 = local_370;
    break;
  case 5:
    pcStack_4e0 = (char *)0x7c836d;
    pvVar2 = operator_new(0x1b0);
    local_8 = 0x11;
    if (pvVar2 == (void *)0x0) {
      local_358 = (char *)0x0;
    }
    else {
      local_358 = (char *)FUN_007af4a0();
    }
    local_8 = 0xffffffff;
    local_240 = local_358;
    break;
  case 6:
    pcStack_4e0 = (char *)0x7c8308;
    pvVar2 = operator_new(0x1a8);
    local_8 = 0x10;
    if (pvVar2 == (void *)0x0) {
      local_320 = (char *)0x0;
    }
    else {
      local_320 = (char *)FUN_007abee0();
    }
    local_8 = 0xffffffff;
    local_240 = local_320;
    break;
  case 7:
    pcStack_4e0 = (char *)0xff;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c7c86;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c7c94;
    pvVar2 = operator_new(0x164);
    local_8 = 2;
    if (pvVar2 == (void *)0x0) {
      local_340 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094ffe0);
      local_340 = (char *)FUN_0078f030(param_1);
    }
    local_8 = 0xffffffff;
    local_240 = local_340;
    break;
  case 8:
    pcStack_4e0 = (char *)0x0;
    uStack_4e4 = 0xff;
    uStack_4e8 = 0x7c7d2a;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c7d38;
    pvVar2 = operator_new(0x164);
    local_8 = 3;
    if (pvVar2 == (void *)0x0) {
      local_2f8 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fea8);
      local_2f8 = (char *)FUN_0078f030(param_1);
    }
    local_8 = 0xffffffff;
    local_240 = local_2f8;
    break;
  case 9:
    pcStack_4e0 = (char *)0xff;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c7dce;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c7ddc;
    pvVar2 = operator_new(0x164);
    local_8 = 4;
    if (pvVar2 == (void *)0x0) {
      local_368 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fef8);
      local_368 = (char *)FUN_0078f030(param_1);
    }
    local_8 = 0xffffffff;
    local_240 = local_368;
    break;
  case 0xb:
    iVar1 = FUN_00572a70();
    if (iVar1 == 0) {
      pcStack_4e0 = (char *)0x7c8716;
      pvVar2 = operator_new(0x148);
      local_8 = 0x19;
      if (pvVar2 == (void *)0x0) {
        local_264 = (char *)0x0;
      }
      else {
        local_264 = (char *)FUN_00789030();
      }
      local_240 = local_264;
    }
    else {
      pcStack_4e0 = (char *)0x7c86b4;
      pvVar2 = operator_new(0x1a8);
      local_8 = 0x18;
      if (pvVar2 == (void *)0x0) {
        local_254 = (char *)0x0;
      }
      else {
        local_254 = (char *)FUN_007a4b60();
      }
      local_240 = local_254;
    }
    local_8 = 0xffffffff;
    break;
  case 0xe:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c84c8;
    FUN_007d4530();
    FUN_00764790();
    FUN_0076a240();
    pcStack_4e0 = (char *)0x7c84e2;
    pvVar2 = operator_new(0x388);
    local_8 = 0x14;
    if (pvVar2 == (void *)0x0) {
      local_330 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c850d;
      local_330 = (char *)FUN_0079ea90();
    }
    local_8 = 0xffffffff;
    local_240 = local_330;
    break;
  case 0xf:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c8551;
    FUN_007d4530();
    FUN_00764790();
    FUN_0076a240();
    pcStack_4e0 = (char *)0x7c856b;
    pvVar2 = operator_new(0x1d8);
    local_8 = 0x15;
    if (pvVar2 == (void *)0x0) {
      local_360 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c8596;
      local_360 = (char *)FUN_00796880();
    }
    local_8 = 0xffffffff;
    local_240 = local_360;
    param_1[0x18] = '\x01';
    break;
  case 0x11:
    pcStack_4e0 = (char *)0x7c816d;
    pvVar2 = operator_new(0x2f8);
    local_8 = 0xc;
    if (pvVar2 == (void *)0x0) {
      local_310 = (char *)0x0;
    }
    else {
      local_310 = (char *)FUN_007ba6f0();
    }
    local_8 = 0xffffffff;
    local_240 = local_310;
    break;
  case 0x12:
    pcStack_4e0 = (char *)0x7c8108;
    pvVar2 = operator_new(0x16c);
    local_8 = 0xb;
    if (pvVar2 == (void *)0x0) {
      local_388 = (char *)0x0;
    }
    else {
      local_388 = (char *)FUN_0078b1f0();
    }
    local_8 = 0xffffffff;
    local_240 = local_388;
    break;
  case 0x13:
    pcStack_4e0 = (char *)0x0;
    uStack_4e4 = 0xff;
    uStack_4e8 = 0x7c83d5;
    FUN_007d4570();
    pcStack_4e0 = (char *)0x7c83e3;
    pvVar2 = operator_new(0x144);
    local_8 = 0x12;
    if (pvVar2 == (void *)0x0) {
      local_328 = (char *)0x0;
    }
    else {
      local_328 = (char *)FUN_00792000();
    }
    local_8 = 0xffffffff;
    local_240 = local_328;
    break;
  case 0x14:
    pcStack_4e0 = (char *)0xff;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c844b;
    FUN_007d4570();
    pcStack_4e0 = (char *)0x7c8459;
    pvVar2 = operator_new(0x160);
    local_8 = 0x13;
    if (pvVar2 == (void *)0x0) {
      local_380 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c8484;
      local_380 = (char *)FUN_00793ca0();
    }
    local_8 = 0xffffffff;
    local_240 = local_380;
    break;
  case 0x15:
    pcStack_4e0 = (char *)0x7c85e1;
    pvVar2 = operator_new(0x18c);
    local_8 = 0x16;
    if (pvVar2 == (void *)0x0) {
      local_250 = (char *)0x0;
    }
    else {
      local_250 = (char *)FUN_007b25b0();
    }
    local_8 = 0xffffffff;
    local_240 = local_250;
    break;
  case 0x16:
    pcStack_4e0 = (char *)0x7c8646;
    pvVar2 = operator_new(0x14c);
    local_8 = 0x17;
    if (pvVar2 == (void *)0x0) {
      local_378 = (char *)0x0;
    }
    else {
      local_378 = (char *)FUN_007b5990();
    }
    local_8 = 0xffffffff;
    local_240 = local_378;
    break;
  case 0x17:
    FUN_004f49e0();
    pcStack_4e0 = (char *)0x7c8780;
    pvVar2 = operator_new(0x158);
    local_8 = 0x1a;
    if (pvVar2 == (void *)0x0) {
      local_274 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c87ab;
      local_274 = (char *)FUN_0078bba0();
    }
    local_8 = 0xffffffff;
    local_240 = local_274;
    param_1[0x18] = '\x01';
    break;
  case 0x18:
    pcStack_4e0 = (char *)0xff;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c8918;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c8926;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x1d;
    if (pvVar2 == (void *)0x0) {
      local_2a4 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094ffe0);
      local_2a4 = (char *)FUN_00790fe0();
    }
    local_8 = 0xffffffff;
    local_240 = local_2a4;
    break;
  case 0x19:
    pcStack_4e0 = (char *)0xff;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c89b5;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c89c3;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x1e;
    if (pvVar2 == (void *)0x0) {
      local_2b4 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fef8);
      local_2b4 = (char *)FUN_00790fe0();
    }
    local_8 = 0xffffffff;
    local_240 = local_2b4;
    break;
  case 0x1a:
    pcStack_4e0 = (char *)0x0;
    uStack_4e4 = 0xff;
    uStack_4e8 = 0x7c887b;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c8889;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x1c;
    if (pvVar2 == (void *)0x0) {
      local_294 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fea8);
      local_294 = (char *)FUN_00790fe0();
    }
    local_8 = 0xffffffff;
    local_240 = local_294;
    break;
  case 0x1b:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c87f9;
    FUN_007d4530();
    FUN_00764790();
    FUN_0076a430();
    pcStack_4e0 = (char *)0x7c8813;
    pvVar2 = operator_new(0x158);
    local_8 = 0x1b;
    if (pvVar2 == (void *)0x0) {
      local_284 = (char *)0x0;
    }
    else {
      local_284 = (char *)FUN_00789c20();
    }
    local_8 = 0xffffffff;
    local_240 = local_284;
    break;
  case 0x1c:
    pcStack_4e0 = (char *)0x7c8d0a;
    pvVar2 = operator_new(0x160);
    local_8 = 0x25;
    if (pvVar2 == (void *)0x0) {
      local_304 = (char *)0x0;
    }
    else {
      local_304 = (char *)FUN_00794810();
    }
    local_8 = 0xffffffff;
    local_240 = local_304;
    break;
  case 0x1d:
    pcStack_4e0 = (char *)0x7c8dd4;
    pvVar2 = operator_new(0x144);
    local_8 = 0x27;
    if (pvVar2 == (void *)0x0) {
      local_324 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c8dff;
      local_324 = (char *)FUN_00787c10();
    }
    local_8 = 0xffffffff;
    local_240 = local_324;
    break;
  case 0x1e:
    pcStack_4e0 = (char *)0x7c8e40;
    pvVar2 = operator_new(0x144);
    local_8 = 0x28;
    if (pvVar2 == (void *)0x0) {
      local_334 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c8e6b;
      local_334 = (char *)FUN_007a4620();
    }
    local_8 = 0xffffffff;
    local_240 = local_334;
    break;
  case 0x1f:
    pcStack_4e0 = (char *)0x7c8d6f;
    pvVar2 = operator_new(0x148);
    local_8 = 0x26;
    if (pvVar2 == (void *)0x0) {
      local_314 = (char *)0x0;
    }
    else {
      local_314 = (char *)FUN_0078a9f0();
    }
    local_8 = 0xffffffff;
    local_240 = local_314;
    break;
  case 0x20:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c8c8b;
    FUN_007d4530();
    FUN_00764790();
    FUN_0076ab20();
    pcStack_4e0 = (char *)0x7c8ca5;
    pvVar2 = operator_new(0x158);
    local_8 = 0x24;
    if (pvVar2 == (void *)0x0) {
      local_2f4 = (char *)0x0;
    }
    else {
      local_2f4 = (char *)FUN_00788300();
    }
    local_8 = 0xffffffff;
    local_240 = local_2f4;
    break;
  case 0x21:
    pcStack_4e0 = (char *)0x0;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c7e72;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c7e80;
    pvVar2 = operator_new(0x164);
    local_8 = 5;
    if (pvVar2 == (void *)0x0) {
      local_300 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fe78);
      local_300 = (char *)FUN_0078f030(param_1);
    }
    local_8 = 0xffffffff;
    local_240 = local_300;
    break;
  case 0x22:
    pcStack_4e0 = (char *)0xcc;
    uStack_4e4 = 0xff;
    uStack_4e8 = 0x7c7f19;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c7f27;
    pvVar2 = operator_new(0x164);
    local_8 = 6;
    if (pvVar2 == (void *)0x0) {
      local_348 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fe90);
      local_348 = (char *)FUN_0078f030(param_1);
    }
    local_8 = 0xffffffff;
    local_240 = local_348;
    break;
  case 0x23:
    pcStack_4e0 = (char *)0x0;
    uStack_4e4 = 0;
    uStack_4e8 = 0x7c8a52;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c8a60;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x1f;
    if (pvVar2 == (void *)0x0) {
      local_2c4 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fe78);
      local_2c4 = (char *)FUN_00790fe0();
    }
    local_8 = 0xffffffff;
    local_240 = local_2c4;
    break;
  case 0x24:
    pcStack_4e0 = (char *)0xcc;
    uStack_4e4 = 0xff;
    uStack_4e8 = 0x7c8af2;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c8b00;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x20;
    if (pvVar2 == (void *)0x0) {
      local_2d4 = (char *)0x0;
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_4f0,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fe90);
      local_2d4 = (char *)FUN_00790fe0();
    }
    local_8 = 0xffffffff;
    local_240 = local_2d4;
    break;
  case 0x25:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c7fbd;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c7fcc;
    BadAllocException();
    local_8 = 7;
    pcStack_4e0 = (char *)0x7c7ff4;
    FUN_00764790();
    pcStack_4e0 = (char *)0x7c7ffb;
    FUN_0076ae60();
    local_8 = 0xffffffff;
    FUN_00482800();
    pcStack_4e0 = (char *)0x7c8018;
    pvVar2 = operator_new(0x164);
    local_8 = 8;
    if (pvVar2 == (void *)0x0) {
      local_308 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c803d;
      iVar1 = BadAllocException();
      local_8 = CONCAT31(local_8._1_3_,9);
      basic_string<>(iVar1 + 0x34);
      local_308 = (char *)FUN_0078f030(param_1);
    }
    local_240 = local_308;
    local_8 = 0xffffffff;
    if (pvVar2 != (void *)0x0) {
      FUN_00482800();
    }
    break;
  case 0x26:
    pcStack_4e0 = (char *)0x9b;
    uStack_4e4 = 0x33;
    uStack_4e8 = 0x7c8b8f;
    FUN_007d4530();
    pcStack_4e0 = (char *)0x7c8b9d;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x21;
    if (pvVar2 == (void *)0x0) {
      local_2e4 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c8bc2;
      iVar1 = BadAllocException();
      local_8 = CONCAT31(local_8._1_3_,0x22);
      basic_string<>(iVar1 + 0x34);
      local_2e4 = (char *)FUN_00790fe0();
    }
    local_240 = local_2e4;
    local_8 = 0xffffffff;
    if (pvVar2 != (void *)0x0) {
      FUN_00482800();
    }
    break;
  case 0x27:
    pcStack_4e0 = (char *)0x7c8eac;
    pvVar2 = operator_new(0x154);
    local_8 = 0x29;
    if (pvVar2 == (void *)0x0) {
      local_344 = (char *)0x0;
    }
    else {
      uStack_4e4 = 0x7c8ed9;
      pcStack_4e0 = param_1;
      local_344 = (char *)FUN_007bc1e0();
    }
    local_8 = 0xffffffff;
    local_240 = local_344;
    break;
  case 0x28:
    pcStack_4e0 = (char *)0x7c8f1a;
    pvVar2 = operator_new(0x154);
    local_8 = 0x2a;
    if (pvVar2 == (void *)0x0) {
      local_354 = (char *)0x0;
    }
    else {
      uStack_4e4 = 0x7c8f47;
      pcStack_4e0 = param_1;
      local_354 = (char *)FUN_007bc1e0();
    }
    local_8 = 0xffffffff;
    local_240 = local_354;
    break;
  case 0x29:
    pcStack_4e0 = (char *)0x7c8f88;
    pvVar2 = operator_new(0x15c);
    local_8 = 0x2b;
    if (pvVar2 == (void *)0x0) {
      local_364 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c8fb3;
      local_364 = (char *)FUN_007aab70();
    }
    local_8 = 0xffffffff;
    local_240 = local_364;
    break;
  case 0x2a:
    pcStack_4e0 = (char *)0x7c8ff1;
    pvVar2 = operator_new(0x16c);
    local_8 = 0x2c;
    if (pvVar2 == (void *)0x0) {
      local_374 = (char *)0x0;
    }
    else {
      pcStack_4e0 = (char *)0x7c901c;
      local_374 = (char *)FUN_007b84b0();
    }
    local_8 = 0xffffffff;
    local_240 = local_374;
  }
  if (local_240 != (char *)0x0) {
    pcStack_4e0 = (char *)0x7c9068;
    FUN_005df1f0();
    if ((DAT_00918132 != '\0') && (param_2 != 0x1d)) {
      param_1[0x24] = '\0';
      param_1[0x28] = '\0';
      pcStack_4e0 = local_240;
      uStack_4e4 = 0x7c90a0;
      FUN_00787de0();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

