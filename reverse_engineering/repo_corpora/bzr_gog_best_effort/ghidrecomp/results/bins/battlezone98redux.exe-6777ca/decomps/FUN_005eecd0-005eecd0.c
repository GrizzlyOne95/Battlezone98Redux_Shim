
void __fastcall FUN_005eecd0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  float10 fVar7;
  undefined1 local_90 [12];
  undefined1 local_84 [12];
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  undefined8 local_68;
  float local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_5c = *(int *)(param_1 + 0x18) + -1;
  local_54 = param_1;
  switch(local_5c) {
  case 0:
    (**(code **)(**(int **)(param_1 + 0x20) + 0x88))(0);
    puVar2 = (undefined4 *)FUN_00462490();
    local_68 = FUN_0045c460(*puVar2,puVar2[1],puVar2[2]);
    (**(code **)(**(int **)(local_54 + 0x20) + 0x8c))(local_68);
    break;
  case 1:
  case 2:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(local_54 + 0x34) + 0x1c))();
    }
    else {
      *(undefined4 *)(local_54 + 0x1c) = 1;
    }
    break;
  case 3:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(local_54 + 0x34) + 0x1c))();
    }
    else {
      *(undefined4 *)(local_54 + 0x1c) = 1;
    }
    break;
  case 4:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(local_54 + 0x34) + 0x1c))();
    }
    else {
      (**(code **)(**(int **)(local_54 + 0x20) + 100))();
      *(undefined4 *)(local_54 + 0x48) = 0;
      puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_54 + 0x20) + 0x18) + 0xc))();
      local_38 = *puVar2;
      local_34 = puVar2[1];
      local_30 = puVar2[2];
      puVar2 = (undefined4 *)FUN_00462490();
      local_50 = *puVar2;
      local_4c = puVar2[1];
      local_48 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00439d00(local_90,local_38,local_34,local_30,0xc1700000,local_50,local_4c,
                            local_48);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      *(undefined4 *)(local_54 + 0x24) = local_20;
      *(undefined4 *)(local_54 + 0x28) = local_1c;
      *(undefined4 *)(local_54 + 0x2c) = local_18;
      *(undefined4 *)(local_54 + 0x1c) = 2;
    }
    break;
  case 5:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(local_54 + 0x34) + 0x1c))();
    }
    else {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_54 + 0x20) + 0x18) + 0xc))();
      local_44 = *puVar2;
      local_40 = puVar2[1];
      local_3c = puVar2[2];
      puVar2 = (undefined4 *)FUN_00462490();
      local_2c = *puVar2;
      local_28 = puVar2[1];
      local_24 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00439d00(local_84,local_44,local_40,local_3c,*(undefined4 *)(local_54 + 0x38),
                            local_2c,local_28,local_24);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      *(undefined4 *)(local_54 + 0x24) = local_14;
      *(undefined4 *)(local_54 + 0x28) = local_10;
      *(undefined4 *)(local_54 + 0x2c) = local_c;
      FUN_005f91e0(*(undefined4 *)(local_54 + 0x20),5,0);
      *(undefined4 *)(local_54 + 0x1c) = 5;
    }
    break;
  case 6:
    FUN_005ef640();
    break;
  case 7:
    if ((*(int *)(param_1 + 0x34) == 0) ||
       (cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x18))(), cVar1 != '\0')) {
      local_58 = FUN_00473940();
      if (local_58 != 0) {
        iVar3 = FUN_00462400();
        fVar7 = (float10)FUN_00462470(*(undefined4 *)(iVar3 + 0xc));
        fVar7 = (float10)FUN_0044fb20((float)fVar7);
        local_74 = (float)fVar7;
        iVar3 = FUN_00462400();
        fVar7 = (float10)FUN_00462470(*(undefined4 *)(iVar3 + 0xc));
        fVar7 = (float10)FUN_0044fb20((float)fVar7);
        local_6c = (float)fVar7;
        fVar7 = (float10)FUN_0044fb20(local_74 + local_6c + 10.0,0x42200000);
        local_60 = (float)fVar7;
        pfVar4 = (float *)(**(code **)(*(int *)(local_58 + 0x18) + 0xc))();
        pfVar5 = (float *)(**(code **)(*(int *)(*(int *)(local_54 + 0x20) + 0x18) + 0xc))();
        fVar7 = (float10)FUN_00453f80(*pfVar4 - *pfVar5);
        local_70 = (float)fVar7;
        if (local_70 < local_60) {
          iVar3 = (**(code **)(*(int *)(local_58 + 0x18) + 0xc))();
          iVar6 = (**(code **)(*(int *)(*(int *)(local_54 + 0x20) + 0x18) + 0xc))();
          fVar7 = (float10)FUN_00453f80(*(float *)(iVar3 + 8) - *(float *)(iVar6 + 8));
          local_78 = (float)fVar7;
          if (local_78 < local_60) {
            (**(code **)(*(int *)(*(int *)(local_54 + 0x20) + 0x18) + 0x24))();
          }
        }
      }
      if (*(int *)(*(int *)(local_54 + 0x20) + 0xac) == 0x12) {
        FUN_004dbc00();
      }
      *(undefined4 *)(local_54 + 0x1c) = 1;
    }
    else {
      (**(code **)(**(int **)(local_54 + 0x34) + 0x1c))();
    }
    break;
  case 8:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(local_54 + 0x34) + 0x1c))();
    }
    else {
      *(undefined4 *)(local_54 + 0x1c) = 1;
    }
  }
  FUN_0083e885();
  return;
}

