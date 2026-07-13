
void FUN_0056f180(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  undefined8 uVar8;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  undefined4 uVar9;
  undefined4 local_54 [10];
  double local_2c;
  double local_24;
  double local_1c;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_008e8d04 < 1) {
    DAT_009180d7 = 1;
    FUN_005d48b0();
    uVar9 = extraout_var;
  }
  else {
    uVar8 = FUN_0045c0c0(&DAT_008e8c74);
    uVar9 = extraout_var_00;
    FUN_004e0f70(uVar8);
    FUN_00570470(&local_14);
    puVar4 = &DAT_008fe1e0;
    puVar5 = local_54;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    fVar6 = (float10)FUN_004a7890();
    fVar7 = (float10)FUN_004a7890();
    local_2c = (double)(((float)fVar6 - (float)fVar7) * 20.0 + local_14);
    local_24 = (double)(local_10 + 50.0);
    fVar6 = (float10)FUN_004a7890();
    fVar7 = (float10)FUN_004a7890();
    local_1c = (double)(((float)fVar6 - (float)fVar7) * 20.0 + local_c);
    piVar1 = (int *)FUN_004e1190(local_54,DAT_00917f50,0,0xffffffff,0);
    (**(code **)(*piVar1 + 0xc))();
    (**(code **)(piVar1[6] + 8))(DAT_00917f50);
    FUN_004b8460();
    do {
      iVar3 = FUN_0061a080();
    } while (iVar3 != 0);
    FUN_006217a0();
    uVar2 = (**(code **)(piVar1[6] + 0x2c))(1);
    FUN_0061d120(uVar2);
  }
  FUN_0083e885(uVar9);
  return;
}

