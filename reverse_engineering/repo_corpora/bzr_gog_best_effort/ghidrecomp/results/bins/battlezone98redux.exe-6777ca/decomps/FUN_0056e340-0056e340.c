
void __fastcall FUN_0056e340(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined4 local_98;
  int local_88;
  undefined4 local_74 [10];
  double local_4c;
  double local_44;
  double local_3c;
  float local_34;
  float local_30;
  float local_2c;
  char local_28 [20];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b47e;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (DAT_00917f48 != 0) {
    iVar1 = FUN_007659f0(local_14);
    if (iVar1 != 0) {
      if (param_1 == 0) {
        local_88 = 0;
      }
      else {
        local_88 = param_1 + 0x54;
      }
      FUN_00758af0(0x23,local_88);
    }
    pvVar2 = operator_new(0x410);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_98 = 0;
    }
    else {
      local_98 = FUN_0056d780(param_1);
    }
    local_8 = 0xffffffff;
    DAT_00917f38 = local_98;
    FUN_00571c60(1);
    iVar1 = FUN_00572a70();
    if (iVar1 != 0) {
      uVar8 = FUN_0045c0c0(&DAT_008e8c74);
      FUN_004e0f70(uVar8);
      uVar3 = FUN_0056b910();
      FUN_00577200(uVar3);
      FUN_00576370(0);
      FUN_007d6a70("Creating player that is on team %d\n",DAT_00917f50);
      sprintf(local_28,"team%da",DAT_00917f50);
      iVar1 = FUN_00460fc0(local_28);
      local_34 = **(float **)(iVar1 + 8);
      local_30 = 0.0;
      local_2c = (*(float **)(iVar1 + 8))[1];
      puVar6 = &DAT_008fe1e0;
      puVar7 = local_74;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      local_4c = (double)local_34;
      local_44 = (double)local_30;
      local_3c = (double)local_2c;
      iVar1 = FUN_004e1190(local_74,DAT_00917f50,1,0xffffffff,0);
      FUN_004b8460();
      pvVar2 = operator_new(200);
      local_8 = 1;
      if (pvVar2 != (void *)0x0) {
        FUN_00608d40(param_1,iVar1);
      }
      local_8 = 0xffffffff;
      if ((*(int *)(iVar1 + 0xec) == 0) &&
         (iVar4 = (*(code *)**(undefined4 **)(iVar1 + 0x18))(), 0 < *(int *)(iVar4 + 0x50))) {
        iVar5 = FUN_00417c70();
        if (iVar1 == iVar5) {
          *(undefined4 *)(iVar1 + 0xec) = *(undefined4 *)(iVar4 + 0xd4);
        }
        else {
          *(undefined4 *)(iVar1 + 0xec) = *(undefined4 *)(iVar4 + 0xd0);
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

