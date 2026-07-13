
int FUN_006aef90(SOCKET param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 == 0xffffffff) {
    FUN_006d8cf0(0x2719);
    iVar2 = -1;
  }
  else {
    FUN_006ae8d0();
    puVar3 = param_3;
    iVar2 = listen(param_1,param_2);
    iVar2 = FUN_006d8d90(iVar2,puVar3);
    if (iVar2 == 0) {
      puVar3 = (undefined4 *)FUN_004fbb60();
      uVar1 = puVar3[1];
      *param_3 = *puVar3;
      param_3[1] = uVar1;
    }
  }
  return iVar2;
}

