
float10 FUN_00822970(float param_1)

{
  undefined1 uVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  uint local_14;
  char local_c;
  
  local_14 = (uint)(param_1 < (float)(int)param_1);
  local_14 = (int)param_1 - local_14;
  param_1 = param_1 - (float)(int)local_14;
  local_c = (char)local_14;
  fVar2 = (float10)FUN_008228e0(param_1);
  uVar1 = FUN_00822930(local_14 & 0xff,param_1);
  fVar3 = (float10)FUN_00822940(uVar1);
  uVar1 = FUN_00822930(local_c + '\x01',param_1 - 1.0);
  fVar4 = (float10)FUN_00822940(uVar1);
  return (float10)(((float)fVar4 - (float)fVar3) * (float)fVar2 + (float)fVar3);
}

