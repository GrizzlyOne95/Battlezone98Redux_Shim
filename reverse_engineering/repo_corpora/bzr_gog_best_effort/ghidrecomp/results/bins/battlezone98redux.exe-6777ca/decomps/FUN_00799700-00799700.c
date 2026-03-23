
undefined4 __thiscall
FUN_00799700(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  
  cVar1 = FUN_007d3360(param_1);
  cVar2 = FUN_007d26c0(param_2,param_3,param_4);
  if (cVar2 == '\0') {
    uVar3 = 0;
  }
  else {
    if (cVar1 == '\x01') {
      cVar1 = FUN_007d3360(param_1);
      if (cVar1 == '\x01') {
        FUN_007997a0();
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

