
void FUN_007ea9a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_34 [36];
  undefined1 local_10 [4];
  undefined1 local_c [7];
  undefined1 local_5;
  
  FUN_0072f030(local_10,param_4);
  FUN_0072f050(local_c,param_4);
  uVar4 = extraout_ECX;
  FUN_00447eb0(local_c);
  uVar3 = extraout_ECX_00;
  FUN_00447eb0(local_10);
  uVar2 = FUN_004324a0(param_1,param_2,param_3);
  FUN_007eb400(uVar2,uVar3,uVar4);
  do {
    cVar1 = FUN_007eb450();
    if (cVar1 != '\0') break;
    local_5 = 0;
    FUN_007eaec0(local_34);
    cVar1 = FUN_007eb9f0();
  } while (cVar1 != '\0');
  FUN_007eba50(param_1);
  return;
}

