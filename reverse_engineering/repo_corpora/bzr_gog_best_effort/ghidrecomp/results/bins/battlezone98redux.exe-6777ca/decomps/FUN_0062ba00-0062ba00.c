
void FUN_0062ba00(int param_1)

{
  int iVar1;
  undefined4 *local_8;
  
  iVar1 = FUN_0062d370(param_1,"Obj76\\Classfnc.c");
  if (iVar1 != 0) {
    FUN_0062bab0(*(undefined4 *)(iVar1 + 0x84),*(undefined4 *)(iVar1 + 0x88));
    *(undefined4 *)(iVar1 + 0x84) = 0;
    *(undefined4 *)(iVar1 + 0x88) = 0;
  }
  local_8 = DAT_02a1f49c;
  while( true ) {
    if (local_8 == (undefined4 *)0x0) {
      return;
    }
    if (local_8[2] == param_1) break;
    local_8 = (undefined4 *)*local_8;
  }
  if (iVar1 != 0) {
    FUN_0062d310(iVar1,"Obj76\\Classfnc.c");
  }
  FUN_0062c100(local_8);
  return;
}

