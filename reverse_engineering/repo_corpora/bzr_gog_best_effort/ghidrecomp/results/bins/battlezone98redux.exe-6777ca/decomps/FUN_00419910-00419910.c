
uint __thiscall FUN_00419910(int *param_1,uint *param_2,uint *param_3,char param_4)

{
  char cVar1;
  uint uVar2;
  
  if ((char)param_1[0x19] == '\0') {
    uVar2 = (uint)param_1 & 0xffffff00;
  }
  else {
    cVar1 = (**(code **)(*param_1 + 0x14))();
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
    else if (((param_1[0x13] == *param_2) && (param_1[0x14] == param_2[1])) ||
            ((uVar2 = param_1[0x13], uVar2 == *param_3 &&
             (uVar2 = param_1[0x14], uVar2 == param_3[1])))) {
      if (((param_4 == '\0') || (uVar2 = 0, *(char *)((int)param_1 + 0x5d) != '\x01')) &&
         ((uVar2 = *param_2, param_1[0xd] < (int)uVar2 ||
          (((uVar2 = *param_2, (int)uVar2 < param_1[0xb] ||
            (uVar2 = param_2[1], (int)uVar2 < param_1[0xc])) ||
           (uVar2 = param_2[1], param_1[0xe] < (int)uVar2)))))) {
        uVar2 = uVar2 & 0xffffff00;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x5d) = 0;
        uVar2 = CONCAT31((int3)(uVar2 >> 8),1);
      }
    }
    else {
      uVar2 = uVar2 & 0xffffff00;
    }
  }
  return uVar2;
}

