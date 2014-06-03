package com.game.src.main;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.lang.ProcessBuilder.Redirect;

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
	public int mitem = 1;
	
	private boolean running = false;
	private Thread thread;
	
	private BufferedImage image = new BufferedImage(WIDTH,HEIGHT,BufferedImage.TYPE_INT_ARGB);
	private BufferedImage background = null;
	private BufferedImage bg2 = null;
	private BufferedImage bg3 = null;
	private BufferedImage bg4 = null;
	
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
		}catch(IOException e){
			//e.printStackTrace();
		}
		this.addKeyListener(new KeyInput(this));
		this.addMouseListener(new MouseInput(this));
		menu = new Menu();
		cred = new Cred();
		play = new Play();
	    try {
	    	File bgmf = new File("sdly.wav");
	        AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(bgmf);
	        Clip clip = AudioSystem.getClip();
	        clip.open(audioInputStream);
	        clip.start();
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
				tick();
				//updates++;
				//delta--;
			}
			render();
			//frames++;
			
			if(System.currentTimeMillis() - timer > 1000){
				timer += 1000;
				//System.out.println(updates + "Ticks, FPS " + frames);
				//updates = 0;
				//frames = 0;
			}
		}
		stop();
	}
	
	private void tick(){
		/*(State == STATE.GAME){
			p.tick();
		}*/
	}
	
	private void render(){
		BufferStrategy bs = this.getBufferStrategy();
		if (bs == null){
			createBufferStrategy(3);
			return;
		}
		Graphics g = bs.getDrawGraphics();
		///////////////////
		g.drawImage(image, 0, 0, getWidth(), getHeight(), this);
		
		g.drawImage(bg4, 0, 0, null);
		g.drawImage(bg3, 0, 0, null);
		g.drawImage(bg2, 0, 0, null);
		g.drawImage(background, 0, 0, null);
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
					this.openGAME("8000","127.0.0.1","BLUE");
				else if(mitem == 2)
					State = STATE.CREDITS;
				else if(mitem == 3)
					System.exit(1);//this.quitGAME();
			}
		}else if(State == STATE.PLAY){
			
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
			String[] cserv = {"./se800","server", "6667"};
			String[] cclie = {"./se800","client", port, addr, color};
			//String[] test = {"C:\\Windows\\System32\\notepad.exe","k1"};
			Process p = new ProcessBuilder(cserv).redirectError(Redirect.INHERIT).redirectOutput(Redirect.INHERIT).start();
			Process q = new ProcessBuilder(cclie).redirectError(Redirect.INHERIT).redirectOutput(Redirect.INHERIT).start();
			p.waitFor();
			q.waitFor();

		}
		catch(Exception e)
		{
			//e.printStackTrace();
		}
	}
}

