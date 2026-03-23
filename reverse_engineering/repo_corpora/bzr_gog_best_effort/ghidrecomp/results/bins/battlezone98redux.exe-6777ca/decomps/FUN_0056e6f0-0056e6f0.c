
void FUN_0056e6f0(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  undefined4 local_68 [10];
  double local_40;
  double local_38;
  double local_30;
  float local_28;
  float local_24;
  float local_20;
  char local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar7 = FUN_0045c0c0(&DAT_008e8c74);
  FUN_004e0f70(uVar7);
  sprintf(local_1c,"team%da",DAT_00917f50);
  iVar1 = FUN_00460fc0(local_1c);
  local_28 = **(float **)(iVar1 + 8);
  local_24 = 0.0;
  local_20 = (*(float **)(iVar1 + 8))[1];
  puVar5 = &DAT_008fe1e0;
  puVar6 = local_68;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  local_40 = (double)local_28;
  local_38 = (double)local_24;
  local_30 = (double)local_20;
  piVar2 = (int *)FUN_004e1190(local_68,DAT_00917f50,1,0xffffffff,0);
  (**(code **)(*piVar2 + 0xc))();
  (**(code **)(piVar2[6] + 8))(DAT_00917f50);
  FUN_004b8460();
  if ((piVar2[0x3b] == 0) && (iVar1 = (**(code **)piVar2[6])(), 0 < *(int *)(iVar1 + 0x50))) {
    piVar3 = (int *)FUN_00417c70();
    if (piVar2 == piVar3) {
      piVar2[0x3b] = *(int *)(iVar1 + 0xd4);
    }
    else {
      piVar2[0x3b] = *(int *)(iVar1 + 0xd0);
    }
  }
  do {
    iVar1 = FUN_0061a080();
  } while (iVar1 != 0);
  FUN_006217a0();
  uVar4 = (**(code **)(piVar2[6] + 0x2c))(1);
  FUN_0061d120(uVar4);
  FUN_0083e885();
  return;
}

