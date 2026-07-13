
undefined4 FUN_004167b0(undefined4 param_1,int param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  
  pcVar1 = std::_Syserror_map(param_2);
  if (pcVar1 == (char *)0x0) {
    uVar2 = FUN_00416810(extraout_var);
    FUN_00416430(param_2,uVar2);
  }
  else {
    uVar2 = FUN_00416800();
    FUN_00416430(param_2,uVar2);
  }
  return param_1;
}

