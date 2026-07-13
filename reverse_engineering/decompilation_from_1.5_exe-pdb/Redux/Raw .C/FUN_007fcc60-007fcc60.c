
undefined4
FUN_007fcc60(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5
            ,undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  undefined1 local_18 [12];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_007fd3b0(local_8,param_4);
  FUN_007dc050(param_6);
  puVar5 = local_8;
  puVar4 = local_18;
  puVar3 = (undefined1 *)&param_2;
  uVar2 = param_1;
  uVar6 = param_6;
  FUN_007fd3b0(local_c,param_3,param_1,puVar3,puVar4,puVar5,param_6);
  cVar1 = FUN_007fd3e0(uVar2,puVar3,puVar4,puVar5,uVar6);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    if (param_5 == 0) {
      FUN_007fd410(param_1,&param_2,local_8);
    }
    uVar2 = 1;
  }
  return uVar2;
}

