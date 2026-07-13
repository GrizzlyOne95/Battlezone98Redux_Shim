; Entry: 00500804
; Name: Terrain_32PolyDouble
; Signature: void Terrain_32PolyDouble(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x005010d3
; Reason: Exception while decompiling 00500804: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x00500804 --stop-address=0x005010d3 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  500804:      	pushl	%ebp
  500805:      	movl	%esp, %ebp
  500807:      	pushl	%ebx
  500808:      	pushl	%esi
  500809:      	pushl	%edi
  50080a:      	pushl	%ebp
  50080b:      	subl	$0x700, %esp            # imm = 0x700
  500811:      	movl	0x14(%ebp), %ebx
  500814:      	movl	$0x186a0, %edx          # imm = 0x186A0
  500819:      	movl	0xc(%ebp), %esi
  50081c:      	movl	0x10(%ebp), %eax
  50081f:      	fildl	0x4(%ebx)
  500822:      	movl	(%ebx), %ecx
  500824:      	movl	%esi, (%esp)
  500827:      	shll	$0x3, %eax
  50082a:      	leal	0x8(%ebx), %edi
  50082d:      	fildl	(%ebx)
  50082f:      	movl	%ecx, 0x10(%esp)
  500833:      	leal	(%eax,%eax,2), %ecx
  500836:      	xorl	%eax, %eax
  500838:      	movl	%edi, 0x50(%esp)
  50083c:      	flds	0x62c808
  500842:      	fsubs	0x14(%esi,%eax)
  500846:      	flds	0x4(%esi,%eax)
  50084a:      	faddl	0x632380
  500850:      	fxch	%st(1)
  500852:      	flds	0xc(%esi,%eax)
  500856:      	fmul	%st(3), %st
  500858:      	flds	0x10(%esi,%eax)
  50085c:      	fmul	%st(5), %st
  50085e:      	fxch	%st(3)
  500860:      	fstpl	0x38(%esp)
  500864:      	fxch	%st(1)
  500866:      	fmuls	0x62c810
  50086c:      	fxch	%st(2)
  50086e:      	fstps	0x10(%esi,%eax)
  500872:      	fstps	0xc(%esi,%eax)
  500876:      	fstps	0x14(%esi,%eax)
  50087a:      	movl	0x38(%esp), %edi
  50087e:      	movl	%eax, 0x3e4(%esp,%eax)
  500885:      	movl	%eax, 0x114(%esp,%eax)
  50088c:      	movl	%edi, 0x400(%esp,%eax)
  500893:      	addl	$0x18, %eax
  500896:      	cmpl	%edx, %edi
  500898:      	jg	0x50089e <.text+0xff89e>
  50089a:      	movl	%eax, %ebx
  50089c:      	movl	%edi, %edx
  50089e:      	cmpl	%ecx, %eax
  5008a0:      	jne	0x50083c <.text+0xff83c>
  5008a2:      	subl	$0x18, %ebx
  5008a5:      	leal	-0x18(%eax), %ecx
  5008a8:      	fcompp
  5008aa:      	movl	$0x0, 0x3e4(%esp,%eax)
  5008b5:      	movl	%ecx, 0xfc(%esp)
  5008bc:      	movl	0x8(%ebp), %edi
  5008bf:      	movl	%ebx, 0xcc(%esp)
  5008c6:      	movl	%ebx, 0x9c(%esp)
  5008cd:      	movl	%ebx, 0xd0(%esp)
  5008d4:      	movl	%esi, %ebp
  5008d6:      	movl	0x20(%edi), %eax
  5008d9:      	movl	(%edi), %ecx
  5008db:      	addl	%edx, %eax
  5008dd:      	movl	0x14(%edi), %esi
  5008e0:      	movl	0x1c(%edi), %edi
  5008e3:      	imull	%ecx
  5008e5:      	addl	%edi, %esi
  5008e7:      	movl	%ecx, 0xc(%esp)
  5008eb:      	addl	%eax, %esi
  5008ed:      	movl	0x400(%esp,%ebx), %edi
  5008f4:      	movl	%esi, 0x98(%esp)
  5008fb:      	movl	%ebx, 0xa0(%esp)
  500902:      	movl	0xd0(%esp), %ecx
  500909:      	movl	0x400(%esp,%ecx), %eax
  500910:      	movl	%edi, 0x4(%esp)
  500914:      	cmpl	%eax, %edi
  500916:      	jl	0x500a3f <.text+0xffa3f>
  50091c:      	movl	0x3fc(%esp,%ecx), %edx
  500923:      	movl	%ecx, %eax
  500925:      	movl	%edx, 0xd0(%esp)
  50092c:      	cmpl	0x9c(%esp), %edx
  500933:      	je	0x5010c7 <.text+0x1000c7>
  500939:      	movl	0x400(%esp,%edx), %esi
  500940:      	movl	%edx, %ecx
  500942:      	cmpl	%esi, %edi
  500944:      	jge	0x50091c <.text+0xff91c>
  500946:      	flds	0x14(%ebp,%edx)
  50094a:      	fsubs	0x14(%ebp,%eax)
  50094e:      	flds	0x4(%ebp,%edx)
  500952:      	fsubs	0x4(%ebp,%eax)
  500956:      	flds	0x10(%ebp,%edx)
  50095a:      	fsubs	0x10(%ebp,%eax)
  50095e:      	fxch	%st(1)
  500960:      	fdivrs	0x62c808
  500966:      	flds	0xc(%ebp,%edx)
  50096a:      	fsubs	0xc(%ebp,%eax)
  50096e:      	fxch	%st(1)
  500970:      	fmul	%st, %st(2)
  500972:      	flds	0x8(%ebp,%edx)
  500976:      	fsubs	0x8(%ebp,%eax)
  50097a:      	fxch	%st(2)
  50097c:      	fmul	%st(1), %st
  50097e:      	flds	(%ebp,%edx)
  500982:      	fsubs	(%ebp,%eax)
  500986:      	fxch	%st(3)
  500988:      	fmul	%st(2), %st
  50098a:      	fxch	%st(4)
  50098c:      	fstps	0xec(%esp)
  500993:      	fstps	0xe8(%esp)
  50099a:      	fmul	%st, %st(3)
  50099c:      	flds	0x4(%ebp,%eax)
  5009a0:      	faddl	0x632380
  5009a6:      	fxch	%st(2)
  5009a8:      	fmulp	%st, %st(1)
  5009aa:      	fxch	%st(3)
  5009ac:      	fstps	0xf8(%esp)
  5009b3:      	fstpl	0x38(%esp)
  5009b7:      	fstps	0xf4(%esp)
  5009be:      	fildl	0x38(%esp)
  5009c2:      	fxch	%st(1)
  5009c4:      	fstps	0xf0(%esp)
  5009cb:      	fsubs	0x4(%ebp,%eax)
  5009cf:      	flds	0xf0(%esp)
  5009d6:      	flds	0xf4(%esp)
  5009dd:      	fmul	%st(2), %st
  5009df:      	flds	0xe8(%esp)
  5009e6:      	fmul	%st(3), %st
  5009e8:      	flds	0xf8(%esp)
  5009ef:      	fmul	%st(4), %st
  5009f1:      	fxch	%st(2)
  5009f3:      	fadds	0x8(%ebp,%eax)
  5009f7:      	flds	0xec(%esp)
  5009fe:      	fmul	%st(5), %st
  500a00:      	fxch	%st(2)
  500a02:      	fadds	0xc(%ebp,%eax)
  500a06:      	fxch	%st(4)
  500a08:      	fmulp	%st, %st(5)
  500a0a:      	fstps	0xd8(%esp)
  500a11:      	fadds	0x10(%ebp,%eax)
  500a15:      	fxch	%st(3)
  500a17:      	fadds	(%ebp,%eax)
  500a1b:      	fxch	%st(2)
  500a1d:      	fstps	0xdc(%esp)
  500a24:      	fadds	0x14(%ebp,%eax)
  500a28:      	fxch	%st(2)
  500a2a:      	fstps	0xe0(%esp)
  500a31:      	fstps	0xd4(%esp)
  500a38:      	fstps	0xe4(%esp)
  500a3f:      	movl	0xa0(%esp), %ecx
  500a46:      	cmpl	0x400(%esp,%ecx), %edi
  500a4d:      	jl	0x500b67 <.text+0xffb67>
  500a53:      	movl	0xfc(%esp,%ecx), %edx
  500a5a:      	movl	%ecx, %eax
  500a5c:      	movl	%edx, 0xa0(%esp)
  500a63:      	movl	%edx, %ecx
  500a65:      	cmpl	0x400(%esp,%edx), %edi
  500a6c:      	jge	0x500a53 <.text+0xffa53>
  500a6e:      	flds	0x14(%ebp,%edx)
  500a72:      	fsubs	0x14(%ebp,%eax)
  500a76:      	flds	0x4(%ebp,%edx)
  500a7a:      	fsubs	0x4(%ebp,%eax)
  500a7e:      	flds	0x10(%ebp,%edx)
  500a82:      	fsubs	0x10(%ebp,%eax)
  500a86:      	fxch	%st(1)
  500a88:      	fdivrs	0x62c808
  500a8e:      	flds	0xc(%ebp,%edx)
  500a92:      	fsubs	0xc(%ebp,%eax)
  500a96:      	fxch	%st(1)
  500a98:      	fmul	%st, %st(2)
  500a9a:      	flds	0x8(%ebp,%edx)
  500a9e:      	fsubs	0x8(%ebp,%eax)
  500aa2:      	fxch	%st(2)
  500aa4:      	fmul	%st(1), %st
  500aa6:      	flds	(%ebp,%edx)
  500aaa:      	fsubs	(%ebp,%eax)
  500aae:      	fxch	%st(3)
  500ab0:      	fmul	%st(2), %st
  500ab2:      	fxch	%st(4)
  500ab4:      	fstps	0xbc(%esp)
  500abb:      	fstps	0xb8(%esp)
  500ac2:      	fmul	%st, %st(3)
  500ac4:      	flds	0x4(%ebp,%eax)
  500ac8:      	faddl	0x632380
  500ace:      	fxch	%st(2)
  500ad0:      	fmulp	%st, %st(1)
  500ad2:      	fxch	%st(3)
  500ad4:      	fstps	0xc8(%esp)
  500adb:      	fstpl	0x38(%esp)
  500adf:      	fstps	0xc4(%esp)
  500ae6:      	fildl	0x38(%esp)
  500aea:      	fxch	%st(1)
  500aec:      	fstps	0xc0(%esp)
  500af3:      	fsubs	0x4(%ebp,%eax)
  500af7:      	flds	0xc0(%esp)
  500afe:      	flds	0xc4(%esp)
  500b05:      	fmul	%st(2), %st
  500b07:      	flds	0xb8(%esp)
  500b0e:      	fmul	%st(3), %st
  500b10:      	flds	0xc8(%esp)
  500b17:      	fmul	%st(4), %st
  500b19:      	fxch	%st(2)
  500b1b:      	fadds	0x8(%ebp,%eax)
  500b1f:      	flds	0xbc(%esp)
  500b26:      	fmul	%st(5), %st
  500b28:      	fxch	%st(2)
  500b2a:      	fadds	0xc(%ebp,%eax)
  500b2e:      	fxch	%st(4)
  500b30:      	fmulp	%st, %st(5)
  500b32:      	fstps	0xa8(%esp)
  500b39:      	fadds	0x10(%ebp,%eax)
  500b3d:      	fxch	%st(3)
  500b3f:      	fadds	(%ebp,%eax)
  500b43:      	fxch	%st(2)
  500b45:      	fstps	0xac(%esp)
  500b4c:      	fadds	0x14(%ebp,%eax)
  500b50:      	fxch	%st(2)
  500b52:      	fstps	0xb0(%esp)
  500b59:      	fstps	0xa4(%esp)
  500b60:      	fstps	0xb4(%esp)
  500b67:      	flds	0xd4(%esp)
  500b6e:      	faddl	0x632380
  500b74:      	flds	0xa4(%esp)
  500b7b:      	faddl	0x632380
  500b81:      	fxch	%st(1)
  500b83:      	fstpl	0x48(%esp)
  500b87:      	fstpl	0x40(%esp)
  500b8b:      	movl	0x48(%esp), %edx
  500b8f:      	movl	0x40(%esp), %ebx
  500b93:      	cmpl	%edx, %ebx
  500b95:      	je	0x500fd0 <.text+0xfffd0>
  500b9b:      	jl	0x500c7a <.text+0xffc7a>
  500ba1:      	flds	0xb4(%esp)
  500ba8:      	fsubs	0xe4(%esp)
  500baf:      	flds	0xa4(%esp)
  500bb6:      	fsubs	0xd4(%esp)
  500bbd:      	flds	0xb0(%esp)
  500bc4:      	fsubs	0xe0(%esp)
  500bcb:      	fxch	%st(1)
  500bcd:      	fdivrs	0x62c808
  500bd3:      	flds	0xac(%esp)
  500bda:      	fsubs	0xdc(%esp)
  500be1:      	fxch	%st(2)
  500be3:      	fmul	%st(1), %st
  500be5:      	flds	0xa8(%esp)
  500bec:      	fsubs	0xd8(%esp)
  500bf3:      	fxch	%st(3)
  500bf5:      	fmul	%st(2), %st
  500bf7:      	fxch	%st(1)
  500bf9:      	fstps	0x1c(%esp)
  500bfd:      	fxch	%st(1)
  500bff:      	fmul	%st, %st(2)
  500c01:      	fxch	%st(1)
  500c03:      	fstps	0x18(%esp)
  500c07:      	fmulp	%st, %st(2)
  500c09:      	fildl	0x48(%esp)
  500c0d:      	fxch	%st(1)
  500c0f:      	fstps	0x20(%esp)
  500c13:      	fsubs	0xd4(%esp)
  500c1a:      	fld	%st(1)
  500c1c:      	faddl	0x632380
  500c22:      	fxch	%st(2)
  500c24:      	fmul	%st(1), %st
  500c26:      	flds	0x1c(%esp)
  500c2a:      	fxch	%st(3)
  500c2c:      	fstpl	0x68(%esp)
  500c30:      	fadds	0xe4(%esp)
  500c37:      	fxch	%st(2)
  500c39:      	flds	0x18(%esp)
  500c3d:      	fmul	%st(2), %st
  500c3f:      	fxch	%st(3)
  500c41:      	faddl	0x632380
  500c47:      	fxch	%st(3)
  500c49:      	flds	0x20(%esp)
  500c4d:      	fmul	%st(3), %st
  500c4f:      	fxch	%st(4)
  500c51:      	fstpl	0x90(%esp)
  500c58:      	fadds	0xdc(%esp)
  500c5f:      	fxch	%st(2)
  500c61:      	fmulp	%st, %st(1)
  500c63:      	fxch	%st(2)
  500c65:      	fadds	0xd8(%esp)
  500c6c:      	fxch	%st(2)
  500c6e:      	fadds	0xe0(%esp)
  500c75:      	jmp	0x500d58 <.text+0xffd58>
  500c7a:      	movl	%ebx, 0x48(%esp)
  500c7e:      	movl	%edx, %ebx
  500c80:      	movl	0x48(%esp), %edx
  500c84:      	flds	0xe4(%esp)
  500c8b:      	fsubs	0xb4(%esp)
  500c92:      	flds	0xd4(%esp)
  500c99:      	fsubs	0xa4(%esp)
  500ca0:      	flds	0xe0(%esp)
  500ca7:      	fsubs	0xb0(%esp)
  500cae:      	fxch	%st(1)
  500cb0:      	fdivrs	0x62c808
  500cb6:      	flds	0xdc(%esp)
  500cbd:      	fsubs	0xac(%esp)
  500cc4:      	fxch	%st(2)
  500cc6:      	fmul	%st(1), %st
  500cc8:      	flds	0xd8(%esp)
  500ccf:      	fsubs	0xa8(%esp)
  500cd6:      	fxch	%st(3)
  500cd8:      	fmul	%st(2), %st
  500cda:      	fxch	%st(1)
  500cdc:      	fstps	0x1c(%esp)
  500ce0:      	fxch	%st(1)
  500ce2:      	fmul	%st, %st(2)
  500ce4:      	fxch	%st(1)
  500ce6:      	fstps	0x18(%esp)
  500cea:      	fmulp	%st, %st(2)
  500cec:      	fildl	0x48(%esp)
  500cf0:      	fxch	%st(1)
  500cf2:      	fstps	0x20(%esp)
  500cf6:      	fsubs	0xa4(%esp)
  500cfd:      	fld	%st(1)
  500cff:      	faddl	0x632380
  500d05:      	fxch	%st(2)
  500d07:      	fmul	%st(1), %st
  500d09:      	flds	0x1c(%esp)
  500d0d:      	fxch	%st(3)
  500d0f:      	fstpl	0x68(%esp)
  500d13:      	fadds	0xb4(%esp)
  500d1a:      	fxch	%st(2)
  500d1c:      	flds	0x18(%esp)
  500d20:      	fmul	%st(2), %st
  500d22:      	fxch	%st(3)
  500d24:      	faddl	0x632380
  500d2a:      	fxch	%st(3)
  500d2c:      	flds	0x20(%esp)
  500d30:      	fmul	%st(3), %st
  500d32:      	fxch	%st(4)
  500d34:      	fstpl	0x90(%esp)
  500d3b:      	fadds	0xac(%esp)
  500d42:      	fxch	%st(2)
  500d44:      	fmulp	%st, %st(1)
  500d46:      	fxch	%st(2)
  500d48:      	fadds	0xa8(%esp)
  500d4f:      	fxch	%st(2)
  500d51:      	fadds	0xb0(%esp)
  500d58:      	movl	0x68(%esp), %eax
  500d5c:      	movl	0x98(%esp), %edi
  500d63:      	andl	$0xffff, %eax           # imm = 0xFFFF
  500d68:      	subl	%edx, %ebx
  500d6a:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  500d6f:      	addl	%edx, %edi
  500d71:      	movl	%eax, 0x68(%esp)
  500d75:      	flds	0x18(%esp)
  500d79:      	fmuls	0x62c814
  500d7f:      	flds	0x1c(%esp)
  500d83:      	fmuls	0x62c814
  500d89:      	flds	0x20(%esp)
  500d8d:      	fmuls	0x62c814
  500d93:      	fxch	%st(2)
  500d95:      	fstps	0x24(%esp)
  500d99:      	fstps	0x28(%esp)
  500d9d:      	fstps	0x2c(%esp)
  500da1:      	fxch	%st(2)
  500da3:      	flds	0x62c80c
  500da9:      	fdiv	%st(1), %st
  500dab:      	fld	%st(3)
  500dad:      	fmul	%st(1), %st
  500daf:      	fld	%st(3)
  500db1:      	fmulp	%st, %st(2)
  500db3:      	faddl	0x632380
  500db9:      	fxch	%st(1)
  500dbb:      	faddl	0x632380
  500dc1:      	fxch	%st(2)
  500dc3:      	fadds	0x2c(%esp)
  500dc7:      	fxch	%st(1)
  500dc9:      	fstpl	0x78(%esp)
  500dcd:      	fxch	%st(1)
  500dcf:      	fstpl	0x70(%esp)
  500dd3:      	flds	0x62c80c
  500dd9:      	fdiv	%st(1), %st
  500ddb:      	decl	%ebx
  500ddc:      	jmp	0x500ed2 <.text+0xffed2>
  500de1:      	flds	0x24(%esp)
  500de5:      	faddp	%st, %st(3)
  500de7:      	flds	0x28(%esp)
  500deb:      	faddp	%st, %st(4)
  500ded:      	fld	%st(2)
  500def:      	fmul	%st(1), %st
  500df1:      	flds	0x2c(%esp)
  500df5:      	fxch	%st(2)
  500df7:      	fmul	%st(5), %st
  500df9:      	fxch	%st(2)
  500dfb:      	faddp	%st, %st(3)
  500dfd:      	faddl	0x632380
  500e03:      	fxch	%st(1)
  500e05:      	faddl	0x632380
  500e0b:      	fld	%st(2)
  500e0d:      	fxch	%st(2)
  500e0f:      	fstpl	0x80(%esp)
  500e16:      	fstpl	0x88(%esp)
  500e1d:      	fdivrs	0x62c80c
  500e23:      	movl	0x78(%esp), %ebp
  500e27:      	movl	0x70(%esp), %esi
  500e2b:      	movl	0x88(%esp), %eax
  500e32:      	movl	0x80(%esp), %edx
  500e39:      	subl	%ebp, %eax
  500e3b:      	subl	%esi, %edx
  500e3d:      	sarl	$0x4, %eax
  500e40:      	movl	%ebx, 0x8(%esp)
  500e44:      	sarl	$0x4, %edx
  500e47:      	movl	0x90(%esp), %ebx
  500e4e:      	movl	%edx, 0x58(%esp)
  500e52:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  500e58:      	movl	%eax, 0x60(%esp)
  500e5c:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  500e62:      	movl	%ebp, %eax
  500e64:      	movl	%esi, %edx
  500e66:      	sarl	$0xb, %eax
  500e69:      	movl	0x50(%esp), %ecx
  500e6d:      	sarl	$0x10, %edx
  500e70:      	andb	$-0x20, %al
  500e72:      	addl	0x60(%esp), %ebp
  500e76:      	addl	0x58(%esp), %esi
  500e7a:      	addl	%ecx, %eax
  500e7c:      	movl	0x68(%esp), %ecx
  500e80:      	addl	0x60(%esp), %ebp
  500e84:      	addl	0x58(%esp), %esi
  500e88:      	movb	(%eax,%edx), %dl
  500e8b:      	addl	$0x2, %edi
  500e8e:      	movb	%bh, %dh
  500e90:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  500e96:      	movb	0xd1e480(%edx), %al
  500e9c:      	addl	%ecx, %ebx
  500e9e:      	movb	%al, %ah
  500ea0:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  500ea6:      	movw	%ax, -0x2(%edi)
  500eaa:      	addl	%ecx, %ebx
  500eac:      	jge	0x500e62 <.text+0xffe62>
  500eae:      	movl	%ebx, 0x90(%esp)
  500eb5:      	movl	0x8(%esp), %ebx
  500eb9:      	movl	0x80(%esp), %eax
  500ec0:      	movl	0x88(%esp), %edx
  500ec7:      	movl	%eax, 0x70(%esp)
  500ecb:      	movl	%edx, 0x78(%esp)
  500ecf:      	subl	$0x10, %ebx
  500ed2:      	cmpl	$0x10, %ebx
  500ed5:      	jge	0x500de1 <.text+0xffde1>
  500edb:      	movl	0x90(%esp), %eax
  500ee2:      	movl	%ebx, %ecx
  500ee4:      	decl	%ebx
  500ee5:      	movl	0x78(%esp), %ebp
  500ee9:      	shll	$0x11, %ebx
  500eec:      	andl	$0xffff, %eax           # imm = 0xFFFF
  500ef1:      	movl	0x70(%esp), %esi
  500ef5:      	orl	%eax, %ebx
  500ef7:      	cmpl	$0x0, %ecx
  500efa:      	je	0x500fae <.text+0xfffae>
  500f00:      	fxch	%st(1)
  500f02:      	fsubs	0x2c(%esp)
  500f06:      	flds	0x20(%esp)
  500f0a:      	fmuls	0x62c810(,%ecx,8)
  500f11:      	flds	0x18(%esp)
  500f15:      	fmuls	0x62c810(,%ecx,8)
  500f1c:      	flds	0x1c(%esp)
  500f20:      	fmuls	0x62c810(,%ecx,8)
  500f27:      	fxch	%st(2)
  500f29:      	faddp	%st, %st(3)
  500f2b:      	faddp	%st, %st(4)
  500f2d:      	faddp	%st, %st(4)
  500f2f:      	fdivrs	0x62c80c
  500f35:      	fmul	%st, %st(2)
  500f37:      	fildl	0x70(%esp)
  500f3b:      	fxch	%st(1)
  500f3d:      	fmul	%st(4), %st
  500f3f:      	fildl	0x78(%esp)
  500f43:      	fxch	%st(2)
  500f45:      	fsubrp	%st, %st(4)
  500f47:      	fsubp	%st, %st(1)
  500f49:      	fxch	%st(2)
  500f4b:      	fmuls	0x62c814(,%ecx,8)
  500f52:      	fxch	%st(2)
  500f54:      	fmuls	0x62c814(,%ecx,8)
  500f5b:      	fxch	%st(2)
  500f5d:      	faddl	0x632380
  500f63:      	fxch	%st(2)
  500f65:      	faddl	0x632380
  500f6b:      	fxch	%st(2)
  500f6d:      	fstl	0x58(%esp)
  500f71:      	fxch	%st(2)
  500f73:      	fstl	0x60(%esp)
  500f77:      	movl	%ebp, %eax
  500f79:      	movl	%esi, %edx
  500f7b:      	sarl	$0xb, %eax
  500f7e:      	movl	0x50(%esp), %ecx
  500f82:      	sarl	$0x10, %edx
  500f85:      	andb	$-0x20, %al
  500f87:      	addl	%ecx, %eax
  500f89:      	movl	0x68(%esp), %ecx
  500f8d:      	addl	0x60(%esp), %ebp
  500f91:      	addl	0x58(%esp), %esi
  500f95:      	movb	(%eax,%edx), %dl
  500f98:      	incl	%edi
  500f99:      	movb	%bh, %dh
  500f9b:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  500fa1:      	movb	0xd1e480(%edx), %al
  500fa7:      	addl	%ecx, %ebx
  500fa9:      	movb	%al, -0x1(%edi)
  500fac:      	jge	0x500f77 <.text+0xfff77>
  500fae:      	sarl	$0xb, %ebp
  500fb1:      	xorl	%edx, %edx
  500fb3:      	sarl	$0x10, %esi
  500fb6:      	movl	0x50(%esp), %eax
  500fba:      	andl	$-0x20, %ebp
  500fbd:      	movb	%bh, %dh
  500fbf:      	addl	%ebp, %eax
  500fc1:      	fcompp
  500fc3:      	movb	(%eax,%esi), %dl
  500fc6:      	fcompp
  500fc8:      	movb	0xd1e480(%edx), %al
  500fce:      	movb	%al, (%edi)
  500fd0:      	flds	0xb4(%esp)
  500fd7:      	fadds	0xc8(%esp)
  500fde:      	flds	0xa8(%esp)
  500fe5:      	fadds	0xc4(%esp)
  500fec:      	flds	0xb0(%esp)
  500ff3:      	fadds	0xbc(%esp)
  500ffa:      	flds	0xac(%esp)
  501001:      	fadds	0xb8(%esp)
  501008:      	flds	0xa4(%esp)
  50100f:      	fadds	0xc0(%esp)
  501016:      	fxch	%st(3)
  501018:      	fstps	0xa8(%esp)
  50101f:      	fstps	0xac(%esp)
  501026:      	fstps	0xb0(%esp)
  50102d:      	fstps	0xa4(%esp)
  501034:      	fstps	0xb4(%esp)
  50103b:      	flds	0xe4(%esp)
  501042:      	fadds	0xf8(%esp)
  501049:      	flds	0xd8(%esp)
  501050:      	fadds	0xf4(%esp)
  501057:      	flds	0xe0(%esp)
  50105e:      	fadds	0xec(%esp)
  501065:      	flds	0xdc(%esp)
  50106c:      	fadds	0xe8(%esp)
  501073:      	flds	0xd4(%esp)
  50107a:      	fadds	0xf0(%esp)
  501081:      	fxch	%st(3)
  501083:      	fstps	0xd8(%esp)
  50108a:      	fstps	0xdc(%esp)
  501091:      	fstps	0xe0(%esp)
  501098:      	fstps	0xd4(%esp)
  50109f:      	fstps	0xe4(%esp)
  5010a6:      	movl	0x98(%esp), %esi
  5010ad:      	movl	0xc(%esp), %eax
  5010b1:      	movl	(%esp), %ebp
  5010b4:      	addl	%eax, %esi
  5010b6:      	movl	0x4(%esp), %edi
  5010ba:      	movl	%esi, 0x98(%esp)
  5010c1:      	incl	%edi
  5010c2:      	jmp	0x500902 <.text+0xff902>
  5010c7:      	addl	$0x700, %esp            # imm = 0x700
  5010cd:      	popl	%ebp
  5010ce:      	popl	%edi
  5010cf:      	popl	%esi
  5010d0:      	popl	%ebx
  5010d1:      	popl	%ebp
  5010d2:      	retl
