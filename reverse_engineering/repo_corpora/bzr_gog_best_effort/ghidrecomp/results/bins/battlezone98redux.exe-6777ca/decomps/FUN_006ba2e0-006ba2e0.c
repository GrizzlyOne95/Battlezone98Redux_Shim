
void __thiscall FUN_006ba2e0(undefined4 param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined8 local_14;
  undefined1 local_c [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = 0;
  if ((param_3 == 0) && (param_2 < 0x7e)) {
    iVar1 = 8;
  }
  else if ((param_3 == 0) && (param_2 < 0x10000)) {
    iVar1 = 6;
  }
  local_14 = FUN_006b9ed0(param_2,param_3,param_1,iVar1);
  FUN_006da2a0((int)&local_14 + iVar1,local_c,param_1);
  FUN_0083e885();
  return;
}

