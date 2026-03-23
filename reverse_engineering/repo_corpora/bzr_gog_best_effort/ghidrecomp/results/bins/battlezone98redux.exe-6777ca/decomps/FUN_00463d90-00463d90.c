
void FUN_00463d90(int param_1,float *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  undefined1 local_64 [12];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined1 local_38 [4];
  int local_34;
  int local_30;
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
  uVar2 = FUN_00462530();
  local_4c = FUN_00462630(uVar2);
  puVar3 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_2c = *puVar3;
  local_28 = puVar3[1];
  local_24 = puVar3[2];
  local_48 = 0;
  local_40 = *param_2;
  local_44 = DAT_00917a74;
  FID_conflict_begin(local_38);
  do {
    uVar2 = FID_conflict_end(local_58);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') {
      FUN_0083e885();
      return;
    }
    piVar4 = (int *)FUN_00421ec0();
    local_30 = *piVar4;
    cVar1 = FUN_004db5b0(local_30);
    if (cVar1 != '\0') {
      uVar2 = FUN_004625b0();
      cVar1 = FUN_004db600(uVar2);
      if (cVar1 != '\0') {
        iVar5 = FUN_004625b0();
        iVar6 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
        if (iVar5 != iVar6) {
          uVar2 = FUN_004625b0();
          cVar1 = FUN_004db600(uVar2);
          if (cVar1 == '\0') goto LAB_00463e01;
        }
        local_34 = (**(code **)(*(int *)(local_30 + 0x18) + 0x30))();
        iVar5 = FUN_00462340(local_34);
        if (((iVar5 != 0) && ((*(uint *)(local_34 + 0x14) & 0x200) == 0)) &&
           ((local_30 == local_4c ||
            (local_50 = *(int *)(local_34 + 0x88), (*(uint *)(local_50 + 0x114) & 0xc) == 0)))) {
          puVar3 = (undefined4 *)
                   (**(code **)(*(int *)(local_30 + 0x18) + 0xc))(local_2c,local_28,local_24);
          puVar3 = (undefined4 *)FUN_004401a0(local_64,*puVar3,puVar3[1],puVar3[2]);
          local_20 = *puVar3;
          local_1c = puVar3[1];
          local_18 = puVar3[2];
          local_14 = local_20;
          local_10 = local_1c;
          local_c = local_18;
          fVar7 = (float10)FUN_00462070(&local_20);
          local_3c = (float)fVar7;
          if (local_3c < local_40) {
            local_48 = local_30;
            local_40 = local_3c;
          }
        }
      }
    }
LAB_00463e01:
    FUN_0046b260(local_54,0);
  } while( true );
}

