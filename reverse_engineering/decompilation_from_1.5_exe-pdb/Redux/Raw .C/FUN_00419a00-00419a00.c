
uint __thiscall
FUN_00419a00(int *param_1,int *param_2,int *param_3,undefined4 param_4,char param_5,char param_6)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  
  if ((char)param_1[0x19] == '\0') {
    uVar3 = (uint)param_1 & 0xffffff00;
  }
  else {
    cVar2 = (**(code **)(*param_1 + 0x14))();
    if (cVar2 == '\0') {
      uVar3 = 0;
    }
    else {
      piVar4 = (int *)param_1[0x13];
      if ((piVar4 == (int *)*param_3) &&
         (piVar4 = (int *)param_1[0x14], piVar4 == (int *)param_3[1])) {
        if (((param_6 == '\0') &&
            (((piVar4 = (int *)0x0, *(char *)((int)param_1 + 0x5d) != '\0' &&
              (piVar4 = (int *)*param_3, (int)piVar4 <= param_1[0xd])) &&
             (piVar4 = (int *)*param_3, param_1[0xb] <= (int)piVar4)))) &&
           ((piVar4 = (int *)param_3[1], param_1[0xc] <= (int)piVar4 &&
            (piVar4 = (int *)param_3[1], (int)piVar4 <= param_1[0xe])))) {
          *(undefined1 *)((int)param_1 + 0x5d) = 0;
        }
        if ((param_5 == '\0') &&
           (((param_6 != '\0' && (*(char *)((int)param_1 + 0x5d) == '\x01')) ||
            ((piVar4 = param_2, *param_2 <= param_1[0xd] &&
             (((param_1[0xb] <= *param_2 && (param_1[0xc] <= param_2[1])) &&
              (param_2[1] <= param_1[0xe])))))))) {
          *(undefined1 *)((int)param_1 + 0x5d) = 1;
          iVar1 = param_2[1];
          param_1[0x13] = *param_2;
          param_1[0x14] = iVar1;
          uVar3 = CONCAT31((int3)((uint)iVar1 >> 8),1);
        }
        else {
          uVar3 = (uint)piVar4 & 0xffffff00;
        }
      }
      else {
        uVar3 = (uint)piVar4 & 0xffffff00;
      }
    }
  }
  return uVar3;
}

