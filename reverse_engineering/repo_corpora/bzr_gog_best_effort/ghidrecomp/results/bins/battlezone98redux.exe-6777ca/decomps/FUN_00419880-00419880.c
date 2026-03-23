
uint __thiscall FUN_00419880(int *param_1,uint *param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  
  if ((char)param_1[0x19] == '\0') {
    uVar3 = (uint)param_1 & 0xffffff00;
  }
  else {
    cVar2 = (**(code **)(*param_1 + 0x14))();
    if (cVar2 == '\0') {
      uVar3 = 0;
    }
    else {
      uVar3 = *param_2;
      if ((((param_1[0xd] < (int)uVar3) || (uVar3 = *param_2, (int)uVar3 < param_1[0xb])) ||
          (uVar3 = param_2[1], (int)uVar3 < param_1[0xc])) ||
         (uVar3 = param_2[1], param_1[0xe] < (int)uVar3)) {
        uVar3 = uVar3 & 0xffffff00;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x5d) = 1;
        uVar3 = *param_2;
        uVar1 = param_2[1];
        param_1[0x13] = uVar3;
        param_1[0x14] = uVar1;
        uVar3 = CONCAT31((int3)(uVar3 >> 8),1);
      }
    }
  }
  return uVar3;
}

