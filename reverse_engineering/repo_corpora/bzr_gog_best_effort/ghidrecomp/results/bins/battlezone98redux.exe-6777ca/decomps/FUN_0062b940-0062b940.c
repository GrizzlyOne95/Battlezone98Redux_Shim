
void __thiscall FUN_0062b940(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(param_2 + 0x84) = param_3;
  iVar1 = FUN_0062be60(param_3,param_1);
  if (0 < iVar1) {
    if (*(int *)(&DAT_008ec7a4 + iVar1 * 0x34) != 0) {
      uVar2 = (**(code **)(&DAT_008ec7a4 + iVar1 * 0x34))();
      *(undefined4 *)(param_2 + 0x88) = uVar2;
    }
    FUN_0062cf50(param_2,"Obj76\\Classfnc.c");
    DAT_02a1f49c = FUN_00824540(DAT_02a1f49c,0,param_2);
    DAT_02a1f498 = FUN_00824540(DAT_02a1f498,0,DAT_02a1f49c);
    DAT_00920c64 = DAT_00920c64 + 1;
    DAT_00920c60 = DAT_00920c60 + 1;
  }
  return;
}

