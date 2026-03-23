
void FUN_00462d50(int param_1,int param_2,int param_3,float param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined4 local_44;
  int local_40;
  float local_3c;
  int local_38;
  int local_34;
  float local_30;
  float local_2c;
  int local_28;
  undefined4 local_24;
  undefined1 local_20 [4];
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_14 = *puVar2;
  local_10 = puVar2[1];
  local_c = puVar2[2];
  local_44 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
  local_28 = 0;
  local_24 = DAT_00917a74;
  FID_conflict_begin(local_20);
  do {
    uVar3 = FID_conflict_end(local_4c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') {
      FUN_0083e885();
      return;
    }
    piVar4 = (int *)FUN_00421ec0();
    local_18 = *piVar4;
    iVar5 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
    if (((*(int *)(iVar5 + 0x14) == param_2) &&
        (local_1c = (**(code **)(*(int *)(local_18 + 0x18) + 0x30))(),
        (*(uint *)(local_1c + 0x14) & 0x200) == 0)) &&
       ((iVar5 = FUN_00462340(local_1c), iVar5 == 0 ||
        (local_34 = *(int *)(local_1c + 0x88), (*(uint *)(local_34 + 0x114) & 0xc) == 0)))) {
      iVar5 = FUN_004626a0(local_1c);
      if ((iVar5 != 0) &&
         (local_40 = *(int *)(local_1c + 0x88), (*(uint *)(local_40 + 0x114) & 0xc) != 0)) {
        puVar2 = (undefined4 *)(**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
        fVar7 = (float10)FUN_004620b0(local_14,local_10,local_c,*puVar2,puVar2[1],puVar2[2]);
        local_3c = (float)fVar7;
        iVar5 = FUN_00462400();
        iVar6 = FUN_00462400();
        local_30 = *(float *)(iVar5 + 0xc) + *(float *)(iVar6 + 0xc) + 3.0;
        if (local_30 * local_30 < local_3c) goto LAB_00462db4;
      }
      cVar1 = FUN_004625d0(local_44);
      if ((cVar1 != '\0') &&
         ((param_3 < 0 || (iVar5 = (**(code **)(*(int *)(local_18 + 0x18) + 4))(), iVar5 == param_3)
          ))) {
        iVar5 = FUN_00417e20(local_1c);
        if (iVar5 != 0) {
          local_38 = local_18;
          cVar1 = FUN_00462670();
          if (cVar1 != '\0') goto LAB_00462db4;
        }
        uVar3 = (**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
        fVar7 = (float10)FUN_00462010(&local_14,uVar3);
        local_2c = (float)fVar7;
        if (local_2c < param_4) {
          local_28 = local_18;
          param_4 = local_2c;
        }
      }
    }
LAB_00462db4:
    FUN_0046b260(local_48,0);
  } while( true );
}

