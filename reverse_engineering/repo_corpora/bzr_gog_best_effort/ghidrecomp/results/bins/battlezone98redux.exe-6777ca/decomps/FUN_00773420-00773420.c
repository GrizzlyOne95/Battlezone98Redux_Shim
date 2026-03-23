
void FUN_00773420(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [8];
  int local_8;
  
  while (local_8 = (param_3 + -1) / 2, param_4 < param_3) {
    uVar3 = param_5;
    FUN_00732eb0(local_10,local_8);
    uVar2 = FUN_00772160(uVar3);
    cVar1 = FUN_00768120(uVar2,uVar3);
    if (cVar1 == '\0') break;
    FUN_00732eb0(local_18,local_8);
    uVar3 = FUN_00772160();
    uVar3 = FUN_00417780(uVar3);
    FUN_00732eb0(local_20,param_3);
    FUN_00772160(uVar3);
    FUN_007529c0(uVar3);
    param_3 = local_8;
  }
  uVar3 = FUN_00417780(param_5);
  FUN_00732eb0(local_28,param_3);
  FUN_00772160(uVar3);
  FUN_007529c0(uVar3);
  return;
}

