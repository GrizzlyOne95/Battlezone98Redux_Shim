
void __thiscall FUN_006b8f70(int param_1,char *param_2,uint param_3)

{
  char cVar1;
  bool bVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *this;
  char *pcVar8;
  undefined1 *puVar9;
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *p_Var10;
  basic_istream<char,struct_std::char_traits<char>_> local_330 [168];
  undefined1 local_288 [4];
  undefined1 local_284 [4];
  undefined1 local_280 [4];
  undefined1 local_27c [4];
  undefined1 local_278 [4];
  undefined1 local_274 [4];
  undefined1 local_270 [4];
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  uint local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  basic_istream<char,struct_std::char_traits<char>_> *local_238;
  uint local_234;
  undefined4 local_230;
  undefined4 local_22c;
  int local_228;
  undefined1 local_224 [88];
  undefined1 local_1cc [88];
  undefined1 local_174 [232];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851088;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_228 = param_1;
  if (*(int *)(param_1 + 0x70) != 3) {
    if (*(int *)(param_1 + 0x70) == 2) {
      FUN_006b9e10(param_2,param_3);
    }
    else {
      pcVar8 = param_2;
      uVar7 = param_3;
      pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00421ec0(param_2,param_3,local_14);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (pbVar3,pcVar8,uVar7);
      puVar4 = &local_230;
      FUN_00421ec0(puVar4);
      FID_conflict_begin(puVar4);
      local_22c = local_230;
      while( true ) {
        pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_00421ec0(local_27c,&DAT_00873200,&DAT_00873202);
        puVar4 = (undefined4 *)
                 std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 end(pbVar3);
        puVar4 = (undefined4 *)FUN_006da060(local_270,local_230,*puVar4);
        local_22c = *puVar4;
        iVar5 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_22c,
                          (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_230);
        *(int *)(local_228 + 0x20) = iVar5 + 3 + *(int *)(local_228 + 0x20);
        if (16000 < *(uint *)(local_228 + 0x20)) {
          basic_string<>("Maximum header size exceeded.");
          local_8 = 0;
          local_26c = basic_string<>();
          local_8._0_1_ = 1;
          local_24c = local_26c;
          local_264 = basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,2);
          local_258 = local_264;
          FUN_006b7140(local_8c,0x1af,local_264,local_26c);
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(local_174,(ThrowInfo *)&DAT_008d838c);
        }
        pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_00421ec0(local_284);
        uVar6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                end(pbVar3);
        cVar1 = FID_conflict_operator__(uVar6);
        if (cVar1 != '\0') {
          puVar9 = local_278;
          FUN_00421ec0(puVar9);
          puVar4 = (undefined4 *)FID_conflict_begin(puVar9);
          FUN_006da1d0(local_288,local_230,local_22c,*puVar4);
          uVar7 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                  operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                             *)&local_22c,
                            (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                             *)&local_230);
          pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   FUN_00421ec0();
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                    (pbVar3,uVar7);
          *(uint *)(local_228 + 0x60) = *(int *)(local_228 + 0x60) + param_3;
          FUN_00421ec0();
          iVar5 = FUN_004170c0();
          *(int *)(local_228 + 0x20) = *(int *)(local_228 + 0x20) - iVar5;
          goto LAB_006b95a4;
        }
        iVar5 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_22c,
                          (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_230);
        if (iVar5 == 0) break;
        if (*(int *)(local_228 + 0x70) == 0) {
          FUN_006b99a0(local_230,local_22c);
          *(undefined4 *)(local_228 + 0x70) = 1;
        }
        else {
          FUN_006b7d60(local_230,local_22c);
        }
        puVar4 = (undefined4 *)FID_conflict_operator_(local_274,2);
        local_230 = *puVar4;
      }
      if (*(int *)(local_228 + 0x70) == 0) {
        basic_string<>("Incomplete Request");
        local_8 = 3;
        local_250 = basic_string<>();
        local_8._0_1_ = 4;
        local_248 = local_250;
        local_268 = basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,5);
        local_260 = local_268;
        FUN_006b7140(local_44,400,local_268,local_250);
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(local_224,(ThrowInfo *)&DAT_008d838c);
      }
      basic_string<>("Content-Length");
      local_8 = 6;
      pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_006b7490(local_5c);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
      local_8._0_1_ = 8;
      ~basic_string<>();
      cVar1 = FUN_0041f890();
      if (cVar1 == '\0') {
        FUN_006ca8e0(local_2c,1,1);
        local_8._0_1_ = 9;
        local_238 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                              (local_330,(uint *)(local_228 + 0x60));
        bVar2 = std::ios_base::fail((ios_base *)(local_238 + *(int *)(*(int *)local_238 + 4)));
        if (bVar2) {
          basic_string<>("Unable to parse Content-Length header");
          local_8._0_1_ = 10;
          local_240 = basic_string<>();
          local_8._0_1_ = 0xb;
          local_23c = local_240;
          local_254 = basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,0xc);
          local_244 = local_254;
          FUN_006b7140(local_74,400,local_254,local_23c);
                    /* WARNING: Subroutine does not return */
          _CxxThrowException(local_1cc,(ThrowInfo *)&DAT_008d838c);
        }
        local_8._0_1_ = 8;
        FUN_006b95c0();
      }
      else {
        *(undefined4 *)(local_228 + 0x60) = 0;
      }
      *(undefined4 *)(local_228 + 0x70) = 2;
      p_Var10 = (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *
                )&local_22c;
      pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00421ec0(local_280);
      this = (_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                       (pbVar3);
      iVar5 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
              operator-(this,p_Var10);
      local_234 = (param_3 - iVar5) + 2;
      if (local_234 < param_3) {
        iVar5 = FUN_006b9e10(param_2 + local_234,param_3 - local_234);
        local_234 = iVar5 + local_234;
      }
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_228 + 100));
      local_25c = local_234;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
LAB_006b95a4:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

