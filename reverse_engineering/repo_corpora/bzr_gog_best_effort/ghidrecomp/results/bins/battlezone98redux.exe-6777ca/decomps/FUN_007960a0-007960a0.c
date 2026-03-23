
void __fastcall FUN_007960a0(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  char *_Source;
  undefined1 *puVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  int iStack_520;
  char *pcStack_51c;
  undefined4 uStack_510;
  undefined4 uStack_508;
  char *pcStack_504;
  undefined *puStack_500;
  size_t _Count;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_444 [48];
  char local_414 [1024];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f258;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00764760();
  iVar3 = FUN_0056f900();
  if (iVar3 != 0) {
    FUN_00764760();
    cVar1 = FUN_00742cf0();
    if ((cVar1 != '\0') &&
       (pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_007a4220(),
       pbVar4 != (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0
       )) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_444,pbVar4)
      ;
      local_8 = 0;
      puStack_500 = (undefined *)0x796158;
      FUN_00426b10();
      local_8._0_1_ = 1;
      FUN_00426a60();
      local_8._0_1_ = 2;
      FUN_00426af0();
      FUN_00417fd0();
      local_8._0_1_ = 3;
      FUN_0041f870();
      FUN_00426c30();
      local_8._0_1_ = 2;
      ~basic_string<>();
      FUN_007a4220();
      FUN_0041f870();
      puStack_500 = &DAT_0089e770;
      pcStack_504 = "multi";
      uStack_508 = 0x796202;
      FUN_00421f90();
      FUN_00417fd0();
      local_8._0_1_ = 4;
      FUN_0041f870();
      FUN_00426c90();
      local_8._0_1_ = 2;
      ~basic_string<>();
      _Count = 0x400;
      _Source = (char *)FUN_0041f870();
      puStack_500 = (undefined *)0x796270;
      strncpy(local_414,_Source,_Count);
      puVar5 = (undefined1 *)FUN_004fbaf0();
      if (puVar5 != (undefined1 *)0x0) {
        *puVar5 = 0;
      }
      pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_007a4220();
      uStack_510 = 0x7962be;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &uStack_508,pbVar4);
      local_8._0_1_ = 5;
      iVar6 = FUN_007a4220();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &iStack_520,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar6 + 0x3c));
      local_8._0_1_ = 6;
      FUN_00764790();
      local_8 = CONCAT31(local_8._1_3_,2);
      FUN_0076b7a0();
      FUN_004afeb0();
      uVar7 = FUN_004b0190();
      FUN_004afe80();
      FUN_00764790();
      FUN_0076ba00();
      FID_conflict_operator_();
      *(undefined4 *)(iVar3 + 0xf8) = uVar7;
      FUN_007a4220();
      FID_conflict_operator_();
      cVar1 = operator!=<>();
      if ((cVar1 == '\0') || (cVar1 = FUN_0041f890(), cVar1 != '\0')) {
        *(undefined1 *)(iVar3 + 0xf4) = 1;
      }
      else {
        piVar8 = (int *)FUN_00764790();
        uVar2 = (**(code **)(*piVar8 + 4))();
        *(undefined1 *)(iVar3 + 0xf4) = uVar2;
      }
      iVar3 = FUN_007a4220();
      uVar7 = *(undefined4 *)(iVar3 + 0x18);
      FUN_007a4220();
      pcStack_51c = "playerLimit";
      iStack_520 = 0x79647e;
      puStack_500 = (undefined *)uVar7;
      basic_string<>();
      local_8._0_1_ = 7;
      pcStack_51c = *(char **)(param_1 + 0x19c);
      iStack_520 = 0x7964b2;
      iStack_520 = FUN_0056f900();
      iStack_520 = iStack_520 + 0x120;
      local_8._0_1_ = 2;
      FUN_0079ba90();
      FUN_0073d020();
      local_8._0_1_ = 1;
      FUN_004180b0();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00426bc0();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

