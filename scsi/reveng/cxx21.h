class Cxx21
{
	// alloc: 0x70 bytes
	char *base_addr;     // 0x000 - iomem base address for device
	void *int_obj;       // 0x008

	int sel_1;           // 0x010
	int sel_2;
	int sel_3;
	int sel_4;
	int sel_5;           // 0x020

	int var_1;           // 0x024
	char var_2;          // 0x028
	
	CSocket *mpFlash[4]; // 0x030
	char arr_x;          // 0x050
	int num_sockets;     // 0x054
	char d_socket;       // 0x058


public:
	Cxx21(char *_base_addr);
	~Cxx21();
	
	char GetIntObj(void *_int_obj);
	char GetSel1(int _sel_1);
	char GetSel2(int _sel_2);
	char GetSel3(int _sel_3);
	char GetSel4(int _sel_4);
	char GetSel5(int _sel_5);
	void GetNumSockets(int _num_sockets);
	
	void Initialize();

	char CardDetection(char socket);	

};

