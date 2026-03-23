
void __thiscall FUN_0047edf0(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_ac [72];
  int *local_64;
  int local_60;
  undefined4 local_5c [6];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_60 = param_1;
  if (*(int *)(param_1 + 0xf4) == *(int *)(param_1 + 0x228)) {
    if (((*(char *)(param_1 + 0x9c) == '\0') || (*(int *)(param_1 + 0xa0) == 0)) ||
       (iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0xa0) + 0x18) + 0x30))(), param_2 != iVar1)
       ) {
      puVar2 = (undefined4 *)FUN_0062bf70(local_ac,param_2);
      puVar3 = local_5c;
      for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      local_14 = local_44;
      local_10 = local_40;
      local_c = local_3c;
      FUN_008245f0(*(undefined4 *)(local_60 + 0xf4),param_2,&local_14,param_3 + 0x6c,param_3 + 0x54)
      ;
    }
  }
  else {
    local_64 = (int *)FUN_00479f30(*(undefined4 *)(param_1 + 0x228));
    (**(code **)(*local_64 + 0x48))(param_2,param_3,param_4);
  }
  FUN_0083e885();
  return;
}

