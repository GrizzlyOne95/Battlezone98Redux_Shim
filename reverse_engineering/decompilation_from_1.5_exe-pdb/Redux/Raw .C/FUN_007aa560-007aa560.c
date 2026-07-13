
void __thiscall FUN_007aa560(int param_1,char param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  void *pvVar7;
  undefined1 *puVar8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 *local_e8;
  undefined1 local_d0 [24];
  undefined1 local_b8 [24];
  undefined1 local_a0 [24];
  undefined1 local_88 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_58 [24];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860962;
  local_10 = ExceptionList;
  uVar4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  bVar1 = false;
  local_14 = uVar4;
  if (param_2 == '\0') {
    puVar8 = local_d0;
    FUN_00764780(puVar8,uVar4);
    uVar5 = FUN_007664f0(puVar8);
    local_8 = 0;
    bVar1 = true;
    cVar3 = FUN_00427310(uVar5,param_1 + 4);
    if (cVar3 != '\0') {
      bVar2 = true;
      goto LAB_007aa614;
    }
  }
  bVar2 = false;
LAB_007aa614:
  local_8 = 0xffffffff;
  if (bVar1) {
    ~basic_string<>();
  }
  if (!bVar2) {
    puVar8 = local_a0;
    FUN_00764780(puVar8,uVar4);
    uVar5 = FUN_007664f0(puVar8);
    FUN_0045e0f0(uVar5);
    ~basic_string<>();
    puVar8 = local_b8;
    FUN_00764780(puVar8);
    FUN_007663a0(puVar8);
    local_8 = 1;
    uVar5 = FUN_0041f870();
    (**(code **)(**(int **)(param_1 + 0x20) + 0x3c))(uVar5);
    local_8 = 0xffffffff;
    ~basic_string<>();
    FUN_007a9ea0();
    puVar8 = local_88;
    FUN_00764780(puVar8);
    FUN_007666a0(puVar8);
    local_8 = 2;
    uVar5 = FUN_0041f870(3);
    (**(code **)(**(int **)(param_1 + 0x2c) + 0x3c))(uVar5);
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (DAT_00945588 != (undefined4 *)0x0) {
      if (DAT_00945588 != (undefined4 *)0x0) {
        (**(code **)*DAT_00945588)(1);
      }
      DAT_00945588 = (undefined4 *)0x0;
    }
    cVar3 = FUN_0041f890();
    if (cVar3 == '\0') {
      pbVar9 = local_70;
      FUN_00764780(pbVar9);
      FUN_007664f0(pbVar9);
      local_8 = 3;
      local_34[0x10] = 0;
      local_34[0x11] = '\0';
      local_34[0x12] = '\0';
      local_34[0x13] = '\0';
      local_34[0x14] = '\0';
      local_34[0x15] = '\0';
      local_34[0x16] = '\0';
      local_34[0x17] = '\0';
      local_34[0x18] = '\0';
      local_34[0x19] = '\0';
      local_34[0x1a] = '\0';
      local_34[0x1b] = '\0';
      local_34[0x1c] = '\0';
      local_34[0x1d] = '\0';
      local_34[0x1e] = '\0';
      local_34[0x1f] = 0;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
                (local_70,".odf");
      uVar5 = FUN_0041f870();
      FUN_00589430(uVar5);
      local_8._0_1_ = 4;
      uVar5 = FUN_0041f870();
      FUN_0047b6c0(0xd3dd9cec,0x794b13b,local_34 + 0x10,uVar5);
      uVar10 = 0;
      puVar8 = &DAT_0094554b;
      uVar5 = FUN_00446460("cloakAllowed",0x811c9dc5,&DAT_0094554b,0);
      FUN_00589920(0xc287c42b,uVar5,puVar8,uVar10);
      local_34[0] = '\0';
      local_34[1] = '\0';
      local_34[2] = '\0';
      local_34[3] = '\0';
      local_34[4] = '\0';
      local_34[5] = '\0';
      local_34[6] = '\0';
      local_34[7] = '\0';
      local_34[8] = '\0';
      local_34[9] = '\0';
      local_34[10] = '\0';
      local_34[0xb] = '\0';
      local_34[0xc] = '\0';
      local_34[0xd] = '\0';
      local_34[0xe] = '\0';
      local_34[0xf] = 0;
      sprintf(local_34,"%.8s",local_34 + 0x10);
      basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,5);
      FUN_0041f830();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
                (local_58,local_34);
      iVar6 = FUN_005871b0(&DAT_008752b0,0);
      if (iVar6 != -1) {
        uVar11 = 0xffffffff;
        uVar4 = FUN_00489f20(&DAT_008752b0,0xffffffff);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                  (local_58,uVar4,uVar11);
      }
      local_40 = 0x41200000;
      local_3c = 0x41200000;
      local_38 = 0x41200000;
      uVar5 = FUN_0041f870(0x41200000,0x41200000,0x41200000);
      FUN_0067d180(uVar5);
      DAT_0094558c = 0;
      DAT_00945590 = 0;
      DAT_00945594 = 0;
      pvVar7 = operator_new(0x14);
      local_8._0_1_ = 6;
      if (pvVar7 == (void *)0x0) {
        local_e8 = (undefined4 *)0x0;
      }
      else {
        local_e8 = (undefined4 *)FUN_006616a0(DAT_00920ec0);
      }
      local_8._0_1_ = 5;
      DAT_00945588 = local_e8;
      FUN_006618b0(DAT_00945594);
      local_8._0_1_ = 4;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,3);
      FUN_00589530();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    (**(code **)(param_1 + 0x28))();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

