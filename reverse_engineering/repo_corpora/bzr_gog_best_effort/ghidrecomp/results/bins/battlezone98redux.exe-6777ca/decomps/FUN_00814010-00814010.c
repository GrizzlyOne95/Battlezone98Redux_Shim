
uint FUN_00814010(uint *param_1,undefined1 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  undefined8 uVar5;
  
  if ((param_1[1] < 0x19999999) || ((param_1[1] < 0x1999999a && (*param_1 < 0x9999999a)))) {
    uVar5 = __allmul(*param_1,param_1[1],10,0);
    *(undefined8 *)param_1 = uVar5;
    uVar3 = FUN_00814580(param_2);
    uVar2 = -((int)uVar3 >> 0x1f) - 1;
    if ((param_1[1] < uVar2) ||
       ((puVar4 = param_1, param_1[1] == uVar2 &&
        (puVar4 = (uint *)*param_1, puVar4 <= (uint *)(-1 - uVar3))))) {
      uVar2 = *param_1;
      uVar1 = *param_1;
      *param_1 = uVar3 + uVar1;
      param_1[1] = ((int)uVar3 >> 0x1f) + param_1[1] + (uint)CARRY4(uVar3,uVar2);
      uVar2 = CONCAT31((int3)(uVar3 + uVar1 >> 8),1);
    }
    else {
      uVar2 = (uint)puVar4 & 0xffffff00;
    }
  }
  else {
    uVar2 = (uint)param_1 & 0xffffff00;
  }
  return uVar2;
}

