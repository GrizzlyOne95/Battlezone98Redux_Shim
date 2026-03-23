
void FUN_0082b8e4(undefined4 param_1,undefined2 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined2 *puVar2;
  char *pcVar3;
  undefined1 local_6c [4];
  undefined2 *local_68;
  void *local_64;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082e171(param_1,0,local_6c);
  if (iVar1 == 0) {
    pcVar3 = "bad argument #%d (%s)";
  }
  else {
    FUN_0082e08b(param_1,&DAT_00894d94,local_6c);
    iVar1 = memcmp(local_64,"method",7);
    if ((iVar1 != 0) || (param_2 = (undefined2 *)((int)param_2 + -1), param_2 != (undefined2 *)0x0))
    {
      puVar2 = &DAT_0088d940;
      if (local_68 != (undefined2 *)0x0) {
        puVar2 = local_68;
      }
      local_68 = puVar2;
      FUN_0082bc39(param_1,"bad argument #%d to \'%s\' (%s)",param_2,puVar2,param_3);
      goto LAB_0082b97a;
    }
    pcVar3 = "calling \'%s\' on bad self (%s)";
    param_2 = local_68;
  }
  FUN_0082bc39(param_1,pcVar3,param_2,param_3);
LAB_0082b97a:
  FUN_0083e885();
  return;
}

