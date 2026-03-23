
void FUN_006ce840(undefined4 param_1,code *param_2)

{
  undefined4 extraout_ECX;
  int iVar1;
  undefined8 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined8 local_4c;
  undefined4 local_44;
  int local_40;
  int local_3c;
  undefined8 local_38;
  undefined4 *local_30;
  undefined1 local_2c [36];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006b22b0(local_5c);
  local_38 = FUN_006dd490(local_5c);
  local_4c = __aulldiv(local_38,1000000,0);
  local_3c = __aullrem(local_38,1000000,0);
  local_30 = (undefined4 *)(*param_2)(&local_4c,local_2c);
  uVar4 = extraout_ECX;
  FUN_006b2520(*(undefined2 *)(local_30 + 3));
  puVar3 = local_30;
  FUN_006b26a0(local_30[4] + 1);
  iVar1 = local_30[5] + 0x76c;
  FUN_006b25f0(iVar1);
  FUN_006b26e0(iVar1,puVar3,uVar4);
  uVar2 = FUN_006d2030();
  local_40 = __alldiv(uVar2,1000000,0);
  iVar1 = local_3c * local_40;
  uVar4 = 0;
  FUN_006b28f0(local_30[2],local_30[1],*local_30,iVar1,0);
  FUN_006b29d0(local_54);
  FUN_006b2960(local_44,iVar1,uVar4);
  FUN_0083e885();
  return;
}

