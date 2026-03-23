
void __fastcall FUN_006617c0(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084d9fb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = EntityTransparency::vftable;
  local_8 = 0;
  local_18 = param_1;
  FUN_00422170(uVar2);
  FUN_00422170();
  puVar3 = (undefined4 *)FID_conflict_end(local_2c);
  local_20 = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_begin(local_30);
  local_14 = *puVar3;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_20);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_24 = (undefined4 *)*piVar4;
    local_1c = local_24;
    if (local_24 == (undefined4 *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = (**(code **)*local_24)(1);
    }
    FUN_00421ee0();
  }
  local_8 = 0xffffffff;
  FUN_0041fe20();
  ExceptionList = local_10;
  return;
}

