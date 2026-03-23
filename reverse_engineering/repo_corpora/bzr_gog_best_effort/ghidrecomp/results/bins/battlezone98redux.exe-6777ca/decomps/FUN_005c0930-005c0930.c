
void FUN_005c0930(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_7c [12];
  float local_70;
  char *local_6c;
  int local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006004a0();
  sprintf(local_58," SAVAttackVehicleTask:");
  FUN_004b70f0();
  cVar1 = (**(code **)(**(int **)(local_68 + 0x10) + 0x68))();
  if (cVar1 == '\0') {
    local_6c = "false";
  }
  else {
    local_6c = "true";
  }
  sprintf(local_58," Deployed: %s");
  FUN_004b70f0();
  fVar4 = (float10)FUN_00822d80();
  local_70 = (float)fVar4;
  sprintf(local_58," TimeOut: (%f)");
  FUN_004b70f0();
  (**(code **)(*(int *)(*(int *)(local_68 + 0x10) + 0x18) + 0xc))();
  FUN_00462010();
  FUN_00417910();
  sprintf(local_58," GotoDist: (%f)");
  FUN_004b70f0();
  FUN_00417910();
  (**(code **)(*(int *)(*(int *)(local_68 + 0x10) + 0x18) + 0xc))();
  FUN_004b71f0();
  uVar2 = FUN_00462630();
  *(undefined4 *)(local_68 + 0x18) = uVar2;
  if (*(int *)(local_68 + 0x18) != 0) {
    FUN_00462490();
    puVar3 = (undefined4 *)
             (**(code **)(*(int *)(*(int *)(local_68 + 0x18) + 0x18) + 0xc))(0x41a00000);
    puVar3 = (undefined4 *)FUN_00439d00(local_7c,*puVar3,puVar3[1],puVar3[2]);
    local_64 = *puVar3;
    local_60 = puVar3[1];
    local_5c = puVar3[2];
    (**(code **)(*(int *)(*(int *)(local_68 + 0x18) + 0x18) + 0xc))();
    FUN_004b7150();
  }
  FUN_0083e885();
  return;
}

