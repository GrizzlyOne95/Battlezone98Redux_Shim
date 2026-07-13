; Entry: 004f296f
; Name: Flat_Perspective_Texture_Map_polygon
; Signature: void Flat_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f317c
; Reason: Exception while decompiling 004f296f: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f296f --stop-address=0x004f317c C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f296f:      	pushl	%ebp
  4f2970:      	movl	%esp, %ebp
  4f2972:      	pushl	%ebx
  4f2973:      	pushl	%edi
  4f2974:      	pushl	%esi
  4f2975:      	movl	0x14(%ebp), %ebx
  4f2978:      	movl	0xcfdbc0, %eax
  4f297d:      	subl	$0x6e8, %esp            # imm = 0x6E8
  4f2983:      	cmpl	%ebx, %eax
  4f2985:      	je	0x4f29f5 <.text+0xf19f5>
  4f2987:      	movl	%ebx, 0xcfdbc0
  4f298d:      	leal	0xcfdbd8, %edx
  4f2993:      	movl	(%ebx), %eax
  4f2995:      	movl	0x4(%ebx), %ecx
  4f2998:      	leal	0x8(%ebx), %esi
  4f299b:      	movl	%ecx, 0x4(%esp)
  4f299f:      	movl	%eax, %edi
  4f29a1:      	addl	$0x3, %ecx
  4f29a4:      	addl	%esi, %edi
  4f29a6:      	leal	(%esi,%eax,2), %ebx
  4f29a9:      	leal	(%eax,%eax,2), %eax
  4f29ac:      	movl	%esi, -0x4(%edx)
  4f29af:      	movl	%esi, -0x8(%edx)
  4f29b2:      	movl	%esi, -0xc(%edx)
  4f29b5:      	movl	%esi, -0x10(%edx)
  4f29b8:      	movl	%esi, (%edx)
  4f29ba:      	movl	%edi, 0x4(%edx)
  4f29bd:      	movl	%ebx, 0x8(%edx)
  4f29c0:      	addl	%eax, %esi
  4f29c2:      	addl	%eax, %edi
  4f29c4:      	addl	%eax, %ebx
  4f29c6:      	addl	$0xc, %edx
  4f29c9:      	subl	$0x3, %ecx
  4f29cc:      	jge	0x4f29b8 <.text+0xf19b8>
  4f29ce:      	movl	0x4(%esp), %edx
  4f29d2:      	movl	0xcfdbd4(,%edx,4), %eax
  4f29d9:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f29e0:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f29e7:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f29ee:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f29f5:      	movl	0x14(%ebp), %ebx
  4f29f8:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f29fd:      	movl	0xc(%ebp), %esi
  4f2a00:      	movl	0x10(%ebp), %eax
  4f2a03:      	fildl	0x4(%ebx)
  4f2a06:      	movl	(%ebx), %ecx
  4f2a08:      	movl	%esi, (%esp)
  4f2a0b:      	shll	$0x3, %eax
  4f2a0e:      	leal	0x8(%ebx), %edi
  4f2a11:      	fsubs	0x62c808
  4f2a17:      	fildl	(%ebx)
  4f2a19:      	movl	%ecx, 0x10(%esp)
  4f2a1d:      	leal	(%eax,%eax,2), %ecx
  4f2a20:      	xorl	%eax, %eax
  4f2a22:      	movl	%edi, 0x1c(%esp)
  4f2a26:      	fsubs	0x62c808
  4f2a2c:      	flds	0x4(%esi,%eax)
  4f2a30:      	faddl	0x632380
  4f2a36:      	flds	0xc(%esi,%eax)
  4f2a3a:      	fmul	%st(2), %st
  4f2a3c:      	flds	0x10(%esi,%eax)
  4f2a40:      	fmul	%st(4), %st
  4f2a42:      	fxch	%st(2)
  4f2a44:      	fstpl	0x48(%esp)
  4f2a48:      	fstps	0xc(%esi,%eax)
  4f2a4c:      	fstps	0x10(%esi,%eax)
  4f2a50:      	movl	0x48(%esp), %edi
  4f2a54:      	movl	%eax, 0x3d0(%esp,%eax)
  4f2a5b:      	movl	%eax, 0x100(%esp,%eax)
  4f2a62:      	movl	%edi, 0x3ec(%esp,%eax)
  4f2a69:      	addl	$0x18, %eax
  4f2a6c:      	cmpl	%edx, %edi
  4f2a6e:      	jg	0x4f2a74 <.text+0xf1a74>
  4f2a70:      	movl	%eax, %ebx
  4f2a72:      	movl	%edi, %edx
  4f2a74:      	cmpl	%ecx, %eax
  4f2a76:      	jne	0x4f2a2c <.text+0xf1a2c>
  4f2a78:      	subl	$0x18, %ebx
  4f2a7b:      	leal	-0x18(%eax), %ecx
  4f2a7e:      	flds	0x62c808
  4f2a84:      	fsubs	0x14(%esi)
  4f2a87:      	fxch	%st(2)
  4f2a89:      	fcompp
  4f2a8b:      	fmuls	0x62c810
  4f2a91:      	movl	$0x0, 0x3d0(%esp,%eax)
  4f2a9c:      	movl	%ecx, 0xe8(%esp)
  4f2aa3:      	movl	0x8(%ebp), %edi
  4f2aa6:      	movl	%ebx, 0xc0(%esp)
  4f2aad:      	faddl	0x632380
  4f2ab3:      	movl	%ebx, 0x98(%esp)
  4f2aba:      	movl	%ebx, 0xc4(%esp)
  4f2ac1:      	movl	%esi, %ebp
  4f2ac3:      	movl	0x20(%edi), %eax
  4f2ac6:      	movl	(%edi), %ecx
  4f2ac8:      	addl	%edx, %eax
  4f2aca:      	movl	0x14(%edi), %esi
  4f2acd:      	movl	0x1c(%edi), %edi
  4f2ad0:      	imull	%ecx
  4f2ad2:      	fstpl	0x38(%esp)
  4f2ad6:      	addl	%edi, %esi
  4f2ad8:      	movl	%ecx, 0xc(%esp)
  4f2adc:      	addl	%eax, %esi
  4f2ade:      	movl	0x3ec(%esp,%ebx), %edi
  4f2ae5:      	movl	%esi, 0x18(%esp)
  4f2ae9:      	movl	%ebx, 0x9c(%esp)
  4f2af0:      	movl	0xc4(%esp), %ecx
  4f2af7:      	movl	0x3ec(%esp,%ecx), %eax
  4f2afe:      	movl	%edi, 0x4(%esp)
  4f2b02:      	cmpl	%eax, %edi
  4f2b04:      	jl	0x4f2c08 <.text+0xf1c08>
  4f2b0a:      	movl	0x3e8(%esp,%ecx), %edx
  4f2b11:      	movl	%ecx, %eax
  4f2b13:      	movl	%edx, 0xc4(%esp)
  4f2b1a:      	cmpl	0x98(%esp), %edx
  4f2b21:      	je	0x4f3171 <.text+0xf2171>
  4f2b27:      	movl	0x3ec(%esp,%edx), %esi
  4f2b2e:      	movl	%edx, %ecx
  4f2b30:      	cmpl	%esi, %edi
  4f2b32:      	jge	0x4f2b0a <.text+0xf1b0a>
  4f2b34:      	flds	0x4(%ebp,%edx)
  4f2b38:      	fsubs	0x4(%ebp,%eax)
  4f2b3c:      	flds	0x10(%ebp,%edx)
  4f2b40:      	fsubs	0x10(%ebp,%eax)
  4f2b44:      	fxch	%st(1)
  4f2b46:      	fdivrs	0x62c808
  4f2b4c:      	flds	0xc(%ebp,%edx)
  4f2b50:      	fsubs	0xc(%ebp,%eax)
  4f2b54:      	fxch	%st(1)
  4f2b56:      	fmul	%st, %st(2)
  4f2b58:      	flds	0x8(%ebp,%edx)
  4f2b5c:      	fsubs	0x8(%ebp,%eax)
  4f2b60:      	fxch	%st(2)
  4f2b62:      	fmul	%st(1), %st
  4f2b64:      	flds	(%ebp,%edx)
  4f2b68:      	fsubs	(%ebp,%eax)
  4f2b6c:      	fxch	%st(3)
  4f2b6e:      	fmul	%st(2), %st
  4f2b70:      	fxch	%st(4)
  4f2b72:      	fstps	0xdc(%esp)
  4f2b79:      	flds	0x4(%ebp,%eax)
  4f2b7d:      	faddl	0x632380
  4f2b83:      	fxch	%st(3)
  4f2b85:      	fmulp	%st, %st(2)
  4f2b87:      	fstps	0xd8(%esp)
  4f2b8e:      	fxch	%st(1)
  4f2b90:      	fstpl	0x48(%esp)
  4f2b94:      	fstps	0xe0(%esp)
  4f2b9b:      	fildl	0x48(%esp)
  4f2b9f:      	fxch	%st(1)
  4f2ba1:      	fstps	0xe4(%esp)
  4f2ba8:      	fsubs	0x4(%ebp,%eax)
  4f2bac:      	flds	0xe0(%esp)
  4f2bb3:      	flds	0xe4(%esp)
  4f2bba:      	fmul	%st(2), %st
  4f2bbc:      	flds	0xd8(%esp)
  4f2bc3:      	fmul	%st(3), %st
  4f2bc5:      	fxch	%st(1)
  4f2bc7:      	fadds	0x8(%ebp,%eax)
  4f2bcb:      	flds	0xdc(%esp)
  4f2bd2:      	fmul	%st(4), %st
  4f2bd4:      	fxch	%st(2)
  4f2bd6:      	fadds	0xc(%ebp,%eax)
  4f2bda:      	fxch	%st(3)
  4f2bdc:      	fmulp	%st, %st(4)
  4f2bde:      	fstps	0xcc(%esp)
  4f2be5:      	fadds	0x10(%ebp,%eax)
  4f2be9:      	fxch	%st(2)
  4f2beb:      	fadds	(%ebp,%eax)
  4f2bef:      	fxch	%st(1)
  4f2bf1:      	fstps	0xd0(%esp)
  4f2bf8:      	fxch	%st(1)
  4f2bfa:      	fstps	0xd4(%esp)
  4f2c01:      	fstps	0xc8(%esp)
  4f2c08:      	movl	0x9c(%esp), %ecx
  4f2c0f:      	cmpl	0x3ec(%esp,%ecx), %edi
  4f2c16:      	jl	0x4f2d0b <.text+0xf1d0b>
  4f2c1c:      	movl	0xe8(%esp,%ecx), %edx
  4f2c23:      	movl	%ecx, %eax
  4f2c25:      	movl	%edx, 0x9c(%esp)
  4f2c2c:      	movl	%edx, %ecx
  4f2c2e:      	cmpl	0x3ec(%esp,%edx), %edi
  4f2c35:      	jge	0x4f2c1c <.text+0xf1c1c>
  4f2c37:      	flds	0x4(%ebp,%edx)
  4f2c3b:      	fsubs	0x4(%ebp,%eax)
  4f2c3f:      	flds	0x10(%ebp,%edx)
  4f2c43:      	fsubs	0x10(%ebp,%eax)
  4f2c47:      	fxch	%st(1)
  4f2c49:      	fdivrs	0x62c808
  4f2c4f:      	flds	0xc(%ebp,%edx)
  4f2c53:      	fsubs	0xc(%ebp,%eax)
  4f2c57:      	fxch	%st(1)
  4f2c59:      	fmul	%st, %st(2)
  4f2c5b:      	flds	0x8(%ebp,%edx)
  4f2c5f:      	fsubs	0x8(%ebp,%eax)
  4f2c63:      	fxch	%st(2)
  4f2c65:      	fmul	%st(1), %st
  4f2c67:      	flds	(%ebp,%edx)
  4f2c6b:      	fsubs	(%ebp,%eax)
  4f2c6f:      	fxch	%st(3)
  4f2c71:      	fmul	%st(2), %st
  4f2c73:      	fxch	%st(4)
  4f2c75:      	fstps	0xb4(%esp)
  4f2c7c:      	flds	0x4(%ebp,%eax)
  4f2c80:      	faddl	0x632380
  4f2c86:      	fxch	%st(3)
  4f2c88:      	fmulp	%st, %st(2)
  4f2c8a:      	fstps	0xb0(%esp)
  4f2c91:      	fxch	%st(1)
  4f2c93:      	fstpl	0x48(%esp)
  4f2c97:      	fstps	0xb8(%esp)
  4f2c9e:      	fildl	0x48(%esp)
  4f2ca2:      	fxch	%st(1)
  4f2ca4:      	fstps	0xbc(%esp)
  4f2cab:      	fsubs	0x4(%ebp,%eax)
  4f2caf:      	flds	0xb8(%esp)
  4f2cb6:      	flds	0xbc(%esp)
  4f2cbd:      	fmul	%st(2), %st
  4f2cbf:      	flds	0xb0(%esp)
  4f2cc6:      	fmul	%st(3), %st
  4f2cc8:      	fxch	%st(1)
  4f2cca:      	fadds	0x8(%ebp,%eax)
  4f2cce:      	flds	0xb4(%esp)
  4f2cd5:      	fmul	%st(4), %st
  4f2cd7:      	fxch	%st(2)
  4f2cd9:      	fadds	0xc(%ebp,%eax)
  4f2cdd:      	fxch	%st(3)
  4f2cdf:      	fmulp	%st, %st(4)
  4f2ce1:      	fstps	0xa4(%esp)
  4f2ce8:      	fadds	0x10(%ebp,%eax)
  4f2cec:      	fxch	%st(2)
  4f2cee:      	fadds	(%ebp,%eax)
  4f2cf2:      	fxch	%st(1)
  4f2cf4:      	fstps	0xa8(%esp)
  4f2cfb:      	fxch	%st(1)
  4f2cfd:      	fstps	0xac(%esp)
  4f2d04:      	fstps	0xa0(%esp)
  4f2d0b:      	flds	0xc8(%esp)
  4f2d12:      	faddl	0x632380
  4f2d18:      	flds	0xa0(%esp)
  4f2d1f:      	faddl	0x632380
  4f2d25:      	fxch	%st(1)
  4f2d27:      	fstpl	0x58(%esp)
  4f2d2b:      	fstpl	0x50(%esp)
  4f2d2f:      	movl	0x58(%esp), %edx
  4f2d33:      	movl	0x50(%esp), %ebx
  4f2d37:      	cmpl	%edx, %ebx
  4f2d39:      	je	0x4f30aa <.text+0xf20aa>
  4f2d3f:      	jl	0x4f2dde <.text+0xf1dde>
  4f2d45:      	flds	0xa0(%esp)
  4f2d4c:      	fsubs	0xc8(%esp)
  4f2d53:      	flds	0xac(%esp)
  4f2d5a:      	fsubs	0xd4(%esp)
  4f2d61:      	fxch	%st(1)
  4f2d63:      	fdivrs	0x62c808
  4f2d69:      	flds	0xa8(%esp)
  4f2d70:      	fsubs	0xd0(%esp)
  4f2d77:      	fxch	%st(2)
  4f2d79:      	fmul	%st(1), %st
  4f2d7b:      	flds	0xa4(%esp)
  4f2d82:      	fsubs	0xcc(%esp)
  4f2d89:      	fxch	%st(3)
  4f2d8b:      	fmul	%st(2), %st
  4f2d8d:      	fxch	%st(1)
  4f2d8f:      	fstps	0x24(%esp)
  4f2d93:      	fxch	%st(1)
  4f2d95:      	fmulp	%st, %st(2)
  4f2d97:      	fstps	0x20(%esp)
  4f2d9b:      	fildl	0x58(%esp)
  4f2d9f:      	fxch	%st(1)
  4f2da1:      	fstps	0x28(%esp)
  4f2da5:      	fsubs	0xc8(%esp)
  4f2dac:      	flds	0x24(%esp)
  4f2db0:      	flds	0x20(%esp)
  4f2db4:      	fmul	%st(2), %st
  4f2db6:      	flds	0x28(%esp)
  4f2dba:      	fmul	%st(3), %st
  4f2dbc:      	fxch	%st(1)
  4f2dbe:      	fadds	0xd0(%esp)
  4f2dc5:      	fxch	%st(3)
  4f2dc7:      	fmulp	%st, %st(2)
  4f2dc9:      	fadds	0xcc(%esp)
  4f2dd0:      	fxch	%st(1)
  4f2dd2:      	fadds	0xd4(%esp)
  4f2dd9:      	jmp	0x4f2e7c <.text+0xf1e7c>
  4f2dde:      	movl	%ebx, 0x58(%esp)
  4f2de2:      	movl	%edx, %ebx
  4f2de4:      	movl	0x58(%esp), %edx
  4f2de8:      	flds	0xc8(%esp)
  4f2def:      	fsubs	0xa0(%esp)
  4f2df6:      	flds	0xd4(%esp)
  4f2dfd:      	fsubs	0xac(%esp)
  4f2e04:      	fxch	%st(1)
  4f2e06:      	fdivrs	0x62c808
  4f2e0c:      	flds	0xd0(%esp)
  4f2e13:      	fsubs	0xa8(%esp)
  4f2e1a:      	fxch	%st(2)
  4f2e1c:      	fmul	%st(1), %st
  4f2e1e:      	flds	0xcc(%esp)
  4f2e25:      	fsubs	0xa4(%esp)
  4f2e2c:      	fxch	%st(3)
  4f2e2e:      	fmul	%st(2), %st
  4f2e30:      	fxch	%st(1)
  4f2e32:      	fstps	0x24(%esp)
  4f2e36:      	fxch	%st(1)
  4f2e38:      	fmulp	%st, %st(2)
  4f2e3a:      	fstps	0x20(%esp)
  4f2e3e:      	fildl	0x58(%esp)
  4f2e42:      	fxch	%st(1)
  4f2e44:      	fstps	0x28(%esp)
  4f2e48:      	fsubs	0xa0(%esp)
  4f2e4f:      	flds	0x24(%esp)
  4f2e53:      	flds	0x20(%esp)
  4f2e57:      	fmul	%st(2), %st
  4f2e59:      	flds	0x28(%esp)
  4f2e5d:      	fmul	%st(3), %st
  4f2e5f:      	fxch	%st(1)
  4f2e61:      	fadds	0xa8(%esp)
  4f2e68:      	fxch	%st(3)
  4f2e6a:      	fmulp	%st, %st(2)
  4f2e6c:      	fadds	0xa4(%esp)
  4f2e73:      	fxch	%st(1)
  4f2e75:      	fadds	0xac(%esp)
  4f2e7c:      	movl	0x18(%esp), %edi
  4f2e80:      	subl	%edx, %ebx
  4f2e82:      	addl	%edx, %edi
  4f2e84:      	flds	0x20(%esp)
  4f2e88:      	fmuls	0x62c814
  4f2e8e:      	flds	0x24(%esp)
  4f2e92:      	fmuls	0x62c814
  4f2e98:      	flds	0x28(%esp)
  4f2e9c:      	fmuls	0x62c814
  4f2ea2:      	fxch	%st(2)
  4f2ea4:      	fstps	0x2c(%esp)
  4f2ea8:      	fstps	0x30(%esp)
  4f2eac:      	fstps	0x34(%esp)
  4f2eb0:      	fxch	%st(1)
  4f2eb2:      	flds	0x62c80c
  4f2eb8:      	fdiv	%st(1), %st
  4f2eba:      	fld	%st(2)
  4f2ebc:      	fmul	%st(1), %st
  4f2ebe:      	fld	%st(4)
  4f2ec0:      	fmulp	%st, %st(2)
  4f2ec2:      	faddl	0x632380
  4f2ec8:      	fxch	%st(1)
  4f2eca:      	faddl	0x632380
  4f2ed0:      	fxch	%st(2)
  4f2ed2:      	fadds	0x34(%esp)
  4f2ed6:      	fxch	%st(1)
  4f2ed8:      	fstpl	0x68(%esp)
  4f2edc:      	fxch	%st(1)
  4f2ede:      	fstpl	0x60(%esp)
  4f2ee2:      	fxch	%st(2)
  4f2ee4:      	flds	0x62c80c
  4f2eea:      	fdiv	%st(3), %st
  4f2eec:      	decl	%ebx
  4f2eed:      	jmp	0x4f2faf <.text+0xf1faf>
  4f2ef2:      	flds	0x2c(%esp)
  4f2ef6:      	faddp	%st, %st(2)
  4f2ef8:      	flds	0x30(%esp)
  4f2efc:      	faddp	%st, %st(3)
  4f2efe:      	fld	%st(1)
  4f2f00:      	fmul	%st(1), %st
  4f2f02:      	flds	0x34(%esp)
  4f2f06:      	fxch	%st(2)
  4f2f08:      	fmul	%st(4), %st
  4f2f0a:      	fxch	%st(2)
  4f2f0c:      	faddp	%st, %st(5)
  4f2f0e:      	faddl	0x632380
  4f2f14:      	fxch	%st(1)
  4f2f16:      	faddl	0x632380
  4f2f1c:      	fld	%st(4)
  4f2f1e:      	fxch	%st(2)
  4f2f20:      	fstpl	0x70(%esp)
  4f2f24:      	fstpl	0x78(%esp)
  4f2f28:      	fdivrs	0x62c80c
  4f2f2e:      	movl	0x68(%esp), %ebp
  4f2f32:      	movl	0x60(%esp), %esi
  4f2f36:      	movl	0x78(%esp), %eax
  4f2f3a:      	movl	0x70(%esp), %edx
  4f2f3e:      	subl	%ebp, %eax
  4f2f40:      	subl	%esi, %edx
  4f2f42:      	sarl	$0x4, %eax
  4f2f45:      	movl	%ebx, 0x8(%esp)
  4f2f49:      	sarl	$0x4, %edx
  4f2f4c:      	movl	%eax, 0x88(%esp)
  4f2f53:      	movl	%edx, 0x80(%esp)
  4f2f5a:      	movl	0x38(%esp), %ebx
  4f2f5e:      	movb	(%edi), %cl
  4f2f60:      	movb	$0x10, %bl
  4f2f62:      	movl	%ebp, %eax
  4f2f64:      	movl	%esi, %edx
  4f2f66:      	sarl	$0x10, %eax
  4f2f69:      	movl	0x88(%esp), %ecx
  4f2f70:      	sarl	$0x10, %edx
  4f2f73:      	addl	%ecx, %ebp
  4f2f75:      	movl	0xcfdbd8(,%eax,4), %eax
  4f2f7c:      	movl	0x80(%esp), %ecx
  4f2f83:      	movb	(%eax,%edx), %dl
  4f2f86:      	incl	%edi
  4f2f87:      	movb	%bh, %dh
  4f2f89:      	addl	%ecx, %esi
  4f2f8b:      	movb	0xd1e480(%edx), %al
  4f2f91:      	decb	%bl
  4f2f93:      	movb	%al, -0x1(%edi)
  4f2f96:      	jne	0x4f2f62 <.text+0xf1f62>
  4f2f98:      	movl	0x8(%esp), %ebx
  4f2f9c:      	movl	0x70(%esp), %eax
  4f2fa0:      	movl	0x78(%esp), %edx
  4f2fa4:      	movl	%eax, 0x60(%esp)
  4f2fa8:      	movl	%edx, 0x68(%esp)
  4f2fac:      	subl	$0x10, %ebx
  4f2faf:      	cmpl	$0x10, %ebx
  4f2fb2:      	jge	0x4f2ef2 <.text+0xf1ef2>
  4f2fb8:      	cmpl	$0x0, %ebx
  4f2fbb:      	movl	0x68(%esp), %ebp
  4f2fbf:      	movl	0x60(%esp), %esi
  4f2fc3:      	je	0x4f3084 <.text+0xf2084>
  4f2fc9:      	fxch	%st(3)
  4f2fcb:      	fsubs	0x34(%esp)
  4f2fcf:      	flds	0x28(%esp)
  4f2fd3:      	fmuls	0x62c810(,%ebx,8)
  4f2fda:      	flds	0x20(%esp)
  4f2fde:      	fmuls	0x62c810(,%ebx,8)
  4f2fe5:      	flds	0x24(%esp)
  4f2fe9:      	fmuls	0x62c810(,%ebx,8)
  4f2ff0:      	fxch	%st(2)
  4f2ff2:      	faddp	%st, %st(3)
  4f2ff4:      	faddp	%st, %st(3)
  4f2ff6:      	faddp	%st, %st(3)
  4f2ff8:      	fdivrs	0x62c80c
  4f2ffe:      	fmul	%st, %st(1)
  4f3000:      	fildl	0x60(%esp)
  4f3004:      	fxch	%st(1)
  4f3006:      	fmul	%st(3), %st
  4f3008:      	fildl	0x68(%esp)
  4f300c:      	fxch	%st(2)
  4f300e:      	fsubrp	%st, %st(3)
  4f3010:      	fsubp	%st, %st(1)
  4f3012:      	fxch	%st(1)
  4f3014:      	fmuls	0x62c814(,%ebx,8)
  4f301b:      	fxch	%st(1)
  4f301d:      	fmuls	0x62c814(,%ebx,8)
  4f3024:      	fxch	%st(1)
  4f3026:      	faddl	0x632380
  4f302c:      	fxch	%st(1)
  4f302e:      	faddl	0x632380
  4f3034:      	fxch	%st(1)
  4f3036:      	fstl	0x80(%esp)
  4f303d:      	fxch	%st(1)
  4f303f:      	fstl	0x88(%esp)
  4f3046:      	movl	0x38(%esp), %eax
  4f304a:      	movb	(%edi), %cl
  4f304c:      	movb	%ah, %bh
  4f304e:      	movl	%ebp, %eax
  4f3050:      	movl	%esi, %edx
  4f3052:      	sarl	$0x10, %eax
  4f3055:      	movl	0x88(%esp), %ecx
  4f305c:      	sarl	$0x10, %edx
  4f305f:      	addl	%ecx, %ebp
  4f3061:      	movl	0xcfdbd8(,%eax,4), %eax
  4f3068:      	movl	0x80(%esp), %ecx
  4f306f:      	movb	(%eax,%edx), %dl
  4f3072:      	incl	%edi
  4f3073:      	movb	%bh, %dh
  4f3075:      	addl	%ecx, %esi
  4f3077:      	movb	0xd1e480(%edx), %al
  4f307d:      	decb	%bl
  4f307f:      	movb	%al, -0x1(%edi)
  4f3082:      	jne	0x4f304e <.text+0xf204e>
  4f3084:      	sarl	$0x10, %ebp
  4f3087:      	movl	0x38(%esp), %ebx
  4f308b:      	sarl	$0x10, %esi
  4f308e:      	andl	$0xff00, %ebx           # imm = 0xFF00
  4f3094:      	movl	0xcfdbd8(,%ebp,4), %eax
  4f309b:      	fcompp
  4f309d:      	movb	(%eax,%esi), %bl
  4f30a0:      	fcompp
  4f30a2:      	movb	0xd1e480(%ebx), %al
  4f30a8:      	movb	%al, (%edi)
  4f30aa:      	flds	0xa4(%esp)
  4f30b1:      	fadds	0xbc(%esp)
  4f30b8:      	flds	0xac(%esp)
  4f30bf:      	fadds	0xb4(%esp)
  4f30c6:      	flds	0xa8(%esp)
  4f30cd:      	fadds	0xb0(%esp)
  4f30d4:      	flds	0xa0(%esp)
  4f30db:      	fadds	0xb8(%esp)
  4f30e2:      	fxch	%st(3)
  4f30e4:      	fstps	0xa4(%esp)
  4f30eb:      	fstps	0xa8(%esp)
  4f30f2:      	fstps	0xac(%esp)
  4f30f9:      	fstps	0xa0(%esp)
  4f3100:      	flds	0xcc(%esp)
  4f3107:      	fadds	0xe4(%esp)
  4f310e:      	flds	0xd4(%esp)
  4f3115:      	fadds	0xdc(%esp)
  4f311c:      	flds	0xd0(%esp)
  4f3123:      	fadds	0xd8(%esp)
  4f312a:      	flds	0xc8(%esp)
  4f3131:      	fadds	0xe0(%esp)
  4f3138:      	fxch	%st(3)
  4f313a:      	fstps	0xcc(%esp)
  4f3141:      	fstps	0xd0(%esp)
  4f3148:      	fstps	0xd4(%esp)
  4f314f:      	fstps	0xc8(%esp)
  4f3156:      	movl	0x18(%esp), %esi
  4f315a:      	movl	0xc(%esp), %eax
  4f315e:      	movl	(%esp), %ebp
  4f3161:      	addl	%eax, %esi
  4f3163:      	movl	0x4(%esp), %edi
  4f3167:      	movl	%esi, 0x18(%esp)
  4f316b:      	incl	%edi
  4f316c:      	jmp	0x4f2af0 <.text+0xf1af0>
  4f3171:      	addl	$0x6e8, %esp            # imm = 0x6E8
  4f3177:      	popl	%esi
  4f3178:      	popl	%edi
  4f3179:      	popl	%ebx
  4f317a:      	popl	%ebp
  4f317b:      	retl
