#ifndef TIFMC_H
#define TIFMC_H

//#include <linux/types.h>

#define PCI_DEVICE_ID_TI_FMC		0x8033

#define TI_FMC_REG_VENDOR_ID		0x00 /* 16 bit */
#define TI_FMC_REG_DEVICE_ID		0x02 /* 16 bit */
#define TI_FMC_REG_COMMAND		0x04 /* 16 bit */
#define TI_FMC_REG_STATUS		0x06 /* 16 bit */
#define TI_FMC_REG_REVISION_ID		0x08 /* 8 bit */
#define TI_FMC_REG_CLASS_CODE		0x09 /* 24 bit */
#define TI_FMC_REG_CACHE_LINE_SIZE	0x0C /* 8 bit */
#define TI_FMC_REG_LATENCY_TIMER	0x0D /* 8 bit */
#define TI_FMC_REG_HEADER_TYPE		0x0E /* 8 bit */
#define TI_FMC_REG_BIST			0x0F /* 8 bit */
#define TI_FMC_REG_BASE_ADDRESS		0x10 /* 32 bit */
#define TI_FMC_REG_SUBSYSTEM_VENDOR_ID	0x2C /* 16 bit */
#define TI_FMC_REG_SUBSYSTEM_ID		0x2E /* 16 bit */
#define TI_FMC_REG_PM_CAP_PTR		0x34 /* 8 bit */
#define TI_FMC_REG_INT_LINE		0x3C /* 8 bit */
#define TI_FMC_REG_INT_PIN		0x3D /* 8 bit */
#define TI_FMC_REG_MIN_GRANT		0x3E /* 8 bit */
#define TI_FMC_REG_MAX_LATENCY		0x3F /* 8 bit */
#define TI_FMC_REG_CAP_ID		0x44 /* 8 bit */
#define TI_FMC_REG_NEXT_ITEM_PTR	0x45 /* 8 bit */
#define TI_FMC_REG_POWER_MAN_CAP	0x46 /* 16 bit */
#define TI_FMC_REG_POWER_MAN_CTRL	0x48 /* 16 bit */
#define TI_FMC_REG_PMCSR_BSE		0x4A /* 8 bit */
#define TI_FMC_REG_PM_DATA		0x4B /* 8 bit */
#define TI_FMC_REG_GENERAL_CTRL		0x4C /* 16 bit */
#define TI_FMC_REG_DIAGNOSTIC		0x54 /* 32 bit */

/* Command Register - 16 bits */
/* RESERVED - bits 15-11 */
#define TI_FMC_CR_INT_DISABLE		0x0400 /* bit 10 */
#define TI_FMC_CR_FBB_ENB		0x0200 /* bit 9 */
#define TI_FMC_CR_SERR_ENB		0x0100 /* bit 8 */
#define TI_FMC_CR_STEP_ENB		0x0080 /* bit 7 */
#define TI_FMC_CR_PERR_ENB		0x0040 /* bit 6 */
#define TI_FMC_CR_VGA_ENB		0x0020 /* bit 5 */
#define TI_FMC_CR_MWI_ENB		0x0010 /* bit 4 */
#define TI_FMC_CR_SPECIAL		0x0008 /* bit 3 */
#define TI_FMC_CR_MASTER_ENB		0x0004 /* bit 2 */
#define TI_FMC_CR_MEMORY_ENB		0x0002 /* bit 1 */
#define TI_FMC_CR_IO_ENB		0x0001 /* bit 0 */

/* Status Register - 16 bits */
#define TI_FMC_SR_PAR_ERR		0x8000 /* bit 15 */
#define TI_FMC_SR_SYS_ERR		0x4000 /* bit 14 */
#define TI_FMC_SR_MABORT		0x2000 /* bit 13 */
#define TI_FMC_SR_TABORT_REC		0x1000 /* bit 12 */
#define TI_FMC_SR_TABORT_SIG		0x0800 /* bit 11 */
#define TI_FMC_SR_PCI_SPEED		0x0600 /* bit 10-9 */
#define TI_FMC_SR_DATAPAR		0x0100 /* bit 8 */
#define TI_FMC_SR_FBB_CAP		0x0080 /* bit 7 */
#define TI_FMC_SR_UDF			0x0040 /* bit 6 */
#define TI_FMC_SR_66MHZ			0x0020 /* bit 5 */
#define TI_FMC_SR_CAPLIST		0x0010 /* bit 4 */
#define TI_FMC_SR_INT_STATUS		0x0008 /* bit 3 */
/* RESERVED - bits 2-0 */

/* Power Management Capabilities Register - 16 bits */
#define TI_FMC_PMCAPR_PME_D3COLD	0x8000 /* bit 15 */
#define TI_FMC_PMCAPR_PME_SUPPORT	0x7800 /* bit 14-11 */
#define TI_FMC_PMCAPR_D2_SUPPORT	0x0400 /* bit 10 */
#define TI_FMC_PMCAPR_D1_SUPPORT	0x0200 /* bit 9 */
#define TI_FMC_PMCAPR_AUX_CURRENT	0x01C0 /* bit 8-6 */
#define TI_FMC_PMCAPR_DSI		0x0020 /* bit 5 */
/* RESERVED - bit 4 */
#define TI_FMC_PMCAPR_PME_CLK		0x0008 /* bit 3 */
#define TI_FMC_PMCAPR_PM_VERSION	0x0007 /* bit 2-0 */

/* Power Management Control and Status Register - 16 bits */
#define TI_FMC_PMCSR_PME_STAT		0x8000 /* bit 15 */
#define TI_FMC_PMCSR_DATA_SCALE		0x6000 /* bit 14-13 */
#define TI_FMC_PMCSR_DATA_SELECT	0x1E00 /* bit 12-9 */
#define TI_FMC_PMCSR_PME_EN		0x0100 /* bit 8 */
/* RESERVED - bit 7-2 */
#define TI_FMC_PMCSR_PWR_STATE		0x0003 /* bit 1-0 */

/* General Control Register - 8 bits */
/* RESERVED - bit 7 */
#define TI_FMC_GCR_INT_SEL		0x0060 /* bit 6-5 */
#define TI_FMC_GCR_D3_COLD		0x0010 /* bit 4 */
/* RESERVED - bit 3 */
#define TI_FMC_GCR_SM_DIS		0x0004 /* bit 2 */
#define TI_FMC_GCR_MMC_SD_DIS		0x0002 /* bit 1 */
#define TI_FMC_GCR_MS_DIS		0x0001 /* bit 0 */

/* Diagnostic Register  - 32 bits */
#define TI_FMC_DR_TBD_CTRL		0xFFFE0000 /* bit 31-17 */
#define TI_FMC_DR_DIAGNOSTIC		0x00010000 /* bit 16 */
/* RESERVED - bit 15-11 */
#define TI_FMC_DR_PLL_N			0x00000700 /* bit 10-8 */
/* RESERVED - bit 7-5 */
#define TI_FMC_DR_PLL_M			0x0000001F /* bit 4-0 */

#define TI_FMC_HEAD_DEVICE_ID		0x00000002

#define TI_FMC_HEAD_OFFSET1		0x00000013
#define TI_FMC_HEAD_OFFSET1_EMPTY	0x00000004
#define TI_FMC_HEAD_OFFSET1_MMC		0x0000000c

#define TI_FMC_HEAD_OFFSET2		0x0000001b
#define TI_FMC_HEAD_OFFSET2_EMPTY	0x00000000
#define TI_FMC_HEAD_OFFSET2_MS		0x00000008

#define TI_FMC_SKT0			0x00000400
#define TI_FMC_SKT1			0x00000800
#define TI_FMC_SKT2			0x00000c00 /* MS Socket */
#define TI_FMC_SKT3			0x00001000 /* MMC Socket */
#define TI_FMC_SKT_OFFSET1		0x0a
#define TI_FMC_SKT_OFFSET1_BIT1		0x01

#define TI_FMC_SKT3_OFFSET2		0x0b
#define TI_FMC_SKT3_OFFSET2_BIT1		0x3a /* SD/MMC card inserted*/

struct tifmc_host;

struct tifmc_host {
	struct pci_dev *dev;
	struct mmc_host* mmc;
	int base;
	int size;
	void __iomem *mem;
	unsigned long port;
	struct resource *res_port;
	int latency;
	int irq;
	u16 vendor_id;
	u16 device_id;
	u16 status;
	u16 command;
	u16 subsystem_vendor_id;
	u16 subsystem_id;
	u8 general;
	u32 diagnostic;
};

#endif // TIFMC_H
