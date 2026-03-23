
undefined8 FUN_004b76c0(byte param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1 < 0x80) {
    uVar1 = 0;
    uVar2 = 0;
  }
  else if (param_1 < 0xe6) {
    uVar1 = *(undefined4 *)(&DAT_0260d3d0 + (uint)param_1 * 8);
    uVar2 = *(undefined4 *)(&DAT_0260d3d4 + (uint)param_1 * 8);
  }
  else {
    FUN_007d6a70("Invalid compact object id %d\n",param_1);
    uVar1 = 0;
    uVar2 = 0;
  }
  return CONCAT44(uVar2,uVar1);
}

