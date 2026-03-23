
int FUN_0043d670(float param_1)

{
  if (param_1 <= 1.0) {
    if (param_1 < -1.0) {
      param_1 = -1.0;
    }
  }
  else {
    param_1 = 1.0;
  }
  return (int)(param_1 * 32767.0);
}

