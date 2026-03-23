
void __fastcall FUN_005d5350(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  float local_30;
  int local_2c;
  undefined1 local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ca28;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(int *)(param_1 + 0x5028) = param_1 + 0x28;
  *(int *)(param_1 + 0x25030) = param_1 + 0x5030;
  local_2c = param_1;
  FUN_00589430("smoke.odf");
  local_8 = 0;
  FUN_00589800(0x23e9d0db,0xdd33060c,&local_30,0x42800000);
  FUN_00589800(0x23e9d0db,0xbcc03185,&local_38,0x3fcccccd);
  FUN_00589800(0x23e9d0db,0x8566cba4,&local_3c,0x3fc00000);
  FUN_00589800(0x23e9d0db,0x2a532704,&local_34,0x3f800000);
  FUN_0047b6c0(0x23e9d0db,0xe4e87623,local_24,"lsmoke.0");
  fVar4 = local_30 / local_38;
  iVar1 = (int)local_30;
  uVar3 = local_3c;
  uVar5 = local_34;
  uVar2 = FUN_0068bed0(local_24,iVar1,fVar4,local_3c,local_34);
  uVar3 = FUN_00491000(uVar2,iVar1,fVar4,uVar3,uVar5);
  *(undefined4 *)(local_2c + 0x25038) = uVar3;
  FUN_0047b6c0(0x23e9d0db,0x89e40141,local_24,"msmoke.0");
  fVar4 = local_30 / local_38;
  iVar1 = (int)local_30;
  uVar3 = local_3c;
  uVar5 = local_34;
  uVar2 = FUN_0068bed0(local_24,iVar1,fVar4,local_3c,local_34);
  uVar3 = FUN_00491000(uVar2,iVar1,fVar4,uVar3,uVar5);
  *(undefined4 *)(local_2c + 0x2503c) = uVar3;
  FUN_0047b6c0(0x23e9d0db,0x55473cb2,local_24,"dsmoke.0");
  fVar4 = local_30 / local_38;
  iVar1 = (int)local_30;
  uVar3 = local_3c;
  uVar5 = local_34;
  uVar2 = FUN_0068bed0(local_24,iVar1,fVar4,local_3c,local_34);
  uVar3 = FUN_00491000(uVar2,iVar1,fVar4,uVar3,uVar5);
  *(undefined4 *)(local_2c + 0x25040) = uVar3;
  FUN_0047b6c0(0x23e9d0db,0x68ad0781,local_24,"bsmoke.0");
  fVar4 = local_30 / local_38;
  iVar1 = (int)local_30;
  uVar3 = local_3c;
  uVar5 = local_34;
  uVar2 = FUN_0068bed0(local_24,iVar1,fVar4,local_3c,local_34);
  uVar3 = FUN_00491000(uVar2,iVar1,fVar4,uVar3,uVar5);
  *(undefined4 *)(local_2c + 0x25044) = uVar3;
  FUN_00589800(0x23e9d0db,0x170efc31,&local_30,0x42800000);
  FUN_00589800(0x23e9d0db,0x4225e338,&local_38,0x40933333);
  FUN_00589800(0x23e9d0db,0x4583bc21,&local_3c,0x40000000);
  FUN_00589800(0x23e9d0db,0xc2c0fe4b,&local_34,0x3f800000);
  FUN_0047b6c0(0x23e9d0db,0x325cf422,local_24,"lsmoke.0");
  fVar4 = local_30 / local_38;
  iVar1 = (int)local_30;
  uVar3 = local_3c;
  uVar5 = local_34;
  uVar2 = FUN_0068bed0(local_24,iVar1,fVar4,local_3c,local_34);
  uVar3 = FUN_00491000(uVar2,iVar1,fVar4,uVar3,uVar5);
  *(undefined4 *)(local_2c + 0x25048) = uVar3;
  FUN_00589800(0x23e9d0db,0xc86d87f8,&local_30,0x42800000);
  FUN_00589800(0x23e9d0db,0xb6fc11f9,&local_38,0x40933333);
  FUN_00589800(0x23e9d0db,0x899409c8,&local_3c,0x40000000);
  FUN_00589800(0x23e9d0db,0x978015a0,&local_34,0x3f800000);
  FUN_0047b6c0(0x23e9d0db,0xb0ca99d,local_24,"lsmoke.0");
  fVar4 = local_30 / local_38;
  iVar1 = (int)local_30;
  uVar3 = FUN_0068bed0(local_24,iVar1,fVar4,local_3c,local_34);
  uVar3 = FUN_00491000(uVar3,iVar1,fVar4,local_3c,local_34);
  *(undefined4 *)(local_2c + 0x2504c) = uVar3;
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

