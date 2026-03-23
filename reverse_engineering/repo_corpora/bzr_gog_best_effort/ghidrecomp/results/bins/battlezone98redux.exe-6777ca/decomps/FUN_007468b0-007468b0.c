
void __thiscall FUN_007468b0(int *param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  int iVar6;
  code *pcVar7;
  ushort uVar8;
  undefined1 *puVar9;
  _func_ios_base_ptr_ios_base_ptr *p_Var10;
  ushort uVar11;
  undefined1 *puVar12;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *p_Var13;
  basic_ostream<char,struct_std::char_traits<char>_> local_40c [176];
  basic_ostream<char,struct_std::char_traits<char>_> local_35c [176];
  basic_ostream<char,struct_std::char_traits<char>_> local_2ac [176];
  undefined1 auStack_1fc [160];
  undefined1 local_15c [16];
  undefined1 local_14c [16];
  undefined1 local_13c [16];
  undefined1 local_12c [16];
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined1 *local_fc;
  char *local_f8;
  char local_f1;
  int *local_f0;
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b7e3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_f0 = param_1;
  if (((0 < param_3) && (param_3 < 0x10)) && (cVar1 = FUN_00742cf0(local_14), cVar1 != '\0')) {
    if (*(short *)(param_2 + 0x28) == 0) {
      basic_string<>("nextmid");
      local_8 = 0;
      local_f8 = (char *)(**(code **)(*local_f0 + 0x2c))(local_f0 + 10,local_2c);
      local_8 = 0xffffffff;
      ~basic_string<>();
      if ((local_f8 == (char *)0x0) || (*local_f8 == '\0')) {
        *(undefined2 *)(param_2 + 0x28) = 1;
      }
      else {
        iVar2 = atoi(local_f8);
        *(short *)(param_2 + 0x28) = (short)iVar2;
      }
      if (*(short *)(param_2 + 0x28) == 0) goto LAB_00746e63;
      if ((uint)*(ushort *)(param_2 + 0x28) < (uint)local_f0[0xe]) {
        *(short *)(param_2 + 0x28) = (short)local_f0[0xe];
      }
      FUN_00574400(3,1);
      local_8 = 1;
      local_f0[0xe] = *(ushort *)(param_2 + 0x28) + 1;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_35c,local_f0[0xe]);
      *(int *)(param_2 + 0x80) = param_3;
      iVar2 = param_2 + 0x28;
      iVar6 = param_2 + 8;
      FUN_007659f0(iVar6,iVar2);
      FUN_0073bb60(iVar6,iVar2);
      local_114 = GetPolicy(local_ec);
      local_8._0_1_ = 2;
      local_104 = local_114;
      uVar3 = FUN_0041f870();
      basic_string<>(uVar3);
      local_8._0_1_ = 3;
      basic_string<>("nextmid");
      local_8._0_1_ = 4;
      puVar9 = local_5c;
      puVar12 = local_44;
      uVar3 = FUN_0073bcf0(local_13c);
      (**(code **)(*local_f0 + 0x20))(uVar3,puVar12,puVar9);
      local_8._0_1_ = 3;
      ~basic_string<>();
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,1);
      ~basic_string<>();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    p_Var13 = (_func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
               *)local_14c;
    uVar3 = (**(code **)(*local_f0 + 0x38))();
    cVar1 = FUN_0056f780(uVar3);
    if (cVar1 == '\0') {
      FUN_00574400(3,1);
      local_8 = 0xb;
      if (&stack0x00000000 == (undefined1 *)0x20c) {
        local_fc = (undefined1 *)0x0;
      }
      else {
        local_fc = auStack_1fc;
      }
      uVar11 = *(ushort *)(param_2 + 0x28);
      p_Var10 = (_func_ios_base_ptr_ios_base_ptr *)PTR_DAT_008eda34;
      uVar3 = FUN_004bc590(local_fc,PTR_DAT_008eda34,&DAT_0089a2fc,PTR_DAT_008eda34,param_2 + 8,
                           PTR_DAT_008eda34);
      uVar3 = FUN_004bc590(uVar3);
      uVar3 = FUN_004bc590(uVar3);
      uVar8 = 0x6d38;
      uVar3 = FUN_0073ba70(uVar3);
      pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
      pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,param_3);
      pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar5);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,uVar8);
      local_10c = GetPolicy(local_bc);
      local_8._0_1_ = 0xc;
      local_100 = local_10c;
      local_f1 = FUN_007458a0(local_10c);
      local_8 = CONCAT31(local_8._1_3_,0xb);
      ~basic_string<>();
      if (local_f1 != '\0') {
        FUN_007476a0();
      }
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else {
      FUN_00574400(3,1);
      local_8 = 5;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                (local_40c,*(ushort *)(param_2 + 0x28));
      basic_string<>("miniid");
      local_8._0_1_ = 6;
      uVar3 = GetPolicy(local_d4);
      local_8._0_1_ = 7;
      p_Var10 = (_func_ios_base_ptr_ios_base_ptr *)local_8c;
      local_11c = uVar3;
      local_108 = uVar3;
      uVar4 = FUN_0073bcf0(local_12c);
      uVar11 = (ushort)uVar3;
      (**(code **)(*local_f0 + 0x1c))(uVar4);
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      ~basic_string<>();
      FUN_00574400(3,1);
      local_8._0_1_ = 8;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_2ac,param_3);
      basic_string<>(&DAT_008757b0);
      local_8._0_1_ = 9;
      uVar3 = GetPolicy(local_a4);
      local_8._0_1_ = 10;
      puVar9 = local_74;
      local_118 = uVar3;
      local_110 = uVar3;
      uVar4 = FUN_0073bcf0(local_15c);
      (**(code **)(*local_f0 + 0x1c))(uVar4,puVar9,uVar3);
      local_8._0_1_ = 9;
      ~basic_string<>();
      local_8._0_1_ = 8;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,5);
      FUN_00417f10();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    iVar2 = *(int *)(param_2 + 0x80);
    pcVar7 = FUN_0056f740;
    FUN_0081e820("Assigned Player ",param_2 + 0x2c," team ",FUN_0056f740,iVar2,", player id ",
                 FUN_0056f740,*(undefined2 *)(param_2 + 0x28),FUN_004bc8c0);
    uVar3 = FUN_0081e660();
    uVar3 = FUN_004bc590(uVar3);
    uVar3 = FUN_00574730(uVar3);
    pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
    pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,pcVar7);
    pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,iVar2);
    pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar5);
    pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,p_Var10);
    pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,uVar11);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,p_Var13);
  }
LAB_00746e63:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

