
void __thiscall
FUN_007cdd50(int param_1,int param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 *puVar6;
  undefined1 local_1f8 [176];
  undefined1 local_148 [176];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  undefined1 local_90 [24];
  float local_78;
  int local_74;
  float local_70;
  undefined4 local_6c;
  int *local_5c;
  int *local_58;
  uint local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862759;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = param_1;
  (**(code **)(**(int **)(param_1 + 0x2950) + 0x24))(0,local_14);
  (**(code **)(**(int **)(local_48 + 0x2954) + 0x24))(0);
  if (*(int *)(local_48 + 0x2958) != 0) {
    (**(code **)(**(int **)(local_48 + 0x2950) + 0x24))(1);
  }
  FUN_004203f0(param_3,3,1);
  local_8 = 0;
  basic_string<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  while( true ) {
    local_58 = (int *)FUN_004272a0(local_1f8,local_44,10);
    bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_58 + *(int *)(*local_58 + 4)));
    if (!bVar1) break;
    FUN_0076f700(local_44);
  }
  local_74 = FUN_007cce90();
  local_54 = 0;
  while ((local_54 < (uint)(*(int *)(local_48 + 0x2958) * local_74) &&
         (iVar2 = FUN_004170c0(), iVar2 != 0))) {
    FUN_007ceb00();
    local_54 = local_54 + 1;
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (param_3,"");
  local_50 = 0;
  while (iVar2 = FUN_004170c0(), local_50 != iVar2) {
    uVar3 = FUN_007cea60(local_50);
    FUN_00449810(uVar3);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_3,"\n");
    local_50 = local_50 + 1;
  }
  while( true ) {
    local_78 = (float)param_2;
    uVar3 = FUN_0041f870();
    fVar5 = (float10)FUN_00689ce0(DAT_0091552c,uVar3);
    local_70 = (float)fVar5;
    if (local_70 < local_78) break;
    (**(code **)(**(int **)(local_48 + 0x2954) + 0x24))(1);
    FUN_004203f0(param_3,3,1);
    local_8._0_1_ = 3;
    basic_string<>();
    local_8._0_1_ = 4;
    vector<>();
    local_8 = CONCAT31(local_8._1_3_,5);
    while( true ) {
      local_5c = (int *)FUN_004272a0(local_148,local_2c,10);
      bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_5c + *(int *)(*local_5c + 4)));
      if (!bVar1) break;
      FUN_006cae50(local_2c);
    }
    uVar3 = 1;
    puVar6 = local_94;
    FID_conflict_end(local_90);
    puVar4 = (undefined4 *)FID_conflict_operator_(puVar6,uVar3);
    local_6c = *puVar4;
    FUN_007cebc0(local_98,local_6c);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_3,"");
    local_4c = 0;
    while (iVar2 = FUN_0048a830(), local_4c != iVar2) {
      uVar3 = FUN_006cf480(local_4c);
      FUN_00449810(uVar3);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (param_3,"\n");
      local_4c = local_4c + 1;
    }
    local_8._0_1_ = 4;
    FUN_0048a040();
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_00417f10();
  }
  local_8._0_1_ = 1;
  ~vector<>();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

