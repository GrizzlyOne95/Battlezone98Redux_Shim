
int FUN_005a3b40(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  undefined4 local_24;
  undefined4 local_18;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00462590();
  uVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_8 = FUN_005e0f70(1);
  if (local_8 == 0) {
    local_8 = FUN_005e0f70(2);
  }
  if (local_8 == 0) {
    local_8 = FUN_005e0f70(3);
  }
  if (local_8 == 0) {
    local_18 = 3.4028235e+38;
  }
  else {
    uVar2 = (**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
    fVar4 = (float10)FUN_00462010(uVar1,uVar2);
    local_18 = (float)fVar4;
  }
  local_24 = local_18;
  for (local_c = 0x4b; local_c < 0x50; local_c = local_c + 1) {
    iVar3 = FUN_005e0f70(local_c);
    if (iVar3 != 0) {
      uVar2 = (**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
      fVar4 = (float10)FUN_00462010(uVar1,uVar2);
      if ((float)fVar4 < local_24) {
        local_24 = (float)fVar4;
        local_8 = iVar3;
      }
    }
  }
  return local_8;
}

