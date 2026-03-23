
bool FUN_0062dc80(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *param_2;
  uVar1 = *param_1;
  if (uVar2 < uVar1) {
    uVar3 = *param_1;
    *param_1 = *param_2;
    *param_2 = uVar3;
  }
  return uVar2 < uVar1;
}

