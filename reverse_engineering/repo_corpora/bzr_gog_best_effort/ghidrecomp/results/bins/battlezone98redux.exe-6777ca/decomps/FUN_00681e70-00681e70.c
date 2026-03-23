
void FUN_00681e70(void)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar7;
  int iVar8;
  code *pcVar9;
  undefined1 auStack_1cc [160];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  undefined1 local_124 [4];
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 *local_118;
  undefined1 *local_114;
  undefined1 *local_110;
  undefined1 *local_10c;
  undefined1 *local_108;
  undefined1 *local_104;
  undefined1 *local_100;
  undefined1 local_fc [4];
  undefined1 local_f8 [24];
  undefined1 local_e0 [24];
  undefined1 local_c8 [24];
  undefined1 local_b0 [24];
  undefined1 local_98 [24];
  undefined1 local_80 [24];
  undefined1 local_68 [24];
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_008e8c0f = 1;
  cVar1 = operator!=<>(&DAT_025f8e68,&DAT_025f8ed0);
  if (cVar1 != '\0') {
    FUN_00574400(3,1);
    if (&stack0x00000000 == (undefined1 *)0x1dc) {
      local_118 = (undefined1 *)0x0;
    }
    else {
      local_118 = auStack_1cc;
    }
    pcVar9 = FUN_004bc8c0;
    uVar2 = FUN_004bc590(local_118,
                         "**************************************************************\nMISSION ISSUE!\nFound meshes that were not preloaded for mission "
                         ,&DAT_00915540);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar9);
    if (&stack0x00000000 == (undefined1 *)0x1dc) {
      local_114 = (undefined1 *)0x0;
    }
    else {
      local_114 = auStack_1cc;
    }
    FUN_004bc590(local_114,&DAT_0087d198);
    basic_string<>();
    basic_string<>();
    basic_string<>();
    FUN_00424640(local_fc);
    FID_conflict_begin(local_11c);
    basic_string<>(&DAT_00892bd0);
    while( true ) {
      cVar1 = FUN_00420f10(local_11c);
      if (cVar1 == '\0') break;
      uVar4 = FUN_004170c0();
      if (0x3c < uVar4) {
        if (&stack0x00000000 == (undefined1 *)0x1dc) {
          local_110 = (undefined1 *)0x0;
        }
        else {
          local_110 = auStack_1cc;
        }
        pcVar9 = FUN_004bc8c0;
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                 FUN_00574730(local_110,local_20);
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar9);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"");
      }
      uVar2 = FID_conflict_begin(local_12c);
      uVar5 = FUN_004237d0(uVar2);
      FUN_00421e00(local_128,uVar5);
      cVar1 = FUN_004221b0(uVar2);
      if (cVar1 != '\0') {
        uVar2 = FUN_004237d0(local_68,&DAT_00892870);
        uVar2 = FUN_00662500(local_c8,local_68,uVar2);
        uVar2 = FUN_00426a20(local_98,uVar2);
        uVar2 = FUN_0045f170(local_80,uVar2);
        FUN_00449810(uVar2);
        ~basic_string<>();
        ~basic_string<>();
        ~basic_string<>();
        uVar2 = FUN_004237d0(&DAT_008848ac);
        uVar2 = FUN_0048b7d0(local_f8,uVar2);
        FUN_00449810(uVar2);
        ~basic_string<>();
      }
      uVar2 = FID_conflict_begin(local_120);
      uVar5 = FUN_004237d0(uVar2);
      FUN_00421e00(local_124,uVar5);
      cVar1 = FUN_004221b0(uVar2);
      if (cVar1 != '\0') {
        uVar2 = FUN_004237d0(&DAT_008848ac);
        uVar2 = FUN_0048b7d0(local_e0,uVar2);
        FUN_00449810(uVar2);
        ~basic_string<>();
      }
      FUN_00422190();
    }
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      iVar6 = FUN_004170c0();
      uVar2 = FUN_0045e1d0(local_b0,0,iVar6 + -2);
      FUN_0045e0f0(uVar2);
      ~basic_string<>();
    }
    if (&stack0x00000000 == (undefined1 *)0x1dc) {
      local_108 = (undefined1 *)0x0;
    }
    else {
      local_108 = auStack_1cc;
    }
    FUN_00574730(local_108,local_20);
    if (&stack0x00000000 == (undefined1 *)0x1dc) {
      local_10c = (undefined1 *)0x0;
    }
    else {
      local_10c = auStack_1cc;
    }
    FUN_004bc590(local_10c,&DAT_00892bd4);
    if (&stack0x00000000 == (undefined1 *)0x1dc) {
      local_100 = (undefined1 *)0x0;
    }
    else {
      local_100 = auStack_1cc;
    }
    pcVar9 = FUN_004bc8c0;
    uVar2 = FUN_004bc590(local_100,"preload=",local_50);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar9);
    if (&stack0x00000000 == (undefined1 *)0x1dc) {
      local_104 = (undefined1 *)0x0;
    }
    else {
      local_104 = auStack_1cc;
    }
    uVar2 = FUN_004bc590(local_104,"newload=",local_38,
                         "\n***********************************************************\n");
    uVar2 = FUN_00574730(uVar2);
    FUN_004bc590(uVar2);
    pbVar7 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar7);
    ~basic_string<>();
    ~basic_string<>();
    ~basic_string<>();
    ~basic_string<>();
    FUN_00417f10();
  }
  iVar6 = FUN_00416410();
  iVar8 = FUN_00416410();
  iVar6 = FUN_00416410(iVar6 - iVar8);
  iVar8 = FUN_00416410();
  uVar2 = FUN_00416410(iVar6 - iVar8);
  FUN_007d6a70("Preload Meshes Results.  %d automatically identified, %d manually identified.  %d additional meshes required\n"
               ,uVar2);
  FUN_00425fd0();
  FUN_00425fd0();
  FUN_00425fd0();
  FUN_0083e885();
  return;
}

