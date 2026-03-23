
void FUN_00666d00(undefined4 param_1,int param_2,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_3,basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          *param_4,char *param_5,long param_6)

{
  Exception local_698 [140];
  InvalidParametersException local_60c [140];
  InvalidCallException local_580 [140];
  ItemIdentityException local_4f4 [140];
  UnimplementedException local_468 [140];
  IOException local_3dc [140];
  RuntimeAssertionException local_350 [140];
  RenderingAPIException local_2c4 [140];
  InternalErrorException local_238 [140];
  InvalidStateException local_1ac [140];
  FileNotFoundException local_120 [140];
  ItemIdentityException local_94 [140];
  undefined4 local_8;
  
  local_8 = param_1;
  switch(param_1) {
  case 0:
    Ogre::IOException::IOException(local_3dc,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_3dc,(ThrowInfo *)&DAT_008d7da8);
  case 1:
    Ogre::InvalidStateException::InvalidStateException
              (local_1ac,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_1ac,(ThrowInfo *)&DAT_008d7eb0);
  case 2:
    Ogre::InvalidParametersException::InvalidParametersException
              (local_60c,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_60c,(ThrowInfo *)&DAT_008d7cec);
  case 3:
    Ogre::RenderingAPIException::RenderingAPIException
              (local_2c4,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_2c4,(ThrowInfo *)&DAT_008d7e74);
  case 4:
    Ogre::ItemIdentityException::ItemIdentityException
              (local_4f4,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_4f4,(ThrowInfo *)&DAT_008d7ed0);
  case 5:
    Ogre::ItemIdentityException::ItemIdentityException
              (local_94,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_94,(ThrowInfo *)&DAT_008d7ed0);
  case 6:
    Ogre::FileNotFoundException::FileNotFoundException
              (local_120,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_120,(ThrowInfo *)&DAT_008d7ec0);
  case 7:
    Ogre::InternalErrorException::InternalErrorException
              (local_238,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_238,(ThrowInfo *)&DAT_008d7d70);
  case 8:
    Ogre::RuntimeAssertionException::RuntimeAssertionException
              (local_350,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_350,(ThrowInfo *)&DAT_008d7db8);
  case 9:
    Ogre::UnimplementedException::UnimplementedException
              (local_468,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_468,(ThrowInfo *)&DAT_008d7dd8);
  case 10:
    Ogre::InvalidCallException::InvalidCallException
              (local_580,param_2,param_3,param_4,param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_580,(ThrowInfo *)&DAT_008d7df8);
  default:
    Ogre::Exception::Exception(local_698,param_2,param_3,param_4,"Exception",param_5,param_6);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_698,(ThrowInfo *)&DAT_008d7e28);
  }
}

