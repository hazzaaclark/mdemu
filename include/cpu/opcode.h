#ifndef M68K_CPU_OPCODE_H
#define M68K_CPU_OPCODE_H

#include <cstdint>
#include <cstdlib>

#define OPCODE
static void LOOKUP_OPCODE(uint32_t CODE);


	/* Motorola's Operation Code for their 68000 series of Microprocessors */
	/* can be broken down into various instructions */
	/* B = Byte */
	/* S = Singleton */
	/* W = Word */
	/* L = Long */
	/* These instructions, on a dis-assembled level, showcase the bytesize */
	/* of each of these operations ranging from 8 bit to 32 bit integer operations */
	/* The following Operation Code enumator was sourced by http://info.sonicretro.org/SCHG:68000_ASM-to-Hex_Code_Reference */

	enum class OPERATION_CODE : uint32_t
	{
		adda_w,
		adda_l,
		adda_w,
		addi_b,
		addi_w,
		addi_l,
		addq_b,
		and_i,
		andi_b,
		andi_w,
		bra_s,
		bra_w,
		bsr_s,
		bhi_s,
		bls_s,
		bcc_s,
		bne_s,
		beq_s,
		bvc_s,
		bvs_s,
		bpl_s,
		bmi_s,
		bge_s,
		blt_s,
		bgt_s,
		ble_s,
		clr_l,
		clr_w,
		cmpi_b,
		cmpi_w,
		cmpi_l,
		dbf,
		divs_w,
		divu_w,
		eori_b,
		eori_w,
		eori_l,
		exg,
		ext_w,
		ext_l,
		illegal,
		jmp,
		jsr,
		lea,
		link,
		lsl_b,
		lsl_w,
		move_b,
		move_l,
		move_w,
		movea_w,
		moveq,
		muls_w,
		mulu_w,
		neg_w,
		neg_l,
		nop,
		not_w,
		not_l,
		ori,
		ori_b,
		ori_w,
		pea,
		rol_w,
		ror_l,
		rte,
		rtr,
		rts,
		st,
		sf,
		shi,
		sls,
		scs,
		sne,
		seq,
		svc,
		svs,
		spl,
		smi,
		sge,
		slt,
		sgt,
		sle,
		stop,
		suba_w,
		suba_l,
		subi_b,
		subi_w,
		subi_l,
		subq_b,
		swap,
		tas_b,
		trap,
		trapv,
		tst_b,
		tst_w,
		tst_l,
		unlk
	};


#endif
