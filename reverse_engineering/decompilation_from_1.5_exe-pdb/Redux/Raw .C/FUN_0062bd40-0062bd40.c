
void FUN_0062bd40(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0062d370(*(undefined4 *)(param_1 + 8),"Obj76\\Classfnc.c");
  if (iVar1 == 0) {
    FUN_0062c100(param_1);
  }
  else {
    iVar2 = FUN_0062be60(*(undefined4 *)(iVar1 + 0x84));
    if (*(int *)(&DAT_008ec7ac + iVar2 * 0x34) != 0) {
      (**(code **)(&DAT_008ec7ac + iVar2 * 0x34))(iVar1);
    }
  }
  return;
}

