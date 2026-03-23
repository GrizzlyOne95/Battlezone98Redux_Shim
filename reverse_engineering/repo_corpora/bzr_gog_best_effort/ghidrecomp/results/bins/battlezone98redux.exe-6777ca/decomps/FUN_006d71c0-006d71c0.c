
undefined4 FUN_006d71c0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  
  cVar1 = FUN_0041fc90();
  if (cVar1 == '\0') {
    uVar2 = FUN_006d7990(local_10,param_1);
    uVar3 = FUN_005111d0(0);
    uVar2 = FUN_006d79b0(local_18,uVar3,uVar2);
    uVar2 = FUN_006d7bd0(local_20,uVar2);
    param_1 = FUN_006df030(uVar2,param_1);
  }
  return param_1;
}

