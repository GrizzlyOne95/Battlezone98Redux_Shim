
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_00790fe0(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puStack_1f67c;
  int *piStack_1f664;
  undefined4 uStack_1f5a0;
  undefined4 uStack_1f59c;
  void *pvStack_1f598;
  void *pvStack_1f594;
  undefined4 uStack_1f590;
  void *pvStack_1f58c;
  void *pvStack_1f588;
  void *pvStack_1f584;
  undefined1 *puStack_1f580;
  uint uStack_1f57c;
  undefined4 uStack_1f578;
  undefined4 uStack_1f574;
  void *pvStack_1f570;
  int *piStack_1f56c;
  undefined4 uStack_1f568;
  int *piStack_1f564;
  void *pvStack_1f560;
  int *piStack_1f55c;
  undefined4 uStack_1f558;
  int *piStack_1f554;
  void *pvStack_1f550;
  void *pvStack_1f54c;
  undefined4 uStack_1f548;
  undefined1 *puStack_1f544;
  int *piStack_1f540;
  int *piStack_1f53c;
  int *piStack_1f538;
  char cStack_1f531;
  undefined4 *puStack_1f530;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085eea6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_007d0fa0();
  local_8._0_1_ = 1;
  *puStack_1f530 = cUI_MissionArchives::vftable;
  puStack_1f530[0x51] = 0;
  puStack_1f530[0x52] = 0;
  puStack_1f530[0x53] = 0;
  basic_string<>();
  local_8._0_1_ = 2;
  iVar2 = FUN_004344a0();
  cStack_1f531 = iVar2 == 2;
  uStack_1f57c = (uint)(byte)cStack_1f531;
  FID_conflict_operator_();
  FUN_00482860();
  DAT_00945534 = puStack_1f530;
  pvStack_1f588 = operator_new(0x144);
  local_8._0_1_ = 3;
  if (pvStack_1f588 == (void *)0x0) {
    uStack_1f590 = 0;
  }
  else {
    piStack_1f664 = (int *)0x0;
    uStack_1f590 = FUN_007d1cc0();
  }
  local_8._0_1_ = 2;
  puStack_1f530[0x5a] = uStack_1f590;
  FUN_007d3f20();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &piStack_1f664,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00489020();
  local_8._0_1_ = 4;
  FUN_0041f870();
  FUN_007d2870();
  local_8._0_1_ = 2;
  ~basic_string<>();
  FUN_007d2110();
  FUN_0081cb40();
  FUN_0081cb40();
  uStack_1f59c = FUN_0081cb40();
  pvStack_1f598 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvStack_1f598 == (void *)0x0) {
    piStack_1f554 = (int *)0x0;
  }
  else {
    piStack_1f664 = (int *)0x43ab0000;
    piStack_1f554 = (int *)FUN_007c2480();
  }
  local_8._0_1_ = 2;
  piStack_1f540 = piStack_1f554;
  FUN_007d2870();
  (**(code **)(*piStack_1f540 + 0x40))();
  (**(code **)(*piStack_1f540 + 0x3c))();
  FUN_007c2950();
  FUN_007c23e0();
  FUN_007d2110();
  pvStack_1f594 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvStack_1f594 == (void *)0x0) {
    piStack_1f55c = (int *)0x0;
  }
  else {
    piStack_1f664 = (int *)0x24;
    puStack_1f67c = (undefined4 *)0x791428;
    piStack_1f55c = (int *)FUN_007c2480();
  }
  local_8._0_1_ = 2;
  piStack_1f53c = piStack_1f55c;
  FUN_007d2870();
  (**(code **)(*piStack_1f53c + 0x40))();
  (**(code **)(*piStack_1f53c + 0x3c))();
  piStack_1f664 = (int *)0x7914a8;
  FUN_007c2950();
  piStack_1f664 = (int *)0x7914b8;
  FUN_007c23e0();
  piStack_1f664 = piStack_1f53c;
  FUN_007d2110();
  if (cStack_1f531 == '\0') {
    piStack_1f664 = (int *)0x7914ec;
    pvStack_1f54c = operator_new(0x1ec);
    local_8._0_1_ = 7;
    if (pvStack_1f54c == (void *)0x0) {
      piStack_1f564 = (int *)0x0;
    }
    else {
      piStack_1f664 = (int *)0xc2200000;
      puStack_1f67c = (undefined4 *)0x0;
      piStack_1f564 = (int *)FUN_007c2480();
    }
    local_8._0_1_ = 2;
    piStack_1f538 = piStack_1f564;
  }
  else {
    piStack_1f664 = (int *)0x7915ab;
    pvStack_1f58c = operator_new(0x1ec);
    local_8._0_1_ = 8;
    if (pvStack_1f58c == (void *)0x0) {
      piStack_1f56c = (int *)0x0;
    }
    else {
      piStack_1f664 = (int *)0xc2800000;
      puStack_1f67c = (undefined4 *)0x0;
      piStack_1f56c = (int *)FUN_007c2480();
    }
    local_8._0_1_ = 2;
    piStack_1f538 = piStack_1f56c;
    piStack_1f664 = (int *)0x7916a3;
    FUN_007c30e0();
  }
  piStack_1f664 = (int *)0x7916b3;
  FUN_007d2870();
  piStack_1f664 = (int *)0x7916cb;
  (**(code **)(*piStack_1f538 + 0x40))();
  piStack_1f664 = (int *)0x89d7e4;
  (**(code **)(*piStack_1f538 + 0x3c))();
  FUN_007c2950();
  FUN_007c23e0();
  FUN_007d2110();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &puStack_1f67c,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0980,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_004880e0();
  FUN_0041f870();
  FUN_004889c0();
  pvStack_1f584 = operator_new(0x295c);
  local_8._0_1_ = 9;
  if (pvStack_1f584 == (void *)0x0) {
    uStack_1f574 = 0;
  }
  else {
    puStack_1f67c = (undefined4 *)0x43d00000;
    uStack_1f574 = FUN_007cd8d0();
  }
  local_8._0_1_ = 2;
  puStack_1f530[0x52] = uStack_1f574;
  DAT_00945538 = puStack_1f530[0x52];
  if (cStack_1f531 != '\0') {
    FUN_007cce50();
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &puStack_1f67c,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00489670();
  (**(code **)(*(int *)puStack_1f530[0x52] + 0x3c))();
  FUN_007d2110();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0978,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00488ec0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0974,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00489b60();
  FUN_004889c0();
  pvStack_1f550 = operator_new(0x294c);
  local_8._0_1_ = 10;
  if (pvStack_1f550 == (void *)0x0) {
    uStack_1f558 = 0;
  }
  else {
    puStack_1f67c = (undefined4 *)0x441e8000;
    uStack_1f558 = FUN_007ccb70();
  }
  local_8._0_1_ = 2;
  puStack_1f530[0x53] = uStack_1f558;
  if (cStack_1f531 != '\0') {
    FUN_007cce50();
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe097c,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00489670();
  (**(code **)(*(int *)puStack_1f530[0x53] + 0x3c))();
  puStack_1f67c = (undefined4 *)puStack_1f530[0x53];
  FUN_007d2110();
  if (cStack_1f531 == '\0') {
    puStack_1f67c = (undefined4 *)0x791ae6;
    pvStack_1f560 = operator_new(0x180);
    local_8._0_1_ = 0xb;
    if (pvStack_1f560 == (void *)0x0) {
      uStack_1f568 = 0;
    }
    else {
      puStack_1f67c = (undefined4 *)0xff00ff00;
      uStack_1f568 = FUN_007c9de0("MissionsList",0x42ba0000,0x42a80000,0x44340000,0x43fa0000);
    }
    puStack_1f530[0x51] = uStack_1f568;
  }
  else {
    puStack_1f67c = (undefined4 *)0x791bc4;
    pvStack_1f570 = operator_new(0x180);
    local_8._0_1_ = 0xc;
    if (pvStack_1f570 == (void *)0x0) {
      uStack_1f578 = 0;
    }
    else {
      puStack_1f67c = (undefined4 *)0xff00ff00;
      uStack_1f578 = FUN_007c9de0("MissionsList",0x42ba0000,0x42a80000,0x44318000,0x44020000);
    }
    puStack_1f530[0x51] = uStack_1f578;
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  DAT_0094553c = puStack_1f530[0x51];
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0974,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  uStack_1f548 = FUN_00488680();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0xfffe0974,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000004);
  FUN_00488f70();
  uStack_1f5a0 = size();
  puStack_1f67c = &uStack_1f5a0;
  puVar3 = (undefined4 *)_Min_value<>();
  puStack_1f580 = (undefined1 *)*puVar3;
  puStack_1f67c = (undefined4 *)&stack0x00000004;
  cVar1 = FUN_00427310();
  if (cVar1 != '\0') {
    puStack_1f580 = (undefined1 *)size();
  }
  for (puStack_1f544 = (undefined1 *)0x0; puStack_1f544 < puStack_1f580;
      puStack_1f544 = puStack_1f544 + 1) {
    cVar1 = FUN_00488d80();
    if (cVar1 == '\0') {
      puStack_1f67c = (undefined4 *)puStack_1f544;
      FUN_004200d0();
      FUN_0041f870();
      FUN_0081cb40();
      FUN_007cabf0();
    }
    else {
      puStack_1f67c = (undefined4 *)puStack_1f544;
      FUN_004200d0();
      FUN_0041f870();
      FUN_007cabf0();
    }
  }
  puStack_1f67c = (undefined4 *)0x791e22;
  FUN_007cb3e0();
  puStack_1f67c = (undefined4 *)puStack_1f530[0x51];
  FUN_007d2110();
  puStack_1f67c = (undefined4 *)0x791e55;
  FUN_007cafa0();
  FUN_00790b40();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

