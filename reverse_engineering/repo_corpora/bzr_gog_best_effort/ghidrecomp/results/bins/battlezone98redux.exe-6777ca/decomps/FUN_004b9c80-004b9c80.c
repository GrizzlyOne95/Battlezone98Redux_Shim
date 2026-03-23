
void FUN_004b9c80(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_38 [4];
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  float local_28;
  undefined1 local_24 [4];
  int *local_20;
  int *local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_2;
  FUN_0046b370(local_24,param_2);
  uVar2 = FID_conflict_begin(local_38);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 == '\0') {
    local_20 = (int *)0x0;
  }
  else {
    iVar3 = FUN_00422150();
    local_20 = *(int **)(iVar3 + 4);
  }
  local_1c = local_20;
  if (local_20 != (int *)0x0) {
    local_34 = 0;
    local_30 = 0;
    local_2c = (uint)(ushort)(*(ushort *)(local_18 + 4) >> 4 & 0xf |
                             (*(ushort *)(local_18 + 4) & 0xf) << 6);
    local_28 = (float)*(ushort *)(local_18 + 6);
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    (**(code **)(*local_20 + 0x38))(&local_34,&local_14);
  }
  FUN_0083e885();
  return;
}

