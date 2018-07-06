/*
{
	desc:"Скрипт Conditioner",
	tag:"import-script",
	target:"IRT",
	selectArea:true,
	addItems:[
		{tag:"item", id:"%TARGET%", name:"NAME", "sub-id":"%SUBID%", type:"conditioner", "t-delta":"11", "t-min":"19", "vane-hor":"0", "vane-ver":"0x3E", "modes":"0x0F", "funs":"0x0E"},
	],
	vars:[
		{name:"IRT",type:"devices-list",required:true,filter:["ir-transmitter"],desc:"ИК-передатчик"},
		{name:"NAME",type:"string",required:true,min:3,max:40,desc:"COND",defaultValue:"Кондиционер"},
		{name:"COND",type:"hidden",value:"%TARGET%:%SUBID%"}
	]
}
*/


u8 tPrev ;

V-ID/COND{
	u8 sw_on[]	 	= {0x20, 0x24};
	u8 sw_mode 		= opt(0) >> 4;
	u8 sw_f     		= opt(4);
	u8 sw_v    	 	= (opt(3) >> 4);								 /*26*/
	u8 data[] 		        = {0x1964020002008906010293000017C551037017310F23CB260100000000000000010000};
	u8 con_modes[] 	={0x07, 0x03, 0x02, 0x01, 0x08};
	u8 con_t	        	= 0xF - opt(1);
	u8 con_van[]		= {0x8, 0x10, 0x18, 0x20, 0x28};
	u8 con_fan[]		= {0x0, 0x2, 0x3, 0x5};

	data[26] = sw_on[(opt(0) & 0x01)];
	data[27] = con_modes[sw_mode];
	data[28] = con_t;
	data[29] = con_van[sw_v] + con_fan[sw_f];
	data[32] = 0x01;
	u8 summ  = 0;
	for(u8 i = 26; i < 34; ++i)
	{
		summ+=data[i];
	}

	u8 text[200];
	sprintf(text,"%con = %X, mode = %X, t = %X, van/fan = %X,",1,data[26],data[27],data[28],data[29]);

	summ+=0x15;
	data[34] = summ;

	setStatus(IRT, &data);
	srvError(&text); 


/*
switch mode
0		  4		 7			 	 15		18 19			   26 27 28	29	   32 33 34
1964 020002 008906 010293000017C551 037017 31 0F23CB260100 24 03 08 22 000001  08 6F	34b|-(08) switch mode	27b|-(0x03 cool mode) mode id

{0x01, 0x08, 0x07, 0x03}
 heat  auto  dry   cool

0		  4			
temp switch													 |27b		 |33b
1964 020002 008996 010293000017C551 037017 1C 0F23CB260100 24 01 0E 22 000001 14/10 7F	temp 28b - temp value(0x0E 17t) | 34b - temp mode (14++)/(10--)
1964 020002 008906 010293000017C751 037017 23 0F23CB260100 24 03 03 1B 000001 10 6B
1964 020002 008906 010293000017C551 037017 23 0F23CB260100 24 03 01 1B 000001 14 6D
1964 020002 008906 010293000017C151 037017 31 0F23CB260100 24 03 02 1B 000001 10 6A

{0x00, 0x01, 0x02 ... 0x0F}
  31,   30,   29, ...  16
// temp down

27b++ (33b == 14)
27b-- (33b == 10) 


on/off
										   |19			   |26 		|29b	  |33b				0x24|on		0x20|off  
1964 020002 008906 010293000017C551 037017 38 0F23CB260100 24 01 00 38 000001 04 77	/on 26b |-on(0x24)
1964 020002 008906 010293000017C451 037017 1C 0F23CB260100 24 03 01 2D 000001 0C 77
1964 020002 008906 010293000017C351 037017 38 0F23CB260100 20 08 07 1B 000001 04 64
1964 020002 008906 010293000017C451 037017 31 0F23CB260100 24 08 07 1B 000001 04 68  


cahnge fan/swing
1964 020002 008906 010293000017C251 037017 1C 0F23CB260100 24 03 06 1B 000001 4C AA    29b 0xXX min 0x08 + 0x08/0x10 
1964 020002 008906 010293000017C651 037017 15 0F23CB260100 24 08 07 2A 000001 0C 7F
1964 020002 008906 010293000017C451 037017 1C 0F23CB260100 24 03 01 2D 000001 0C 77
1964 020002 008906 010293000017C151 037017 38 0F23CB260100 24 03 01 28 000001 0C 72
1964 020002 008906 010293000017C451 037017 40 0F23CB260100 24 03 01 08 000001 4C 92
// change swing
29b + 0x08

//change fan speed
29b + 0x01
{0x08, 0x0A, 0x0B ,0x0C, 0x0D}
*/
