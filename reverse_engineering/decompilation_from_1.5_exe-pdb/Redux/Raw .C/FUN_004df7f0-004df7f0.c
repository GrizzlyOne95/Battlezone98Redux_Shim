
int * FUN_004df7f0(int *param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint local_1c;
  ushort local_8;
  ushort local_6;
  
  local_6 = (ushort)((*(uint *)(param_2 + 0x14) & 0x30) != 0);
  local_8 = (ushort)((*(uint *)(param_2 + 0x14) & 0x20) != 0);
  iVar2 = FUN_00479f30(param_2);
  if (iVar2 == 0) {
    uVar1 = FUN_0047e9a0(param_2);
  }
  else {
    uVar1 = (**(code **)(*(int *)(iVar2 + 0x18) + 4))();
  }
  local_1c = (uint)(ushort)(local_6 << 4 | 8 | local_8 << 5 | (uVar1 & 0xf) << 6);
  *param_1 = param_2;
  param_1[1] = param_2;
  param_1[2] = local_1c;
  param_1[3] = 0;
  return param_1;
}

