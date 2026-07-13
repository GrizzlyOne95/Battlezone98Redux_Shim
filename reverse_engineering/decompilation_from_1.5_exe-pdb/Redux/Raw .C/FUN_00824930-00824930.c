
bool FUN_00824930(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    sprintf(&DAT_009467c0,"Error %d during compression library operation: %s",param_1,param_2);
  }
  return param_1 == 0;
}

