#include "cxx21.h"

Cxx21::Cxx21(char *_base_addr)
      :base_addr(_base_addr), var_1(0), var_2(0), num_sockets(4), d_socket(2)
{
	for(int c = 4; c>0; c--) { mpFlash[c] = 0; arr_x[c] = 0; }
}

char
Cxx21::GetIntObj(void *_int_obj)
{
	int_obj = _int_obj; return 0;
}

char
Cxx21::GetSel1(int _sel_1)
{
	sel_1 = _sel_1; return 0;
}

char
Cxx21::GetSel2(int _sel_2)
{
	sel_2 = _sel_2; return 0;
}

char
Cxx21::GetSel3(int _sel_3)
{
	sel_3 = _sel_3; return 0;
}

char
Cxx21::GetSel4(int _sel_4)
{
	sel_4 = _sel_4; return 0;
}

char
Cxx21::GetSel5(int _sel_5)
{
	sel_5 = _sel_5; return 0;
}

void
Cxx21::GetNumSockets(int _num_sockets)
{
	num_sockets = _num_sockets;
	if(num_sockets != 4) d_socket = 0;
}

void
Cxx21::Initialize()
{
	write32(iomem + 0xc, 0xffffffff);
        write32(iomem + 0x8, 0x8000000f);
}

char
Cxx21::CardDetection(char socket)
{
	char *socket_ptr = base_addr + (((long)socket + 1) << 10);
	char m_id;
	CSocket *t_socket;

	if(mpFlash[socket] != 0)
        {
            m_id = mpFlash[socket]->GetMediaID();
            if(m_id == 0x43) goto loc_0_1A328;
        }

        t_socket = new CSocket(sock_ptr);
        if(num_sockets != 4) //xx21 controlles
            t_socket->is_xx12 = 1;

        t_socket->SocketPowerCtrl();
        m_id = t_socket->GetMediaID();
        t_socket->vtable[m_id](); // call from table

loc_0_1A328:
	switch(m_id)
	{
	    case 1:
	    case 2:
	    case 3:
	}

	// no valid card message
	r15b = 0x83;
	if(mpFlash[socket] != 0)
	{
	    // old card removed
	    sub_0_1FE70(mpFlash[socket]);
	}
	
	switch(socket)
	{
	    case 0:
		write32(iomem + 0xc, 0x00010100);
		arr_x[socket] = 0;
		break;
	    case 1:
		write32(iomem + 0xc, 0x00020200);
		arr_x[socket] = 0;
		break;
	    case 2:
		write32(iomem + 0xc, 0x00040400);
		arr_x[socket] = 0;
		break;
	    case 3:
		write32(iomem + 0xc, 0x00080800);
		arr_x[socket] = 0;
		break;
	    default:
		arr_x[socket] = 0;
	    
	}	
	// loc_0_1A543
	
}

char
Cxx21::sub_0_1A100()
{
    unsigned int v1;
    
    v1 = read32(base_addr + 0x14);
    if(v1 == 0 || v1 == 0xffffffff) return 0;
loc_0_1A129:
    
}
