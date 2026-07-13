
float10 FUN_005fce50(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_2 == 0) {
    fVar3 = (float10)0;
  }
  else {
    local_8 = *(float *)(param_2 + 0x58);
    if (*(int *)(param_2 + 0xc) == 0x54524754) {
      local_8 = 1400.0;
    }
    if (param_1 == 0) {
      local_10 = *(int *)(param_2 + 0x3c);
    }
    else {
      uVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 0x30))();
      iVar2 = FUN_00477d70(uVar1);
      if (iVar2 == 0) {
        local_c = *(int *)(param_2 + 0x40);
      }
      else {
        local_c = *(int *)(param_2 + 0x44);
      }
      local_10 = local_c;
    }
    if (local_10 != 0) {
      local_8 = local_8 + *(float *)(local_10 + 0x54);
    }
    fVar3 = (float10)local_8;
  }
  return fVar3;
}

