
void FUN_00696f00(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 undefined4 param_7)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  float10 fVar7;
  
  bVar2 = false;
  iVar1 = *(int *)(DAT_00920f04 + param_1 * 4);
  if (iVar1 != 0) {
    if (param_4 != 0) {
      param_2 = param_2 / *(int *)(DAT_00920f04 + 0x88);
      param_3 = param_3 / *(int *)(DAT_00920f04 + 0x88);
    }
    if (-1 < param_5) {
      iVar3 = param_5 / *(int *)(DAT_00920f04 + 0x88);
      iVar4 = param_6 / *(int *)(DAT_00920f04 + 0x88);
      if ((iVar3 == param_2) && (iVar4 == param_3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      uVar5 = iVar3 - param_2;
      uVar6 = (int)uVar5 >> 0x1f;
      if ((1 < (int)((uVar5 ^ uVar6) - uVar6)) ||
         (uVar5 = iVar4 - param_3, uVar6 = (int)uVar5 >> 0x1f, 1 < (int)((uVar5 ^ uVar6) - uVar6)))
      {
        param_6 = -1;
        param_5 = -1;
      }
    }
    iVar3 = *(int *)(*(int *)(*(int *)(iVar1 + 0x80) + param_3 * 4) + param_2 * 4);
    if ((*(int *)(iVar3 + 4) == 6) || (*(int *)(iVar3 + 4) == 1)) {
      fVar7 = (float10)FUN_00822d80();
      *(float *)(iVar3 + 0x7c) = (float)fVar7;
      if (*(int *)(iVar3 + 0x74) != 0) {
        if (*(int *)(iVar3 + 0x74) != 2) {
          return;
        }
        if (*(char *)(iVar3 + 0x78) == '\x01') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + -4 + param_3 * 4) + -4 +
                              param_2 * 4),1,1,0x80);
        }
        else if (*(char *)(iVar3 + 0x78) == '\b') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + param_3 * 4) + -4 + param_2 * 4),1,
                       0,0x10);
        }
        else if (*(char *)(iVar3 + 0x78) == ' ') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + 4 + param_3 * 4) + -4 + param_2 * 4
                              ),1,0xffffffff,4);
        }
        else if (*(char *)(iVar3 + 0x78) == '\x02') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + -4 + param_3 * 4) + param_2 * 4),0,
                       1,0x40);
        }
        else if (*(char *)(iVar3 + 0x78) == '@') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + 4 + param_3 * 4) + param_2 * 4),0,
                       0xffffffff,2);
        }
        else if (*(char *)(iVar3 + 0x78) == '\x04') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + -4 + param_3 * 4) + 4 + param_2 * 4
                              ),0xffffffff,1,0x20);
        }
        else if (*(char *)(iVar3 + 0x78) == '\x10') {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + param_3 * 4) + 4 + param_2 * 4),
                       0xffffffff,0,8);
        }
        else if (*(char *)(iVar3 + 0x78) == -0x80) {
          FUN_00696c90(iVar1,*(undefined4 *)
                              (*(int *)(*(int *)(iVar1 + 0x80) + 4 + param_3 * 4) + 4 + param_2 * 4)
                       ,0xffffffff,0xffffffff,1);
        }
      }
      *(undefined4 *)(iVar3 + 0x74) = 1;
      FUN_00696b60(iVar1,iVar3,param_5,param_6,param_7);
      if ((bVar2) && (*(int *)(iVar3 + 0x14) != 0)) {
        FUN_006a4ed0(*(undefined4 *)(iVar3 + 0x14),iVar3,param_7);
      }
    }
  }
  return;
}

