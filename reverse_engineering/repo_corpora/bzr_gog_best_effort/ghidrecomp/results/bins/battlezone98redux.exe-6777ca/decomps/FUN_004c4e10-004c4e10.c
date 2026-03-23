
void __thiscall FUN_004c4e10(int param_1,ushort *param_2,int param_3,int param_4,undefined4 param_5)

{
  float fVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  undefined2 local_28;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar4 = param_3 - (int)(*(float *)(param_1 + 0x2046c) / 2.0);
  fVar1 = *(float *)(param_1 + 0x2046c);
  local_c = param_4 - (int)(*(float *)(param_1 + 0x2046c) / 2.0);
  iVar2 = (int)*(float *)(param_1 + 0x2046c) + local_c;
  local_1c = 0.0;
  local_14 = 0;
  for (; local_c <= iVar2; local_c = local_c + 1) {
    local_18 = 0;
    for (local_10 = iVar4; local_10 <= (int)fVar1 + iVar4; local_10 = local_10 + 1) {
      puVar3 = (ushort *)FUN_00492d60(local_10,local_c);
      local_1c = (float)(*puVar3 & 0xfff) *
                 *(float *)(param_1 + 0x20470 + local_14 * 0x44 + local_18 * 4) + local_1c;
      local_18 = local_18 + 1;
    }
    local_14 = local_14 + 1;
  }
  if ((*param_2 & 0xfff) != (int)(local_1c + 0.5)) {
    FUN_004c10a0(param_3,param_4,*param_2,param_5);
    local_28 = (ushort)(int)(local_1c + 0.5);
    *param_2 = local_28;
    FUN_00780b80(param_3 + -2,param_4 + -2,param_3 + 2,param_4 + 2);
  }
  return;
}

