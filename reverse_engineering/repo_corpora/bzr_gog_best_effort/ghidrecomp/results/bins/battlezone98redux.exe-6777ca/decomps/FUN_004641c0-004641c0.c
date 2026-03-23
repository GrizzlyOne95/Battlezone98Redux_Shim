
void FUN_004641c0(int param_1,float *param_2,int param_3)

{
  char cVar1;
  float *pfVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_78 [44];
  undefined1 local_4c [12];
  float local_40;
  undefined4 *local_3c;
  float local_38;
  int local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar2 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_2c = *pfVar2;
  local_28 = pfVar2[1];
  local_24 = pfVar2[2];
  local_34 = 0;
  fVar6 = (float10)FUN_00417910(*param_2);
  local_40 = (float)fVar6;
  FUN_005b28e0((double)local_2c,(double)local_24,(double)local_40,local_78);
  while (cVar1 = FUN_00462710(&local_3c), cVar1 != '\0') {
    local_30 = FUN_00462630(*local_3c);
    if (((local_30 != 0) && (local_30 != param_3)) && (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) {
      uVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
      cVar1 = FUN_004625f0(uVar3);
      if (cVar1 == '\0') {
        uVar3 = (**(code **)(*(int *)(local_30 + 0x18) + 0x30))();
        iVar4 = FUN_00417e20(uVar3);
        if (((iVar4 != 0) && (iVar4 = FUN_0045bdf0(), iVar4 == 0)) &&
           ((*(int *)(local_30 + 0xec) == 0 &&
            (iVar4 = (*(code *)**(undefined4 **)(local_30 + 0x18))(), *(int *)(iVar4 + 0x50) != 0)))
           ) {
          FUN_00462590(local_30);
          cVar1 = FUN_00464140();
          if (cVar1 != '\0') {
            puVar5 = (undefined4 *)
                     (**(code **)(*(int *)(local_30 + 0x18) + 0xc))(local_2c,local_28,local_24);
            puVar5 = (undefined4 *)FUN_004401a0(local_4c,*puVar5,puVar5[1]);
            local_20 = *puVar5;
            local_1c = puVar5[1];
            local_18 = puVar5[2];
            local_14 = local_20;
            local_10 = local_1c;
            local_c = local_18;
            fVar6 = (float10)FUN_00462070(&local_20);
            local_38 = (float)fVar6;
            if (local_38 < *param_2) {
              *param_2 = local_38;
              local_34 = local_30;
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

