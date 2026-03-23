
void __thiscall
FUN_007cd720(undefined4 param_1,int param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_108 [176];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined4 local_50;
  undefined4 local_4c;
  float local_48;
  float local_44;
  int *local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086269b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_50 = param_1;
  local_14 = uVar2;
  while( true ) {
    local_44 = (float)param_2;
    uVar3 = FUN_0041f870(uVar2);
    fVar6 = (float10)FUN_00689ce0(DAT_0091552c,uVar3);
    local_48 = (float)fVar6;
    if (local_48 < local_44) break;
    FUN_004203f0(param_3,3,1);
    local_8 = 0;
    basic_string<>();
    local_8._0_1_ = 1;
    vector<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    while( true ) {
      local_34 = (int *)FUN_004272a0(local_108,local_2c,10);
      bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_34 + *(int *)(*local_34 + 4)));
      if (!bVar1) break;
      FUN_006cae50(local_2c);
    }
    puVar4 = (undefined4 *)FID_conflict_begin(local_58);
    local_4c = *puVar4;
    FUN_007cebc0(local_54,local_4c);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_3,"");
    local_30 = 0;
    while( true ) {
      iVar5 = FUN_0048a830();
      if (local_30 == iVar5) break;
      uVar3 = FUN_006cf480(local_30);
      FUN_00449810(uVar3);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (param_3,"\n");
      local_30 = local_30 + 1;
    }
    local_8._0_1_ = 1;
    FUN_0048a040();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

