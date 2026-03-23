
void * FUN_00428050(undefined *param_1)

{
  void *local_8;
  
  local_8 = (void *)0x0;
  if ((param_1 != (undefined *)0x0) &&
     ((&DAT_01bacf91 < param_1 ||
      (local_8 = operator_new((int)param_1 * 0x94), local_8 == (void *)0x0)))) {
                    /* WARNING: Subroutine does not return */
    std::_Xbad_alloc();
  }
  return local_8;
}

