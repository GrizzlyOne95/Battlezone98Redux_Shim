
uint __thiscall FUN_00841340(undefined4 *param_1,ushort *param_2,uint param_3,uint param_4)

{
  ushort uVar1;
  ushort *puVar2;
  undefined4 *puVar3;
  ushort *puVar4;
  uint uVar5;
  ushort *puVar6;
  
  if (param_4 == 0) {
    uVar5 = param_1[4];
    if (param_3 < (uint)param_1[4]) {
      uVar5 = param_3;
    }
    return uVar5;
  }
  if ((uint)param_1[4] < param_4) {
    return 0xffffffff;
  }
  uVar5 = param_1[4] - param_4;
  if (param_3 < uVar5) {
    uVar5 = param_3;
  }
  puVar3 = param_1;
  if (7 < (uint)param_1[5]) {
    puVar3 = (undefined4 *)*param_1;
  }
  puVar6 = (ushort *)((int)puVar3 + uVar5 * 2);
  uVar1 = *param_2;
  do {
    puVar4 = puVar6;
    uVar5 = param_4;
    puVar2 = param_2;
    if (*puVar6 == uVar1) {
      while( true ) {
        if (uVar5 == 0) goto LAB_008413b1;
        if (*puVar4 != *puVar2) break;
        puVar4 = puVar4 + 1;
        uVar5 = uVar5 - 1;
        puVar2 = puVar2 + 1;
      }
      if ((-(uint)(*puVar4 < *puVar2) & 0xfffffffe) == 0xffffffff) {
LAB_008413b1:
        if (7 < (uint)param_1[5]) {
          param_1 = (undefined4 *)*param_1;
        }
        return (int)puVar6 - (int)param_1 >> 1;
      }
    }
    puVar4 = (ushort *)Myptr();
    if (puVar6 == puVar4) {
      return 0xffffffff;
    }
    puVar6 = puVar6 + -1;
  } while( true );
}

