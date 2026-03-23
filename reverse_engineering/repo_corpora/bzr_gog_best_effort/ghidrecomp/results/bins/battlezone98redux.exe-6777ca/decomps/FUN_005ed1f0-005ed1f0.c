
undefined4 __thiscall FUN_005ed1f0(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (param_2 == 4) {
    uVar3 = 0;
    uVar2 = 0;
    uVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(0,0);
    FUN_004dbe70(8,uVar1,uVar2,uVar3);
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a8560(param_2);
  }
  return uVar1;
}

