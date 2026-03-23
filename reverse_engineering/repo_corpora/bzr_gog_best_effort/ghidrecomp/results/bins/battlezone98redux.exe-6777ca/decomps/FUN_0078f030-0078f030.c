
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __thiscall FUN_0078f030(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  bool bVar5;
  undefined4 uStack_1f7c0;
  code *pcStack_1f7b0;
  undefined1 *puStack_1f7a8;
  int *piStack_1f798;
  int *piStack_1f5c8;
  int *piStack_1f5c0;
  int *piStack_1f5b0;
  int *piStack_1f5a8;
  int *piStack_1f5a4;
  int *piStack_1f5a0;
  undefined4 uStack_1f594;
  int *piStack_1f584;
  int *piStack_1f574;
  int *piStack_1f56c;
  int *piStack_1f544;
  int *piStack_1f540;
  undefined1 auStack_1f514 [128000];
  undefined1 local_114 [256];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085ed53;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_007d0fa0();
  local_8._0_1_ = 1;
  *param_1 = cUI_Mission::vftable;
  basic_string<>();
  local_8._0_1_ = 2;
  iVar2 = FUN_004344a0();
  bVar5 = iVar2 == 2;
  param_1[0x4e] = param_2;
  FUN_00482860();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &piStack_1f798,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  DAT_0091831c = FUN_00488ec0();
  FID_conflict_operator_();
  DAT_0094552c = param_1;
  pvVar3 = operator_new(0x144);
  local_8._0_1_ = 3;
  if (pvVar3 != (void *)0x0) {
    piStack_1f798 = (int *)0x0;
    FUN_007d1cc0();
  }
  local_8._0_1_ = 2;
  FUN_007d3f20();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &piStack_1f798,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00489020();
  local_8._0_1_ = 4;
  FUN_0041f870();
  FUN_007d2870();
  local_8._0_1_ = 2;
  ~basic_string<>();
  FUN_007d2110();
  FUN_0081cb40();
  FUN_0081cb40();
  FUN_0081cb40();
  FUN_0081cb40();
  FUN_0081cb40();
  iVar2 = FUN_007c7a20();
  if (1 < iVar2) {
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 5;
    if (pvVar3 == (void *)0x0) {
      piStack_1f5a0 = (int *)0x0;
    }
    else {
      piStack_1f798 = (int *)0x43ab0000;
      puStack_1f7a8 = (undefined1 *)0x78f381;
      piStack_1f5a0 = (int *)FUN_007c2480();
    }
    local_8._0_1_ = 2;
    FUN_007d2870();
    (**(code **)(*piStack_1f5a0 + 0x40))();
    (**(code **)(*piStack_1f5a0 + 0x3c))();
    FUN_007c2950();
    FUN_007c23e0();
    FUN_007d2110();
  }
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar3 == (void *)0x0) {
    piStack_1f56c = (int *)0x0;
  }
  else {
    piStack_1f798 = (int *)0x43ab0000;
    puStack_1f7a8 = (undefined1 *)0x78f4ae;
    piStack_1f56c = (int *)FUN_007c2480();
  }
  local_8._0_1_ = 2;
  FUN_007d2870();
  (**(code **)(*piStack_1f56c + 0x40))();
  (**(code **)(*piStack_1f56c + 0x3c))();
  FUN_007c2950();
  FUN_007c23e0();
  FUN_007d2110();
  if (bVar5) {
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 8;
    if (pvVar3 == (void *)0x0) {
      piStack_1f5c8 = (int *)0x0;
    }
    else {
      piStack_1f798 = (int *)0xa6;
      puStack_1f7a8 = (undefined1 *)0x0;
      pcStack_1f7b0 = (code *)0x78f6dc;
      piStack_1f5c8 = (int *)FUN_007c2480();
    }
    local_8._0_1_ = 2;
    piStack_1f540 = piStack_1f5c8;
    FUN_007c30e0();
  }
  else {
    pvVar3 = operator_new(0x1ec);
    local_8._0_1_ = 7;
    if (pvVar3 == (void *)0x0) {
      piStack_1f5a8 = (int *)0x0;
    }
    else {
      piStack_1f798 = (int *)0xa2;
      puStack_1f7a8 = (undefined1 *)0x0;
      pcStack_1f7b0 = (code *)0x78f5ed;
      piStack_1f5a8 = (int *)FUN_007c2480();
    }
    local_8._0_1_ = 2;
    piStack_1f540 = piStack_1f5a8;
  }
  FUN_007d2870();
  (**(code **)(*piStack_1f540 + 0x40))();
  (**(code **)(*piStack_1f540 + 0x3c))();
  piStack_1f798 = (int *)0x78f775;
  FUN_007c2950();
  piStack_1f798 = (int *)0x78f785;
  FUN_007c23e0();
  piStack_1f798 = piStack_1f540;
  FUN_007d2110();
  pcStack_1f7b0 = (code *)0x78f7ad;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &puStack_1f7a8,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  cVar1 = FUN_004895d0();
  if (cVar1 != '\0') {
    if (bVar5) {
      piStack_1f798 = (int *)0x78f8a9;
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 10;
      if (pvVar3 == (void *)0x0) {
        piStack_1f5c0 = (int *)0x0;
      }
      else {
        piStack_1f798 = (int *)0xc2200000;
        puStack_1f7a8 = (undefined1 *)0x43ab0000;
        pcStack_1f7b0 = (code *)0x0;
        piStack_1f5c0 = (int *)FUN_007c2480();
      }
      piStack_1f544 = piStack_1f5c0;
    }
    else {
      piStack_1f798 = (int *)0x78f7ea;
      pvVar3 = operator_new(0x1ec);
      local_8._0_1_ = 9;
      if (pvVar3 == (void *)0x0) {
        piStack_1f5b0 = (int *)0x0;
      }
      else {
        piStack_1f798 = (int *)0xc2200000;
        puStack_1f7a8 = (undefined1 *)0x43ab0000;
        pcStack_1f7b0 = (code *)0x0;
        piStack_1f5b0 = (int *)FUN_007c2480();
      }
      piStack_1f544 = piStack_1f5b0;
    }
    local_8._0_1_ = 2;
    piStack_1f798 = (int *)0x78f968;
    FUN_007d2870();
    piStack_1f798 = (int *)0x78f980;
    (**(code **)(*piStack_1f544 + 0x40))();
    piStack_1f798 = (int *)0x89d7e4;
    (**(code **)(*piStack_1f544 + 0x3c))();
    piStack_1f798 = (int *)0x78f9aa;
    FUN_007c2950();
    piStack_1f798 = (int *)0x78f9ba;
    FUN_007c23e0();
    piStack_1f798 = piStack_1f544;
    FUN_007d2110();
  }
  piStack_1f798 = (int *)0x78f9d9;
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 0xb;
  if (pvVar3 == (void *)0x0) {
    piStack_1f574 = (int *)0x0;
  }
  else {
    piStack_1f798 = (int *)0x0;
    puStack_1f7a8 = (undefined1 *)0x43b88000;
    pcStack_1f7b0 = (code *)0x0;
    piStack_1f574 = (int *)FUN_007c2480();
  }
  local_8._0_1_ = 2;
  piStack_1f798 = (int *)0x78fa95;
  FUN_007d2870();
  piStack_1f798 = (int *)0x78faad;
  (**(code **)(*piStack_1f574 + 0x40))();
  piStack_1f798 = (int *)0x89e1f0;
  (**(code **)(*piStack_1f574 + 0x3c))();
  FUN_007c2950();
  FUN_007c23e0();
  FUN_007d2110();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &pcStack_1f7b0,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe084c,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_004880e0();
  FUN_0041f870();
  FUN_004889c0();
  pvVar3 = operator_new(0x294c);
  local_8._0_1_ = 0xc;
  if (pvVar3 == (void *)0x0) {
    piStack_1f584 = (int *)0x0;
  }
  else {
    puStack_1f7a8 = (undefined1 *)0x43d00000;
    pcStack_1f7b0 = (code *)0x44620000;
    piStack_1f584 = (int *)FUN_007ccb70();
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_007d2110();
  cVar1 = FUN_00488d80();
  if (cVar1 == '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &pcStack_1f7b0,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &stack0x00000008);
    FUN_00489670();
    FUN_0041f870();
    puStack_1f7a8 = (undefined1 *)0x78fc97;
    FUN_0081cb40();
    (**(code **)(*piStack_1f584 + 0x3c))();
  }
  else {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &pcStack_1f7b0,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &stack0x00000008);
    FUN_00489670();
    FUN_0041f870();
    (**(code **)(*piStack_1f584 + 0x3c))();
  }
  if (bVar5) {
    puStack_1f7a8 = (undefined1 *)0x78fd25;
    FUN_007cce50();
  }
  puStack_1f7a8 = (undefined1 *)0x78fd30;
  pvVar3 = operator_new(0x295c);
  local_8._0_1_ = 0xd;
  if (pvVar3 == (void *)0x0) {
    uStack_1f594 = 0;
  }
  else {
    puStack_1f7a8 = (undefined1 *)0x20;
    pcStack_1f7b0 = FUN_0078ed20;
    uStack_1f7c0 = 0x44620000;
    uStack_1f594 = FUN_007cd8d0();
  }
  local_8._0_1_ = 2;
  param_1[0x57] = uStack_1f594;
  DAT_00945530 = param_1[0x57];
  if (bVar5) {
    puStack_1f7a8 = (undefined1 *)0x78fe12;
    FUN_007cce50();
  }
  uStack_1f7c0 = 0x78fe26;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0848,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00489670();
  puStack_1f7a8 = auStack_1f514;
  (**(code **)(*(int *)param_1[0x57] + 0x3c))();
  pcStack_1f7b0 = (code *)param_1[0x57];
  FUN_007d2110();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe083c,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  pcStack_1f7b0 = (code *)FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0838,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00489b60();
  pcStack_1f7b0 = (code *)local_114;
  FUN_004889c0();
  pcStack_1f7b0 = (code *)0x78fefa;
  pvVar3 = operator_new(0x294c);
  local_8._0_1_ = 0xe;
  if (pvVar3 == (void *)0x0) {
    piStack_1f5a4 = (int *)0x0;
  }
  else {
    pcStack_1f7b0 = (code *)0x20;
    uStack_1f7c0 = 0x42ea0000;
    piStack_1f5a4 = (int *)FUN_007ccb70();
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  if (bVar5) {
    pcStack_1f7b0 = (code *)0x78ffb3;
    FUN_007cce50();
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &uStack_1f7c0,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00489670();
  pcStack_1f7b0 = (code *)auStack_1f514;
  (**(code **)(*piStack_1f5a4 + 0x3c))();
  FUN_007d2110();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0838,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0834,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  iVar2 = FUN_004880e0();
  cVar1 = FUN_00488d80();
  if (cVar1 == '\x01') {
    FUN_007ccd20();
    FUN_007ccd20();
    FUN_007ccd20();
  }
  param_1[0x58] = 0;
  pvVar3 = operator_new(0x144);
  local_8._0_1_ = 0xf;
  if (pvVar3 != (void *)0x0) {
    uStack_1f7c0 = 0x4400c000;
    FUN_007d1cc0("movie");
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  cVar1 = FUN_00427310();
  if (cVar1 != '\0') {
    FUN_007d3850();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &stack0xfffe0838,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &stack0x00000008);
    iVar2 = FUN_00488ec0();
    if (iVar2 == 0) {
      FUN_007d3e00();
      FUN_0078ef60();
    }
    else {
      FUN_007d3e00();
    }
    goto LAB_00790987;
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0838,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0834,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008);
  iVar4 = FUN_004880e0();
  switch(*(undefined4 *)(iVar4 + 0x78)) {
  case 1:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 == 0) {
        FUN_007d3e00();
        FUN_0078ef60();
        break;
      }
    }
    FUN_007d3e00();
    break;
  case 2:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 == 2) {
        FUN_007d3e00();
        FUN_0078ef60();
        FUN_0043a170();
        break;
      }
    }
    FUN_007d3e00();
    break;
  case 3:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
LAB_00790432:
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0xfffe0838,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0x00000008);
        iVar2 = FUN_00488ec0();
        if (iVar2 == 0) goto LAB_0079047b;
      }
      FUN_007d3e00();
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 != 5) goto LAB_00790432;
LAB_0079047b:
      FUN_007d3e00();
      FUN_0078ef60();
    }
    break;
  case 4:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
LAB_0079050b:
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0xfffe0838,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0x00000008);
        iVar2 = FUN_00488ec0();
        if (iVar2 == 2) goto LAB_00790554;
      }
      FUN_007d3e00();
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 != 8) goto LAB_0079050b;
LAB_00790554:
      FUN_007d3e00();
      FUN_0078ef60();
    }
    break;
  case 5:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 == 10) {
        FUN_007d3e00();
        FUN_0078ef60();
        break;
      }
    }
    FUN_007d3e00();
    break;
  case 6:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
LAB_00790674:
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0xfffe0838,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0x00000008);
        iVar2 = FUN_00488ec0();
        if (iVar2 == 4) goto LAB_007906bd;
      }
      FUN_007d3e00();
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 != 0xc) goto LAB_00790674;
LAB_007906bd:
      FUN_007d3e00();
      FUN_0078ef60();
    }
    break;
  case 7:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 == 0xf) {
        FUN_007d3e00();
        FUN_0078ef60();
        break;
      }
    }
    FUN_007d3e00();
    break;
  case 8:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
LAB_007907dd:
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0xfffe0838,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0x00000008);
        iVar2 = FUN_00488ec0();
        if (iVar2 == 0) goto LAB_00790826;
      }
      FUN_007d3e00();
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 != 0) goto LAB_007907dd;
LAB_00790826:
      FUN_007d3e00();
      FUN_0078ef60();
    }
    break;
  case 9:
    FUN_007d3850();
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
LAB_007908b6:
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0xfffe0838,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0x00000008);
        iVar2 = FUN_00488ec0();
        if (iVar2 == 4) goto LAB_007908ff;
      }
      FUN_007d3e00();
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0838,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000008);
      iVar2 = FUN_00488ec0();
      if (iVar2 != 6) goto LAB_007908b6;
LAB_007908ff:
      FUN_007d3e00();
      FUN_0078ef60();
    }
    break;
  default:
    if (*(char *)(iVar2 + 200) == '\0') {
      FUN_0041f870();
      FUN_007d2870();
    }
    else {
      FUN_0041f870();
      FUN_007d3850();
      FUN_007d3dd0();
    }
  }
LAB_00790987:
  FUN_007d2110();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  pcStack_1f7b0 = (code *)0x7909c5;
  FUN_0083e885();
  return;
}

