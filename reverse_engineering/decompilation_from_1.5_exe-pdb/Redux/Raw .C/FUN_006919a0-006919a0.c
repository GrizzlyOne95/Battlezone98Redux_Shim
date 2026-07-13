
void FUN_006919a0(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined1 local_18 [4];
  int local_14;
  undefined4 local_10;
  int local_c;
  short local_8;
  
  local_8 = FUN_00690fc0(param_1,**(undefined2 **)(param_2 + 0x14),0,&local_10,local_18,local_18);
  if (local_8 != 0) {
    cVar1 = FUN_006a0600(local_8);
    if (cVar1 == '\0') {
      local_14 = FUN_006a0670(local_8);
      *(undefined4 *)(param_2 + 0x20) = local_10;
      *(undefined4 *)(param_2 + 0x24) = *(undefined4 *)(local_14 + 0x20);
      FUN_006a4380(param_2,local_14);
    }
    else {
      local_c = FUN_006a0670(local_8);
      *(undefined4 *)(param_2 + 0x20) = local_10;
      *(uint *)(param_2 + 0x24) = (uint)*(ushort *)(local_c + 0x56);
      FUN_006a4230(param_2,local_c);
    }
  }
  return;
}

