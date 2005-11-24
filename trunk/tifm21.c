#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#include "tifm21.h"

#define DRIVER_NAME "tifm21"
#define DRIVER_VERSION "0.1"
#define DRIVER_DESCRIPTION "Texas Instruments PCI7xx1 Integrated FlashMedia Controller driver"
#define DRIVER_AUTHOR "Paul Webster <pjwebster at gmail dot com>"

static int ms_dis = 0;
static int mmc_sd_dis = 0;
static int sm_dis = 0;

static struct pci_device_id tifmc_dev_table[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_FMC), },
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, tifmc_dev_table);

static irqreturn_t tifmc_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	printk(KERN_INFO DRIVER_NAME ": Excuse me, can I interrupt you for a moment?\n");
	/* do nothing */
	return IRQ_HANDLED;
}

static int tifmc_init_memory_stick(struct pci_dev *dev, int disable)
{
    int result = 0;
    u8 gcr = 0;

    result = pci_read_config_byte(dev, TI_FMC_REG_GENERAL_CTRL, &gcr);

    if(!result)
    {
        if(disable)
        {
            gcr |= TI_FMC_GCR_MS_DIS;
        }
        else
        {
            gcr &= ~TI_FMC_GCR_MS_DIS;
        }

        result = pci_write_config_byte(dev, TI_FMC_REG_GENERAL_CTRL, gcr);

        if(!result)
        {
            if(disable)
            {
                printk(KERN_INFO DRIVER_NAME ": Memory Stick disabled\n");
            }
        }
    }

    return result;
}

static int tifmc_init_mmc_sd(struct pci_dev *dev, int disable)
{
    int result = 0;
    u8 gcr = 0;

    result = pci_read_config_byte(dev, TI_FMC_REG_GENERAL_CTRL, &gcr);

    if(!result)
    {
        if(disable)
        {
            gcr |= TI_FMC_GCR_MMC_SD_DIS;
        }
        else
        {
            gcr &= ~TI_FMC_GCR_MMC_SD_DIS;
        }

        result = pci_write_config_byte(dev, TI_FMC_REG_GENERAL_CTRL, gcr);

        if(!result)
        {
            if(disable)
            {
                printk(KERN_INFO DRIVER_NAME ": MMC/SD disabled\n");
            }
        }
    }

    return result;
}

static int tifmc_init_smartmedia(struct pci_dev *dev, int disable)
{
    int result = 0;
    u8 gcr = 0;

    result = pci_read_config_byte(dev, TI_FMC_REG_GENERAL_CTRL, &gcr);

    if(!result)
    {
        if(disable)
        {
            gcr |= TI_FMC_GCR_SM_DIS;
        }
        else
        {
            gcr &= ~TI_FMC_GCR_SM_DIS;
        }

        result = pci_write_config_byte(dev, TI_FMC_REG_GENERAL_CTRL, gcr);

        if(!result)
        {
            if(disable)
            {
                printk(KERN_INFO DRIVER_NAME ": SmartMedia disabled\n");
            }
        }
    }

    return result;
}

static int tifmc_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct tifmc_host *host = NULL;
	
	int result = 0;

	host = kmalloc(sizeof(struct tifmc_host), GFP_KERNEL);

	if(!host)
	{
		return -ENOMEM;
	}
	
	memset(host, 0, sizeof(*host));
	
	host->dev = dev;
	pci_set_drvdata(dev, host);

	if((result = pci_enable_device(dev)))
	{
		printk(KERN_ERR DRIVER_NAME ": Cannot enable PCI device, aborting.\n");
		goto free_host;
	}

	pci_set_master(dev);
	
	host->base = pci_resource_start(dev, 0);

	if(!host->base)
	{
		printk(KERN_ERR DRIVER_NAME ": No TI resource!\n");
		result = -ENODEV;
		goto disable_device;
	}

	host->size = pci_resource_len(dev, 0);

	printk(KERN_INFO DRIVER_NAME ": found %d bytes at 0x%08x\n", host->size, host->base);

	result = pci_request_regions(dev, DRIVER_NAME);

	if(result)
	{
		printk(KERN_ERR DRIVER_NAME ": Cannot obtain PCI resources, aborting.\n");
		goto disable_device;
	}
	
	request_mem_region(host->base, host->size, DRIVER_NAME);
	host->mem = ioremap(host->base, host->size);

	host->irq = -1;

	result = request_irq(dev->irq, tifmc_interrupt, SA_SHIRQ, DRIVER_NAME, dev);

	if(result)
	{
		printk(KERN_ERR DRIVER_NAME ": Cannot grab IRQ, aborting.\n");
		goto disable_device;
	}

	host->irq = dev->irq;

        tifmc_init_memory_stick(dev, ms_dis);
        tifmc_init_mmc_sd(dev, mmc_sd_dis);
        tifmc_init_smartmedia(dev, sm_dis);

	goto finished_probe;

disable_device:
	pci_disable_device(dev);
free_host:
	kfree(host);
finished_probe:
	return result;
}

static void tifmc_remove(struct pci_dev *dev)
{
	struct tifmc_host *host = pci_get_drvdata(dev);

	if(host->irq >= 0)
	{
		free_irq(host->irq, tifmc_interrupt);
	}
	
	iounmap(((void __iomem *)host->base));
	release_mem_region(host->base, host->size);

	pci_release_regions(dev);
	pci_disable_device(dev);
	
	pci_set_drvdata(dev, NULL);
}

static struct pci_driver tifmc_driver = {
	.name = DRIVER_NAME,
	.id_table = tifmc_dev_table,
	.probe = tifmc_probe,
	.remove = tifmc_remove,
};

static int __init tifmc_drv_init(void)
{
	int result;

	printk(KERN_INFO DRIVER_NAME ": " DRIVER_DESCRIPTION ", " DRIVER_VERSION "\n");
	printk(KERN_INFO DRIVER_NAME ": " DRIVER_AUTHOR "\n");

	result = pci_register_driver(&tifmc_driver);

	return result;
}

static void __exit tifmc_drv_exit(void)
{
	pci_unregister_driver(&tifmc_driver);
	printk(KERN_INFO DRIVER_NAME ": driver unregistered\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);

module_init(tifmc_drv_init);
module_exit(tifmc_drv_exit);

module_param(ms_dis, int, S_IRUGO|S_IWUSR);
module_param(mmc_sd_dis, int, S_IRUGO|S_IWUSR);
module_param(sm_dis, int, S_IRUGO|S_IWUSR);

MODULE_PARM_DESC(ms_dis, "Disable support for Memory Stick cards.");
MODULE_PARM_DESC(mmc_sd_dis, "Disable support for MMC/SD cards.");
MODULE_PARM_DESC(sm_dis, "Disable support for SmartMedia cards.");
