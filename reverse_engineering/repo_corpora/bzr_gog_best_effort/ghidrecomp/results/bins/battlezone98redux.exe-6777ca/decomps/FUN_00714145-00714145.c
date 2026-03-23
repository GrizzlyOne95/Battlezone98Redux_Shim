
void FUN_00714145(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_EBP;
  int iStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  int iStack_c;
  code *pcStack_8;
  code *pcStack_4;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  pcStack_4 = (code *)(unaff_EBP + -0xdc);
  pcStack_8 = (code *)0x714172;
  uVar2 = FUN_006b9760();
  *(undefined4 *)(unaff_EBP + -0x168) = uVar2;
  *(undefined4 *)(unaff_EBP + -0x178) = *(undefined4 *)(unaff_EBP + -0x168);
  *(undefined4 *)(unaff_EBP + -4) = 5;
  pcStack_4 = (code *)0x8999a4;
  pcStack_8 = (code *)0x71419b;
  uVar2 = basic_string<>();
  *(undefined4 *)(unaff_EBP + -0x170) = uVar2;
  *(undefined4 *)(unaff_EBP + -0x180) = *(undefined4 *)(unaff_EBP + -0x170);
  *(undefined1 *)(unaff_EBP + -4) = 6;
  pcStack_4 = *(code **)(unaff_EBP + -0x178);
  pcStack_8 = *(code **)(unaff_EBP + -0x180);
  iStack_c = unaff_EBP + -0x7c;
  uStack_10 = 0x7141c8;
  uVar2 = FUN_006625c0();
  *(undefined4 *)(unaff_EBP + -0x134) = uVar2;
  *(undefined4 *)(unaff_EBP + -0x128) = *(undefined4 *)(unaff_EBP + -0x134);
  *(undefined1 *)(unaff_EBP + -4) = 7;
  pcStack_4 = *(code **)(unaff_EBP + -0x128);
  pcStack_8 = (code *)0x400;
  iStack_c = 0x7141fe;
  FUN_006d4480();
  *(undefined1 *)(unaff_EBP + -4) = 6;
  pcStack_4 = (code *)0x71420a;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 5;
  pcStack_4 = (code *)0x714219;
  ~basic_string<>();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  pcStack_4 = (code *)0x71422b;
  ~basic_string<>();
  pcStack_4 = (code *)0x71423c;
  cVar1 = FUN_006b8ef0();
  if (cVar1 == '\0') {
    *(code **)(unaff_EBP + -0x124) = FUN_00713e50;
    *(undefined4 *)(unaff_EBP + -0x120) = 0;
    pcStack_4 = (code *)(unaff_EBP + -400);
    pcStack_8 = (code *)0x714578;
    uVar2 = FUN_006e1540();
    *(undefined4 *)(unaff_EBP + -0x164) = uVar2;
    *(undefined4 *)(unaff_EBP + -0x14c) = *(undefined4 *)(unaff_EBP + -0x164);
    *(undefined4 *)(unaff_EBP + -4) = 0xc;
    pcStack_4 = _2_exref;
    pcStack_8 = _1_exref;
    iStack_c = *(undefined4 *)(unaff_EBP + -0x14c);
    uStack_10 = *(undefined4 *)(unaff_EBP + -0x120);
    uStack_14 = *(undefined4 *)(unaff_EBP + -0x124);
    iStack_18 = unaff_EBP + -0x1e0;
    uVar2 = FUN_0070a660();
    *(undefined4 *)(unaff_EBP + -0x11c) = uVar2;
    *(undefined4 *)(unaff_EBP + -0x154) = *(undefined4 *)(unaff_EBP + -0x11c);
    *(undefined1 *)(unaff_EBP + -4) = 0xd;
    *(int **)(unaff_EBP + -0x198) = &iStack_18;
    uVar2 = FUN_0070a6c0(*(undefined4 *)(unaff_EBP + -0x154));
    *(undefined4 *)(unaff_EBP + -0x1a0) = uVar2;
    FUN_006ffbc0(1,*(int *)(unaff_EBP + -0x100) + 0xa30,0x4000);
    *(undefined1 *)(unaff_EBP + -4) = 0xc;
    pcStack_4 = (code *)0x714623;
    ~input_processor<>();
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    pcStack_4 = (code *)0x714635;
    FUN_006ca8c0();
  }
  else {
    pcStack_4 = (code *)0x714258;
    cVar1 = FUN_006ab7d0();
    if (cVar1 != '\0') {
      pcStack_4 = (code *)0x714270;
      FUN_00421ec0();
      pcStack_4 = (code *)0x714277;
      FUN_006d70d0();
      pcStack_4 = (code *)0x714288;
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)
                 (*(int *)(unaff_EBP + -0x100) + 0x4a58));
    }
    pcStack_4 = (code *)0x714299;
    uVar2 = FUN_00421ec0();
    *(undefined4 *)(unaff_EBP + -0x118) = uVar2;
    pcStack_4 = (code *)(*(int *)(unaff_EBP + -0x100) + 0x4b40);
    pcStack_8 = (code *)(*(int *)(unaff_EBP + -0x100) + 0x4abc);
    iStack_c = unaff_EBP + -0x130;
    uStack_10 = 0x7142d2;
    (**(code **)(**(int **)(unaff_EBP + -0x118) + 0x20))();
    pcStack_4 = (code *)0x7142dd;
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      pcStack_4 = (code *)0x71431c;
      FUN_006e48d0();
      *(undefined4 *)(unaff_EBP + -4) = 8;
      pcStack_4 = (code *)0x714334;
      uVar2 = FUN_00421ec0();
      *(undefined4 *)(unaff_EBP + -0x114) = uVar2;
      pcStack_4 = (code *)(*(int *)(unaff_EBP + -0x100) + 0x4b40);
      pcStack_8 = (code *)(unaff_EBP + -0xfc);
      iStack_c = 0x714360;
      uVar2 = (**(code **)(**(int **)(unaff_EBP + -0x114) + 0xc))();
      *(undefined4 *)(unaff_EBP + -0x138) = uVar2;
      *(undefined4 *)(unaff_EBP + -0x140) = *(undefined4 *)(unaff_EBP + -0x138);
      *(undefined1 *)(unaff_EBP + -4) = 9;
      pcStack_4 = *(code **)(unaff_EBP + -0x140);
      pcStack_8 = (code *)0x714385;
      FUN_007100a0();
      *(undefined1 *)(unaff_EBP + -4) = 8;
      pcStack_4 = (code *)0x714394;
      FUN_006e4470();
      pcStack_4 = (code *)0x71439c;
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        pcStack_4 = (code *)(unaff_EBP + -0x94);
        pcStack_8 = (code *)0x7143b6;
        uVar2 = FUN_006ab780();
        *(undefined4 *)(unaff_EBP + -0x15c) = uVar2;
        *(undefined4 *)(unaff_EBP + -0x13c) = *(undefined4 *)(unaff_EBP + -0x15c);
        *(undefined1 *)(unaff_EBP + -4) = 10;
        pcStack_4 = *(code **)(unaff_EBP + -0x13c);
        pcStack_8 = (code *)0x8999dc;
        iStack_c = unaff_EBP + -0xac;
        uStack_10 = 0x7143e4;
        uVar2 = FUN_006dd7f0();
        *(undefined4 *)(unaff_EBP + -0x17c) = uVar2;
        *(undefined4 *)(unaff_EBP + -0x144) = *(undefined4 *)(unaff_EBP + -0x17c);
        *(undefined1 *)(unaff_EBP + -4) = 0xb;
        pcStack_4 = *(code **)(unaff_EBP + -0x144);
        pcStack_8 = (code *)0x400;
        iStack_c = 0x71441a;
        FUN_006d4480();
        *(undefined1 *)(unaff_EBP + -4) = 10;
        pcStack_4 = (code *)0x714429;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 8;
        pcStack_4 = (code *)0x714438;
        ~basic_string<>();
        pcStack_4 = (code *)0x20;
        pcStack_8 = (code *)(unaff_EBP + -0x1c0);
        iStack_c = 0x714446;
        pcStack_4 = (code *)make_error_code();
        pcStack_8 = (code *)0x714455;
        FUN_006daf10();
      }
      *(undefined4 *)(*(int *)(unaff_EBP + -0x100) + 0xa24) = 7;
      *(undefined4 *)(*(int *)(unaff_EBP + -0x100) + 0xa20) = 1;
      pcStack_4 = (code *)0x714480;
      FUN_00720a50();
      pcStack_4 = (code *)0x714491;
      cVar1 = FUN_006caba0();
      if (cVar1 != '\0') {
        iStack_c = *(int *)(unaff_EBP + -0x100) + 0x918;
        *(code ***)(unaff_EBP + -0x19c) = &pcStack_8;
        uStack_10 = 0x7144b5;
        uVar2 = shared_ptr<>();
        *(undefined4 *)(unaff_EBP + -0x194) = uVar2;
        iStack_c = 0x7144cc;
        FUN_006e6250();
      }
      pcStack_4 = (code *)(*(int *)(unaff_EBP + -0x100) + 0xa30);
      pcStack_8 = (code *)(*(int *)(unaff_EBP + -0x100) + 0xa30 + *(int *)(unaff_EBP + 0xc));
      iStack_c = *(int *)(unaff_EBP + -0x100) + 0xa30 + *(int *)(unaff_EBP + -0x10c);
      uStack_10 = 0x714502;
      FUN_006da2a0();
      *(int *)(*(int *)(unaff_EBP + -0x100) + 0x4a30) =
           *(int *)(unaff_EBP + 0xc) - *(int *)(unaff_EBP + -0x10c);
      pcStack_4 = *(code **)(*(int *)(unaff_EBP + -0x100) + 0x4a30);
      pcStack_8 = (code *)0x714532;
      pcStack_8 = (code *)FUN_006ab750();
      iStack_c = 0x71453e;
      FUN_007099f0();
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      pcStack_4 = (code *)0x71454d;
      FUN_006e4470();
    }
    else {
      pcStack_4 = (code *)(unaff_EBP + -0x130);
      pcStack_8 = (code *)0x8999fc;
      iStack_c = 0x10;
      uStack_10 = 0x7142fd;
      FUN_006f90a0();
      pcStack_4 = (code *)(unaff_EBP + -0x130);
      pcStack_8 = (code *)0x71430f;
      FUN_006daf10();
    }
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

