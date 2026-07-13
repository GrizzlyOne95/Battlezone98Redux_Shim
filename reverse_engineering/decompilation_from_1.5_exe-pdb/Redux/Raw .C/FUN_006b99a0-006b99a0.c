
void FUN_006b99a0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  basic_istream<char,struct_std::char_traits<char>_> local_350 [168];
  undefined1 local_2a8 [4];
  undefined1 local_2a4 [4];
  undefined1 local_2a0 [4];
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  int local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  basic_istream<char,struct_std::char_traits<char>_> *local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined1 local_23e;
  undefined1 local_23d;
  undefined1 local_23c [88];
  undefined1 local_1e4 [88];
  undefined1 local_18c [304];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851173;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_248 = param_1;
  local_23d = 0x20;
  FUN_006da220(&local_244,param_1,param_2,&local_23d,local_14);
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 != '\0') {
    basic_string<>("Invalid response line");
    local_8 = 0;
    local_290 = basic_string<>();
    local_8._0_1_ = 1;
    local_288 = local_290;
    local_278 = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    local_270 = local_278;
    FUN_006b7140(local_2c,400,local_278,local_288);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_23c,(ThrowInfo *)&DAT_008d838c);
  }
  local_298 = FUN_006da0a0(local_248,local_244);
  local_8 = 3;
  local_258 = local_298;
  FUN_006b7470(local_298);
  local_8 = 0xffffffff;
  ~basic_string<>();
  puVar3 = (undefined4 *)FID_conflict_operator_(local_2a0,1);
  local_248 = *puVar3;
  local_23e = 0x20;
  puVar3 = (undefined4 *)FUN_006da220(local_2a4,local_248,param_2,&local_23e);
  local_244 = *puVar3;
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 != '\0') {
    basic_string<>("Invalid request line");
    local_8 = 4;
    local_26c = basic_string<>();
    local_8._0_1_ = 5;
    local_25c = local_26c;
    local_274 = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,6);
    local_264 = local_274;
    FUN_006b7140(local_5c,400,local_274,local_26c);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_1e4,(ThrowInfo *)&DAT_008d838c);
  }
  local_284 = FUN_006da0a0(local_248,local_244);
  local_8 = 7;
  local_27c = local_284;
  FUN_006ca8e0(local_284,1,1);
  local_8._0_1_ = 9;
  ~basic_string<>();
  local_24c = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                        (local_350,&local_268);
  bVar2 = std::ios_base::fail((ios_base *)(local_24c + *(int *)(*(int *)local_24c + 4)));
  if (bVar2) {
    basic_string<>("Unable to parse response code");
    local_8._0_1_ = 10;
    local_29c = basic_string<>();
    local_8._0_1_ = 0xb;
    local_28c = local_29c;
    local_294 = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,0xc);
    local_254 = local_294;
    FUN_006b7140(local_44,400,local_294,local_29c);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_18c,(ThrowInfo *)&DAT_008d838c);
  }
  uVar4 = param_2;
  puVar3 = (undefined4 *)FID_conflict_operator_(local_2a8,1);
  local_280 = FUN_006da0a0(*puVar3,uVar4);
  local_8._0_1_ = 0xd;
  local_260 = local_280;
  FUN_006b9970(local_268,local_280);
  local_8 = CONCAT31(local_8._1_3_,9);
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_006b95c0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

