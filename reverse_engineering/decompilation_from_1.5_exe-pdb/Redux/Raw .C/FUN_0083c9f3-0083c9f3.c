
void FUN_0083c9f3(int *param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1[6];
  if (param_1[7] < iVar1) {
    if (iVar1 == 0) {
      if ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2) {
        return;
      }
    }
    else {
      uVar2 = *(uint *)(*(int *)(*param_1 + 0xc) + -4 + iVar1 * 4);
      if (((((byte)uVar2 & 0x3f) == 3) && ((int)(uVar2 >> 6 & 0xff) <= param_2)) &&
         (param_2 <= (int)((uVar2 >> 0x17) + 1))) {
        if (param_3 + -1 + param_2 <= (int)(uVar2 >> 0x17)) {
          return;
        }
        *(uint *)(*(int *)(*param_1 + 0xc) + -4 + iVar1 * 4) =
             (param_2 + -1 + param_3) * 0x800000 | uVar2 & 0x7fffff;
        return;
      }
    }
  }
  FUN_0083c5d2(param_1,3,param_2,param_3 + -1 + param_2,0);
  return;
}

