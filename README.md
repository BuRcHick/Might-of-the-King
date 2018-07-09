
/*
<?xml version="1.0" encoding="UTF-8"?>
<xml>
	<langs>
		<tplvar name="DESCRIPTION_1" en="Speakers" ru="" />
		<tplvar name="DESCRIPTION_2" en="Selct speaker and actions for them" ru="" />
		<tplvar name="COM1" en="" ru="" />
		<tplvar name="ITEM1" en="Speaker" ru="" />
		<tplvar name="ITEM2" en="speakerStatus" ru="" />
		<tplvar name="ITEM3" en="Play" ru="" />
		<tplvar name="ITEM4" en="Stop" ru="" />
	</langs>

	<description>
		<b>##DESCRIPTION_1##</b>
		<br/>
		##DESCRIPTION_2##
	</description>

	<name value="Speaker actions"/>
	<tag value = "item"/>

	<item type="div" />

	<item type="comment" name="comment" comment="" weight="12" value="##COM1##"/>
	<item type="devices-list" name="SPEAKER1" filter="speaker" comment="##ITEM1##" required="1" />
	<item type="list" name="SPSTATUS1" required="1" weight="6" comment="##ITEM2##">
		<option key="1" value="##ITEM3##"/>
		<option key="0" value="##ITEM4##"/>
	</item>
	
	<item type="string" name="PATH1" comment="Song1 path" value = "Здесь могла быть ваша реклама" required="1"/>
	
	<item type="div" />
	
	<item type="devices-list" name="SPEAKER2" filter="speaker" comment="##ITEM1##" required="1" />
	<item type="list" name="SPSTATUS2" required="1" weight="6" comment="##ITEM2##">
		<option key="1" value="##ITEM3##"/>
		<option key="0" value="##ITEM4##"/>
	</item>
	<item type="string" name="PATH2" comment="Song2 path" value = "Здесь могла быть ваша реклама" required="1"/>
	
</xml>
*/



V-ID/V-ADDR
{
	if(opt(0))
	{
		#ifdef SPEAKER1
		setStatus(SPEAKER1, SPSTATUS1, 200, cmd);
		#endif//SPEAKER1
		
		#ifdef SPEAKER2
		setStatus(SPEAKER2, SPSTATUS2);
		#endif//SPEAKER2
	}
	else
	{
	    #ifdef SPEAKER1
		setStatus(SPEAKER1, 0);
		#endif//SPEAKER1
		
		#ifdef SPEAKER2
		setStatus(SPEAKER2, 0);
		#endif//SPEAKER2
	}
}
