
void __thiscall FUN_006b8220(int param_1,char *param_2,uint param_3)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *this;
  char *pcVar7;
  undefined1 *puVar8;
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *p_Var9;
  undefined1 local_1c4 [4];
  undefined1 local_1c0 [4];
  undefined1 local_1bc [4];
  undefined1 local_1b8 [4];
  undefined1 local_1b4 [4];
  undefined1 local_1b0 [4];
  undefined1 local_1ac [4];
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  uint local_184;
  char local_17d;
  undefined4 local_17c;
  int local_178;
  undefined4 local_174;
  int local_170;
  undefined1 local_16c [88];
  undefined1 local_114 [184];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850eb8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_184 = 0;
  local_170 = param_1;
  if (*(char *)(param_1 + 0x80) == '\0') {
    if (*(int *)(param_1 + 0x3c) == 0) {
      pcVar7 = param_2;
      uVar6 = param_3;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00421ec0(param_2,param_3,local_14);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (pbVar2,pcVar7,uVar6);
      puVar3 = &local_17c;
      FUN_00421ec0(puVar3);
      FID_conflict_begin(puVar3);
      FUN_00422170();
      while( true ) {
        pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_00421ec0(local_1ac,&DAT_00873200,&DAT_00873202);
        puVar3 = (undefined4 *)
                 std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 end(pbVar2);
        puVar3 = (undefined4 *)FUN_006da060(local_1b4,local_17c,*puVar3);
        local_174 = *puVar3;
        iVar4 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_174,
                          (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_17c);
        *(int *)(local_170 + 0x20) = iVar4 + 3 + *(int *)(local_170 + 0x20);
        if (16000 < *(uint *)(local_170 + 0x20)) {
          basic_string<>("Maximum header size exceeded.");
          local_8 = 0;
          local_1a8 = basic_string<>();
          local_8._0_1_ = 1;
          local_1a4 = local_1a8;
          local_1a0 = basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,2);
          local_194 = local_1a0;
          FUN_006b7140(local_44,0x1af,local_1a0,local_1a8);
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(local_16c,(ThrowInfo *)&DAT_008d838c);
        }
        pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_00421ec0(local_1bc);
        uVar5 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                end(pbVar2);
        cVar1 = FID_conflict_operator__(uVar5);
        if (cVar1 != '\0') {
          puVar8 = local_1c4;
          FUN_00421ec0(puVar8);
          puVar3 = (undefined4 *)FID_conflict_begin(puVar8);
          FUN_006da1d0(local_1c0,local_17c,local_174,*puVar3);
          uVar6 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                  operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                             *)&local_174,
                            (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                             *)&local_17c);
          pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   FUN_00421ec0();
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                    (pbVar2,uVar6);
          FUN_00421ec0();
          iVar4 = FUN_004170c0();
          *(int *)(local_170 + 0x20) = *(int *)(local_170 + 0x20) - iVar4;
          goto LAB_006b87a7;
        }
        iVar4 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_174,
                          (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_17c);
        if (iVar4 == 0) break;
        cVar1 = FUN_0041f890();
        if (cVar1 == '\0') {
          FUN_006b7d60(local_17c,local_174);
        }
        else {
          FUN_006b8af0(local_17c,local_174);
        }
        puVar3 = (undefined4 *)FID_conflict_operator_(local_1b0,2);
        local_17c = *puVar3;
      }
      cVar1 = FUN_0041f890();
      if (cVar1 == '\0') {
        basic_string<>(&DAT_00897554);
        local_8 = 3;
        local_184 = local_184 | 1;
        FUN_006b7490(local_5c);
        cVar1 = FUN_0041f890();
        if (cVar1 != '\0') goto LAB_006b8581;
        local_188 = 0;
      }
      else {
LAB_006b8581:
        local_188 = 1;
      }
      local_17d = (char)local_188;
      local_8 = 0xffffffff;
      if ((local_184 & 1) != 0) {
        local_184 = local_184 & 0xfffffffe;
        ~basic_string<>();
      }
      if (local_17d != '\0') {
        basic_string<>("Incomplete Request");
        local_8 = 4;
        local_190 = basic_string<>();
        local_8._0_1_ = 5;
        local_18c = local_190;
        local_19c = basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,6);
        local_198 = local_19c;
        FUN_006b7140(local_2c,400,local_19c,local_190);
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(local_114,(ThrowInfo *)&DAT_008d838c);
      }
      p_Var9 = (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_174;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00421ec0(local_1b8);
      this = (_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                       (pbVar2);
      iVar4 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
              operator-(this,p_Var9);
      local_178 = (param_3 - iVar4) + 2;
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_170 + 0x48));
      cVar1 = FUN_006b78d0();
      if (cVar1 == '\0') {
        *(undefined1 *)(local_170 + 0x80) = 1;
      }
      else {
        iVar4 = FUN_006b7b30(param_2 + local_178,param_3 - local_178);
        local_178 = iVar4 + local_178;
        cVar1 = FUN_006b7420();
        if (cVar1 != '\0') {
          *(undefined1 *)(local_170 + 0x80) = 1;
        }
      }
    }
    else {
      local_178 = FUN_006b7b30(param_2,param_3);
      cVar1 = FUN_006b7420();
      if (cVar1 != '\0') {
        *(undefined1 *)(local_170 + 0x80) = 1;
      }
    }
  }
LAB_006b87a7:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

