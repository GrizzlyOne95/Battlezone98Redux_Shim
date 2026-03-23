
int * FUN_00463120(int param_1)

{
  char cVar1;
  float10 fVar2;
  undefined4 uVar3;
  float local_10;
  int *local_c;
  int *local_8;
  
  uVar3 = 1;
  FUN_00462590(1);
  local_8 = (int *)FUN_005e0f70(uVar3);
  if (local_8 != (int *)0x0) {
    cVar1 = (**(code **)(*local_8 + 0x68))();
    if (cVar1 == '\0') {
      local_8 = (int *)0x0;
    }
  }
  if (local_8 == (int *)0x0) {
    local_10 = 1e+30;
  }
  else {
    uVar3 = (**(code **)(local_8[6] + 0xc))();
    uVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(uVar3);
    fVar2 = (float10)FUN_00462010(uVar3);
    local_10 = (float)fVar2;
  }
  local_c = (int *)FUN_00462fd0(param_1,local_10);
  if (local_c == (int *)0x0) {
    local_c = local_8;
  }
  return local_c;
}

