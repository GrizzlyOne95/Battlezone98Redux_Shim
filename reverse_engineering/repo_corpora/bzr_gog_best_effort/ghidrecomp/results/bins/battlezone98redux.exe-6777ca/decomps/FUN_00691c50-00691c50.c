
undefined4 FUN_00691c50(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00691b80(param_3,param_4 + -1 + (*(uint *)(param_2 + 0x24) >> 0x16 & 0xf),
                       *(uint *)(param_2 + 0x24) >> 0x12 & 0xf,2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_00691ae0(param_3 + -1,param_4 + -1,(*(uint *)(param_2 + 0x24) >> 0x12 & 0xf) + 2,
                         (*(uint *)(param_2 + 0x24) >> 0x16 & 0xf) + 2);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

