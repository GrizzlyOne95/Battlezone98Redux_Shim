
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_0045dd40(undefined4 param_1,char *param_2,char param_3,byte param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puStackY_d4;
  int iStackY_d0;
  undefined *puStackY_cc;
  uint local_c4;
  undefined1 local_c0 [8];
  undefined1 local_b8 [8];
  char *local_b0;
  undefined *local_ac;
  undefined *local_a8;
  undefined4 local_a4;
  undefined1 *local_a0;
  char *local_9c;
  char *local_98;
  undefined4 local_94;
  undefined1 local_90 [8];
  char *local_88;
  int local_84;
  uint local_80;
  undefined1 *local_7c;
  int local_78;
  undefined8 local_74;
  undefined1 *local_6c;
  undefined1 local_68 [24];
  undefined1 local_50 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_38 [24];
  int local_20;
  undefined4 local_1c;
  undefined1 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084727b;
  local_10 = ExceptionList;
  local_c4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_80 = 0;
  local_14 = local_c4;
  FUN_0045e380();
  local_8 = 0;
  basic_string<>();
  local_8._0_1_ = 1;
  if (param_2 == (char *)0x0) {
    puStackY_cc = (undefined *)0x45de4f;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_38,"netveh.odf");
  }
  else {
    puStackY_cc = (undefined *)0x45dda6;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_38,param_2);
    puStackY_cc = &DAT_008752b0;
    iStackY_d0 = 0x45ddba;
    local_84 = FUN_0045e1a0();
    if (local_84 == -1) {
      puStackY_cc = (undefined *)0x45de40;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_38,"netveh.odf");
    }
    else {
      puStackY_cc = (undefined *)0x0;
      iStackY_d0 = (int)local_50;
      puStackY_d4 = (undefined1 *)0x45ddda;
      puStackY_cc = (undefined *)FUN_0045e1d0();
      local_8._0_1_ = 2;
      iStackY_d0 = (int)local_68;
      puStackY_d4 = (undefined1 *)0x45de05;
      local_ac = puStackY_cc;
      local_a8 = puStackY_cc;
      local_a4 = FUN_0045f170();
      puStackY_cc = (undefined *)0x45de1d;
      FUN_0045e0f0();
      ~basic_string<>();
      local_8._0_1_ = 1;
      ~basic_string<>();
    }
  }
  FUN_0041f870();
  puStackY_cc = (undefined *)0x45de5d;
  iVar1 = FUN_00481f10();
  if (iVar1 == 0) {
    puStackY_cc = (undefined *)0x45de71;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_38,"netveh.odf");
  }
  FUN_0041f870();
  puStackY_cc = (undefined *)0x45de7f;
  local_94 = FUN_00481af0();
  FUN_0041f870();
  puStackY_cc = (undefined *)0x45de96;
  local_78 = FUN_00481a60();
  iVar1 = -(local_78 + 1);
  local_a0 = local_c0 + iVar1 + -4;
  local_7c = local_c0 + iVar1 + -4;
  *(int *)(&stack0xffffff38 + iVar1) = local_78;
  *(undefined4 *)((int)&puStackY_cc + iVar1) = local_94;
  *(undefined1 **)((int)&iStackY_d0 + iVar1) = local_7c;
  *(undefined4 *)((int)&puStackY_d4 + iVar1) = 0x45deca;
  memcpy(*(void **)((int)&iStackY_d0 + iVar1),*(void **)((int)&puStackY_cc + iVar1),
         *(size_t *)(&stack0xffffff38 + iVar1));
  local_7c[local_78] = 0;
  *(undefined4 *)(&stack0xffffff38 + iVar1) = 0x45dede;
  uVar2 = FUN_0041f870();
  *(undefined4 *)(&stack0xffffff38 + iVar1) = uVar2;
  *(undefined4 *)((int)&puStackY_cc + iVar1) = 0x45dee4;
  FUN_00481990();
  local_6c = local_7c;
  while( true ) {
    *(undefined **)(&stack0xffffff38 + iVar1) = &DAT_008752c8;
    *(undefined1 **)((int)&puStackY_cc + iVar1) = local_6c;
    *(undefined4 *)((int)&iStackY_d0 + iVar1) = 0x45defc;
    local_88 = strtok(*(char **)((int)&puStackY_cc + iVar1),*(char **)(&stack0xffffff38 + iVar1));
    local_6c = (undefined1 *)0x0;
    *(undefined **)(&stack0xffffff38 + iVar1) = &DAT_008752c8;
    *(undefined1 **)((int)&puStackY_cc + iVar1) = local_6c;
    *(undefined4 *)((int)&iStackY_d0 + iVar1) = 0x45df1b;
    local_b0 = strtok(*(char **)((int)&puStackY_cc + iVar1),*(char **)(&stack0xffffff38 + iVar1));
    *(undefined **)(&stack0xffffff38 + iVar1) = &DAT_008752c8;
    *(undefined1 **)((int)&puStackY_cc + iVar1) = local_6c;
    *(undefined4 *)((int)&iStackY_d0 + iVar1) = 0x45df33;
    local_9c = strtok(*(char **)((int)&puStackY_cc + iVar1),*(char **)(&stack0xffffff38 + iVar1));
    *(undefined **)(&stack0xffffff38 + iVar1) = &DAT_00871530;
    *(undefined1 **)((int)&puStackY_cc + iVar1) = local_6c;
    *(undefined4 *)((int)&iStackY_d0 + iVar1) = 0x45df4b;
    local_98 = strtok(*(char **)((int)&puStackY_cc + iVar1),*(char **)(&stack0xffffff38 + iVar1));
    if ((((local_88 == (char *)0x0) || (local_b0 == (char *)0x0)) || (local_9c == (char *)0x0)) ||
       (local_98 == (char *)0x0)) break;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    *(undefined4 *)(&stack0xffffff38 + iVar1) = 8;
    *(char **)((int)&puStackY_cc + iVar1) = local_88;
    *(int **)((int)&iStackY_d0 + iVar1) = &local_20;
    *(undefined4 *)((int)&puStackY_d4 + iVar1) = 0x45df9b;
    strncpy(*(char **)((int)&iStackY_d0 + iVar1),*(char **)((int)&puStackY_cc + iVar1),
            *(size_t *)(&stack0xffffff38 + iVar1));
    local_74._0_4_ = local_20;
    local_74._4_4_ = local_1c;
    *(undefined8 **)(&stack0xffffff38 + iVar1) = &local_74;
    *(undefined1 **)((int)&puStackY_cc + iVar1) = local_c0;
    *(undefined4 *)((int)&iStackY_d0 + iVar1) = 0x45dfc0;
    FUN_0045e3e0();
    if (param_3 != '\0') {
      *(uint *)(&stack0xffffff38 + iVar1) = (uint)param_4;
      *(undefined4 *)((int)&puStackY_cc + iVar1) = local_74._4_4_;
      *(int *)((int)&iStackY_d0 + iVar1) = (int)local_74;
      *(undefined4 *)((int)&puStackY_d4 + iVar1) = 0x45dfda;
      local_74 = FUN_0045dbb0();
      if (local_74 != 0) {
        *(undefined8 **)(&stack0xffffff38 + iVar1) = &local_74;
        *(undefined1 **)((int)&puStackY_cc + iVar1) = local_b8;
        *(undefined4 *)((int)&iStackY_d0 + iVar1) = 0x45e001;
        FUN_0045e3e0();
      }
    }
  }
  *(undefined1 **)(&stack0xffffff38 + iVar1) = local_90;
  *(undefined4 *)((int)&puStackY_cc + iVar1) = 0x45e015;
  FUN_0045e3b0();
  local_80 = local_80 | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  *(undefined4 *)(&stack0xffffff38 + iVar1) = 0x45e02a;
  ~basic_string<>();
  local_8 = 0xffffffff;
  *(undefined4 *)(&stack0xffffff38 + iVar1) = 0x45e03c;
  FUN_0045c7d0();
  ExceptionList = local_10;
  local_c4 = 0x45e05a;
  FUN_0083e885();
  return;
}

