	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0"
	.file	"output"
	.globl	f                               # -- Begin function f
	.p2align	2
	.type	f,@function
f:                                      # @f
	.cfi_startproc
# %bb.0:                                # %entry_f
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	li	a0, 1
	sw	a0, 12(sp)
	sw	a0, 8(sp)
	li	a0, 2
	sw	a0, 4(sp)
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	f, .Lfunc_end0-f
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
