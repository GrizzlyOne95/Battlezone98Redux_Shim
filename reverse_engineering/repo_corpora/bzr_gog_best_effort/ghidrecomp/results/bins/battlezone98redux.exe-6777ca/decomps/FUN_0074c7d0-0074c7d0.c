
void FUN_0074c7d0(undefined4 param_1,char param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined1 local_b4 [16];
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  undefined1 local_9c [4];
  int local_98;
  undefined1 local_94 [4];
  int *local_90;
  undefined1 local_7c [104];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bcdb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_0073e240(param_2,param_1,2);
  if (param_2 == '\0') {
    FUN_00765c90(param_3,uVar2);
  }
  else {
    iVar3 = get();
    if (*(int *)(iVar3 + 0xc3c) != 0) {
      FUN_00578c20(local_9c,param_1);
      uVar4 = param_1;
      get(param_1);
      FUN_0075ca90(uVar4);
      uVar4 = FID_conflict_begin(local_a4);
      cVar1 = FUN_00420f10(uVar4);
      if (cVar1 != '\0') {
        local_98 = FUN_00422150();
        local_98 = local_98 + 0x48;
        FUN_00420260(local_94);
        FID_conflict_begin(local_a0);
        while (cVar1 = FUN_00420f10(local_a0), cVar1 != '\0') {
          uVar4 = FUN_00423870();
          FUN_0072b380(uVar4);
          local_8 = 0;
          uVar4 = (**(code **)(*local_90 + 0x38))(local_b4);
          cVar1 = FUN_0073ba10(uVar4);
          if (cVar1 != '\0') {
            puVar5 = local_7c;
            uVar4 = param_1;
            get(param_1,puVar5);
            FUN_0075d090(uVar4,puVar5);
          }
          local_8 = 0xffffffff;
          FUN_006ff9c0();
          FUN_00428570();
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

