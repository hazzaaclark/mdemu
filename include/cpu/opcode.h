#ifndef M68K_CPU_OPCODE_H
#define M68K_CPU_OPCODE_H

#include <cstdint>
#include <cstdlib>

class OPCODE
{
	/* Motorola's Operation Code for their 68000 series of Microprocessors */
	/* can be broken down into various instructions */
	/* B = Byte */
	/* S = Sequence */
	/* W = Word */
	/* L = Long */
	/* These instructions, on a dis-assembled level, showcase the bytesize */
	/* of each of these operations ranging from 8 bit to 32 bit integer operations */

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


	};
};

#endif