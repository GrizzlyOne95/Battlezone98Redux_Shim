
void * __thiscall FUN_006e0840(void *param_1,uint param_2)

{
  FID_conflict__vbase_destructor_();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

