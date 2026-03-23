
undefined4 FUN_005ca740(undefined4 *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  uint uVar6;
  float10 fVar7;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined *local_14;
  float local_10;
  undefined4 local_c;
  int local_8;
  
  if (-1 < param_2) {
    local_8 = FUN_00462630(param_3);
    if (local_8 != 0) {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
      fVar7 = (float10)FUN_004620b0(*param_1,param_1[1],param_1[2],*puVar2,puVar2[1],puVar2[2]);
      local_1c = (float)fVar7;
      iVar3 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
      local_10 = *(float *)(iVar3 + 0x160);
      if (local_1c < local_10 * local_10) {
        return param_3;
      }
    }
    local_20 = FUN_005e0bc0(param_2);
    local_14 = &DAT_025cce7c;
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin(local_28);
    local_c = *puVar2;
    while( true ) {
      uVar4 = FID_conflict_end(local_30);
      cVar1 = FID_conflict_operator__(uVar4);
      if (cVar1 == '\0') break;
      piVar5 = (int *)FUN_00421ec0();
      local_8 = *piVar5;
      uVar6 = FUN_0045c4b0();
      if ((uVar6 & 0x200) == 0) {
        uVar4 = (**(code **)(*(int *)(local_8 + 0x18) + 4))();
        cVar1 = FUN_005e1310(uVar4);
        if (cVar1 != '\0') {
          puVar2 = (undefined4 *)(**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
          fVar7 = (float10)FUN_004620b0(*param_1,param_1[1],param_1[2],*puVar2,puVar2[1],puVar2[2]);
          local_24 = (float)fVar7;
          iVar3 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
          local_18 = *(float *)(iVar3 + 0x160);
          if (local_24 < local_18 * local_18) {
            uVar4 = FUN_00477590(local_8);
            return uVar4;
          }
        }
      }
      FUN_0046b260(local_2c,0);
    }
  }
  return 0;
}

