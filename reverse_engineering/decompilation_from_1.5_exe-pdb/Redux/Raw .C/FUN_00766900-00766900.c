
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00766900(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int aiStackY_108 [3];
  uint local_f8;
  int local_f4;
  int local_f0;
  undefined4 local_ec;
  undefined1 *local_e8;
  int local_e4;
  int local_e0;
  char *local_dc;
  int local_d8;
  char *local_d4;
  int local_d0;
  undefined1 *local_cc;
  int local_c8;
  uint local_c4;
  undefined1 *local_c0;
  uint local_bc;
  char *local_b8;
  char *local_b4;
  char local_ad;
  int local_ac;
  int local_a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d24b;
  local_10 = ExceptionList;
  local_f8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  aiStackY_108[2] = 0x76693d;
  local_14 = local_f8;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_1);
  local_8 = 0;
  FUN_0041f870();
  aiStackY_108[2] = 0x766952;
  iVar2 = FUN_00481f10();
  if (iVar2 == 0) {
    aiStackY_108[2] = 0x766966;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"netveh.odf");
  }
  aiStackY_108[2] = local_a8 + 0x40;
  aiStackY_108[1] = 0x766979;
  cVar1 = operator!=<>();
  if (cVar1 == '\0') {
    local_f4 = FUN_0081dee0();
    local_f0 = local_f4 >> 0x1f;
    local_e0 = local_a8;
    if ((*(int *)(local_a8 + 0x58) == local_f4) && (*(int *)(local_a8 + 0x5c) == local_f0))
    goto LAB_00766e09;
  }
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  if ((*(int *)(local_a8 + 0x3c) != -1) &&
     (iVar2 = FUN_00766f80(), *(int *)(local_a8 + 0x3c) < iVar2)) {
    aiStackY_108[2] = 0x766a1e;
    FUN_00766fa0();
    aiStackY_108[2] = 0x766a27;
    FID_conflict_operator_();
  }
  for (local_c4 = 0; local_c4 < 5; local_c4 = local_c4 + 1) {
    FUN_007670d0();
  }
  *(undefined4 *)(local_a8 + 0x3c) = 0;
  FUN_0041f870();
  aiStackY_108[2] = 0x766a7a;
  local_ec = FUN_00481af0();
  FUN_0041f870();
  aiStackY_108[2] = 0x766a91;
  local_d0 = FUN_00481a60();
  aiStackY_108[2] = 0x766aac;
  FID_conflict_operator_();
  iVar2 = FUN_0081dee0();
  *(int *)(local_a8 + 0x58) = iVar2;
  *(int *)(local_a8 + 0x5c) = iVar2 >> 0x1f;
  iVar2 = -(local_d0 + 1);
  local_e8 = (undefined1 *)&local_f8;
  local_cc = (undefined1 *)&local_f8;
  *(int *)(&stack0xffffff04 + iVar2) = local_d0;
  *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = local_ec;
  *(undefined1 **)((int)aiStackY_108 + iVar2 + 4) = local_cc;
  *(undefined4 *)((int)aiStackY_108 + iVar2) = 0x766af8;
  memcpy(*(void **)((int)aiStackY_108 + iVar2 + 4),*(void **)((int)aiStackY_108 + iVar2 + 8),
         *(size_t *)(&stack0xffffff04 + iVar2));
  local_cc[local_d0] = 0;
  local_c0 = local_cc;
  while( true ) {
    *(undefined **)(&stack0xffffff04 + iVar2) = &DAT_008752c8;
    *(undefined1 **)((int)aiStackY_108 + iVar2 + 8) = local_c0;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 4) = 0x766b28;
    local_dc = strtok(*(char **)((int)aiStackY_108 + iVar2 + 8),*(char **)(&stack0xffffff04 + iVar2)
                     );
    local_c0 = (undefined1 *)0x0;
    *(undefined **)(&stack0xffffff04 + iVar2) = &DAT_008752c8;
    *(undefined1 **)((int)aiStackY_108 + iVar2 + 8) = local_c0;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 4) = 0x766b4d;
    local_b4 = strtok(*(char **)((int)aiStackY_108 + iVar2 + 8),*(char **)(&stack0xffffff04 + iVar2)
                     );
    *(undefined **)(&stack0xffffff04 + iVar2) = &DAT_008752c8;
    *(undefined1 **)((int)aiStackY_108 + iVar2 + 8) = local_c0;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 4) = 0x766b68;
    local_d4 = strtok(*(char **)((int)aiStackY_108 + iVar2 + 8),*(char **)(&stack0xffffff04 + iVar2)
                     );
    *(undefined **)(&stack0xffffff04 + iVar2) = &DAT_00871530;
    *(undefined1 **)((int)aiStackY_108 + iVar2 + 8) = local_c0;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 4) = 0x766b83;
    local_b8 = strtok(*(char **)((int)aiStackY_108 + iVar2 + 8),*(char **)(&stack0xffffff04 + iVar2)
                     );
    if ((((local_dc == (char *)0x0) || (local_b4 == (char *)0x0)) || (local_d4 == (char *)0x0)) ||
       (local_b8 == (char *)0x0)) break;
    while( true ) {
      *(int *)(&stack0xffffff04 + iVar2) = (int)*local_b8;
      *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766bc5;
      iVar4 = isspace(*(int *)(&stack0xffffff04 + iVar2));
      if (iVar4 == 0) break;
      local_b8 = local_b8 + 1;
    }
    *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766be8;
    FUN_00766e70();
    local_8 = CONCAT31(local_8._1_3_,2);
    *(char **)(&stack0xffffff04 + iVar2) = local_dc;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766bfe;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_a4,*(char **)(&stack0xffffff04 + iVar2));
    *(char **)(&stack0xffffff04 + iVar2) = local_b4;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c10;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_8c,*(char **)(&stack0xffffff04 + iVar2));
    *(char **)(&stack0xffffff04 + iVar2) = local_d4;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c1f;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_74,*(char **)(&stack0xffffff04 + iVar2));
    *(char **)(&stack0xffffff04 + iVar2) = local_b8;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c2e;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_5c,*(char **)(&stack0xffffff04 + iVar2));
    *(char **)(&stack0xffffff04 + iVar2) = local_b4;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c3a;
    local_e4 = FUN_00481a60();
    *(char **)(&stack0xffffff04 + iVar2) = local_b4;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c4f;
    local_d8 = FUN_00481af0();
    if ((local_e4 != 0) && (local_d8 != 0)) {
      *(int *)(&stack0xffffff04 + iVar2) = local_d8;
      *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c7c;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_8c,*(char **)(&stack0xffffff04 + iVar2));
    }
    *(char **)(&stack0xffffff04 + iVar2) = local_b4;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c88;
    FUN_00481990();
    *(undefined4 *)(&stack0xffffff04 + iVar2) = 0;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766c98;
    pcVar3 = (char *)FUN_00766f30();
    local_ad = *pcVar3;
    local_c8 = local_ad + -0x61;
    switch(local_ad) {
    case 'a':
      local_ac = 0;
      break;
    case 'b':
      local_ac = 2;
      break;
    case 'c':
      local_ac = 3;
      break;
    default:
      local_ac = 4;
      break;
    case 's':
      local_ac = 1;
    }
    if (*(int *)(local_a8 + 0x60) == local_ac) {
      *(undefined1 **)(&stack0xffffff04 + iVar2) = local_44;
      *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
       ((int)aiStackY_108 + iVar2 + 8) = local_a4;
      *(undefined4 *)((int)aiStackY_108 + iVar2 + 4) = 0x766d34;
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766d50;
        uVar5 = FUN_00766f80();
        *(undefined4 *)(local_a8 + 0x3c) = uVar5;
      }
    }
    *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
     (&stack0xffffff04 + iVar2) = local_a4;
    *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766d72;
    FUN_00766fc0();
    local_8 = CONCAT31(local_8._1_3_,1);
    *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766d81;
    FUN_00766ef0();
  }
  *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766d9b;
  iVar4 = FUN_00766f80();
  if (iVar4 == 0) {
    for (local_bc = 0; local_bc < 5; local_bc = local_bc + 1) {
      *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766dd5;
      iVar4 = FUN_00766f80();
      if (iVar4 != 0) {
        *(uint *)(local_a8 + 0x60) = local_bc;
        break;
      }
    }
  }
  *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766df4;
  uVar5 = FUN_0041f870();
  *(undefined4 *)(&stack0xffffff04 + iVar2) = uVar5;
  *(undefined4 *)((int)aiStackY_108 + iVar2 + 8) = 0x766dfa;
  FUN_00481990();
  local_8 = local_8 & 0xffffff00;
  *(undefined4 *)(&stack0xffffff04 + iVar2) = 0x766e09;
  ~basic_string<>();
LAB_00766e09:
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  local_f8 = 0x766e33;
  FUN_0083e885();
  return;
}

