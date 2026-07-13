; Entry: 004f5a3a
; Name: Gouraud_Tile_Perspective_Texture_Map_polygon
; Signature: void Gouraud_Tile_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f6405
; Reason: Exception while decompiling 004f5a3a: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f5a3a --stop-address=0x004f6405 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f5a3a:      	pushl	%ebp
  4f5a3b:      	movl	%esp, %ebp
  4f5a3d:      	pushl	%ebx
  4f5a3e:      	pushl	%esi
  4f5a3f:      	pushl	%edi
  4f5a40:      	movl	0x14(%ebp), %ebx
  4f5a43:      	pushl	%ebp
  4f5a44:      	movl	0xcfdbc0, %eax
  4f5a49:      	subl	$0x700, %esp            # imm = 0x700
  4f5a4f:      	cmpl	%ebx, %eax
  4f5a51:      	je	0x4f5ac1 <.text+0xf4ac1>
  4f5a53:      	movl	%ebx, 0xcfdbc0
  4f5a59:      	leal	0xcfdbd8, %edx
  4f5a5f:      	movl	(%ebx), %eax
  4f5a61:      	movl	0x4(%ebx), %ecx
  4f5a64:      	leal	0x8(%ebx), %esi
  4f5a67:      	movl	%ecx, 0x4(%esp)
  4f5a6b:      	movl	%eax, %edi
  4f5a6d:      	addl	$0x3, %ecx
  4f5a70:      	addl	%esi, %edi
  4f5a72:      	leal	(%esi,%eax,2), %ebx
  4f5a75:      	leal	(%eax,%eax,2), %eax
  4f5a78:      	movl	%esi, -0x4(%edx)
  4f5a7b:      	movl	%esi, -0x8(%edx)
  4f5a7e:      	movl	%esi, -0xc(%edx)
  4f5a81:      	movl	%esi, -0x10(%edx)
  4f5a84:      	movl	%esi, (%edx)
  4f5a86:      	movl	%edi, 0x4(%edx)
  4f5a89:      	movl	%ebx, 0x8(%edx)
  4f5a8c:      	addl	%eax, %esi
  4f5a8e:      	addl	%eax, %edi
  4f5a90:      	addl	%eax, %ebx
  4f5a92:      	addl	$0xc, %edx
  4f5a95:      	subl	$0x3, %ecx
  4f5a98:      	jge	0x4f5a84 <.text+0xf4a84>
  4f5a9a:      	movl	0x4(%esp), %edx
  4f5a9e:      	movl	0xcfdbd4(,%edx,4), %eax
  4f5aa5:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f5aac:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f5ab3:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f5aba:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f5ac1:      	movl	0x14(%ebp), %ebx
  4f5ac4:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f5ac9:      	movl	0xc(%ebp), %esi
  4f5acc:      	movl	0x10(%ebp), %eax
  4f5acf:      	movl	(%ebx), %ecx
  4f5ad1:      	movl	0x4(%ebx), %edi
  4f5ad4:      	decl	%ecx
  4f5ad5:      	decl	%edi
  4f5ad6:      	fildl	0x4(%ebx)
  4f5ad9:      	movl	%ecx, 0x18(%esp)
  4f5add:      	movl	%edi, 0x1c(%esp)
  4f5ae1:      	incl	%ecx
  4f5ae2:      	movl	%esi, (%esp)
  4f5ae5:      	shll	$0x3, %eax
  4f5ae8:      	leal	0x8(%ebx), %edi
  4f5aeb:      	fildl	(%ebx)
  4f5aed:      	movl	%ecx, 0x10(%esp)
  4f5af1:      	leal	(%eax,%eax,2), %ecx
  4f5af4:      	xorl	%eax, %eax
  4f5af6:      	movl	%edi, 0x24(%esp)
  4f5afa:      	flds	0x62c808
  4f5b00:      	fsubs	0x14(%esi,%eax)
  4f5b04:      	flds	0x4(%esi,%eax)
  4f5b08:      	faddl	0x632380
  4f5b0e:      	fxch	%st(1)
  4f5b10:      	flds	0xc(%esi,%eax)
  4f5b14:      	fmul	%st(3), %st
  4f5b16:      	flds	0x10(%esi,%eax)
  4f5b1a:      	fmul	%st(5), %st
  4f5b1c:      	fxch	%st(3)
  4f5b1e:      	fstpl	0x648(%esp)
  4f5b25:      	fxch	%st(1)
  4f5b27:      	fmuls	0x62c810
  4f5b2d:      	fxch	%st(2)
  4f5b2f:      	fstps	0x10(%esi,%eax)
  4f5b33:      	fstps	0xc(%esi,%eax)
  4f5b37:      	fstps	0x14(%esi,%eax)
  4f5b3b:      	movl	0x648(%esp), %edi
  4f5b42:      	movl	%eax, 0x328(%esp,%eax)
  4f5b49:      	movl	%eax, 0x58(%esp,%eax)
  4f5b4d:      	movl	%edi, 0x344(%esp,%eax)
  4f5b54:      	addl	$0x18, %eax
  4f5b57:      	cmpl	%edx, %edi
  4f5b59:      	jg	0x4f5b5f <.text+0xf4b5f>
  4f5b5b:      	movl	%eax, %ebx
  4f5b5d:      	movl	%edi, %edx
  4f5b5f:      	cmpl	%ecx, %eax
  4f5b61:      	jne	0x4f5afa <.text+0xf4afa>
  4f5b63:      	subl	$0x18, %ebx
  4f5b66:      	leal	-0x18(%eax), %ecx
  4f5b69:      	fcompp
  4f5b6b:      	movl	$0x0, 0x328(%esp,%eax)
  4f5b76:      	movl	%ecx, 0x40(%esp)
  4f5b7a:      	movl	0x8(%ebp), %edi
  4f5b7d:      	movl	%ebx, 0x6d0(%esp)
  4f5b84:      	movl	%ebx, 0x6a0(%esp)
  4f5b8b:      	movl	%ebx, 0x6d4(%esp)
  4f5b92:      	movl	%esi, %ebp
  4f5b94:      	movl	0x20(%edi), %eax
  4f5b97:      	movl	(%edi), %ecx
  4f5b99:      	addl	%edx, %eax
  4f5b9b:      	movl	0x14(%edi), %esi
  4f5b9e:      	movl	0x1c(%edi), %edi
  4f5ba1:      	imull	%ecx
  4f5ba3:      	addl	%edi, %esi
  4f5ba5:      	movl	%ecx, 0xc(%esp)
  4f5ba9:      	addl	%eax, %esi
  4f5bab:      	movl	0x344(%esp,%ebx), %edi
  4f5bb2:      	movl	%esi, 0x20(%esp)
  4f5bb6:      	movl	%ebx, 0x6a4(%esp)
  4f5bbd:      	movl	0x6d4(%esp), %ecx
  4f5bc4:      	movl	0x344(%esp,%ecx), %eax
  4f5bcb:      	movl	%edi, 0x4(%esp)
  4f5bcf:      	cmpl	%eax, %edi
  4f5bd1:      	jl	0x4f5d00 <.text+0xf4d00>
  4f5bd7:      	movl	0x340(%esp,%ecx), %edx
  4f5bde:      	movl	%ecx, %eax
  4f5be0:      	movl	%edx, 0x6d4(%esp)
  4f5be7:      	cmpl	0x6a0(%esp), %edx
  4f5bee:      	je	0x4f63f9 <.text+0xf53f9>
  4f5bf4:      	movl	0x344(%esp,%edx), %esi
  4f5bfb:      	movl	%edx, %ecx
  4f5bfd:      	cmpl	%esi, %edi
  4f5bff:      	jge	0x4f5bd7 <.text+0xf4bd7>
  4f5c01:      	flds	0x14(%ebp,%edx)
  4f5c05:      	fsubs	0x14(%ebp,%eax)
  4f5c09:      	flds	0x4(%ebp,%edx)
  4f5c0d:      	fsubs	0x4(%ebp,%eax)
  4f5c11:      	flds	0x10(%ebp,%edx)
  4f5c15:      	fsubs	0x10(%ebp,%eax)
  4f5c19:      	fxch	%st(1)
  4f5c1b:      	fdivrs	0x62c808
  4f5c21:      	flds	0xc(%ebp,%edx)
  4f5c25:      	fsubs	0xc(%ebp,%eax)
  4f5c29:      	fxch	%st(1)
  4f5c2b:      	fmul	%st, %st(2)
  4f5c2d:      	flds	0x8(%ebp,%edx)
  4f5c31:      	fsubs	0x8(%ebp,%eax)
  4f5c35:      	fxch	%st(2)
  4f5c37:      	fmul	%st(1), %st
  4f5c39:      	flds	(%ebp,%edx)
  4f5c3d:      	fsubs	(%ebp,%eax)
  4f5c41:      	fxch	%st(3)
  4f5c43:      	fmul	%st(2), %st
  4f5c45:      	fxch	%st(4)
  4f5c47:      	fstps	0x6f0(%esp)
  4f5c4e:      	fstps	0x6ec(%esp)
  4f5c55:      	fmul	%st, %st(3)
  4f5c57:      	flds	0x4(%ebp,%eax)
  4f5c5b:      	faddl	0x632380
  4f5c61:      	fxch	%st(2)
  4f5c63:      	fmulp	%st, %st(1)
  4f5c65:      	fxch	%st(3)
  4f5c67:      	fstps	0x6fc(%esp)
  4f5c6e:      	fstpl	0x648(%esp)
  4f5c75:      	fstps	0x6f8(%esp)
  4f5c7c:      	fildl	0x648(%esp)
  4f5c83:      	fxch	%st(1)
  4f5c85:      	fstps	0x6f4(%esp)
  4f5c8c:      	fsubs	0x4(%ebp,%eax)
  4f5c90:      	flds	0x6f4(%esp)
  4f5c97:      	flds	0x6f8(%esp)
  4f5c9e:      	fmul	%st(2), %st
  4f5ca0:      	flds	0x6ec(%esp)
  4f5ca7:      	fmul	%st(3), %st
  4f5ca9:      	flds	0x6fc(%esp)
  4f5cb0:      	fmul	%st(4), %st
  4f5cb2:      	fxch	%st(2)
  4f5cb4:      	fadds	0x8(%ebp,%eax)
  4f5cb8:      	flds	0x6f0(%esp)
  4f5cbf:      	fmul	%st(5), %st
  4f5cc1:      	fxch	%st(2)
  4f5cc3:      	fadds	0xc(%ebp,%eax)
  4f5cc7:      	fxch	%st(4)
  4f5cc9:      	fmulp	%st, %st(5)
  4f5ccb:      	fstps	0x6dc(%esp)
  4f5cd2:      	fadds	0x10(%ebp,%eax)
  4f5cd6:      	fxch	%st(3)
  4f5cd8:      	fadds	(%ebp,%eax)
  4f5cdc:      	fxch	%st(2)
  4f5cde:      	fstps	0x6e0(%esp)
  4f5ce5:      	fadds	0x14(%ebp,%eax)
  4f5ce9:      	fxch	%st(2)
  4f5ceb:      	fstps	0x6e4(%esp)
  4f5cf2:      	fstps	0x6d8(%esp)
  4f5cf9:      	fstps	0x6e8(%esp)
  4f5d00:      	movl	0x6a4(%esp), %ecx
  4f5d07:      	cmpl	0x344(%esp,%ecx), %edi
  4f5d0e:      	jl	0x4f5e2b <.text+0xf4e2b>
  4f5d14:      	movl	0x40(%esp,%ecx), %edx
  4f5d18:      	movl	%ecx, %eax
  4f5d1a:      	movl	%edx, 0x6a4(%esp)
  4f5d21:      	movl	%edx, %ecx
  4f5d23:      	cmpl	0x344(%esp,%edx), %edi
  4f5d2a:      	jge	0x4f5d14 <.text+0xf4d14>
  4f5d2c:      	flds	0x14(%ebp,%edx)
  4f5d30:      	fsubs	0x14(%ebp,%eax)
  4f5d34:      	flds	0x4(%ebp,%edx)
  4f5d38:      	fsubs	0x4(%ebp,%eax)
  4f5d3c:      	flds	0x10(%ebp,%edx)
  4f5d40:      	fsubs	0x10(%ebp,%eax)
  4f5d44:      	fxch	%st(1)
  4f5d46:      	fdivrs	0x62c808
  4f5d4c:      	flds	0xc(%ebp,%edx)
  4f5d50:      	fsubs	0xc(%ebp,%eax)
  4f5d54:      	fxch	%st(1)
  4f5d56:      	fmul	%st, %st(2)
  4f5d58:      	flds	0x8(%ebp,%edx)
  4f5d5c:      	fsubs	0x8(%ebp,%eax)
  4f5d60:      	fxch	%st(2)
  4f5d62:      	fmul	%st(1), %st
  4f5d64:      	flds	(%ebp,%edx)
  4f5d68:      	fsubs	(%ebp,%eax)
  4f5d6c:      	fxch	%st(3)
  4f5d6e:      	fmul	%st(2), %st
  4f5d70:      	fxch	%st(4)
  4f5d72:      	fstps	0x6c0(%esp)
  4f5d79:      	fstps	0x6bc(%esp)
  4f5d80:      	fmul	%st, %st(3)
  4f5d82:      	flds	0x4(%ebp,%eax)
  4f5d86:      	faddl	0x632380
  4f5d8c:      	fxch	%st(2)
  4f5d8e:      	fmulp	%st, %st(1)
  4f5d90:      	fxch	%st(3)
  4f5d92:      	fstps	0x6cc(%esp)
  4f5d99:      	fstpl	0x648(%esp)
  4f5da0:      	fstps	0x6c8(%esp)
  4f5da7:      	fildl	0x648(%esp)
  4f5dae:      	fxch	%st(1)
  4f5db0:      	fstps	0x6c4(%esp)
  4f5db7:      	fsubs	0x4(%ebp,%eax)
  4f5dbb:      	flds	0x6c4(%esp)
  4f5dc2:      	flds	0x6c8(%esp)
  4f5dc9:      	fmul	%st(2), %st
  4f5dcb:      	flds	0x6bc(%esp)
  4f5dd2:      	fmul	%st(3), %st
  4f5dd4:      	flds	0x6cc(%esp)
  4f5ddb:      	fmul	%st(4), %st
  4f5ddd:      	fxch	%st(2)
  4f5ddf:      	fadds	0x8(%ebp,%eax)
  4f5de3:      	flds	0x6c0(%esp)
  4f5dea:      	fmul	%st(5), %st
  4f5dec:      	fxch	%st(2)
  4f5dee:      	fadds	0xc(%ebp,%eax)
  4f5df2:      	fxch	%st(4)
  4f5df4:      	fmulp	%st, %st(5)
  4f5df6:      	fstps	0x6ac(%esp)
  4f5dfd:      	fadds	0x10(%ebp,%eax)
  4f5e01:      	fxch	%st(3)
  4f5e03:      	fadds	(%ebp,%eax)
  4f5e07:      	fxch	%st(2)
  4f5e09:      	fstps	0x6b0(%esp)
  4f5e10:      	fadds	0x14(%ebp,%eax)
  4f5e14:      	fxch	%st(2)
  4f5e16:      	fstps	0x6b4(%esp)
  4f5e1d:      	fstps	0x6a8(%esp)
  4f5e24:      	fstps	0x6b8(%esp)
  4f5e2b:      	flds	0x6d8(%esp)
  4f5e32:      	faddl	0x632380
  4f5e38:      	flds	0x6a8(%esp)
  4f5e3f:      	faddl	0x632380
  4f5e45:      	fxch	%st(1)
  4f5e47:      	fstpl	0x658(%esp)
  4f5e4e:      	fstpl	0x650(%esp)
  4f5e55:      	movl	0x658(%esp), %edx
  4f5e5c:      	movl	0x650(%esp), %ebx
  4f5e63:      	cmpl	%edx, %ebx
  4f5e65:      	je	0x4f6308 <.text+0xf5308>
  4f5e6b:      	jl	0x4f5f50 <.text+0xf4f50>
  4f5e71:      	flds	0x6b8(%esp)
  4f5e78:      	fsubs	0x6e8(%esp)
  4f5e7f:      	flds	0x6a8(%esp)
  4f5e86:      	fsubs	0x6d8(%esp)
  4f5e8d:      	flds	0x6b4(%esp)
  4f5e94:      	fsubs	0x6e4(%esp)
  4f5e9b:      	fxch	%st(1)
  4f5e9d:      	fdivrs	0x62c808
  4f5ea3:      	flds	0x6b0(%esp)
  4f5eaa:      	fsubs	0x6e0(%esp)
  4f5eb1:      	fxch	%st(2)
  4f5eb3:      	fmul	%st(1), %st
  4f5eb5:      	flds	0x6ac(%esp)
  4f5ebc:      	fsubs	0x6dc(%esp)
  4f5ec3:      	fxch	%st(3)
  4f5ec5:      	fmul	%st(2), %st
  4f5ec7:      	fxch	%st(1)
  4f5ec9:      	fstps	0x2c(%esp)
  4f5ecd:      	fxch	%st(1)
  4f5ecf:      	fmul	%st, %st(2)
  4f5ed1:      	fxch	%st(1)
  4f5ed3:      	fstps	0x28(%esp)
  4f5ed7:      	fmulp	%st, %st(2)
  4f5ed9:      	fildl	0x658(%esp)
  4f5ee0:      	fxch	%st(1)
  4f5ee2:      	fstps	0x30(%esp)
  4f5ee6:      	fsubs	0x6d8(%esp)
  4f5eed:      	fld	%st(1)
  4f5eef:      	faddl	0x632380
  4f5ef5:      	fxch	%st(2)
  4f5ef7:      	fmul	%st(1), %st
  4f5ef9:      	flds	0x2c(%esp)
  4f5efd:      	fxch	%st(3)
  4f5eff:      	fstpl	0x698(%esp)
  4f5f06:      	fadds	0x6e8(%esp)
  4f5f0d:      	fxch	%st(2)
  4f5f0f:      	flds	0x28(%esp)
  4f5f13:      	fmul	%st(2), %st
  4f5f15:      	fxch	%st(3)
  4f5f17:      	faddl	0x632380
  4f5f1d:      	fxch	%st(3)
  4f5f1f:      	flds	0x30(%esp)
  4f5f23:      	fmul	%st(3), %st
  4f5f25:      	fxch	%st(4)
  4f5f27:      	fstpl	0x680(%esp)
  4f5f2e:      	fadds	0x6e0(%esp)
  4f5f35:      	fxch	%st(2)
  4f5f37:      	fmulp	%st, %st(1)
  4f5f39:      	fxch	%st(2)
  4f5f3b:      	fadds	0x6dc(%esp)
  4f5f42:      	fxch	%st(2)
  4f5f44:      	fadds	0x6e4(%esp)
  4f5f4b:      	jmp	0x4f603a <.text+0xf503a>
  4f5f50:      	movl	%ebx, 0x658(%esp)
  4f5f57:      	movl	%edx, %ebx
  4f5f59:      	movl	0x658(%esp), %edx
  4f5f60:      	flds	0x6e8(%esp)
  4f5f67:      	fsubs	0x6b8(%esp)
  4f5f6e:      	flds	0x6d8(%esp)
  4f5f75:      	fsubs	0x6a8(%esp)
  4f5f7c:      	flds	0x6e4(%esp)
  4f5f83:      	fsubs	0x6b4(%esp)
  4f5f8a:      	fxch	%st(1)
  4f5f8c:      	fdivrs	0x62c808
  4f5f92:      	flds	0x6e0(%esp)
  4f5f99:      	fsubs	0x6b0(%esp)
  4f5fa0:      	fxch	%st(2)
  4f5fa2:      	fmul	%st(1), %st
  4f5fa4:      	flds	0x6dc(%esp)
  4f5fab:      	fsubs	0x6ac(%esp)
  4f5fb2:      	fxch	%st(3)
  4f5fb4:      	fmul	%st(2), %st
  4f5fb6:      	fxch	%st(1)
  4f5fb8:      	fstps	0x2c(%esp)
  4f5fbc:      	fxch	%st(1)
  4f5fbe:      	fmul	%st, %st(2)
  4f5fc0:      	fxch	%st(1)
  4f5fc2:      	fstps	0x28(%esp)
  4f5fc6:      	fmulp	%st, %st(2)
  4f5fc8:      	fildl	0x658(%esp)
  4f5fcf:      	fxch	%st(1)
  4f5fd1:      	fstps	0x30(%esp)
  4f5fd5:      	fsubs	0x6a8(%esp)
  4f5fdc:      	fld	%st(1)
  4f5fde:      	faddl	0x632380
  4f5fe4:      	fxch	%st(2)
  4f5fe6:      	fmul	%st(1), %st
  4f5fe8:      	flds	0x2c(%esp)
  4f5fec:      	fxch	%st(3)
  4f5fee:      	fstpl	0x698(%esp)
  4f5ff5:      	fadds	0x6b8(%esp)
  4f5ffc:      	fxch	%st(2)
  4f5ffe:      	flds	0x28(%esp)
  4f6002:      	fmul	%st(2), %st
  4f6004:      	fxch	%st(3)
  4f6006:      	faddl	0x632380
  4f600c:      	fxch	%st(3)
  4f600e:      	flds	0x30(%esp)
  4f6012:      	fmul	%st(3), %st
  4f6014:      	fxch	%st(4)
  4f6016:      	fstpl	0x680(%esp)
  4f601d:      	fadds	0x6b0(%esp)
  4f6024:      	fxch	%st(2)
  4f6026:      	fmulp	%st, %st(1)
  4f6028:      	fxch	%st(2)
  4f602a:      	fadds	0x6ac(%esp)
  4f6031:      	fxch	%st(2)
  4f6033:      	fadds	0x6b4(%esp)
  4f603a:      	movl	0x698(%esp), %eax
  4f6041:      	movl	0x20(%esp), %edi
  4f6045:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f604a:      	subl	%edx, %ebx
  4f604c:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4f6051:      	addl	%edx, %edi
  4f6053:      	movl	%eax, 0x698(%esp)
  4f605a:      	flds	0x28(%esp)
  4f605e:      	fmuls	0x62c814
  4f6064:      	flds	0x2c(%esp)
  4f6068:      	fmuls	0x62c814
  4f606e:      	flds	0x30(%esp)
  4f6072:      	fmuls	0x62c814
  4f6078:      	fxch	%st(2)
  4f607a:      	fstps	0x34(%esp)
  4f607e:      	fstps	0x38(%esp)
  4f6082:      	fstps	0x3c(%esp)
  4f6086:      	fxch	%st(2)
  4f6088:      	flds	0x62c80c
  4f608e:      	fdiv	%st(1), %st
  4f6090:      	fld	%st(3)
  4f6092:      	fmul	%st(1), %st
  4f6094:      	fld	%st(3)
  4f6096:      	fmulp	%st, %st(2)
  4f6098:      	faddl	0x632380
  4f609e:      	fxch	%st(1)
  4f60a0:      	faddl	0x632380
  4f60a6:      	fxch	%st(2)
  4f60a8:      	fadds	0x3c(%esp)
  4f60ac:      	fxch	%st(1)
  4f60ae:      	fstpl	0x668(%esp)
  4f60b5:      	fxch	%st(1)
  4f60b7:      	fstpl	0x660(%esp)
  4f60be:      	flds	0x62c80c
  4f60c4:      	fdiv	%st(1), %st
  4f60c6:      	decl	%ebx
  4f60c7:      	jmp	0x4f61d4 <.text+0xf51d4>
  4f60cc:      	flds	0x34(%esp)
  4f60d0:      	faddp	%st, %st(3)
  4f60d2:      	flds	0x38(%esp)
  4f60d6:      	faddp	%st, %st(4)
  4f60d8:      	fld	%st(2)
  4f60da:      	fmul	%st(1), %st
  4f60dc:      	flds	0x3c(%esp)
  4f60e0:      	fxch	%st(2)
  4f60e2:      	fmul	%st(5), %st
  4f60e4:      	fxch	%st(2)
  4f60e6:      	faddp	%st, %st(3)
  4f60e8:      	faddl	0x632380
  4f60ee:      	fxch	%st(1)
  4f60f0:      	faddl	0x632380
  4f60f6:      	fld	%st(2)
  4f60f8:      	fxch	%st(2)
  4f60fa:      	fstpl	0x670(%esp)
  4f6101:      	fstpl	0x678(%esp)
  4f6108:      	fdivrs	0x62c80c
  4f610e:      	movl	0x668(%esp), %ebp
  4f6115:      	movl	0x660(%esp), %esi
  4f611c:      	movl	0x678(%esp), %eax
  4f6123:      	movl	0x670(%esp), %edx
  4f612a:      	subl	%ebp, %eax
  4f612c:      	subl	%esi, %edx
  4f612e:      	sarl	$0x4, %eax
  4f6131:      	movl	%ebx, 0x8(%esp)
  4f6135:      	sarl	$0x4, %edx
  4f6138:      	movl	0x680(%esp), %ebx
  4f613f:      	movl	%edx, 0x688(%esp)
  4f6146:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4f614c:      	movl	%eax, 0x690(%esp)
  4f6153:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4f6159:      	movb	(%edi), %dl
  4f615b:      	movl	%ebp, %eax
  4f615d:      	movl	0x690(%esp), %ecx
  4f6164:      	sarl	$0x10, %eax
  4f6167:      	movl	0x1c(%esp), %edx
  4f616b:      	addl	%ecx, %ebp
  4f616d:      	andl	%edx, %eax
  4f616f:      	movl	0x688(%esp), %ecx
  4f6176:      	movl	%esi, %edx
  4f6178:      	addl	%ecx, %esi
  4f617a:      	movl	0x18(%esp), %ecx
  4f617e:      	sarl	$0x10, %edx
  4f6181:      	movl	0xcfdbd8(,%eax,4), %eax
  4f6188:      	andl	%ecx, %edx
  4f618a:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f6190:      	movl	0x698(%esp), %ecx
  4f6197:      	movb	(%eax,%edx), %dl
  4f619a:      	incl	%edi
  4f619b:      	movb	%bh, %dh
  4f619d:      	movb	0xd1e480(%edx), %al
  4f61a3:      	addl	%ecx, %ebx
  4f61a5:      	movb	%al, -0x1(%edi)
  4f61a8:      	jge	0x4f615b <.text+0xf515b>
  4f61aa:      	movl	%ebx, 0x680(%esp)
  4f61b1:      	movl	0x8(%esp), %ebx
  4f61b5:      	movl	0x670(%esp), %eax
  4f61bc:      	movl	0x678(%esp), %edx
  4f61c3:      	movl	%eax, 0x660(%esp)
  4f61ca:      	movl	%edx, 0x668(%esp)
  4f61d1:      	subl	$0x10, %ebx
  4f61d4:      	cmpl	$0x10, %ebx
  4f61d7:      	jge	0x4f60cc <.text+0xf50cc>
  4f61dd:      	movl	0x680(%esp), %eax
  4f61e4:      	movl	%ebx, %ecx
  4f61e6:      	decl	%ebx
  4f61e7:      	movl	0x668(%esp), %ebp
  4f61ee:      	shll	$0x11, %ebx
  4f61f1:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f61f6:      	movl	0x660(%esp), %esi
  4f61fd:      	orl	%eax, %ebx
  4f61ff:      	cmpl	$0x0, %ecx
  4f6202:      	je	0x4f62dc <.text+0xf52dc>
  4f6208:      	fxch	%st(1)
  4f620a:      	fsubs	0x3c(%esp)
  4f620e:      	flds	0x30(%esp)
  4f6212:      	fmuls	0x62c810(,%ecx,8)
  4f6219:      	flds	0x28(%esp)
  4f621d:      	fmuls	0x62c810(,%ecx,8)
  4f6224:      	flds	0x2c(%esp)
  4f6228:      	fmuls	0x62c810(,%ecx,8)
  4f622f:      	fxch	%st(2)
  4f6231:      	faddp	%st, %st(3)
  4f6233:      	faddp	%st, %st(4)
  4f6235:      	faddp	%st, %st(4)
  4f6237:      	fdivrs	0x62c80c
  4f623d:      	fmul	%st, %st(2)
  4f623f:      	fildl	0x660(%esp)
  4f6246:      	fxch	%st(1)
  4f6248:      	fmul	%st(4), %st
  4f624a:      	fildl	0x668(%esp)
  4f6251:      	fxch	%st(2)
  4f6253:      	fsubrp	%st, %st(4)
  4f6255:      	fsubp	%st, %st(1)
  4f6257:      	fxch	%st(2)
  4f6259:      	fmuls	0x62c814(,%ecx,8)
  4f6260:      	fxch	%st(2)
  4f6262:      	fmuls	0x62c814(,%ecx,8)
  4f6269:      	fxch	%st(2)
  4f626b:      	faddl	0x632380
  4f6271:      	fxch	%st(2)
  4f6273:      	faddl	0x632380
  4f6279:      	fxch	%st(2)
  4f627b:      	fstl	0x688(%esp)
  4f6282:      	fxch	%st(2)
  4f6284:      	fstl	0x690(%esp)
  4f628b:      	movb	(%edi), %dl
  4f628d:      	movl	%ebp, %eax
  4f628f:      	movl	0x690(%esp), %ecx
  4f6296:      	sarl	$0x10, %eax
  4f6299:      	movl	0x1c(%esp), %edx
  4f629d:      	addl	%ecx, %ebp
  4f629f:      	andl	%edx, %eax
  4f62a1:      	movl	0x688(%esp), %ecx
  4f62a8:      	movl	%esi, %edx
  4f62aa:      	addl	%ecx, %esi
  4f62ac:      	movl	0x18(%esp), %ecx
  4f62b0:      	sarl	$0x10, %edx
  4f62b3:      	movl	0xcfdbd8(,%eax,4), %eax
  4f62ba:      	andl	%ecx, %edx
  4f62bc:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f62c2:      	movl	0x698(%esp), %ecx
  4f62c9:      	movb	(%eax,%edx), %dl
  4f62cc:      	incl	%edi
  4f62cd:      	movb	%bh, %dh
  4f62cf:      	movb	0xd1e480(%edx), %al
  4f62d5:      	addl	%ecx, %ebx
  4f62d7:      	movb	%al, -0x1(%edi)
  4f62da:      	jge	0x4f628d <.text+0xf528d>
  4f62dc:      	sarl	$0x10, %ebp
  4f62df:      	movl	0x1c(%esp), %ecx
  4f62e3:      	xorl	%edx, %edx
  4f62e5:      	andl	%ecx, %ebp
  4f62e7:      	sarl	$0x10, %esi
  4f62ea:      	movl	0x18(%esp), %eax
  4f62ee:      	movb	%bh, %dh
  4f62f0:      	andl	%eax, %esi
  4f62f2:      	movl	0xcfdbd8(,%ebp,4), %eax
  4f62f9:      	fcompp
  4f62fb:      	movb	(%eax,%esi), %dl
  4f62fe:      	fcompp
  4f6300:      	movb	0xd1e480(%edx), %al
  4f6306:      	movb	%al, (%edi)
  4f6308:      	flds	0x6b8(%esp)
  4f630f:      	fadds	0x6cc(%esp)
  4f6316:      	flds	0x6ac(%esp)
  4f631d:      	fadds	0x6c8(%esp)
  4f6324:      	flds	0x6b4(%esp)
  4f632b:      	fadds	0x6c0(%esp)
  4f6332:      	flds	0x6b0(%esp)
  4f6339:      	fadds	0x6bc(%esp)
  4f6340:      	flds	0x6a8(%esp)
  4f6347:      	fadds	0x6c4(%esp)
  4f634e:      	fxch	%st(3)
  4f6350:      	fstps	0x6ac(%esp)
  4f6357:      	fstps	0x6b0(%esp)
  4f635e:      	fstps	0x6b4(%esp)
  4f6365:      	fstps	0x6a8(%esp)
  4f636c:      	fstps	0x6b8(%esp)
  4f6373:      	flds	0x6e8(%esp)
  4f637a:      	fadds	0x6fc(%esp)
  4f6381:      	flds	0x6dc(%esp)
  4f6388:      	fadds	0x6f8(%esp)
  4f638f:      	flds	0x6e4(%esp)
  4f6396:      	fadds	0x6f0(%esp)
  4f639d:      	flds	0x6e0(%esp)
  4f63a4:      	fadds	0x6ec(%esp)
  4f63ab:      	flds	0x6d8(%esp)
  4f63b2:      	fadds	0x6f4(%esp)
  4f63b9:      	fxch	%st(3)
  4f63bb:      	fstps	0x6dc(%esp)
  4f63c2:      	fstps	0x6e0(%esp)
  4f63c9:      	fstps	0x6e4(%esp)
  4f63d0:      	fstps	0x6d8(%esp)
  4f63d7:      	fstps	0x6e8(%esp)
  4f63de:      	movl	0x20(%esp), %esi
  4f63e2:      	movl	0xc(%esp), %eax
  4f63e6:      	movl	(%esp), %ebp
  4f63e9:      	addl	%eax, %esi
  4f63eb:      	movl	0x4(%esp), %edi
  4f63ef:      	movl	%esi, 0x20(%esp)
  4f63f3:      	incl	%edi
  4f63f4:      	jmp	0x4f5bbd <.text+0xf4bbd>
  4f63f9:      	addl	$0x700, %esp            # imm = 0x700
  4f63ff:      	popl	%ebp
  4f6400:      	popl	%edi
  4f6401:      	popl	%esi
  4f6402:      	popl	%ebx
  4f6403:      	popl	%ebp
  4f6404:      	retl
