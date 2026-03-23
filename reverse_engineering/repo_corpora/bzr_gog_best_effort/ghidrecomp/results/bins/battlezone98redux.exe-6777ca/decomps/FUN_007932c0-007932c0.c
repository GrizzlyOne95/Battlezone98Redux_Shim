
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Removing unreachable block (ram,0x00793b3a) */

void __fastcall FUN_007932c0(int param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  bool bVar6;
  undefined4 uStack_1f51c;
  char *pcStack_1f518;
  int *piStack_1f490;
  undefined4 uStack_1f488;
  int *piStack_1f484;
  undefined4 uStack_1f47c;
  int *piStack_1f468;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
  abStack_1f42c [128028];
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f011;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  bVar6 = false;
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00482850();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(abStack_1f42c,pbVar2)
  ;
  local_8 = 0;
  cVar1 = FUN_00427310();
  if (cVar1 == '\0') {
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0xfffe0af4,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094ffe0);
      iVar5 = FUN_004885d0();
      iVar3 = FUN_004888b0();
      if (iVar3 + 1 == iVar5) {
        pcStack_1f518 = (char *)0x7933c3;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &stack0xfffe0af0,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &DAT_0094ffe0);
        FUN_004880e0();
        FUN_0041f870();
        FUN_007d2870();
        bVar6 = true;
        goto LAB_0079340a;
      }
    }
    FUN_007d2870();
  }
  else {
    FUN_007d2870();
  }
LAB_0079340a:
  if (*(int *)(param_1 + 0x150) != 0) {
    FUN_007d21c0();
    if (*(undefined4 **)(param_1 + 0x150) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x150))();
    }
    *(undefined4 *)(param_1 + 0x150) = 0;
  }
  DAT_0091830c = 2;
  FUN_0081cb40();
  FUN_0081cb40();
  FUN_0081cb40();
  FUN_0081cb40();
  if (!bVar6) {
    pvVar4 = operator_new(0x1ec);
    local_8._0_1_ = 1;
    if (pvVar4 == (void *)0x0) {
      piStack_1f484 = (int *)0x0;
    }
    else {
      pcStack_1f518 = "MainMenu";
      uStack_1f51c = 0x7935a0;
      piStack_1f484 = (int *)FUN_007c2480();
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_007d2870();
    (**(code **)(*piStack_1f484 + 0x40))();
    (**(code **)(*piStack_1f484 + 0x3c))();
    FUN_007c2950();
    FUN_007c23e0();
    FUN_007d2110();
  }
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar4 == (void *)0x0) {
    piStack_1f468 = (int *)0x0;
  }
  else {
    pcStack_1f518 = "Save";
    uStack_1f51c = 0x7936d3;
    piStack_1f468 = (int *)FUN_007c2480();
  }
  local_8._0_1_ = 0;
  FUN_007d2870();
  (**(code **)(*piStack_1f468 + 0x40))();
  (**(code **)(*piStack_1f468 + 0x3c))();
  FUN_007c2950();
  FUN_007c23e0();
  FUN_007d2110();
  pvVar4 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar4 == (void *)0x0) {
    piStack_1f490 = (int *)0x0;
  }
  else {
    pcStack_1f518 = (char *)0x0;
    uStack_1f51c = 0;
    piStack_1f490 = (int *)FUN_007c2480(&DAT_0089e55c);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870();
  (**(code **)(*piStack_1f490 + 0x40))();
  (**(code **)(*piStack_1f490 + 0x3c))();
  FUN_007c2950();
  FUN_007c23e0();
  FUN_007c30e0();
  FUN_007d2110();
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00482850();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &uStack_1f51c,pbVar2);
  iVar5 = FUN_004885d0();
  bVar6 = DAT_0091831c == iVar5 + -1;
  if (DAT_00918314 == 0) {
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00482850();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &uStack_1f51c,pbVar2);
    iVar5 = FUN_00488ec0();
    if (DAT_0091831c < iVar5) {
      DAT_00918314 = 1;
    }
  }
  if (DAT_00918314 != 0 || bVar6) {
    FUN_0081cb40();
    FUN_007c2950();
  }
  pvVar4 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar4 == (void *)0x0) {
    uStack_1f488 = 0;
  }
  else {
    pcStack_1f518 = (char *)0x44908000;
    uStack_1f51c = 0x43710000;
    uStack_1f488 = FUN_007cc390("MISSION_COMPLETE",0x430e0000);
  }
  local_8._0_1_ = 0;
  *(undefined4 *)(param_1 + 0x154) = uStack_1f488;
  (**(code **)(**(int **)(param_1 + 0x154) + 0x3c))();
  FUN_007d2110();
  BadAllocException();
  local_8._0_1_ = 5;
  FUN_0041f870();
  FUN_004889c0();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  pvVar4 = operator_new(0x294c);
  local_8._0_1_ = 6;
  if (pvVar4 == (void *)0x0) {
    uStack_1f47c = 0;
  }
  else {
    pcStack_1f518 = (char *)0x44908000;
    uStack_1f51c = 0x43a30000;
    uStack_1f47c = FUN_007ccb70("RESULT",0x430e0000);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  *(undefined4 *)(param_1 + 0x158) = uStack_1f47c;
  iVar5 = FUN_004344a0();
  if (iVar5 == 2) {
    FUN_007cce50();
  }
  (**(code **)(**(int **)(param_1 + 0x158) + 0x3c))();
  pcStack_1f518 = *(char **)(param_1 + 0x158);
  uStack_1f51c = 0x793c6a;
  FUN_007d2110();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

