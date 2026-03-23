
void * FUN_0042d350(uint param_1)

{
  void *local_8;
  
  local_8 = (void *)0x0;
  if ((param_1 != 0) &&
     ((0xccccccc < param_1 || (local_8 = operator_new(param_1 * 0x14), local_8 == (void *)0x0)))) {
                    /* WARNING: Subroutine does not return */
    std::_Xbad_alloc();
  }
  return local_8;
}

