
void FUN_0043bbf0(undefined4 *param_1)

{
  undefined4 local_8;
  
  if (param_1 == DAT_00915598) {
    DAT_00915598 = (undefined4 *)*param_1;
  }
  else {
    for (local_8 = DAT_00915598; (undefined4 *)*local_8 != param_1; local_8 = (undefined4 *)*local_8
        ) {
    }
    *local_8 = *param_1;
  }
  free(param_1);
  return;
}

