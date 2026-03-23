
float10 FUN_005d8f00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    float param_5)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  float local_1c;
  int local_18;
  undefined *local_14;
  float local_10;
  undefined1 local_c [4];
  int local_8;
  
  local_10 = param_5;
  local_14 = &DAT_0094e2d4;
  FID_conflict_begin(local_c);
  while( true ) {
    uVar2 = FID_conflict_end(local_24);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_8 = *piVar3;
    cVar1 = FUN_004db600(param_4);
    if ((cVar1 != '\0') && (iVar4 = FUN_0045bdf0(), iVar4 != 0)) {
      local_18 = (**(code **)(*(int *)(local_8 + 0x18) + 0x30))();
      iVar4 = FUN_00462340(local_18);
      if ((iVar4 == 0) || ((*(uint *)(local_18 + 0x14) & 0x30) != 0)) {
        puVar5 = (undefined4 *)(**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
        fVar6 = (float10)FUN_004620b0(param_1,param_2,param_3,*puVar5,puVar5[1],puVar5[2]);
        local_1c = (float)fVar6;
        if (local_1c < local_10) {
          local_10 = local_1c;
        }
      }
    }
    FUN_0046b260(local_20,0);
  }
  return (float10)local_10;
}

