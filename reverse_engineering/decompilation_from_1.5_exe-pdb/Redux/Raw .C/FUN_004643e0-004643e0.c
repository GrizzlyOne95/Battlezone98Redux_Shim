
void FUN_004643e0(int param_1,int param_2)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_6c [44];
  undefined4 *local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar2 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_14 = *pfVar2;
  local_10 = pfVar2[1];
  local_c = pfVar2[2];
  local_34 = 2500.0;
  local_30 = 0;
  local_3c = 0x42480000;
  FUN_005b28e0((double)local_14,(double)local_c,0x4049000000000000,local_6c);
  while (cVar1 = FUN_00462710(&local_40), cVar1 != '\0') {
    local_24 = FUN_00462630(*local_40);
    if ((((local_24 != 0) && (param_1 != local_24)) && (param_2 != local_24)) &&
       (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) {
      iVar3 = (*(code *)**(undefined4 **)(local_24 + 0x18))();
      local_2c = *(int *)(iVar3 + 0x14);
      if (((local_2c != 0x54554700) ||
          (iVar3 = (*(code *)**(undefined4 **)(param_1 + 0x18))(),
          *(int *)(iVar3 + 0x14) != 0x52435943)) && (local_2c != 0x4745495a)) {
        iVar3 = (*(code *)**(undefined4 **)(local_24 + 0x18))();
        local_28 = *(int *)(iVar3 + 0x1c);
        if (((local_28 != 7) && ((local_28 != 3 || (local_2c == 0x544f5250)))) &&
           ((local_28 != 4 || (cVar1 = FUN_004db5b0(local_24), cVar1 == '\0')))) {
          puVar4 = (undefined4 *)(**(code **)(*(int *)(local_24 + 0x18) + 0xc))();
          local_20 = *puVar4;
          local_1c = puVar4[1];
          local_18 = puVar4[2];
          fVar5 = (float10)FUN_004620b0();
          local_38 = (float)fVar5;
          if (local_38 < local_34) {
            local_30 = local_24;
            local_34 = local_38;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

