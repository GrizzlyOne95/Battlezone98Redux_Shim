
void FUN_0056c7c0(void)

{
  allocator<char> *this;
  float *pfVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined4 local_54 [10];
  double local_2c;
  double local_24;
  double local_1c;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar8 = FUN_0045c0c0(&DAT_008e8c74);
  FUN_004e0f70(uVar8);
  FUN_00570470(&local_14);
  this = (allocator<char> *)FUN_005d9240(DAT_00917f50);
  if (this != (allocator<char> *)0x0) {
    pfVar1 = (float *)std::allocator<char>::allocator<char>(this);
    local_14 = *pfVar1;
    local_10 = pfVar1[1];
    local_c = pfVar1[2];
  }
  puVar6 = &DAT_008fe1e0;
  puVar7 = local_54;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  local_2c = (double)local_14;
  local_24 = (double)local_10;
  local_1c = (double)local_c;
  piVar2 = (int *)FUN_004e1190(local_54,DAT_00917f50,0,0xffffffff,0);
  (**(code **)(*piVar2 + 0xc))();
  (**(code **)(piVar2[6] + 8))(DAT_00917f50);
  FUN_004b8460();
  if ((piVar2[0x3b] == 0) && (iVar5 = (**(code **)piVar2[6])(), 0 < *(int *)(iVar5 + 0x50))) {
    piVar3 = (int *)FUN_00417c70();
    if (piVar2 == piVar3) {
      piVar2[0x3b] = *(int *)(iVar5 + 0xd4);
    }
    else {
      piVar2[0x3b] = *(int *)(iVar5 + 0xd0);
    }
  }
  do {
    iVar5 = FUN_0061a080();
  } while (iVar5 != 0);
  FUN_006217a0();
  uVar4 = (**(code **)(piVar2[6] + 0x2c))(1);
  FUN_0061d120(uVar4);
  FUN_0083e885();
  return;
}

