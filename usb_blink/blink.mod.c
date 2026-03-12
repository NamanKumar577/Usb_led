#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf145940c, "pci_iomap" },
	{ 0x02f9bbf0, "timer_init_key" },
	{ 0x058c185a, "jiffies" },
	{ 0x32feeafc, "mod_timer" },
	{ 0x587292b0, "pci_dev_put" },
	{ 0x2352b148, "timer_delete_sync" },
	{ 0x2d88a3ab, "flush_work" },
	{ 0xabfbaeb0, "pci_iounmap" },
	{ 0xaef1f20d, "system_wq" },
	{ 0x49733ad6, "queue_work_on" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xefa198af, "pci_get_class" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xf145940c,
	0x02f9bbf0,
	0x058c185a,
	0x32feeafc,
	0x587292b0,
	0x2352b148,
	0x2d88a3ab,
	0xabfbaeb0,
	0xaef1f20d,
	0x49733ad6,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0xefa198af,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"pci_iomap\0"
	"timer_init_key\0"
	"jiffies\0"
	"mod_timer\0"
	"pci_dev_put\0"
	"timer_delete_sync\0"
	"flush_work\0"
	"pci_iounmap\0"
	"system_wq\0"
	"queue_work_on\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"pci_get_class\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A2757A274BF7A39D9CF5F35");
