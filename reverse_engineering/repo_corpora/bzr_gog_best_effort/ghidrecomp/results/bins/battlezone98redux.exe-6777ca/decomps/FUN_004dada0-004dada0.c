
int FUN_004dada0(int param_1)

{
  int *piVar1;
  int local_8;
  
  local_8 = 0;
  switch(*(undefined4 *)(param_1 + 0x84)) {
  case 1:
  case 6:
    local_8 = FUN_004a84b0(param_1);
    break;
  case 2:
  case 5:
  case 7:
  case 10:
    local_8 = FUN_0047ec90(param_1);
    break;
  case 3:
    local_8 = FUN_005a7d00(param_1);
    break;
  case 4:
    local_8 = FUN_0059cec0(param_1);
  }
  if ((local_8 != 0) && (piVar1 = (int *)FUN_0045ca50(), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x14))(local_8);
  }
  return local_8;
}

