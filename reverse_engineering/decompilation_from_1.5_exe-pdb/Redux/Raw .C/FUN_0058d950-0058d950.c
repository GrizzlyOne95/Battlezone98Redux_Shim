
/* WARNING: Removing unreachable block (ram,0x0058da23) */

int FUN_0058d950(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float10 fVar3;
  float fVar4;
  int local_8;
  
  fVar3 = (float10)FUN_0058bec0(*(undefined4 *)(param_3 + 0x10));
  if ((float)fVar3 == 99999.0) {
    local_8 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_4 + 0x24);
    uVar2 = *(undefined4 *)(param_4 + 0x28);
    *(undefined4 *)(param_4 + 0x24) = param_1;
    *(undefined4 *)(param_4 + 0x28) = param_2;
    fVar3 = (float10)FUN_0058d590(param_3,param_4,(float)fVar3);
    fVar4 = (float)fVar3 + *(float *)(param_3 + 0x2c);
    local_8 = param_4;
    if (*(float *)(param_4 + 0x2c) <= fVar4 && fVar4 != *(float *)(param_4 + 0x2c)) {
      *(undefined4 *)(param_4 + 0x24) = uVar1;
      *(undefined4 *)(param_4 + 0x28) = uVar2;
      local_8 = 0;
    }
  }
  return local_8;
}

