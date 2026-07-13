
int __fastcall FUN_00840de0(undefined4 *param_1)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = param_1[4];
  if (iVar2 != 0) {
    puVar3 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar3 = (undefined4 *)*param_1;
    }
    if (*(short *)((int)puVar3 + iVar2 * 2 + -2) != 0x3a) {
      if (7 < (uint)param_1[5]) {
        param_1 = (undefined4 *)*param_1;
      }
      sVar1 = *(short *)((int)param_1 + iVar2 * 2 + -2);
      if ((sVar1 != 0x2f) && (sVar1 != 0x5c)) {
        FUN_0083fc20(1,0x5c);
        return iVar2;
      }
    }
  }
  return 0;
}

