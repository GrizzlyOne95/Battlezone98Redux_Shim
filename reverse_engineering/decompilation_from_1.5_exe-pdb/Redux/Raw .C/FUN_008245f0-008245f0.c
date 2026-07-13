
void FUN_008245f0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  undefined4 local_14;
  undefined4 local_10;
  uint local_c;
  float local_8;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0.0;
  FUN_00824710(param_2,&local_14);
  if ((local_c & 8) != 0) {
    fVar3 = (float10)FUN_008247f0(param_1,param_2,param_3,param_4);
    local_8 = (float)fVar3;
    iVar1 = FUN_0062dfe0(param_1);
    if ((iVar1 != 0) && (20.0 < local_8)) {
      FUN_008244f0((local_8 - 20.0) * 0.5);
    }
    if ((param_2 != 0) && (param_1 != 0)) {
      iVar1 = FUN_0047e9a0(param_2);
      iVar2 = FUN_0047e9a0(param_1);
      if (((iVar1 == iVar2) && ((*(int *)(param_2 + 0x84) == 1 || (*(int *)(param_2 + 0x84) == 6))))
         && ((*(int *)(param_1 + 0x84) == 1 || (*(int *)(param_1 + 0x84) == 6)))) {
        local_8 = 0.0;
      }
    }
  }
  FUN_0062c0b0(param_1,&local_14,param_5);
  return;
}

