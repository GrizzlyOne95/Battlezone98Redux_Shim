
void FUN_005c9bc0(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  int local_20;
  float local_1c;
  float local_18;
  int local_14;
  undefined4 local_10;
  undefined1 local_c [4];
  int local_8;
  
  local_1c = 1e+30;
  local_20 = 0;
  local_10 = DAT_00917a74;
  FID_conflict_begin(local_c);
  while( true ) {
    uVar2 = FID_conflict_end(local_28);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_8 = *piVar3;
    if (((local_8 != param_2) &&
        (local_14 = (**(code **)(*(int *)(local_8 + 0x18) + 0x30))(),
        (*(uint *)(local_14 + 0x14) & 0x200) == 0)) && (iVar4 = FUN_00417e20(local_14), iVar4 != 0))
    {
      uVar2 = (**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
      fVar5 = (float10)FUN_00462010(param_1,uVar2);
      local_18 = (float)fVar5;
      if (local_18 < local_1c) {
        local_20 = local_8;
        local_1c = local_18;
      }
    }
    FUN_0046b260(local_24,0);
  }
  FUN_00477590(local_20);
  return;
}

