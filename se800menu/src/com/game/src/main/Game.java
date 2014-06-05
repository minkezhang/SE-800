package com.game.src.main;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.lang.ProcessBuilder.Redirect;
//import java.util.Arrays;


import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.JFrame;

public class Game extends Canvas implements Runnable {
	
	private static final long serialVersionUID = 1l;
	public static final int WIDTH = 320;
	public static final int HEIGHT = WIDTH / 12 * 9;
	public static final int SCALE = 2;
	public final String TITLE = "SE-800";
	public static int imgsize;
	public int mitem = 1;
	public int tickcount = 0;
	public int[] pos = new int[] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//8 images 0-3 xs 4-7 ys 8-15= duplicates
	public JFrame frame;
	public String color = "RED";
	public int tiscounter = 0;
	public int[] addr1 = new int[] {1,2,7};
	public int[] addr2 = new int[] {0,0,0};
	public int[] addr3 = new int[] {0,0,0};
	public int[] addr4 = new int[] {0,0,1};
	public String sadr1 = "127";
	public String sadr2 = "0";
	public String sadr3 = "0";
	public String sadr4 = "1";
	public int[] portnum = new int[] {8,0,0,0};
	public String addr = "127.0.0.1";
	public String port = "8000";
	public boolean host = true;
	public boolean bgmon = true;
	public Clip clip;
	public Rectangle clear = new Rectangle(0,0,WIDTH*SCALE,HEIGHT*SCALE);
	private boolean running = false;
	private Thread thread;
	
	private BufferedImage image = new BufferedImage(WIDTH,HEIGHT,BufferedImage.TYPE_INT_ARGB);
	private BufferedImage background = null;
	private BufferedImage bg2 = null;
	private BufferedImage bg3 = null;
	private BufferedImage bg4 = null;
	private BufferedImage background2 = null;
	private BufferedImage bg22 = null;
	private BufferedImage bg32 = null;
	private BufferedImage bg42 = null;
	
	//private Player p;
	private Menu menu;//main menu
	private Cred cred;//team credits
	private Play play;//play submenu
	
	public void init(){
		requestFocus();
		BufferedImageLoader loader = new BufferedImageLoader();
		try{
			background = loader.loadImage("/sb5.png");
			bg2 = loader.loadImage("/sb4.png");
			bg3 = loader.loadImage("/sb3.png");
			bg4 = loader.loadImage("/sb2.png");
			background2 = loader.loadImage("/sb5.png");
			bg22 = loader.loadImage("/sb4.png");
			bg32 = loader.loadImage("/sb3.png");
			bg42 = loader.loadImage("/sb2.png");
			imgsize = background2.getWidth();
			pos[11] = background2.getWidth();
			pos[10] = bg22.getWidth();
			pos[9] = bg32.getWidth();
			pos[8] = bg42.getWidth();
		}catch(IOException e){
			//e.printStackTrace();
		}
		this.addKeyListener(new KeyInput(this));
		this.addMouseListener(new MouseInput(this));
		menu = new Menu(this);
		cred = new Cred(this);
		play = new Play(this);
	    try {
	    	File bgmf = new File(/*"sdly.ogg");//*/"sdly.wav");
	        AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(bgmf);
	        Clip clip = AudioSystem.getClip();
	        this.clip = clip;
	        this.clip.open(audioInputStream);
	        this.clip.loop(Clip.LOOP_CONTINUOUSLY);
	        //Thread.sleep(10000);
	        this.clip.start();
	    } catch(Exception ex) {
	        //System.out.println("Error with playing sound.");
	        //ex.printStackTrace();
	    }
	}
	
	public enum STATE{
		MENU,
		CREDITS,
		PLAY
	};
	
	public static STATE State = STATE.MENU;
	
	
	private synchronized void start(){
		if(running)
			return;
		running = true;
		thread = new Thread(this);
		thread.start();
	}
	
	private synchronized void stop(){
		if(!running)
			return;
		running = false;
		try {
		thread.join();
		} catch(InterruptedException e){
			//e.printStackTrace();
		}
		System.exit(1);
	}
	public void run(){
		init();
		long lastTime = System.nanoTime();
		final double amountOfTicks = 60.0;
		double ns = 1000000000/amountOfTicks;
		double delta = 0;
		//int updates = 0;
		//int frames = 0;
		long timer = System.currentTimeMillis();
		
		while(running){
			//this would be the game loop
			long now = System.nanoTime();
			delta += (now - lastTime) / ns;
			lastTime = now;
			if(delta >=1){
				System.out.println("ticking");
				tick();
				//System.out.println("tock");
				//updates++;
				//delta--;
			}
			//System.out.println("Start Render");
			render();
			System.out.println("Stop Render");
			//frames++;
			
			if(System.currentTimeMillis() - timer > 1000){
				timer += 1000;
				//System.out.println(updates + "Ticks, FPS " + frames);
				//updates = 0;
				//frames = 0;
			}
			System.out.println(running);
		}
		System.out.println("STAHP!");
		stop();
	}
	
	private void tick(){
		//bg4, pos[0], pos[4]
		//bg3, pos[1], pos[5]
		//bg2, pos[2], pos[6]
		//background, pos[3], pos[7]
		//bg4, pos[8], pos[12]
				//bg3, pos[9], pos[13]
				//bg2, pos[10], pos[14]
				//background, pos[11], pos[15]
		if(tickcount%30==0){
			pos[3]--;
			pos[11]--;
		}
		if(tickcount%60==0){
			pos[2]--;
			pos[10]--;
			pos[1]--;
			pos[9]--;
			pos[0]--;
			pos[8]--;
		}
		for(int q=0;q<11;q++){
			if(pos[q]==4)
				q=8;
			if(pos[q]<(-imgsize)){//assuming all images the same size
				pos[q]=imgsize;
			}
		}
		tickcount++;
		if(tickcount>60){
			//tickcount = 0;
			for(int i = 0; i < pos.length;i++)
				System.out.print("|"+pos[i]+"|");
			System.out.println(tickcount);
		}
		//System.out.println(tickcount);
	}
	
	private void render(){
		BufferStrategy bs = this.getBufferStrategy();
		if (bs == null){
			createBufferStrategy(3);
			return;
		}
		Graphics g = bs.getDrawGraphics();
		Graphics2D g2d = (Graphics2D) g;
		g.setColor(Color.BLACK);
		g2d.draw(clear);
		g2d.fill(clear);
		///////////////////
		//drawImage(Image img, int x, int y, ImageObserver observer)
		g.drawImage(image, 0, 0, getWidth(), getHeight(), this);
		//We control the vertical and the horizontal
		g.drawImage(bg4, pos[0], pos[4], null);
		g.drawImage(bg3, pos[1], pos[5], null);
		g.drawImage(bg2, pos[2], pos[6], null);
		g.drawImage(background, pos[3], pos[7], null);
		g.drawImage(bg42, pos[8], pos[4], null);
		g.drawImage(bg32, pos[9], pos[5], null);
		g.drawImage(bg22, pos[10], pos[6], null);
		g.drawImage(background2, pos[11], pos[7], null);
		//////////////////
		if(State == STATE.MENU){
			menu.render(g,mitem);
		}else if(State == STATE.PLAY){
			play.render(g,mitem);
		}else if(State == STATE.CREDITS){
			cred.render(g,mitem);
		}
		g.dispose();
		bs.show();
	}
	
	public int intmerge(int[] array){
		int fS = 0;
		for (int i = 0; i < array.length; i++)
			fS += array[i] * Math.pow(10, array.length-i-1);
		return fS;
	}
	
	public int key2int(int k){
		int key = k;
		if(key == KeyEvent.VK_0)
			return 0;
		if(key == KeyEvent.VK_1)
			return 1;
		if(key == KeyEvent.VK_2)
			return 2;
		if(key == KeyEvent.VK_3)
			return 3;
		if(key == KeyEvent.VK_4)
			return 4;
		if(key == KeyEvent.VK_5)
			return 5;
		if(key == KeyEvent.VK_6)
			return 6;
		if(key == KeyEvent.VK_7)
			return 7;
		if(key == KeyEvent.VK_8)
			return 8;
		if(key == KeyEvent.VK_9)
			return 9;
		return 0;
	}
	
	public void keyPressed(KeyEvent e){
		int key = e.getKeyCode();
		
		if(State == STATE.MENU){
			if(key == KeyEvent.VK_UP){
				mitem -= 1;
				if(mitem<1)
					mitem = 3;
			} else if(key == KeyEvent.VK_DOWN){
				mitem += 1;
				if(mitem>3)
					mitem = 1;
			} else if(key == KeyEvent.VK_ENTER ||
					key == KeyEvent.VK_CONTROL||
					key == KeyEvent.VK_SPACE){
				if(mitem == 1)
					State = STATE.PLAY;//
				else if(mitem == 2)
					State = STATE.CREDITS;
				else if(mitem == 3)
					System.exit(1);//this.quitGAME();
			}
		}else if(State == STATE.PLAY){
			if(key == KeyEvent.VK_UP){
				mitem -= 1;
				if(mitem<1)
					mitem = 14;
			} else if(key == KeyEvent.VK_DOWN){
				mitem += 1;
				if(mitem>14)
					mitem = 1;
			} else if(mitem >= 4 && mitem <=8
					||key == KeyEvent.VK_0
					||key == KeyEvent.VK_1
					||key == KeyEvent.VK_2
					||key == KeyEvent.VK_3
					||key == KeyEvent.VK_4
					||key == KeyEvent.VK_5
					||key == KeyEvent.VK_6
					||key == KeyEvent.VK_7
					||key == KeyEvent.VK_8
					||key == KeyEvent.VK_9){
				switch(mitem){
				case 4://port
					portnum[tiscounter] = key2int(key);
					tiscounter++;
					if(tiscounter>=4){
						mitem++;
						tiscounter=0;
						port = Integer.toString(intmerge(portnum));
					}
					break;
				case 5://addr 1
					addr1[tiscounter] = key2int(key);
					tiscounter++;
					if(tiscounter>=3){
						mitem++;
						tiscounter=0;
						sadr1 = Integer.toString(intmerge(addr1));
					}
					break;
				case 6://addr 2
					addr2[tiscounter] = key2int(key);
					tiscounter++;
					if(tiscounter>=3){
						mitem++;
						tiscounter=0;
						sadr2 = Integer.toString(intmerge(addr2));
					}
					break;
				case 7://addr 3
					addr3[tiscounter] = key2int(key);
					tiscounter++;
					if(tiscounter>=3){
						mitem++;
						tiscounter=0;
						sadr3 = Integer.toString(intmerge(addr3));
					}
					break;
				case 8://addr 4
					addr4[tiscounter] = key2int(key);
					tiscounter++;
					if(tiscounter>=3){
						mitem++;
						tiscounter=0;
						sadr4 = Integer.toString(intmerge(addr4));
					}
					break;
				}
			}else if(key == KeyEvent.VK_ENTER ||
					key == KeyEvent.VK_CONTROL||
					key == KeyEvent.VK_SPACE){
				switch(mitem){
				case 1:
					State = STATE.MENU;
					break;
				case 2:
					host = true;
					break;
				case 3:
					host = false;
					break;
				case 4:
					port = Integer.toString(intmerge(portnum));
					break;
				case 5:
					sadr1 = Integer.toString(intmerge(addr1));
					sadr2 = Integer.toString(intmerge(addr2));
					sadr3 = Integer.toString(intmerge(addr3));
					sadr4 = Integer.toString(intmerge(addr4));
					addr = sadr1+"."+sadr2+"."+sadr3+"."+sadr4;
					break;
				case 6:
					sadr1 = Integer.toString(intmerge(addr1));
					sadr2 = Integer.toString(intmerge(addr2));
					sadr3 = Integer.toString(intmerge(addr3));
					sadr4 = Integer.toString(intmerge(addr4));
					addr = sadr1+"."+sadr2+"."+sadr3+"."+sadr4;
					break;
				case 7:
					sadr1 = Integer.toString(intmerge(addr1));
					sadr2 = Integer.toString(intmerge(addr2));
					sadr3 = Integer.toString(intmerge(addr3));
					sadr4 = Integer.toString(intmerge(addr4));
					addr = sadr1+"."+sadr2+"."+sadr3+"."+sadr4;
					break;
				case 8:
					sadr1 = Integer.toString(intmerge(addr1));
					sadr2 = Integer.toString(intmerge(addr2));
					sadr3 = Integer.toString(intmerge(addr3));
					sadr4 = Integer.toString(intmerge(addr4));
					addr = sadr1+"."+sadr2+"."+sadr3+"."+sadr4;
					break;
				case 9:
					color = "RED";
					break;
				case 10:
					color = "BLUE";
					break;
				case 11:
					color = "GREEN";
					break;
				case 12:
					color = "YELLOW";
					break;
				case 13:
					color = "ORANGE";
					break;
				case 14:
					port = Integer.toString(intmerge(portnum));
					sadr1 = Integer.toString(intmerge(addr1));
					sadr2 = Integer.toString(intmerge(addr2));
					sadr3 = Integer.toString(intmerge(addr3));
					sadr4 = Integer.toString(intmerge(addr4));
					addr = sadr1+"."+sadr2+"."+sadr3+"."+sadr4;
					this.openGAME(port,addr,color);
					break;
				}
			}
		}else if(State == STATE.CREDITS){
			if(key == KeyEvent.VK_UP||key == KeyEvent.VK_DOWN){
				if(mitem==0)
					mitem = 1;
				else
					mitem = 0;
			} else if(key == KeyEvent.VK_ENTER ||
					key == KeyEvent.VK_CONTROL||
					key == KeyEvent.VK_SPACE){
				if(mitem == 1)
					State = STATE.MENU;
			}
		}
	}
	
	public void keyReleased(KeyEvent e){
		//int key = e.getKeyCode();
	}
	
	
	
	public static void main(String args[]){
		Game game = new Game();
		
		game.setPreferredSize(new Dimension(WIDTH * SCALE, HEIGHT * SCALE));
		game.setMaximumSize(new Dimension(WIDTH * SCALE, HEIGHT * SCALE));
		game.setMinimumSize(new Dimension(WIDTH * SCALE, HEIGHT * SCALE));
	
		JFrame frame = new JFrame(game.TITLE);
		frame.add(game);
		//frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
		
		game.start();
	}
	
	public BufferedImage getSpriteSheet(){
		return null;//spriteSheet;
	}
	public void openGAME(String port, String addr, String color) {
		try
		{
		//Runtime rt = Runtime.getRuntime();
		//Process p = rt.exec("C:\\Windows\\System32\\notepad.exe");
		//Process p = Runtime.getRuntime().exec(new String[] {"./se800", "server", "6667"});
		//Process q = Runtime.getRuntime().exec(new String[] {"./se800", "client", "6667", "127.0.0.1"});
			
			String[] cserv = {"./se800","server", port};
			String[] cclie = {"./se800","client", port, addr, color};
			//String[] test = {"C:\\Windows\\System32\\notepad.exe","k1"};
			if(this.host == true){
				for(int w = 0; w < cserv.length;w++)
					System.out.println(cserv[w]);
				@SuppressWarnings("unused")
				Process p = new ProcessBuilder(cserv).redirectError(Redirect.INHERIT).redirectOutput(Redirect.INHERIT).start();
			}
			
			for(int r = 0; r < cclie.length;r++)
				System.out.println(cclie[r]);
			Process q = new ProcessBuilder(cclie).redirectError(Redirect.INHERIT).redirectOutput(Redirect.INHERIT).start();
			q.wait(1);//force client to wait

		}
		catch(Exception e)
		{
			//e.printStackTrace();
		}
	}
}

