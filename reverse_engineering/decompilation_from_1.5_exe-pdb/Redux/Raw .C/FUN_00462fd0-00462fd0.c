
void FUN_00462fd0(int param_1,float param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  int local_28;
  undefined4 local_24;
  float local_20;
  undefined1 local_1c [4];
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
  local_28 = 0;
  local_24 = DAT_00917a74;
  FID_conflict_begin(local_1c);
  while( true ) {
    uVar3 = FID_conflict_end(local_30);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_18 = *piVar4;
    iVar5 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
    if (*(int *)(iVar5 + 0x14) == 0x53494c4f) {
      iVar5 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
      iVar6 = (**(code **)(*(int *)(local_18 + 0x18) + 4))();
      if ((iVar5 == iVar6) &&
         (iVar5 = (**(code **)(*(int *)(local_18 + 0x18) + 0x30))(),
         (*(uint *)(iVar5 + 0x14) & 0x200) == 0)) {
        uVar3 = (**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
        fVar7 = (float10)FUN_00462010(&local_14,uVar3);
        local_20 = (float)fVar7;
        if (local_20 <= param_2) {
          local_28 = local_18;
          param_2 = local_20;
        }
      }
    }
    FUN_0046b260(local_2c,0);
  }
  FUN_0083e885();
  return;
}

