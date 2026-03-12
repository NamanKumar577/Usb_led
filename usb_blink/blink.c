#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/pci.h>
#include <linux/io.h>

#define TARGET_PORT    2
#define BLINK_INTERVAL (2*HZ/1)
#define PORTSC_RESET   (1 << 4)

static struct timer_list blink_timer;
static struct work_struct blink_work;
static void __iomem *xhci_base = NULL;
static void __iomem *portsc_reg = NULL;
static struct pci_dev *xhci_pdev = NULL;
static int led_state = 0;

static void blink_work_fn(struct work_struct *w)
{
    u32 val;
    if (!portsc_reg) return;

    led_state ^= 1;
    val = readl(portsc_reg);

    if (led_state) {
        writel(val | PORTSC_RESET, portsc_reg);
        printk(KERN_INFO "usb_blink: D+ LOW  PORTSC=0x%08x\n", readl(portsc_reg));
    } else {
        writel(val & ~PORTSC_RESET, portsc_reg);
        printk(KERN_INFO "usb_blink: D+ HIGH PORTSC=0x%08x\n", readl(portsc_reg));
    }
}

static void blink_timer_fn(struct timer_list *t)
{
    schedule_work(&blink_work);
    mod_timer(&blink_timer, jiffies + BLINK_INTERVAL);
}

static int __init blink_init(void)
{
    u8 cap_length;
    u32 portsc_offset;

    xhci_pdev = pci_get_class(PCI_CLASS_SERIAL_USB_XHCI, NULL);
    if (!xhci_pdev) {
        printk(KERN_ERR "usb_blink: xHCI not found\n");
        return -ENODEV;
    }

    /* Use pci_iomap — works with IOMMU unlike raw ioremap */
    xhci_base = pci_iomap(xhci_pdev, 0, 0);
    if (!xhci_base) {
        printk(KERN_ERR "usb_blink: pci_iomap failed\n");
        pci_dev_put(xhci_pdev);
        return -ENOMEM;
    }

    cap_length = readb(xhci_base);
    printk(KERN_INFO "usb_blink: cap_length=0x%x\n", cap_length);

    /* PORTSC = cap_length + 0x400 + (port-1)*0x10 */
    portsc_offset = cap_length + 0x400 + (TARGET_PORT - 1) * 0x10;
    portsc_reg = xhci_base + portsc_offset;

    printk(KERN_INFO "usb_blink: PORTSC offset=0x%x val=0x%08x\n",
           portsc_offset, readl(portsc_reg));

    INIT_WORK(&blink_work, blink_work_fn);
    timer_setup(&blink_timer, blink_timer_fn, 0);
    mod_timer(&blink_timer, jiffies + BLINK_INTERVAL);
    return 0;
}

static void __exit blink_exit(void)
{
    timer_delete_sync(&blink_timer);
    flush_work(&blink_work);
    if (xhci_base)
        pci_iounmap(xhci_pdev, xhci_base);
    if (xhci_pdev)
        pci_dev_put(xhci_pdev);
    printk(KERN_INFO "usb_blink: unloaded\n");
}

module_init(blink_init);
module_exit(blink_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aniket");
MODULE_DESCRIPTION("Blink LED via xHCI PORTSC direct register access");
