
int FUN_00463fc0(int param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  int local_24;
  float local_20;
  float local_1c;
  int local_18;
  undefined4 local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  local_20 = 1e+30;
  local_24 = 0;
  local_14 = DAT_00917a74;
  FID_conflict_begin(local_10);
  while( true ) {
    uVar2 = FID_conflict_end(local_2c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_8 = *piVar3;
    if ((param_1 != local_8) && (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) {
      iVar4 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
      local_18 = *(int *)(iVar4 + 0x14);
      if ((local_18 != 0x54554700) ||
         (iVar4 = (*(code *)**(undefined4 **)(param_1 + 0x18))(),
         *(int *)(iVar4 + 0x14) != 0x52435943)) {
        iVar4 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
        local_c = *(int *)(iVar4 + 0x1c);
        if (((((local_c != 5) && (local_c != 7)) && (local_c != 2)) && (local_c != 10)) &&
           ((local_c != 3 || (local_18 == 0x544f5250)))) {
          puVar5 = (undefined4 *)(**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
          fVar6 = (float10)FUN_004620b0(*param_2,param_2[1],param_2[2],*puVar5,puVar5[1],puVar5[2]);
          local_1c = (float)fVar6;
          if (local_1c < local_20) {
            local_24 = local_8;
            local_20 = local_1c;
          }
        }
      }
    }
    FUN_0046b260(local_28,0);
  }
  return local_24;
}

