#pragma once

#ifndef _GOLBAL_DEFINE_
#define _GOLBAL_DEFINE_

#define DEFAULT_FONT						_T("Tahoma")

/////////////////////////////////////////////////////////////////////////////
// Program Version
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Debug Option
/////////////////////////////////////////////////////////////////////////////
#define DEBUG_COMM_LOG				0
#define DEBUG_POINT					1

/////////////////////////////////////////////////////////////////////////////
// General Define
/////////////////////////////////////////////////////////////////////////////
#define MLOG_LENGTH					1024*4 // max mlog length
#define UDP_LENGTH					1024*4	// max packet length

#define OFF							0
#define ON							1

#define LOW							0
#define HIGH						1

#define NG							0
#define OK							1
#define RDY							0xFF

#define STOP						0
#define START						1

#define DISABLE						0
#define ENABLE						1

#define ADDON_01					0
#define ADDON_02					1
#define ADDON_MAX					2

#define ADDON_01_IP					_T("192.168.10.3")
#define ADDON_02_IP					_T("192.168.10.102")
#define LOCAL_HOST_IP				_T("127.0.0.1")
/////////////////////////////////////////////////////////////////////////////
// COLORREF
/////////////////////////////////////////////////////////////////////////////
//#define COLOR_BLACK					RGB(0,0,0)
//#define COLOR_WHITE					RGB(255,255,255)
//#define COLOR_RED					RGB(255,0,0)
//#define COLOR_GREEN					RGB(0,255,0)
//#define COLOR_BLUE					RGB(0,0,255)
//#define COLOR_YELLOW				RGB(255,255,0)
//#define COLOR_CYAN					RGB(0,255,255)
//#define COLOR_SKYBLUE				RGB(173,216,230)
//#define COLOR_SEABLUE				RGB(21,85,147)
//#define COLOR_ORANGE				RGB(245,136,22)
//#define COLOR_VERDANT				RGB(116,192,24)
//#define COLOR_GRAY64				RGB(64,64,64)
//#define COLOR_GRAY128				RGB(128,128,128)
//#define COLOR_GRAY159				RGB(159,159,159)
//#define COLOR_GRAY192				RGB(192,192,192)
//#define COLOR_GRAY224				RGB(224,224,224)
//#define COLOR_GRAY240				RGB(240,240,240)
//#define COLOR_PINK					RGB(255,192,192)
//#define COLOR_MAGENTA				RGB(224,0,224)
//#define COLOR_DARK_RED				RGB(255,63,63)
//#define COLOR_DARK_GREEN			RGB(63,140,63)
//#define COLOR_DARK_BLUE				RGB(63,63,192)
//#define COLOR_DARK_ORANGE			RGB(230,160,0)
//#define COLOR_DARK_YELLOW			RGB(127,127,32)
//#define COLOR_DARK_MAGENTA			RGB(125,100,125)
//#define COLOR_LIGHT_RED				RGB(255,224,224)
//#define COLOR_LIGHT_GREEN			RGB(224,255,224)
//#define COLOR_LIGHT_BLUE			RGB(224,224,255)
//#define COLOR_LIGHT_ORANGE			RGB(255,234,218)
//#define COLOR_LIGHT_YELLOW			RGB(192,192,32)
//#define COLOR_LIGHT_CYAN			RGB(150,230,220)
//#define COLOR_JADEGREEN				RGB(192,220,192)
//#define COLOR_JADEBLUE				RGB(0,156,220)
//#define COLOR_JADERED				RGB(236,112,112)
//#define COLOR_BLUISH				RGB(77, 97, 128)
#define COLOR_USER_BACKGROUND		RGB(240, 240, 255)
#define COLOR_BLACK					RGB(0,0,0)
#define COLOR_WHITE					RGB(255,255,255)
#define COLOR_RED					RGB(255,0,0)
#define COLOR_GREEN					RGB(0,255,0)
#define COLOR_BLUE					RGB(0,0,255)
#define COLOR_YELLOW				RGB(255,255,0)
#define COLOR_CYAN					RGB(0,255,255)
#define COLOR_SKYBLUE				RGB(199,199,255)
#define COLOR_SEABLUE				RGB(31,78,121)
#define COLOR_ORANGE				RGB(245,136,22)
#define COLOR_VERDANT				RGB(112,146,108)
#define COLOR_VERDANT2				RGB(240,255,240)
#define COLOR_GRAY16				RGB(16,16,16)
#define COLOR_GRAY32				RGB(32,32,32)
#define COLOR_GRAY48				RGB(48,48,48)
#define COLOR_GRAY64				RGB(64,64,64)
#define COLOR_GRAY80				RGB(80,80,80)
#define COLOR_GRAY94				RGB(94,94,94)
#define COLOR_GRAY96				RGB(96,96,96)
#define COLOR_GRAY128				RGB(128,128,128)
#define COLOR_GRAY159				RGB(159,159,159)
#define COLOR_GRAY192				RGB(192,192,192)
#define COLOR_GRAY224				RGB(224,224,224)
#define COLOR_GRAY240				RGB(240,240,240)
#define COLOR_GREEN128				RGB(0,128,0)
#define COLOR_GREEN224				RGB(0,224,0)
#define COLOR_RED128				RGB(128,0,0)
#define COLOR_BLUE128				RGB(0,0,128)
#define COLOR_PINK					RGB(255,130,169)
#define COLOR_MAGENTA				RGB(224,0,224)
#define COLOR_DARK_RED				RGB(169,100,100)
#define COLOR_DARK_GREEN			RGB(63,128,63)
#define COLOR_DARK_BLUE				RGB(63,63,255)
#define COLOR_DARK_ORANGE			RGB(230,160,0)
#define COLOR_DARK_YELLOW			RGB(224,224,128)
#define COLOR_DARK_MAGENTA			RGB(64,16,64)
#define COLOR_DARK_NAVY				RGB(68, 75, 83)
#define COLOR_BLUISH				RGB(65, 105, 225)
#define COLOR_LIGHT_RED				RGB(255,224,224)
#define COLOR_LIGHT_GREEN			RGB(113,255,170)
#define COLOR_LIGHT_BLUE			RGB(224,224,255)
#define COLOR_LIGHT_ORANGE			RGB(255,234,218)
#define COLOR_LIGHT_CYAN			RGB(150,230,220)
#define COLOR_LIGHT_YELLOW			RGB(231,250,205)
#define COLOR_LIGHT_BROWN			RGB(196,189,151)
#define COLOR_JADEGREEN				RGB(192,220,192)
#define COLOR_JADEBLUE				RGB(0,156,220)
#define COLOR_JADERED				RGB(236,112,112)
#define COLOR_DEEP_BLUE				RGB(77,97,128)
#define COLOR_GREENISH				RGB(146,208,80)
#define COLOR_PURPLE				RGB(112,48,160)
#define COLOR_DEF_LEVEL0_5			RGB(250,240,239)
#define COLOR_DEF_LEVEL1_0			RGB(243,225,224)
#define COLOR_DEF_LEVEL1_5			RGB(236,210,209)
#define COLOR_DEF_LEVEL2_0			RGB(229,195,194)
#define COLOR_DEF_LEVEL2_5			RGB(222,180,179)
#define COLOR_DEF_LEVEL3_0			RGB(215,175,174)
#define COLOR_DEF_LEVEL3_5			RGB(208,160,159)
#define COLOR_DEF_LEVEL4_0			RGB(201,145,144)
#define COLOR_DEF_LEVEL4_5			RGB(194,130,129)
#define COLOR_DEF_LEVEL5_0			RGB(187,115,114)
#define COLOR_DARK_BG				RGB(51,54,63)
#define COLOR_BUTTON_SEL			RGB(102,157,178)
#define COLOR_BUTTON_DARK			RGB(28,44,68)
#define COLOR_MAIN_TITLE			RGB(132,187,207)
#define COLOR_ITEM_HEAD				RGB(126,177,86)
#define COLOR_ITEM_TITLE			RGB(62,69,88)

typedef enum _COLOR_IDX_{
	/*COLOR_IDX_BLACK=0,
	COLOR_IDX_RED,
	COLOR_IDX_GREEN,
	COLOR_IDX_BLUE,
	COLOR_IDX_YELLOW,
	COLOR_IDX_CYAN,
	COLOR_IDX_SKYBLUE,
	COLOR_IDX_SEABLUE,
	COLOR_IDX_ORANGE,
	COLOR_IDX_VERDANT,
	COLOR_IDX_LIGHT_RED,
	COLOR_IDX_LIGHT_GREEN,
	COLOR_IDX_LIGHT_BLUE,
	COLOR_IDX_LIGHT_ORANGE,
	COLOR_IDX_LIGHT_YELLOW,
	COLOR_IDX_LIGHT_CYAN,
	COLOR_IDX_GRAY64,
	COLOR_IDX_GRAY128,
	COLOR_IDX_GRAY159,
	COLOR_IDX_GRAY192,
	COLOR_IDX_GRAY224,
	COLOR_IDX_GRAY240,
	COLOR_IDX_PINK,
	COLOR_IDX_JADEGREEN,
	COLOR_IDX_JADEBLUE,
	COLOR_IDX_JADERED,
	COLOR_IDX_BLUISH,
	COLOR_IDX_DARK_RED,
	COLOR_IDX_DARK_GREEN,
	COLOR_IDX_DARK_BLUE,
	COLOR_IDX_DARK_ORANGE,
	COLOR_IDX_DARK_YELLOW,
	COLOR_IDX_DARK_MAGENTA,
	COLOR_IDX_WHITE,
	COLOR_IDX_MAX*/
	COLOR_IDX_USER_BACKGROUND = 0,
	COLOR_IDX_BLACK,
	COLOR_IDX_RED,
	COLOR_IDX_GREEN,
	COLOR_IDX_BLUE,
	COLOR_IDX_YELLOW,
	COLOR_IDX_ORANGE,
	COLOR_IDX_VERDANT,
	COLOR_IDX_VERDANT2,
	COLOR_IDX_CYAN,
	COLOR_IDX_MAGENTA,
	COLOR_IDX_SKYBLUE,
	COLOR_IDX_SEABLUE,
	COLOR_IDX_LIGHT_RED,
	COLOR_IDX_LIGHT_GREEN,
	COLOR_IDX_LIGHT_BLUE,
	COLOR_IDX_LIGHT_ORANGE,
	COLOR_IDX_LIGHT_CYAN,
	COLOR_IDX_LIGHT_YELLOW,
	COLOR_IDX_LIGHT_BROWN,
	COLOR_IDX_GRAY64,
	COLOR_IDX_GRAY94,
	COLOR_IDX_GRAY96,
	COLOR_IDX_GRAY128,
	COLOR_IDX_GRAY159,
	COLOR_IDX_GRAY192,
	COLOR_IDX_GRAY224,
	COLOR_IDX_GRAY240,
	COLOR_IDX_RED128,
	COLOR_IDX_GREEN128,
	COLOR_IDX_BLUE128,
	COLOR_IDX_PINK,
	COLOR_IDX_BLUISH,
	COLOR_IDX_JADEGREEN,
	COLOR_IDX_JADEBLUE,
	COLOR_IDX_JADERED,
	COLOR_IDX_DARK_RED,
	COLOR_IDX_DARK_GREEN,
	COLOR_IDX_DARK_BLUE,
	COLOR_IDX_DARK_ORANGE,
	COLOR_IDX_DARK_YELLOW,
	COLOR_IDX_DARK_MAGENTA,
	COLOR_IDX_DARK_NAVY,
	COLOR_IDX_DARK_BG,
	COLOR_IDX_WHITE,
	COLOR_IDX_DEEP_BLUE,
	COLOR_IDX_GREENISH,
	COLOR_IDX_PURPLE,
	COLOR_IDX_ITEM_HEAD,
	COLOR_IDX_ITEM_TITLE,
	COLOR_IDX_DEF_LEVEL0_5,
	COLOR_IDX_DEF_LEVEL1_0,
	COLOR_IDX_DEF_LEVEL1_5,
	COLOR_IDX_DEF_LEVEL2_0,
	COLOR_IDX_DEF_LEVEL2_5,
	COLOR_IDX_DEF_LEVEL3_0,
	COLOR_IDX_DEF_LEVEL3_5,
	COLOR_IDX_DEF_LEVEL4_0,
	COLOR_IDX_DEF_LEVEL4_5,
	COLOR_IDX_DEF_LEVEL5_0,
	COLOR_IDX_DEF_SIMPLIFY1,
	COLOR_IDX_DEF_SIMPLIFY2,
	COLOR_IDX_DEF_SIMPLIFY3,
	COLOR_IDX_DEF_SIMPLIFY4,
	COLOR_IDX_DEF_SIMPLIFY5,
	COLOR_IDX_MAX
};

#define FONT_IDX_MAX				10


/////////////////////////////////////////////////////////////////////////////
// GRID Define
/////////////////////////////////////////////////////////////////////////////
#define	_CELL_LEFT_					0
#define	_CELL_CENTER_				4
#define	_CELL_RIGHT_				7
#define GRID_FONT_WIDTH				4
#define GRID_TWIDTH					520
#define GRID_WIDTH					420
#define GRID_HEIGHT					420


/////////////////////////////////////////////////////////////////////////////
// RS232 CHANNEL Definition
/////////////////////////////////////////////////////////////////////////////
#define COM_PORT1		1
#define COM_LENGTH		65535




/////////////////////////////////////////////////////////////////////////////
// Communication Protocol Packet
/////////////////////////////////////////////////////////////////////////////
#define CMD_START_CHAR      					0x02    // ''
#define CMD_END_CHAR        					0x03    // ''  

#define ADDR_PC									0xA1
#define ADDR_CTRL								0xA2

#define ProtocolStartOfText						0 
#define ProtocolSender							ProtocolStartOfText 		+ 1
#define ProtocolReceiver						ProtocolSender 				+ 2
#define ProtocolID								ProtocolReceiver 			+ 2
#define ProtocolCommand							ProtocolID 					+ 2
#define ProtocolLength							ProtocolCommand 			+ 2
#define ProtocolData							ProtocolLength 				+ 4




/////////////////////////////////////////////////////////////////////////////
// Definition
/////////////////////////////////////////////////////////////////////////////
enum SIGNAL_BIT // Signal Bit List
{
	SIG_6BIT = 0,
	SIG_8BIT,
	SIG_10BIT,
	SIG_12BIT
};

enum PG_PIXEL
{
	PIX_SINGLE=0,
	PIX_DUAL,
	PIX_QUAD,
	PIX_OCTA,
	PIX_HEXA,
};

#define		tpTMDS		0
#define		tpLVDS		1
#define		tpDP		2
#define		tpEdp		3
#define		tpHDMI		4
#define		tpVx1		5

#define LIMIT_LOW		0
#define LIMIT_HIGH		1










/////////////////////////////////////////////////////////////////////////////
// Command Packet
/////////////////////////////////////////////////////////////////////////////

#define CMD_CTRL_FUSING_SYSTEM_INFO						0xA0
#define CMD_CTRL_FUSING_CTRL_IO							0xA4
#define CMD_CTRL_FUSING_FIRST_PTN						0xA5
#define CMD_CTRL_FUSING_PATTERN							0xA6

#define CMD_CTRL_CREATE_FILE							0xC1
#define CMD_CTRL_WRITE_FILE								0xC2
#define CMD_CTRL_DELETE_ALL_MOD							0xC3
#define CMD_CTRL_DELETE_ONE_MOD							0xC8
#define CMD_CTRL_WRITE_APPLY_FILE						0xC9


#define CMD_CTRL_GOTO_BOOT_DOWNLOAD 					0xF3
#define CMD_CTRL_GOTO_BOOT_UPLOAD						0xF4
#define CMD_CTRL_RST									0xFD

#define CMD_CTRL_VER_GET								0xFE






/////////////////////////////////////////////////////////////////////////////
// Macro Define
/////////////////////////////////////////////////////////////////////////////
#define round(a) ( int ) ( a + .5 )

#endif