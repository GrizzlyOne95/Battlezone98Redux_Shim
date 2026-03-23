
void __thiscall FUN_007d3f20(int *param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c;
  int *local_8;
  
  *(undefined1 *)(param_1 + 0x3a) = param_2;
  local_8 = param_1;
  if (param_1[0x48] != 0) {
    uVar2 = FUN_007d3ee0();
    (**(code **)(*(int *)local_8[0x48] + 0xa8))((uVar2 & 0xff) + 0x3c);
  }
  (**(code **)(*local_8 + 0x38))();
  puVar3 = (undefined4 *)FID_conflict_begin(local_14);
  local_c = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_end(local_18);
  local_10 = *puVar3;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_10);
    if (cVar1 == '\0') break;
    get();
    uVar2 = FUN_007c19b0();
    uVar2 = uVar2 & 0xff;
    get(uVar2);
    FUN_007d3f20(uVar2);
    FUN_00421f70();
  }
  return;
}

