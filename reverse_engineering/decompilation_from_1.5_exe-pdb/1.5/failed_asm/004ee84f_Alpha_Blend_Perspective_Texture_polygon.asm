; Entry: 004ee84f
; Name: Alpha_Blend_Perspective_Texture_polygon
; Signature: void Alpha_Blend_Perspective_Texture_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004ef09c
; Reason: Exception while decompiling 004ee84f: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004ee84f --stop-address=0x004ef09c C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4ee84f:      	pushl	%ebp
  4ee850:      	movl	%esp, %ebp
  4ee852:      	pushl	%ebx
  4ee853:      	pushl	%esi
  4ee854:      	pushl	%edi
  4ee855:      	movl	0x14(%ebp), %ebx
  4ee858:      	pushl	%ebp
  4ee859:      	movl	0xcfdbc0, %eax
  4ee85e:      	subl	$0x6d8, %esp            # imm = 0x6D8
  4ee864:      	cmpl	%ebx, %eax
  4ee866:      	je	0x4ee8d6 <.text+0xed8d6>
  4ee868:      	movl	%ebx, 0xcfdbc0
  4ee86e:      	leal	0xcfdbd8, %edx
  4ee874:      	movl	(%ebx), %eax
  4ee876:      	movl	0x4(%ebx), %ecx
  4ee879:      	leal	0x8(%ebx), %esi
  4ee87c:      	movl	%ecx, 0x4(%esp)
  4ee880:      	movl	%eax, %edi
  4ee882:      	addl	$0x3, %ecx
  4ee885:      	addl	%esi, %edi
  4ee887:      	leal	(%esi,%eax,2), %ebx
  4ee88a:      	leal	(%eax,%eax,2), %eax
  4ee88d:      	movl	%esi, -0x4(%edx)
  4ee890:      	movl	%esi, -0x8(%edx)
  4ee893:      	movl	%esi, -0xc(%edx)
  4ee896:      	movl	%esi, -0x10(%edx)
  4ee899:      	movl	%esi, (%edx)
  4ee89b:      	movl	%edi, 0x4(%edx)
  4ee89e:      	movl	%ebx, 0x8(%edx)
  4ee8a1:      	addl	%eax, %esi
  4ee8a3:      	addl	%eax, %edi
  4ee8a5:      	addl	%eax, %ebx
  4ee8a7:      	addl	$0xc, %edx
  4ee8aa:      	subl	$0x3, %ecx
  4ee8ad:      	jge	0x4ee899 <.text+0xed899>
  4ee8af:      	movl	0x4(%esp), %edx
  4ee8b3:      	movl	0xcfdbd4(,%edx,4), %eax
  4ee8ba:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4ee8c1:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4ee8c8:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4ee8cf:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4ee8d6:      	movl	0x14(%ebp), %ebx
  4ee8d9:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4ee8de:      	movl	0xc(%ebp), %esi
  4ee8e1:      	movl	0x10(%ebp), %eax
  4ee8e4:      	fildl	0x4(%ebx)
  4ee8e7:      	movl	(%ebx), %ecx
  4ee8e9:      	movl	%esi, (%esp)
  4ee8ec:      	shll	$0x3, %eax
  4ee8ef:      	leal	0x8(%ebx), %edi
  4ee8f2:      	fsubs	0x62c808
  4ee8f8:      	fildl	(%ebx)
  4ee8fa:      	movl	%ecx, 0x10(%esp)
  4ee8fe:      	leal	(%eax,%eax,2), %ecx
  4ee901:      	xorl	%eax, %eax
  4ee903:      	movl	%edi, 0x1c(%esp)
  4ee907:      	fsubs	0x62c808
  4ee90d:      	flds	0x4(%esi,%eax)
  4ee911:      	faddl	0x632380
  4ee917:      	flds	0xc(%esi,%eax)
  4ee91b:      	fmul	%st(2), %st
  4ee91d:      	flds	0x10(%esi,%eax)
  4ee921:      	fmul	%st(4), %st
  4ee923:      	fxch	%st(2)
  4ee925:      	fstpl	0x640(%esp)
  4ee92c:      	fstps	0xc(%esi,%eax)
  4ee930:      	fstps	0x10(%esi,%eax)
  4ee934:      	movl	0x640(%esp), %edi
  4ee93b:      	movl	%eax, 0x320(%esp,%eax)
  4ee942:      	movl	%eax, 0x50(%esp,%eax)
  4ee946:      	movl	%edi, 0x33c(%esp,%eax)
  4ee94d:      	addl	$0x18, %eax
  4ee950:      	cmpl	%edx, %edi
  4ee952:      	jg	0x4ee958 <.text+0xed958>
  4ee954:      	movl	%eax, %ebx
  4ee956:      	movl	%edi, %edx
  4ee958:      	cmpl	%ecx, %eax
  4ee95a:      	jne	0x4ee90d <.text+0xed90d>
  4ee95c:      	subl	$0x18, %ebx
  4ee95f:      	leal	-0x18(%eax), %ecx
  4ee962:      	fcompp
  4ee964:      	movl	$0x0, 0x320(%esp,%eax)
  4ee96f:      	movl	%ecx, 0x38(%esp)
  4ee973:      	movl	0x8(%ebp), %edi
  4ee976:      	movl	%ebx, 0x6b0(%esp)
  4ee97d:      	movl	%ebx, 0x688(%esp)
  4ee984:      	movl	%ebx, 0x6b4(%esp)
  4ee98b:      	movl	%esi, %ebp
  4ee98d:      	movl	0x20(%edi), %eax
  4ee990:      	movl	(%edi), %ecx
  4ee992:      	addl	%edx, %eax
  4ee994:      	movl	0x14(%edi), %esi
  4ee997:      	movl	0x1c(%edi), %edi
  4ee99a:      	imull	%ecx
  4ee99c:      	addl	%edi, %esi
  4ee99e:      	movl	%ecx, 0xc(%esp)
  4ee9a2:      	addl	%eax, %esi
  4ee9a4:      	movl	0x33c(%esp,%ebx), %edi
  4ee9ab:      	movl	%esi, 0x18(%esp)
  4ee9af:      	movl	%ebx, 0x68c(%esp)
  4ee9b6:      	movl	0x6b4(%esp), %ecx
  4ee9bd:      	movl	0x33c(%esp,%ecx), %eax
  4ee9c4:      	movl	%edi, 0x4(%esp)
  4ee9c8:      	cmpl	%eax, %edi
  4ee9ca:      	jl	0x4eead4 <.text+0xedad4>
  4ee9d0:      	movl	0x338(%esp,%ecx), %edx
  4ee9d7:      	movl	%ecx, %eax
  4ee9d9:      	movl	%edx, 0x6b4(%esp)
  4ee9e0:      	cmpl	0x688(%esp), %edx
  4ee9e7:      	je	0x4ef090 <.text+0xee090>
  4ee9ed:      	movl	0x33c(%esp,%edx), %esi
  4ee9f4:      	movl	%edx, %ecx
  4ee9f6:      	cmpl	%esi, %edi
  4ee9f8:      	jge	0x4ee9d0 <.text+0xed9d0>
  4ee9fa:      	flds	0x4(%ebp,%edx)
  4ee9fe:      	fsubs	0x4(%ebp,%eax)
  4eea02:      	flds	0x10(%ebp,%edx)
  4eea06:      	fsubs	0x10(%ebp,%eax)
  4eea0a:      	fxch	%st(1)
  4eea0c:      	fdivrs	0x62c808
  4eea12:      	flds	0xc(%ebp,%edx)
  4eea16:      	fsubs	0xc(%ebp,%eax)
  4eea1a:      	fxch	%st(1)
  4eea1c:      	fmul	%st, %st(2)
  4eea1e:      	flds	0x8(%ebp,%edx)
  4eea22:      	fsubs	0x8(%ebp,%eax)
  4eea26:      	fxch	%st(2)
  4eea28:      	fmul	%st(1), %st
  4eea2a:      	flds	(%ebp,%edx)
  4eea2e:      	fsubs	(%ebp,%eax)
  4eea32:      	fxch	%st(3)
  4eea34:      	fmul	%st(2), %st
  4eea36:      	fxch	%st(4)
  4eea38:      	fstps	0x6cc(%esp)
  4eea3f:      	flds	0x4(%ebp,%eax)
  4eea43:      	faddl	0x632380
  4eea49:      	fxch	%st(3)
  4eea4b:      	fmulp	%st, %st(2)
  4eea4d:      	fstps	0x6c8(%esp)
  4eea54:      	fxch	%st(1)
  4eea56:      	fstpl	0x640(%esp)
  4eea5d:      	fstps	0x6d0(%esp)
  4eea64:      	fildl	0x640(%esp)
  4eea6b:      	fxch	%st(1)
  4eea6d:      	fstps	0x6d4(%esp)
  4eea74:      	fsubs	0x4(%ebp,%eax)
  4eea78:      	flds	0x6d0(%esp)
  4eea7f:      	flds	0x6d4(%esp)
  4eea86:      	fmul	%st(2), %st
  4eea88:      	flds	0x6c8(%esp)
  4eea8f:      	fmul	%st(3), %st
  4eea91:      	fxch	%st(1)
  4eea93:      	fadds	0x8(%ebp,%eax)
  4eea97:      	flds	0x6cc(%esp)
  4eea9e:      	fmul	%st(4), %st
  4eeaa0:      	fxch	%st(2)
  4eeaa2:      	fadds	0xc(%ebp,%eax)
  4eeaa6:      	fxch	%st(3)
  4eeaa8:      	fmulp	%st, %st(4)
  4eeaaa:      	fstps	0x6bc(%esp)
  4eeab1:      	fadds	0x10(%ebp,%eax)
  4eeab5:      	fxch	%st(2)
  4eeab7:      	fadds	(%ebp,%eax)
  4eeabb:      	fxch	%st(1)
  4eeabd:      	fstps	0x6c0(%esp)
  4eeac4:      	fxch	%st(1)
  4eeac6:      	fstps	0x6c4(%esp)
  4eeacd:      	fstps	0x6b8(%esp)
  4eead4:      	movl	0x68c(%esp), %ecx
  4eeadb:      	cmpl	0x33c(%esp,%ecx), %edi
  4eeae2:      	jl	0x4eebda <.text+0xedbda>
  4eeae8:      	movl	0x38(%esp,%ecx), %edx
  4eeaec:      	movl	%ecx, %eax
  4eeaee:      	movl	%edx, 0x68c(%esp)
  4eeaf5:      	movl	%edx, %ecx
  4eeaf7:      	cmpl	0x33c(%esp,%edx), %edi
  4eeafe:      	jge	0x4eeae8 <.text+0xedae8>
  4eeb00:      	flds	0x4(%ebp,%edx)
  4eeb04:      	fsubs	0x4(%ebp,%eax)
  4eeb08:      	flds	0x10(%ebp,%edx)
  4eeb0c:      	fsubs	0x10(%ebp,%eax)
  4eeb10:      	fxch	%st(1)
  4eeb12:      	fdivrs	0x62c808
  4eeb18:      	flds	0xc(%ebp,%edx)
  4eeb1c:      	fsubs	0xc(%ebp,%eax)
  4eeb20:      	fxch	%st(1)
  4eeb22:      	fmul	%st, %st(2)
  4eeb24:      	flds	0x8(%ebp,%edx)
  4eeb28:      	fsubs	0x8(%ebp,%eax)
  4eeb2c:      	fxch	%st(2)
  4eeb2e:      	fmul	%st(1), %st
  4eeb30:      	flds	(%ebp,%edx)
  4eeb34:      	fsubs	(%ebp,%eax)
  4eeb38:      	fxch	%st(3)
  4eeb3a:      	fmul	%st(2), %st
  4eeb3c:      	fxch	%st(4)
  4eeb3e:      	fstps	0x6a4(%esp)
  4eeb45:      	flds	0x4(%ebp,%eax)
  4eeb49:      	faddl	0x632380
  4eeb4f:      	fxch	%st(3)
  4eeb51:      	fmulp	%st, %st(2)
  4eeb53:      	fstps	0x6a0(%esp)
  4eeb5a:      	fxch	%st(1)
  4eeb5c:      	fstpl	0x640(%esp)
  4eeb63:      	fstps	0x6a8(%esp)
  4eeb6a:      	fildl	0x640(%esp)
  4eeb71:      	fxch	%st(1)
  4eeb73:      	fstps	0x6ac(%esp)
  4eeb7a:      	fsubs	0x4(%ebp,%eax)
  4eeb7e:      	flds	0x6a8(%esp)
  4eeb85:      	flds	0x6ac(%esp)
  4eeb8c:      	fmul	%st(2), %st
  4eeb8e:      	flds	0x6a0(%esp)
  4eeb95:      	fmul	%st(3), %st
  4eeb97:      	fxch	%st(1)
  4eeb99:      	fadds	0x8(%ebp,%eax)
  4eeb9d:      	flds	0x6a4(%esp)
  4eeba4:      	fmul	%st(4), %st
  4eeba6:      	fxch	%st(2)
  4eeba8:      	fadds	0xc(%ebp,%eax)
  4eebac:      	fxch	%st(3)
  4eebae:      	fmulp	%st, %st(4)
  4eebb0:      	fstps	0x694(%esp)
  4eebb7:      	fadds	0x10(%ebp,%eax)
  4eebbb:      	fxch	%st(2)
  4eebbd:      	fadds	(%ebp,%eax)
  4eebc1:      	fxch	%st(1)
  4eebc3:      	fstps	0x698(%esp)
  4eebca:      	fxch	%st(1)
  4eebcc:      	fstps	0x69c(%esp)
  4eebd3:      	fstps	0x690(%esp)
  4eebda:      	flds	0x6b8(%esp)
  4eebe1:      	faddl	0x632380
  4eebe7:      	flds	0x690(%esp)
  4eebee:      	faddl	0x632380
  4eebf4:      	fxch	%st(1)
  4eebf6:      	fstpl	0x650(%esp)
  4eebfd:      	fstpl	0x648(%esp)
  4eec04:      	movl	0x650(%esp), %edx
  4eec0b:      	movl	0x648(%esp), %ebx
  4eec12:      	cmpl	%edx, %ebx
  4eec14:      	je	0x4eefc9 <.text+0xedfc9>
  4eec1a:      	jl	0x4eecbc <.text+0xedcbc>
  4eec20:      	flds	0x690(%esp)
  4eec27:      	fsubs	0x6b8(%esp)
  4eec2e:      	flds	0x69c(%esp)
  4eec35:      	fsubs	0x6c4(%esp)
  4eec3c:      	fxch	%st(1)
  4eec3e:      	fdivrs	0x62c808
  4eec44:      	flds	0x698(%esp)
  4eec4b:      	fsubs	0x6c0(%esp)
  4eec52:      	fxch	%st(2)
  4eec54:      	fmul	%st(1), %st
  4eec56:      	flds	0x694(%esp)
  4eec5d:      	fsubs	0x6bc(%esp)
  4eec64:      	fxch	%st(3)
  4eec66:      	fmul	%st(2), %st
  4eec68:      	fxch	%st(1)
  4eec6a:      	fstps	0x24(%esp)
  4eec6e:      	fxch	%st(1)
  4eec70:      	fmulp	%st, %st(2)
  4eec72:      	fstps	0x20(%esp)
  4eec76:      	fildl	0x650(%esp)
  4eec7d:      	fxch	%st(1)
  4eec7f:      	fstps	0x28(%esp)
  4eec83:      	fsubs	0x6b8(%esp)
  4eec8a:      	flds	0x24(%esp)
  4eec8e:      	flds	0x20(%esp)
  4eec92:      	fmul	%st(2), %st
  4eec94:      	flds	0x28(%esp)
  4eec98:      	fmul	%st(3), %st
  4eec9a:      	fxch	%st(1)
  4eec9c:      	fadds	0x6c0(%esp)
  4eeca3:      	fxch	%st(3)
  4eeca5:      	fmulp	%st, %st(2)
  4eeca7:      	fadds	0x6bc(%esp)
  4eecae:      	fxch	%st(1)
  4eecb0:      	fadds	0x6c4(%esp)
  4eecb7:      	jmp	0x4eed63 <.text+0xedd63>
  4eecbc:      	movl	%ebx, 0x650(%esp)
  4eecc3:      	movl	%edx, %ebx
  4eecc5:      	movl	0x650(%esp), %edx
  4eeccc:      	flds	0x6b8(%esp)
  4eecd3:      	fsubs	0x690(%esp)
  4eecda:      	flds	0x6c4(%esp)
  4eece1:      	fsubs	0x69c(%esp)
  4eece8:      	fxch	%st(1)
  4eecea:      	fdivrs	0x62c808
  4eecf0:      	flds	0x6c0(%esp)
  4eecf7:      	fsubs	0x698(%esp)
  4eecfe:      	fxch	%st(2)
  4eed00:      	fmul	%st(1), %st
  4eed02:      	flds	0x6bc(%esp)
  4eed09:      	fsubs	0x694(%esp)
  4eed10:      	fxch	%st(3)
  4eed12:      	fmul	%st(2), %st
  4eed14:      	fxch	%st(1)
  4eed16:      	fstps	0x24(%esp)
  4eed1a:      	fxch	%st(1)
  4eed1c:      	fmulp	%st, %st(2)
  4eed1e:      	fstps	0x20(%esp)
  4eed22:      	fildl	0x650(%esp)
  4eed29:      	fxch	%st(1)
  4eed2b:      	fstps	0x28(%esp)
  4eed2f:      	fsubs	0x690(%esp)
  4eed36:      	flds	0x24(%esp)
  4eed3a:      	flds	0x20(%esp)
  4eed3e:      	fmul	%st(2), %st
  4eed40:      	flds	0x28(%esp)
  4eed44:      	fmul	%st(3), %st
  4eed46:      	fxch	%st(1)
  4eed48:      	fadds	0x698(%esp)
  4eed4f:      	fxch	%st(3)
  4eed51:      	fmulp	%st, %st(2)
  4eed53:      	fadds	0x694(%esp)
  4eed5a:      	fxch	%st(1)
  4eed5c:      	fadds	0x69c(%esp)
  4eed63:      	movl	0x18(%esp), %edi
  4eed67:      	subl	%edx, %ebx
  4eed69:      	addl	%edx, %edi
  4eed6b:      	flds	0x20(%esp)
  4eed6f:      	fmuls	0x62c814
  4eed75:      	flds	0x24(%esp)
  4eed79:      	fmuls	0x62c814
  4eed7f:      	flds	0x28(%esp)
  4eed83:      	fmuls	0x62c814
  4eed89:      	fxch	%st(2)
  4eed8b:      	fstps	0x2c(%esp)
  4eed8f:      	fstps	0x30(%esp)
  4eed93:      	fstps	0x34(%esp)
  4eed97:      	fxch	%st(1)
  4eed99:      	flds	0x62c80c
  4eed9f:      	fdiv	%st(1), %st
  4eeda1:      	fld	%st(2)
  4eeda3:      	fmul	%st(1), %st
  4eeda5:      	fld	%st(4)
  4eeda7:      	fmulp	%st, %st(2)
  4eeda9:      	faddl	0x632380
  4eedaf:      	fxch	%st(1)
  4eedb1:      	faddl	0x632380
  4eedb7:      	fxch	%st(2)
  4eedb9:      	fadds	0x34(%esp)
  4eedbd:      	fxch	%st(1)
  4eedbf:      	fstpl	0x680(%esp)
  4eedc6:      	fxch	%st(1)
  4eedc8:      	fstpl	0x678(%esp)
  4eedcf:      	fxch	%st(2)
  4eedd1:      	flds	0x62c80c
  4eedd7:      	fdiv	%st(3), %st
  4eedd9:      	decl	%ebx
  4eedda:      	jmp	0x4eeec1 <.text+0xedec1>
  4eeddf:      	flds	0x2c(%esp)
  4eede3:      	faddp	%st, %st(2)
  4eede5:      	flds	0x30(%esp)
  4eede9:      	faddp	%st, %st(3)
  4eedeb:      	fld	%st(1)
  4eeded:      	fmul	%st(1), %st
  4eedef:      	flds	0x34(%esp)
  4eedf3:      	fxch	%st(2)
  4eedf5:      	fmul	%st(4), %st
  4eedf7:      	fxch	%st(2)
  4eedf9:      	faddp	%st, %st(5)
  4eedfb:      	faddl	0x632380
  4eee01:      	fxch	%st(1)
  4eee03:      	faddl	0x632380
  4eee09:      	fld	%st(4)
  4eee0b:      	fxch	%st(2)
  4eee0d:      	fstpl	0x658(%esp)
  4eee14:      	fstpl	0x668(%esp)
  4eee1b:      	fdivrs	0x62c80c
  4eee21:      	movl	0x680(%esp), %ebp
  4eee28:      	movl	0x678(%esp), %esi
  4eee2f:      	movl	0x668(%esp), %eax
  4eee36:      	movl	0x658(%esp), %edx
  4eee3d:      	subl	%ebp, %eax
  4eee3f:      	subl	%esi, %edx
  4eee41:      	sarl	$0x4, %eax
  4eee44:      	movl	%ebx, 0x8(%esp)
  4eee48:      	sarl	$0x4, %edx
  4eee4b:      	movl	%eax, 0x670(%esp)
  4eee52:      	movl	%edx, 0x660(%esp)
  4eee59:      	movl	$0x10, %ebx
  4eee5e:      	movl	%ebp, %eax
  4eee60:      	movl	%esi, %edx
  4eee62:      	sarl	$0x10, %eax
  4eee65:      	movl	0x670(%esp), %ecx
  4eee6c:      	sarl	$0x10, %edx
  4eee6f:      	addl	%ecx, %ebp
  4eee71:      	movl	0xcfdbd8(,%eax,4), %eax
  4eee78:      	movl	0x660(%esp), %ecx
  4eee7f:      	movb	(%eax,%edx), %dh
  4eee82:      	addl	%ecx, %esi
  4eee84:      	cmpb	$-0x1, %dh
  4eee87:      	jne	0x4eee8f <.text+0xede8f>
  4eee89:      	incl	%edi
  4eee8a:      	decl	%ebx
  4eee8b:      	jne	0x4eee5e <.text+0xede5e>
  4eee8d:      	jmp	0x4eee9e <.text+0xede9e>
  4eee8f:      	movb	(%edi), %dl
  4eee91:      	incl	%edi
  4eee92:      	movb	0xd2e480(%edx), %al
  4eee98:      	decl	%ebx
  4eee99:      	movb	%al, -0x1(%edi)
  4eee9c:      	jne	0x4eee5e <.text+0xede5e>
  4eee9e:      	movl	0x8(%esp), %ebx
  4eeea2:      	movl	0x658(%esp), %eax
  4eeea9:      	movl	0x668(%esp), %edx
  4eeeb0:      	movl	%eax, 0x678(%esp)
  4eeeb7:      	movl	%edx, 0x680(%esp)
  4eeebe:      	subl	$0x10, %ebx
  4eeec1:      	cmpl	$0x10, %ebx
  4eeec4:      	jge	0x4eeddf <.text+0xedddf>
  4eeeca:      	cmpl	$0x0, %ebx
  4eeecd:      	movl	0x680(%esp), %ebp
  4eeed4:      	movl	0x678(%esp), %esi
  4eeedb:      	je	0x4eefa4 <.text+0xedfa4>
  4eeee1:      	fxch	%st(3)
  4eeee3:      	fsubs	0x34(%esp)
  4eeee7:      	flds	0x28(%esp)
  4eeeeb:      	fmuls	0x62c810(,%ebx,8)
  4eeef2:      	flds	0x20(%esp)
  4eeef6:      	fmuls	0x62c810(,%ebx,8)
  4eeefd:      	flds	0x24(%esp)
  4eef01:      	fmuls	0x62c810(,%ebx,8)
  4eef08:      	fxch	%st(2)
  4eef0a:      	faddp	%st, %st(3)
  4eef0c:      	faddp	%st, %st(3)
  4eef0e:      	faddp	%st, %st(3)
  4eef10:      	fdivrs	0x62c80c
  4eef16:      	fmul	%st, %st(1)
  4eef18:      	fildl	0x678(%esp)
  4eef1f:      	fxch	%st(1)
  4eef21:      	fmul	%st(3), %st
  4eef23:      	fildl	0x680(%esp)
  4eef2a:      	fxch	%st(2)
  4eef2c:      	fsubrp	%st, %st(3)
  4eef2e:      	fsubp	%st, %st(1)
  4eef30:      	fxch	%st(1)
  4eef32:      	fmuls	0x62c814(,%ebx,8)
  4eef39:      	fxch	%st(1)
  4eef3b:      	fmuls	0x62c814(,%ebx,8)
  4eef42:      	fxch	%st(1)
  4eef44:      	faddl	0x632380
  4eef4a:      	fxch	%st(1)
  4eef4c:      	faddl	0x632380
  4eef52:      	fxch	%st(1)
  4eef54:      	fstl	0x660(%esp)
  4eef5b:      	fxch	%st(1)
  4eef5d:      	fstl	0x670(%esp)
  4eef64:      	movl	%ebp, %eax
  4eef66:      	movl	%esi, %edx
  4eef68:      	sarl	$0x10, %eax
  4eef6b:      	movl	0x670(%esp), %ecx
  4eef72:      	sarl	$0x10, %edx
  4eef75:      	addl	%ecx, %ebp
  4eef77:      	movl	0xcfdbd8(,%eax,4), %eax
  4eef7e:      	movl	0x660(%esp), %ecx
  4eef85:      	movb	(%eax,%edx), %dh
  4eef88:      	addl	%ecx, %esi
  4eef8a:      	cmpb	$-0x1, %dh
  4eef8d:      	jne	0x4eef95 <.text+0xedf95>
  4eef8f:      	incl	%edi
  4eef90:      	decl	%ebx
  4eef91:      	jne	0x4eef64 <.text+0xedf64>
  4eef93:      	jmp	0x4eefa4 <.text+0xedfa4>
  4eef95:      	movb	(%edi), %dl
  4eef97:      	incl	%edi
  4eef98:      	movb	0xd2e480(%edx), %al
  4eef9e:      	decl	%ebx
  4eef9f:      	movb	%al, -0x1(%edi)
  4eefa2:      	jne	0x4eef64 <.text+0xedf64>
  4eefa4:      	sarl	$0x10, %ebp
  4eefa7:      	xorl	%edx, %edx
  4eefa9:      	sarl	$0x10, %esi
  4eefac:      	movb	(%edi), %dl
  4eefae:      	movl	0xcfdbd8(,%ebp,4), %eax
  4eefb5:      	fcompp
  4eefb7:      	movb	(%eax,%esi), %dh
  4eefba:      	fcompp
  4eefbc:      	cmpb	$-0x1, %dh
  4eefbf:      	je	0x4eefc9 <.text+0xedfc9>
  4eefc1:      	movb	0xd2e480(%edx), %al
  4eefc7:      	movb	%al, (%edi)
  4eefc9:      	flds	0x694(%esp)
  4eefd0:      	fadds	0x6ac(%esp)
  4eefd7:      	flds	0x69c(%esp)
  4eefde:      	fadds	0x6a4(%esp)
  4eefe5:      	flds	0x698(%esp)
  4eefec:      	fadds	0x6a0(%esp)
  4eeff3:      	flds	0x690(%esp)
  4eeffa:      	fadds	0x6a8(%esp)
  4ef001:      	fxch	%st(3)
  4ef003:      	fstps	0x694(%esp)
  4ef00a:      	fstps	0x698(%esp)
  4ef011:      	fstps	0x69c(%esp)
  4ef018:      	fstps	0x690(%esp)
  4ef01f:      	flds	0x6bc(%esp)
  4ef026:      	fadds	0x6d4(%esp)
  4ef02d:      	flds	0x6c4(%esp)
  4ef034:      	fadds	0x6cc(%esp)
  4ef03b:      	flds	0x6c0(%esp)
  4ef042:      	fadds	0x6c8(%esp)
  4ef049:      	flds	0x6b8(%esp)
  4ef050:      	fadds	0x6d0(%esp)
  4ef057:      	fxch	%st(3)
  4ef059:      	fstps	0x6bc(%esp)
  4ef060:      	fstps	0x6c0(%esp)
  4ef067:      	fstps	0x6c4(%esp)
  4ef06e:      	fstps	0x6b8(%esp)
  4ef075:      	movl	0x18(%esp), %esi
  4ef079:      	movl	0xc(%esp), %eax
  4ef07d:      	movl	(%esp), %ebp
  4ef080:      	addl	%eax, %esi
  4ef082:      	movl	0x4(%esp), %edi
  4ef086:      	movl	%esi, 0x18(%esp)
  4ef08a:      	incl	%edi
  4ef08b:      	jmp	0x4ee9b6 <.text+0xed9b6>
  4ef090:      	addl	$0x6d8, %esp            # imm = 0x6D8
  4ef096:      	popl	%ebp
  4ef097:      	popl	%edi
  4ef098:      	popl	%esi
  4ef099:      	popl	%ebx
  4ef09a:      	popl	%ebp
  4ef09b:      	retl
