
void * __thiscall FUN_0044d550(void *param_1,uint param_2)

{
  if ((param_2 & 2) == 0) {
    FUN_0044dc30();
    if ((param_2 & 1) != 0) {
      operator_delete(param_1);
    }
  }
  else {
    _eh_vector_destructor_iterator_(param_1,4,*(int *)((int)param_1 + -4),FUN_0044dc30);
    if ((param_2 & 1) != 0) {
      operator_delete__((void *)((int)param_1 + -4));
    }
    param_1 = (void *)((int)param_1 + -4);
  }
  return param_1;
}

