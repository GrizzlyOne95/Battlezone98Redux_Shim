
void FUN_005ca520(undefined4 param_1,float param_2,int param_3,char *param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  int local_54 [3];
  float local_48;
  float local_44;
  uint local_40;
  uint local_3c;
  int local_38;
  undefined4 local_34;
  uint local_30;
  int local_2c;
  int local_28;
  undefined1 local_24 [7];
  char local_1d;
  int local_1c;
  char local_16;
  char local_15;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_15 = param_2 < 10000.0;
  local_40 = (uint)(byte)local_15;
  if ((bool)local_15) {
    local_2c = FUN_00462630(param_1);
    if (local_2c == 0) {
      FUN_007d6a70("CountUnitsNearObject passed dead object\n");
      goto LAB_005ca72e;
    }
    puVar2 = (undefined4 *)(**(code **)(*(int *)(local_2c + 0x18) + 0xc))();
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    local_48 = param_2 * param_2;
  }
  local_1d = -1 < param_3;
  local_3c = (uint)(byte)local_1d;
  local_16 = param_4 != (char *)0x0;
  local_30 = (uint)(byte)local_16;
  local_54[0] = 0;
  local_54[1] = 0;
  if ((bool)local_16) {
    strncpy((char *)local_54,param_4,8);
  }
  local_28 = 0;
  local_34 = DAT_00917a74;
  FID_conflict_begin(local_24);
  while( true ) {
    uVar3 = FID_conflict_end(local_58);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_1c = *piVar4;
    local_54[2] = (**(code **)(*(int *)(local_1c + 0x18) + 0x30))();
    if (((*(uint *)(local_54[2] + 0x14) & 0x200) == 0) &&
       ((local_1d == '\0' ||
        (iVar5 = (**(code **)(*(int *)(local_1c + 0x18) + 4))(), iVar5 == param_3)))) {
      if (local_16 != '\0') {
        local_38 = (*(code *)**(undefined4 **)(local_1c + 0x18))();
        if ((*(int *)(local_38 + 0x30) != local_54[0]) || (*(int *)(local_38 + 0x34) != local_54[1])
           ) goto LAB_005ca62f;
      }
      if (local_15 != '\0') {
        uVar3 = (**(code **)(*(int *)(local_1c + 0x18) + 0xc))();
        fVar6 = (float10)FUN_00462010(&local_14,uVar3);
        local_44 = (float)fVar6;
        if (local_48 < local_44) goto LAB_005ca62f;
      }
      local_28 = local_28 + 1;
    }
LAB_005ca62f:
    FUN_0046b260(local_5c,0);
  }
LAB_005ca72e:
  FUN_0083e885();
  return;
}

