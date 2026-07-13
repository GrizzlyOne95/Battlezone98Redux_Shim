
void __fastcall FUN_004b79f0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 **ppuVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  *param_1 = DistributedObject::vftable;
  local_c = param_1;
  local_8 = param_1;
  puVar1 = (undefined4 *)FID_conflict_end(local_18);
  local_10 = *puVar1;
  ppuVar3 = &local_c;
  puVar1 = (undefined4 *)FID_conflict_end(local_1c);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_20);
  puVar1 = (undefined4 *)FUN_0046e930(local_24,*puVar1,uVar2,ppuVar3);
  local_14 = *puVar1;
  FID_conflict_erase(local_28,local_14,local_10);
  if (*(char *)(local_8 + 0x1a) == '\x02') {
    FUN_004badc0(local_8 + 0x19);
  }
  else if (*(char *)(local_8 + 0x1a) == '\x01') {
    FUN_004badc0(local_8 + 0x19);
  }
  return;
}

