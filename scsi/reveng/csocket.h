class CSocket
{
	//alloc: 0x38 bytes
	void *vtable;    // 0x000 - function table ???
	char *base_addr; // 0x008 - iomem base address for socket

	char is_xx12;    // 0x030

	friend class Cxx21;
public:	
	CSocket_0(void *_base_addr); 
	CSocket_1(void *_base_addr); 
	~CSocket();
	char GetMediaID();
};



