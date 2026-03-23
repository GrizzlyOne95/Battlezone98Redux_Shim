
void FUN_0079bdf0(int *param_1,char param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  char in_stack_0000002c;
  char in_stack_00000030;
  undefined4 uStack_288;
  char *pcStack_284;
  char *pcVar7;
  int local_208;
  int local_204;
  int local_1d8;
  int local_1cc;
  uint local_1c0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_12c [24];
  char local_114 [128];
  char local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085f91b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  iVar2 = FUN_0056f900();
  if ((iVar2 != 0) && (iVar2 = FUN_007a4220(), iVar2 != 0)) {
    basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,1);
    iVar2 = *param_1;
    if (*param_1 == 0) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_12c,"OFF");
    }
    else if (param_2 == '\0') {
      sprintf(local_94,"%u");
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_12c,local_94);
    }
    else {
      pcStack_284 = (char *)0x79beec;
      sprintf(local_114,"%u:%02u");
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_12c,local_114);
    }
    for (local_1c0 = 0; uVar3 = FUN_0048a830(), local_1c0 < uVar3; local_1c0 = local_1c0 + 1) {
      FUN_006cf480();
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') {
        if (in_stack_0000002c != '\0') {
          if (in_stack_00000030 == '\0') {
            if (local_1c0 == 0) {
              FUN_0048a830();
            }
          }
          else {
            FUN_0048a830();
          }
        }
        FUN_006cf480();
        FID_conflict_operator_();
        FUN_00426b10();
        local_8._0_1_ = 2;
        FUN_00426a60();
        local_8._0_1_ = 3;
        FUN_00426af0();
        FUN_00417fd0();
        local_8._0_1_ = 4;
        FUN_0041f870();
        FUN_00426c30();
        local_8._0_1_ = 3;
        ~basic_string<>();
        FUN_0041f870();
        FUN_0041f870();
        pcStack_284 = "multi";
        uStack_288 = 0x79c0c1;
        FUN_00421f90();
        FUN_00417fd0();
        local_8._0_1_ = 5;
        FUN_0041f870();
        FUN_00426c90();
        local_8 = CONCAT31(local_8._1_3_,3);
        ~basic_string<>();
        cVar1 = FUN_00427270();
        if (cVar1 == '\0') {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                    ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )&uStack_288,local_12c);
          FUN_007c44a0();
        }
        else {
          uVar4 = FUN_0081cb40();
          basic_string<>(uVar4);
          FUN_007c44a0();
        }
        pcVar7 = "%d:%d";
        pcVar5 = (char *)FUN_0041f870();
        pcStack_284 = (char *)0x79c1a6;
        iVar6 = sscanf(pcVar5,pcVar7);
        if (iVar6 == 2) {
          *param_1 = local_1d8 * 0x3c + local_204;
        }
        else if (iVar6 == 1) {
          *param_1 = local_1d8;
        }
        else {
          *param_1 = 0;
        }
        if (iVar2 != *param_1) {
          FUN_0073d020();
        }
        local_8._0_1_ = 2;
        FUN_004180b0();
        local_8._0_1_ = 1;
        FUN_00426bc0();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        goto LAB_0079c450;
      }
    }
    FUN_006cf480();
    FID_conflict_operator_();
    FUN_00426b10();
    local_8._0_1_ = 6;
    FUN_00426a60();
    local_8._0_1_ = 7;
    FUN_00426af0();
    FUN_00417fd0();
    local_8._0_1_ = 8;
    FUN_0041f870();
    FUN_00426c30();
    local_8._0_1_ = 7;
    ~basic_string<>();
    FUN_0041f870();
    FUN_0041f870();
    pcStack_284 = "multi";
    uStack_288 = 0x79c317;
    FUN_00421f90();
    FUN_00417fd0();
    local_8._0_1_ = 9;
    FUN_0041f870();
    FUN_00426c90();
    local_8 = CONCAT31(local_8._1_3_,7);
    ~basic_string<>();
    pcVar7 = "%d:%d";
    pcVar5 = (char *)FUN_0041f870();
    pcStack_284 = (char *)0x79c38c;
    iVar6 = sscanf(pcVar5,pcVar7);
    if (iVar6 == 2) {
      *param_1 = local_1cc * 0x3c + local_208;
    }
    else if (iVar6 == 1) {
      *param_1 = local_1cc;
    }
    else {
      *param_1 = 0;
    }
    if (iVar2 != *param_1) {
      FUN_0073d020();
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &uStack_288,local_12c);
    FUN_007c44a0();
    local_8._0_1_ = 6;
    FUN_004180b0();
    local_8._0_1_ = 1;
    FUN_00426bc0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
LAB_0079c450:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

