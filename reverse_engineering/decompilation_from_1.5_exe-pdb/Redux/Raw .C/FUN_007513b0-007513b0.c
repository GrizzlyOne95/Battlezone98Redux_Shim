
void FUN_007513b0(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined1 local_34 [12];
  int *local_28;
  int local_24;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c [3];
  char local_19;
  int local_10;
  short local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1e = 0;
  local_28 = (int *)FUN_007508e0();
  puVar3 = local_1c;
  puVar2 = (undefined4 *)FUN_0073a970(local_34);
  cVar1 = (**(code **)(*local_28 + 0x18))(*puVar2,puVar2[1],puVar3);
  if (((cVar1 != '\0') && (local_24 = FUN_00746690(param_1), local_24 != 0)) &&
     ((*(int *)(local_24 + 0x90) != local_10 ||
      ((local_1f = local_19 == '\0', *(char *)(local_24 + 0x8c) != local_1f ||
       (*(short *)(local_24 + 0x94) != local_c)))))) {
    local_1d = local_19 != '\0';
    *(undefined1 *)(local_24 + 0x8c) = local_1d;
    *(int *)(local_24 + 0x90) = local_10;
    *(short *)(local_24 + 0x94) = local_c;
    local_1e = 1;
  }
  FUN_0083e885();
  return;
}

