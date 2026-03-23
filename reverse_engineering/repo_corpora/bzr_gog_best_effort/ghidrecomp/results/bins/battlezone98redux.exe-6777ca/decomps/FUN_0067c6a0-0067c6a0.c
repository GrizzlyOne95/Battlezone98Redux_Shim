
HardwareVertexBufferSharedPtr * __thiscall
FUN_0067c6a0(HardwareVertexBufferSharedPtr *param_1,uint param_2)

{
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

