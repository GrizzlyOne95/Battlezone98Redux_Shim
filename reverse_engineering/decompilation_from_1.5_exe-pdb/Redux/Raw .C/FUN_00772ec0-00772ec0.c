
void FUN_00772ec0(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,
                 undefined1 param_6)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  int local_c;
  int local_8;
  
  local_c = param_3;
  while (local_8 = param_3 * 2 + 2, local_8 < param_4) {
    FUN_00732eb0(local_14,param_3 * 2 + 1);
    uVar2 = FUN_00772160();
    FUN_00732eb0(local_1c,local_8);
    uVar3 = FUN_00772160(uVar2);
    cVar1 = FUN_00768120(uVar3,uVar2);
    if (cVar1 != '\0') {
      local_8 = local_8 + -1;
    }
    FUN_00732eb0(local_24,local_8);
    uVar2 = FUN_00772160();
    uVar2 = FUN_00417780(uVar2);
    FUN_00732eb0(local_2c,param_3);
    FUN_00772160(uVar2);
    FUN_007529c0(uVar2);
    param_3 = local_8;
  }
  if (local_8 == param_4) {
    FUN_00732eb0(local_34,param_4 + -1);
    uVar2 = FUN_00772160();
    uVar2 = FUN_00417780(uVar2);
    FUN_00732eb0(local_3c,param_3);
    FUN_00772160(uVar2);
    FUN_007529c0(uVar2);
    param_3 = param_4 + -1;
  }
  uVar2 = FUN_00417780(param_5,param_6);
  FUN_00773420(param_1,param_2,param_3,local_c,uVar2);
  return;
}

