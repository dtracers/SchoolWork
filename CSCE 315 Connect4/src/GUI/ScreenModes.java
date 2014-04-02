package GUI;

import java.awt.DisplayMode;

public class ScreenModes
{
	public static final MyDisplayMode[] ALL_MODES=
    {
		new MyDisplayMode(new DisplayMode(1680, 1050, 16, 0),"1440 X 900 16 bit color"),
		new MyDisplayMode(new DisplayMode(1680, 1050, 32, 0),"1440 X 900 32 bit color"),
		new MyDisplayMode(new DisplayMode(1680, 1050, 24, 0),"1440 X 900 24 bit color"),
		new MyDisplayMode(new DisplayMode(1440, 900, 16, 0),"1440 X 900 16 bit color"),
		new MyDisplayMode(new DisplayMode(1440, 900, 32, 0),"1440 X 900 32 bit color"),
		new MyDisplayMode(new DisplayMode(1440, 900, 24, 0),"1440 X 900 24 bit color"),
		new MyDisplayMode(new DisplayMode(1344, 840, 16, 0),"1344 X 840 16 bit color"),
		new MyDisplayMode(new DisplayMode(1344, 840, 32, 0),"1344 X 840 32 bit color"),
		new MyDisplayMode(new DisplayMode(1344, 840, 24, 0),"1344 X 840 24 bit color"),
		new MyDisplayMode(new DisplayMode(1366, 768, 16, 0),"1344 X 840 24 bit color"),
		new MyDisplayMode(new DisplayMode(1366, 768, 32, 0),"1344 X 840 24 bit color"),
		new MyDisplayMode(new DisplayMode(1366, 768, 24, 0),"1344 X 840 24 bit color"),
    	new MyDisplayMode(new DisplayMode(1280, 1024, 16, 0),"1280 X 1024 16 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 1024, 32, 0),"1280 X 1024 32 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 1024, 24, 0),"1280 X 1024 24 bit color"),
    	new MyDisplayMode(new DisplayMode(1280, 960, 16, 0),"1280 X 960 16 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 960, 32, 0),"1280 X 960 32 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 960, 24, 0),"1280 X 960 24 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 768, 16, 0),"1280 X 768 16 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 768, 32, 0),"1280 X 768 32 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 768, 24, 0),"1280 X 768 24 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 720, 16, 0),"1280 X 720 16 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 720, 32, 0),"1280 X 720 32 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 720, 24, 0),"1280 X 720 24 bit color"),
    	new MyDisplayMode(new DisplayMode(1024, 768, 16, 0),"1024 X 768 16 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 32, 0),"1024 X 768 32 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 24, 0),"1024 X 768 24 bit color"),
        new MyDisplayMode(new DisplayMode(1052, 864, 16, 0),"1052 X 864 16 bit color"),
        new MyDisplayMode(new DisplayMode(1052, 864, 32, 0),"1052 X 864 32 bit color"),
        new MyDisplayMode(new DisplayMode(1052, 864, 24, 0),"1052 X 864 24 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 600, 16, 0),"1280 X 600 16 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 600, 32, 0),"1280 X 600 32 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 600, 24, 0),"1280 X 600 24 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 720, 16, 0),"1280 X 720 16 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 720, 32, 0),"1280 X 720 32 bit color"),
        new MyDisplayMode(new DisplayMode(1280, 720, 24, 0),"1280 X 720 24 bit color"),
    	new MyDisplayMode(new DisplayMode(800, 600, 16, 0),"800 X 600 16 bit color"),
        new MyDisplayMode(new DisplayMode(800, 600, 32, 0),"800 X 600 32 bit color"),
        new MyDisplayMode(new DisplayMode(800, 600, 24, 0),"800 X 600 24 bit color"),
        new MyDisplayMode(new DisplayMode(640, 480, 16, 0),"640 X 480 16 bit color"),
        new MyDisplayMode(new DisplayMode(640, 480, 32, 0),"640 X 480 32 bit color"),
        new MyDisplayMode(new DisplayMode(640, 480, 24, 0),"640 X 480 24 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 16, 0),"1024 X 768 16 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 32, 0),"1024 X 768 32 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 24, 0),"1024 X 768 24 bit color"),
    	new MyDisplayMode(new DisplayMode(640, 480, 16, 0),"640 X 480 16 bit color"),
        new MyDisplayMode(new DisplayMode(640, 480, 32, 0),"640 X 480 32 bit color"),
        new MyDisplayMode(new DisplayMode(640, 480, 24, 0),"640 X 480 24 bit color"),
        new MyDisplayMode(new DisplayMode(800, 600, 16, 0),"800 X 600 16 bit color"),
        new MyDisplayMode(new DisplayMode(800, 600, 32, 0),"800 X 600 32 bit color"),
        new MyDisplayMode(new DisplayMode(800, 600, 24, 0),"800 X 600 24 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 16, 0),"1024 X 768 16 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 32, 0),"1024 X 768 32 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 24, 0),"1024 X 768 24 bit color"),
    	new MyDisplayMode(new DisplayMode(320, 240, 16, 0),"320 X 240 16 bit color"),
        new MyDisplayMode(new DisplayMode(400, 300, 16, 0),"400 X 300 16 bit color"),
        new MyDisplayMode(new DisplayMode(512, 384, 16, 0),"512 X 384 16 bit color"),
        new MyDisplayMode(new DisplayMode(640, 480, 16, 0),"640 X 480 16 bit color"),
        new MyDisplayMode(new DisplayMode(800, 600, 16, 0),"800 X 600 16 bit color"),
    };
    public static final MyDisplayMode[] NORMAL_MODES=
    {
    	new MyDisplayMode(new DisplayMode(1440, 900, 16, 0),"1440 X 900 16 bit color"),
		new MyDisplayMode(new DisplayMode(1440, 900, 32, 0),"1440 X 900 32 bit color"),
		new MyDisplayMode(new DisplayMode(1440, 900, 24, 0),"1440 X 900 24 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 16, 0),"1024 X 768 16 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 32, 0),"1024 X 768 32 bit color"),
        new MyDisplayMode(new DisplayMode(1024, 768, 24, 0),"1024 X 768 24 bit color")
    };
    public static DisplayMode[] transfer(MyDisplayMode[] g)
    {
    	DisplayMode[] temp=new DisplayMode[g.length];
    	for(int k=0;k<g.length;k++)
    	{
    		temp[k]=g[k].getmode();
    	}
    	return temp;
    }
}
