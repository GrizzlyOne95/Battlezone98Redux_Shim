
/* WARNING: Removing unreachable block (ram,0x0074305b) */

void FUN_00742ee0(int param_1,char param_2)

{
  char cVar1;
  char *_Source;
  int iVar2;
  int iVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_630 [16];
  undefined4 uStack_620;
  undefined4 uStack_618;
  undefined1 *puStack_614;
  char *pcStack_610;
  size_t _Count;
  code *pcVar6;
  undefined1 auStack_5e8 [160];
  undefined4 local_548;
  undefined1 *local_544;
  undefined1 *local_540;
  undefined4 local_53c;
  undefined4 local_538;
  undefined4 local_534;
  undefined4 local_530;
  undefined4 local_52c;
  undefined4 local_528;
  undefined1 *local_524;
  undefined1 *local_520;
  undefined4 local_51c;
  undefined1 *local_518;
  undefined4 local_510;
  int *local_50c;
  int local_508;
  undefined1 local_4ff;
  undefined1 local_4fe;
  undefined1 local_4fd;
  undefined1 local_4f5;
  char local_4a8;
  int local_4a4;
  undefined1 local_450;
  int local_44c;
  char local_414 [1023];
  undefined1 uStack_15;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b2b2;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007435c0();
  local_8 = 0;
  cVar1 = operator!=<>();
  if ((cVar1 != '\0') && (cVar1 = FUN_00742d50(), cVar1 == '\0')) {
    local_508 = 0;
    cVar1 = FUN_0056f780();
    if (cVar1 != '\0') {
      FUN_0073bbd0();
      local_8 = CONCAT31(local_8._1_3_,1);
      FUN_0073c450();
      cVar1 = FUN_00427310();
      if ((((cVar1 == '\0') || (cVar1 = FUN_00427310(), cVar1 == '\0')) || (local_4a8 == '\0')) ||
         (local_4a4 == 0)) {
        _Count = 0x400;
        _Source = (char *)FUN_0041f870();
        pcStack_610 = (char *)0x743039;
        strncpy(local_414,_Source,_Count);
        local_510 = 0x3ff;
        uStack_15 = 0;
        local_518 = (undefined1 *)FUN_004fbaf0();
        if (local_518 != (undefined1 *)0x0) {
          *local_518 = 0;
        }
        local_544 = (undefined1 *)&uStack_618;
        uStack_620 = 0x7430b1;
        local_53c = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&uStack_618,
                               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(param_1 + 0xdc));
        local_8._0_1_ = 2;
        local_540 = abStack_630;
        local_528 = local_53c;
        local_548 = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              (abStack_630,
                               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(param_1 + 0xfc));
        local_8._0_1_ = 3;
        local_530 = local_548;
        FUN_00764790();
        local_8 = CONCAT31(local_8._1_3_,1);
        FUN_0076b7a0();
        FUN_004afeb0();
        local_508 = FUN_004b0190();
        FUN_004afe80();
        FUN_00764790();
        FUN_0076ba00();
      }
      else {
        local_508 = local_4a4;
      }
      local_8 = local_8 & 0xffffff00;
      FUN_0073cb40();
    }
    local_44c = local_508;
    cVar1 = operator!=<>();
    if ((cVar1 == '\0') || (cVar1 = FUN_0041f890(), cVar1 != '\0')) {
      local_450 = 1;
    }
    else {
      cVar1 = FUN_0056f780();
      if ((cVar1 == '\0') || (*(int *)(param_1 + 0xf8) == local_44c)) {
        local_4f5 = 0;
      }
      else {
        local_4f5 = 1;
      }
      local_50c = (int *)FUN_00764790();
      local_450 = (**(code **)(*local_50c + 4))();
    }
    *(int *)(param_1 + 0x4c) = local_44c;
    *(undefined1 *)(param_1 + 0x48) = local_450;
    local_52c = FUN_0073c0b0();
    FUN_0045e0f0();
    ~basic_string<>();
  }
  FUN_0042d8c0();
  FID_conflict_begin();
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    while (cVar1 = FUN_00420f10(), cVar1 != '\0') {
      FUN_0042da60();
      cVar1 = FUN_00427310();
      if ((cVar1 == '\0') && (iVar2 = FUN_0042da60(), *(char *)(iVar2 + 0x7c) == '\0')) {
        local_51c = 0;
      }
      else {
        local_51c = 1;
      }
      iVar2 = FUN_0042da60();
      *(undefined1 *)(iVar2 + 0x60) = (undefined1)local_51c;
      FUN_0042da80();
    }
  }
  else {
    while (cVar1 = FUN_00420f10(), cVar1 != '\0') {
      iVar2 = FUN_0042da60();
      iVar3 = FUN_0042da60();
      *(undefined1 *)(iVar3 + 0x60) = *(undefined1 *)(iVar2 + 0x7c);
      FUN_0042da80();
    }
  }
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    cVar1 = operator!=<>();
    if (cVar1 == '\0') {
      local_4ff = 1;
      local_8 = 0xffffffff;
      FUN_0073cb40();
    }
    else {
      if (param_2 != '\0') {
        FUN_00574400();
        local_8 = CONCAT31(local_8._1_3_,4);
        if (&stack0x00000000 == (undefined1 *)0x5f8) {
          local_524 = (undefined1 *)0x0;
        }
        else {
          local_524 = auStack_5e8;
        }
        pcStack_610 = "multi_two";
        puStack_614 = (undefined1 *)0x743423;
        FUN_0081cb40();
        pcStack_610 = local_524;
        puStack_614 = (undefined1 *)0x743433;
        FUN_004bc590();
        pcStack_610 = (char *)0x74343c;
        FUN_004bc590();
        FUN_00574730();
        cVar1 = operator!=<>();
        if (cVar1 != '\0') {
          if (&stack0x00000000 == (undefined1 *)0x5f8) {
            local_520 = (undefined1 *)0x0;
          }
          else {
            local_520 = auStack_5e8;
          }
          pcStack_610 = "multi_two";
          puStack_614 = (undefined1 *)0x7434a8;
          FUN_0081cb40();
          pcStack_610 = " ";
          puStack_614 = local_520;
          uStack_618 = 0x7434bd;
          pcStack_610 = (char *)FUN_004bc590();
          puStack_614 = (undefined1 *)0x7434c6;
          FUN_004bc590();
          pcStack_610 = (char *)0x7434cf;
          FUN_004bc590();
          FUN_00574730();
        }
        local_538 = GetPolicy();
        local_8._0_1_ = 5;
        local_534 = local_538;
        FUN_00745770();
        local_8._0_1_ = 4;
        ~basic_string<>();
        pcVar6 = FUN_004bc8c0;
        pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
        FUN_0081e820();
        pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
        pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,pbVar4);
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,pcVar6);
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_00417f10();
      }
      local_4fd = 0;
      local_8 = 0xffffffff;
      FUN_0073cb40();
    }
  }
  else {
    local_4fe = 0;
    local_8 = 0xffffffff;
    FUN_0073cb40();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

